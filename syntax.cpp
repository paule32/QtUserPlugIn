#include "syntax.h"

#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_ACTIONS_ALLOW_ATTR_COMPAT

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <set>
#include <utility>
#include <vector>

#include <QMessageBox>

using namespace std;
using namespace boost::spirit;

namespace bs    = boost::spirit;
namespace phx   = boost::phoenix;
namespace ascii = boost::spirit::ascii;

using boost::spirit::ascii::space; // use the ASCII space parser
using boost::spirit::ascii::char_;
using boost::spirit::_val;

using boost::phoenix::val;

namespace rechnerParser
{
    // -------------------
    // AST for rechner ...
    // -------------------
    struct binary_op;
    struct unary_op;
    struct nil { };

    struct expression_ast
    {
        typedef
        boost::variant<
              nil
            , int
            , std::string
            , boost::recursive_wrapper<expression_ast>
            , boost::recursive_wrapper<binary_op>
            , boost::recursive_wrapper<unary_op>
        >
        type;
        type expr;

        template <typename Expr>
        expression_ast(Expr const & expr)
            : expr(expr) {  }

        expression_ast() {}
        expression_ast& operator += (expression_ast const & rhs);
        expression_ast& operator -= (expression_ast const & rhs);
        expression_ast& operator *= (expression_ast const & rhs);
        expression_ast& operator /= (expression_ast const & rhs);
    };

    expression_ast dast;

    struct binary_op
    {
        binary_op(
              char op
            , expression_ast const & left
            , expression_ast const & right)
            : op(op)
            , left(left)
            , right(right)
        {
            std::cout << "Math2: " << std::endl;
        }

        char op;
        expression_ast left;
        expression_ast right;
    };
    struct unary_op
    {
        unary_op(
            char op
          , expression_ast const& subject)
        : op(op), subject(subject) {}

        char op;
        expression_ast subject;
    };

