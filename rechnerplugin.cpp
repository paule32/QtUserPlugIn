#include "rechnerplugin.h"
#include "rechnertaskmenufactory.h"
#include "rechner.h"

#include <QtPlugin>

RechnerPlugin::RechnerPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void RechnerPlugin::initialize(QDesignerFormEditorInterface * formEditor)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    QExtensionManager * manager = formEditor->extensionManager();
    Q_ASSERT(manager != 0);

    manager->registerExtensions(
        new RechnerTaskMenuFactory(manager),
        Q_TYPEID(QDesignerTaskMenuExtension));

    m_initialized = true;
}

bool RechnerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RechnerPlugin::createWidget(QWidget *parent)
{
    Rechner *panel = new Rechner(parent);
    return   panel;
}

QString RechnerPlugin::name() const
{
    return QLatin1String("Rechner");
}

QString RechnerPlugin::group() const
{
    return QLatin1String("KALLUP * NET");
}

QIcon RechnerPlugin::icon() const
{
    return QIcon(":/pics/icon.png");
}

QString RechnerPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RechnerPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RechnerPlugin::isContainer() const
{
    return false;
}

QString RechnerPlugin::domXml() const
{
    return QLatin1String("\
    <ui language=\"c++\">\
        <widget class=\"Rechner\" name=\"rechner\"/>\
        <customwidgets>\
            <customwidget>\
                <class>Rechner</class>\
                <propertyspecifications>\
                <stringpropertyspecification name=\"state\" notr=\"true\" type=\"singleline\"/>\
                </propertyspecifications>\
            </customwidget>\
        </customwidgets>}\
    </ui>");
}

QString RechnerPlugin::includeFile() const
{
    return QLatin1String("rechner.h");
}

