#ifndef RECHNERTASKMENU_H
#define RECHNERTASKMENU_H

#include <QObject>
#include <QList>
#include <QAction>
#include <QPaintEvent>

#include <QDesignerTaskMenuExtension>

#include "rechner.h"

class RechnerTaskMenu : public QObject, public QDesignerTaskMenuExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerTaskMenuExtension)

public:
    RechnerTaskMenu(Rechner *calc, QObject * parent = 0);

    QAction *preferredEditAction() const;
    QList<QAction *> taskActions() const;

private slots:
    void onClicked();

private:
    QAction * editElementAction;
    Rechner * rechner;

    QObject * paintElement;
};

#endif // RECHNERTASKMENU_H