    expression_ast& expression_ast::operator += (expression_ast const& rhs)
    {
        expr = binary_op('+', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator -= (expression_ast const& rhs)
    {
        expr = binary_op('-', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator *= (expression_ast const& rhs)
    {
        expr = binary_op('*', expr, rhs);
        return *this;
    }

    expression_ast& expression_ast::operator /= (expression_ast const& rhs)
    {
        expr = binary_op('/', expr, rhs);
        return *this;
    }

    // We should be using expression_ast::operator-. There's a bug
    // in phoenix type deduction mechanism that prevents us from
    // doing so. Phoenix will be switching to BOOST_TYPEOF. In the
    // meantime, we will use a phoenix::function below:
    struct negate_expr
    {
        template <typename T>
        struct result { typedef T type; };

        expression_ast operator()(expression_ast & expr) const
        {
            cout << "lllllllllllllllll\n";
            return expression_ast(unary_op('-', expr));
        }
    };

    phx::function<negate_expr> neg;

    // -----------------------
    // walk throug the AST ...
    // -----------------------
    struct ast_print
    {
        typedef void result_type;

        void operator()(struct nil nop) const
        {
            cout << "nop" << endl;
        }
        void operator()(int const value) const
        {
            cout << "const int = " << value << endl;
            dast = value;
            cout << dast.expr.type().name() << endl;
        }

        void operator()(const std::string st) const
        {
            cout << "const std::string = " << st << endl;
        }

        void operator()(expression_ast const& ast) const
        {
            //if (!(ast.expr.type().name() == std::string("N11dBaseParser3nilE")))
            boost::apply_visitor(*this, ast.expr);
        }

        void operator()(binary_op const& expr) const
        {
            std::cout << "op:" << expr.op << "(";
            boost::apply_visitor(*this, expr.left.expr);
            std::cout << ", ";
            boost::apply_visitor(*this, expr.right.expr);
            std::cout << ')';
        }

        void operator()(unary_op const& expr) const
        {
            std::cout << "op:" << expr.op << "(";
            boost::apply_visitor(*this, expr.subject.expr);
            std::cout << ')';
        }
    };

    template <typename Lexer>
    struct rechner_token : lex::lexer<Lexer>
    {
        // ----------------------------
        // tokens with no attributes...
        // ----------------------------
        lex::token_def<lex::omit> whitespace;
        lex::token_def<lex::omit> cpcomment;
        lex::token_def<lex::omit> d_comment;
        lex::token_def<lex::omit> c_comment;

        // --------------------------
        // tokens with attributes ...
        // --------------------------
        lex::token_def<int>         number_digit;
        lex::token_def<std::string> identifier;
        lex::token_def<std::string> quoted_string;

        rechner_token()
        {
            // Values.
            number_digit      = "[0-9]*";
            quoted_string     = "\\\"(\\\\.|[^\\\"])*\\\"";

            // Identifier.
            identifier        = "[a-zA-Z][a-zA-Z0-9_]*";

            cpcomment = "\\/\\/[^\\n]*\\n";                    // single line comment
            d_comment = "\\*\\*[^\\n]*\\n";                    // dBase  line comment
            c_comment = "\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/"; // c-style comments

            whitespace = "[ \\t\\n]+";

            this->self += lex::token_def<>
                ('(') | ')'
                | '+' | '-'
                | '*' | '/'
                | ',' | '.';

            this->self +=
                  identifier
                | number_digit
                | quoted_string
                ;

            this->self +=
                  whitespace [ lex::_pass = lex::pass_flags::pass_ignore ]
                | cpcomment
                | c_comment
                | d_comment
                ;
        }
    };

    template <typename Iterator, typename Lexer>
    struct rechner_grammar
    :   public qi::grammar<Iterator>
    {   template <typename TokenDef>

        rechner_grammar(TokenDef const& tok) :
        rechner_grammar::base_type(start, "start")
        {
            using qi::_val;

            start
                = *symsbols
                ;

            expression =
                term                            [ _val  = qi::_1 ]
                >> *(   ('+' >> term            [ _val += qi::_1 ])
                    |   ('-' >> term            [ _val -= qi::_1 ])
                    )
                ;

            term =
                factor                          [ _val  = qi::_1]
                >> *(   ('*' >> factor          [ _val *= qi::_1])
                    |   ('/' >> factor          [ _val /= qi::_1])
                    )
                ;

            factor =
                tok.number_digit                [ _val = qi::_1 ]
                |  '('   >> expression          [ _val = qi::_1 ] >> ')'
                |   ('-' >> factor              [ _val = neg(qi::_1)])
                |   ('+' >> factor              [ _val = qi::_1 ] )
                ;

            symsbols
                = printLn
                | comments
                ;

            comments
                = tok.cpcomment
                | tok.c_comment
                | tok.d_comment
                ;

            symsbols
                = expression
                ;

            start.name("start");
            symsbols.name("symsbols");
            comments.name("comments");
            expression.name("expression");
            term.name("term");
            factor.name("factor");
        }

        typedef qi::unused_type skipper_type;
        typedef qi::rule<Iterator, skipper_type> simple_rule;

        simple_rule start, symsbols, comments, printLn;

        qi::rule<Iterator, expression_ast()>
        expression, term, factor;
    };
}

bool mathParser(char *text)
{
    using rechnerParser::expression_ast;
    using rechnerParser::ast_print;

    std::string data(text);
    if (data.size() < 1) {
        QMessageBox::warning(0,"Error","No Data for parser.\nABORT.");
        return false;
    }

    typedef std::string::iterator base_iterator_type;
    typedef lex::lexertl::token<
        base_iterator_type, boost::mpl::vector<char, int, std::size_t, std::string>
    > token_type;
    typedef lex::lexertl::actor_lexer<token_type> lexer_type;

    typedef rechnerParser::rechner_token<lexer_type> rechner_token;
    typedef rechner_token::iterator_type iterator_type;
    typedef rechnerParser::rechner_grammar<iterator_type, rechner_token::lexer_def> rechner_grammar;

    rechner_token   token;
    rechner_grammar rechner(token);

    base_iterator_type it = data .begin();
    iterator_type iter    = token.begin(it, data.end());
    iterator_type end     = token.end();

    expression_ast ast;
    bool r = qi::parse(iter, end, rechner, ast);

    rechnerParser::ast_print  printer;
    if (r == true) {
        QMessageBox::information(0,"math parser","SUCCESS");
        //printer(rechnerParser::dast);
        return true;
    }   else {
        QMessageBox::information(0,"math parser","ERROR");
        return false;
    }   return false;
}
