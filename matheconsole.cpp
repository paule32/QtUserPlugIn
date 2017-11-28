#include <stdio.h>
#include <strings.h>

#include <QWidget>
#include <QMessageBox>
#include <QStringList>

#include <gmp.h>
#include <gmpxx.h>

#include "matheconsole.h"

// parser ...
extern bool mathParser(char*);

MatheConsole::MatheConsole() {
    setBuffer((char*)"");
}
MatheConsole::MatheConsole(QWidget *prev) {
    output = prev->findChild<AusgabeTextEdit *>
    ("ausgabeTextEdit");
}

void MatheConsole::setBuffer(char *a)
{
    buffer = new char[strlen(a)];
    strcpy(buffer,a);
}
bool MatheConsole::calc(void)
{
    mpf_t x, y, z;

    mpf_init2(x,6);
    mpf_init2(y,6);
    mpf_init2(z,6);

    mpf_set_d(x,0.2);
    mpf_set_d(y,0.12);

    mpf_add(z,x,y);

    buffer = new char[200];
    gmp_sprintf(buffer,"%F.f", z);

    /*
    mpf_clear(x);
    mpf_clear(y);
    mpf_clear(z);*/

    QMessageBox::information(0,"math parser",buffer);

    bool r = mathParser(buffer);
    if  (r == false) {
        QMessageBox::warning(0,"math parser",
        "Ergebnis konnte nicht berechnet werden.");
    }

    return r;
}
