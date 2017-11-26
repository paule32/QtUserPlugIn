#include <QObject>
#include <QAction>
#include <QList>
#include <QMessageBox>

#include "rechnertaskmenu.h"
#include "rechnerdialog.h"
#include "rechner.h"

#include "rechnerpropertypage.h"

RechnerTaskMenu::RechnerTaskMenu(
      Rechner *calc,
      QObject *parent)
    : QObject (parent)
{
    paintElement = nullptr;

    rechner = calc;
    editElementAction = new QAction("Edit PlugIn-Properties...", this);

    connect(editElementAction, &QAction::triggered,
    this, &RechnerTaskMenu::onClicked);
}

void RechnerTaskMenu::onClicked()
{
    /*
    if (qobject_cast<QPushButton*>(rechner->ZahlButton1)->underMouse() == true) {
        paintElement = rechner->ZahlButton1;
        QMessageBox::information(0,"qqqqq","1212212");
    }*/

    RechnerPropertyPage p(rechner);
    p.exec();
}

QAction *
RechnerTaskMenu::preferredEditAction() const
{
    return editElementAction;
}

QList<QAction *>
RechnerTaskMenu::taskActions() const
{
    QList<QAction *> list;
    list.append(editElementAction);
    return list;
}
