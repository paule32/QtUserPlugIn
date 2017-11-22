#include "rechnertaskmenu.h"
#include "rechnertaskmenufactory.h"
#include "rechner.h"

RechnerTaskMenuFactory::RechnerTaskMenuFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{
}

QObject *
RechnerTaskMenuFactory::createExtension(
    QObject *object,
    const QString &iid,
    QObject *parent) const
{
    if (iid != Q_TYPEID(QDesignerTaskMenuExtension))
    return 0;

    if (Rechner * calc = qobject_cast<Rechner*>(object))
    return new RechnerTaskMenu(calc, parent);

    return 0;
}
