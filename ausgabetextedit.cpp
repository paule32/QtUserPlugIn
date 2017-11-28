#include <QWidget>
#include <QScrollArea>
#include <QKeyEvent>
#include "ausgabetextedit.h"

AusgabeTextEdit::AusgabeTextEdit(QWidget *parent)
    : QScrollArea(parent)
{
    move(5,5);
    resize(1024, 70);
    setObjectName("ausgabeTextEdit");
}

AusgabeTextEdit::~AusgabeTextEdit()
{
}

void AusgabeTextEdit::keyPressEvent(QKeyEvent *e)
{
    QWidget::keyPressEvent(e);
    /*
    if ((e->key() >= Qt::Key_0)
    &&  (e->key() <= Qt::Key_9)) {
         e->accept();
         document()->setHtml(
         document()->toPlainText() + e->key());
    }*/
}
