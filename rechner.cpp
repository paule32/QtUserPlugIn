#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QComboBox>
#include <QPalette>
#include <QPushButton>
#include <QLayout>
#include <QHBoxLayout>
#include <QGridLayout>

#include <coreplugin/coreconstants.h>
#include <coreplugin/modemanager.h>

#include "rechner.h"

#include <gmp.h>
#include <gmpxx.h>

#define ZAHLEN_E     12
#define OPERATOREN_E  1

const char fontName[] = "Arial";

struct elements element[44] = {
    // Zahlen
    { 0, 0, 1, 1, "1",          fontName, nullptr, nullptr, nullptr },
    { 0, 1, 1, 1, "2",          fontName, nullptr, nullptr, nullptr },
    { 0, 2, 1, 1, "3",          fontName, nullptr, nullptr, nullptr },
    { 1, 0, 1, 1, "4",          fontName, nullptr, nullptr, nullptr },
    { 1, 1, 1, 1, "5",          fontName, nullptr, nullptr, nullptr },
    { 1, 2, 1, 1, "6",          fontName, nullptr, nullptr, nullptr },
    { 2, 0, 1, 1, "7",          fontName, nullptr, nullptr, nullptr },
    { 2, 1, 1, 1, "8",          fontName, nullptr, nullptr, nullptr },
    { 2, 2, 1, 1, "9",          fontName, nullptr, nullptr, nullptr },
    { 3, 0, 1, 1, "0",          fontName, nullptr, nullptr, nullptr },
    { 3, 2, 1, 1, ",",          fontName, nullptr, nullptr, nullptr },
    { 3, 1, 1, 1, "=",          fontName, nullptr, nullptr, nullptr },

    // Operator
    { 0, 0, 1, 1, "+",          fontName, nullptr, nullptr, nullptr },
    { 0, 1, 1, 1, "-",          fontName, nullptr, nullptr, nullptr },
    { 0, 2, 1, 1, "*",          fontName, nullptr, nullptr, nullptr },
    { 0, 3, 1, 1, "/",          fontName, nullptr, nullptr, nullptr },

    { 7, 0, 1, 1, "Prozent",    fontName, nullptr, nullptr, nullptr },
    { 7, 1, 1, 1, "Promille",   fontName, nullptr, nullptr, nullptr },

    { 2, 1, 1, 1, "Wurzel^2",   fontName, nullptr, nullptr, nullptr },
    { 2, 2, 1, 1, "Wurzel^n",   fontName, nullptr, nullptr, nullptr },

    { 3, 1, 1, 1, "x^2",        fontName, nullptr, nullptr, nullptr },
    { 4, 1, 1, 1, "x^y",        fontName, nullptr, nullptr, nullptr },

    { 1, 1, 1, 1, "modulo",     fontName, nullptr, nullptr, nullptr },

    { 1, 0, 1, 1, "sin",        fontName, nullptr, nullptr, nullptr },
    { 2, 0, 1, 1, "cos",        fontName, nullptr, nullptr, nullptr },
    { 3, 0, 1, 1, "tan",        fontName, nullptr, nullptr, nullptr },

    { 5, 0, 1, 1, "Pi",         fontName, nullptr, nullptr, nullptr },

    { 3, 3, 1, 1, "(",          fontName, nullptr, nullptr, nullptr },
    { 3, 4, 1, 1, ")",          fontName, nullptr, nullptr, nullptr },

    { 2, 3, 1, 1, "n!",         fontName, nullptr, nullptr, nullptr },
    { 2, 4, 1, 1, "log",        fontName, nullptr, nullptr, nullptr },

    { 1, 3, 1, 1, "e",          fontName, nullptr, nullptr, nullptr },
    { 1, 4, 1, 1, "ln",         fontName, nullptr, nullptr, nullptr },

    { 0, 6, 1, 1, "A",          fontName, nullptr, nullptr, nullptr },
    { 1, 6, 1, 1, "B",          fontName, nullptr, nullptr, nullptr },
    { 2, 6, 1, 1, "C",          fontName, nullptr, nullptr, nullptr },
    { 3, 6, 1, 1, "D",          fontName, nullptr, nullptr, nullptr },
    { 4, 6, 1, 1, "E",          fontName, nullptr, nullptr, nullptr },
    { 5, 6, 1, 1, "F",          fontName, nullptr, nullptr, nullptr },

    { 6, 5, 1, 1, "dez",        fontName, nullptr, nullptr, nullptr },
    { 6, 6, 1, 1, "bin",        fontName, nullptr, nullptr, nullptr },
    { 6, 7, 1, 1, "hex",        fontName, nullptr, nullptr, nullptr },

    { 12, 0, 1, 1, "DEL",       fontName, nullptr, nullptr, nullptr },
    { 12, 1, 1, 1, "AC",        fontName, nullptr, nullptr, nullptr }
};

