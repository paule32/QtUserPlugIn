#include <QObject>
#include <QDialog>
#include <QWidget>
#include <QSize>
#include <QTableWidget>

#include "rechnerdialog.h"
#include "rechner.h"

RechnerDialog::RechnerDialog(Rechner *plugin, QWidget *parent)
    : QDialog(parent)
{
    rechner = plugin;
    editor  = new Rechner;

    QTableWidget *tableWidget;

    tableWidget = new QTableWidget(plugin);
    tableWidget->setObjectName(QStringLiteral("tableWidget"));
    tableWidget->setGeometry(QRect(40, 150,100,100));
}

QSize RechnerDialog::sizeHint() const
{
    return QSize(500,509);
}
