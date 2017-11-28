#ifndef MATHECONSOLE_H
#define MATHECONSOLE_H

#include <QObject>
#include <QWidget>

#include "ausgabetextedit.h"

class MatheConsole
{
public:
    MatheConsole();
    MatheConsole(QWidget *prev = 0);

    bool calc(void);

    void   setBuffer(char *);
    char * result() const { return buffer; }

private:
    char * buffer;
    QWidget * parent;
    AusgabeTextEdit * output;
};

#endif // MATHECONSOLE_H
