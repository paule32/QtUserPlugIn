CONFIG      += plugin debug
TARGET      = rechnerplugin
TEMPLATE    = lib

HEADERS     = \
    rechnerplugin.h \
    rechnertaskmenufactory.h \
    rechnertaskmenu.h \
    rechnerdialog.h \
    rechnerpropertypage.h

SOURCES     = \
    rechnerplugin.cpp \
    rechnertaskmenufactory.cpp \
    rechnertaskmenu.cpp \
    rechnerdialog.cpp \
    rechnerpropertypage.cpp
LIBS        += -L. 

QT += designer widgets

include(rechner.pri)

FORMS += \
    form.ui \
    rechnerpropertypage.ui

RESOURCES += \
    resources.qrc


