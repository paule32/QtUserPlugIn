#ifndef RECHNERDIALOG_H
#define RECHNERDIALOG_H

#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QSize>

#include "rechner.h"

class RechnerDialog : public QDialog
{
public:
    explicit RechnerDialog(Rechner *plugin = 0, QWidget *parent = 0);

    QSize sizeHint() const;

private:
    Rechner * editor;
    Rechner * rechner;
};

#endif // RECHNERDIALOG_H
