#ifndef RECHNERTASKMENUFACTORY_H
#define RECHNERTASKMENUFACTORY_H

#include <QObject>
#include <QString>

#include <QExtensionManager>
#include <QExtensionFactory>

class RechnerTaskMenuFactory : public QExtensionFactory
{
    Q_OBJECT
public:
    RechnerTaskMenuFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

#endif // RECHNERTASKMENUFACTORY_H