void Rechner::AddNumPadElement(struct elements pad)
{
    QPushButton *btn = new QPushButton(pad.name,pad.parent);

    btn->sizePolicy().setHeightForWidth(
    btn->sizePolicy().hasHeightForWidth());
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(btn, SIGNAL(clicked()), this, SLOT(btnOnClicked()));

    int fontsize = 0;
    if (btn->text() == "modulo"
    ||  btn->text() == "Wurzel^2" || btn->text() == "Prozent"
    ||  btn->text() == "Wurzel^n" || btn->text() == "Promille")
    fontsize = 12; else
    fontsize = 18;

    QFont f;
    f.setBold(true);
    f.setPointSize(fontsize);
    f.setWeight(70);
    f.setFamily(pad.fontName);

    btn->setFont(f);

    pad.grid->addWidget(btn,
    pad.x1, pad.y1,
    pad.x2, pad.y2);
}

//Rechner::~Rechner() { }
Rechner::Rechner(QWidget *parent) : QWidget(parent)
{
    if (parent == nullptr) {
        QMessageBox::warning(0,"Warnung !!!","Plugin konnte nicht erstellt werden.");
        return;
    }

    first_input = false;
    parent = this;
    setMouseTracking(true);

    QVBoxLayout * mainLayout  = new QVBoxLayout(parent);
    QVBoxLayout * upperLayout = new QVBoxLayout;
    QHBoxLayout * lowerLayout = new QHBoxLayout;

    QPlainTextEdit  *
    ausgabeTextEdit = new QPlainTextEdit(parent);
    ausgabeTextEdit->move(5,5);
    ausgabeTextEdit->resize(1024, 70);

    ausgabeTextEdit->setFont(QFont("Arial",10));
    ausgabeTextEdit->setPlainText("Bitte Eingabe machen");
    ausgabeTextEdit->setObjectName("ausgabeTextEdit");

    upperLayout->addWidget(ausgabeTextEdit);

    QVBoxLayout * nump = new QVBoxLayout;
    QHBoxLayout * stdopLayout = new QHBoxLayout;
    QGridLayout * numpadGridLayout = new QGridLayout;

    nump->addLayout(numpadGridLayout);
    nump->addLayout(stdopLayout);

    // Zahlen
    for (int i = 0; i < 12; i++) {
        element[i].parent = parent;
        element[i].grid   = numpadGridLayout;
        AddNumPadElement(element[i]);
    }

    QWidget * stdopWidget = new QWidget;
    stdopLayout->addWidget(stdopWidget);

    lowerLayout->addLayout(nump);

    QVBoxLayout * eingabeLayout = new QVBoxLayout;
    nump->addLayout(eingabeLayout);

    QPlainTextEdit *
    eingabeTextEdit = new QPlainTextEdit(parent);
    eingabeTextEdit->move(5,5);
    eingabeTextEdit->resize(1024, 70);
    eingabeTextEdit->setFont(QFont("Arial",10));

    eingabeLayout->addWidget(eingabeTextEdit);


    QHBoxLayout * TabserLayout = new QHBoxLayout;
    QTabWidget  * Tabser       = new QTabWidget;
    QWidget     * AllgemeinTab = new QWidget;
    QWidget     * ErweitertTab = new QWidget;

    Tabser->addTab(AllgemeinTab, "Allgemein");
    Tabser->addTab(ErweitertTab, "Erweitert");

    // operatoren
    QGridLayout * AllgemeinTabLayout = new QGridLayout(AllgemeinTab);
    for (int i = 0+12; i < 12+32; i++) {
        element[i].parent = AllgemeinTab;
        element[i].grid   = AllgemeinTabLayout;
        AddNumPadElement(element[i]);
    }

    QComboBox *comboBox = new QComboBox(AllgemeinTab);
    comboBox->addItem("f(x)");
    comboBox->addItem("Ganzzahliger Anteil");
    comboBox->addItem("Gebrochener Anteil");

    comboBox->addItem("Runden");
    comboBox->addItem("Abrunden");
    comboBox->addItem("Aufrunden");
    comboBox->setCurrentText("f(x)");

    QFont f;
    f.setBold(true);
    f.setPointSize(14);
    f.setWeight(70);
    f.setFamily(fontName);

    comboBox->setFont(f);
    AllgemeinTabLayout->addWidget(comboBox, 12, 3, 1, 3);

    TabserLayout->addWidget(Tabser);
    lowerLayout->addLayout(TabserLayout);

    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);
}

    //connect(ZahlButtonResult, SIGNAL(clicked()), this, SLOT(btnResultClicked()));
    //connect(ZahlButtonKomma, SIGNAL(clicked()), this, SLOT(btnKommaClicked()));

void Rechner::btnKommaClicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += ".";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btnResultClicked()
{
    char buffer[100];

    mpf_t x, y, z;

    mpf_init2(x,6);
    mpf_init2(y,6);
    mpf_init2(z,6);

    mpf_set_d(x,100.220);
    mpf_set_d(y,200.010);

    mpf_add(z,x,y);

    gmp_sprintf(buffer,"==> %F.f", z);
    plainTextEdit->document()->setPlainText(buffer);

    mpf_clear(x);
    mpf_clear(y);
    mpf_clear(z);
}

void Rechner::btnOnClicked()
{
    QString arg;

    QPlainTextEdit *ptr = parentWidget()->findChildren("ausgabeTextEdit");
    QPushButton    *btn;

    QString sbtn = btn->property("clickname").toString();

    if (!first_input) {
    first_input = true;
    ptr->document()->clear();}

    arg  = ptr->document()->toPlainText();
    arg += sbtn;
    ptr->document()->setPlainText(arg);
}
