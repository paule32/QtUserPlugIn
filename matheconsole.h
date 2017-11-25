#ifndef MATHECONSOLE_H
#define MATHECONSOLE_H

#include <QObject>
#include <QWidget>
#include <QProcess>

class MatheConsole
{
public:
    MatheConsole();

public slots:
   void go();
   void ready();
   void finish();

private:
     QProcess prc;
};

#endif // MATHECONSOLE_H
