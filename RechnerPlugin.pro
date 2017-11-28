CONFIG      += plugin debug
TARGET      = rechnerplugin
TEMPLATE    = lib

HEADERS     = \
    rechner.h \
    rechnerplugin.h \
    rechnertaskmenufactory.h \
    rechnertaskmenu.h \
    rechnerdialog.h \
    rechnerpropertypage.h \
    matheconsole.h \
    syntax.h \
    ausgabetextedit.h \
    wurzelbox.h

SOURCES     = \
    rechner.cpp \
    rechnerplugin.cpp \
    rechnertaskmenufactory.cpp \
    rechnertaskmenu.cpp \
    rechnerdialog.cpp \
    rechnerpropertypage.cpp \
    matheconsole.cpp \
    syntax.cpp \
    ausgabetextedit.cpp \
    wurzelbox.cpp

INCLUDEPATH    += /home/jens/Projekte/RechnerPlugin
INCLUDEPATH    += /home/jens/qtcreator-4.4.1/qt-creator/src/plugins

OBJECTS_DIR = ./.objs
MOC_DIR     = ./.mocs
DESTDIR     = ../rechnerTest/bin
UI_DIR      = ./.ui

LIBS += \
    -L/usr/local/lib \
    -L/home/jens/Qt5.10/Tools/QtCreator/lib/Qt/plugins/designer \
    -L/home/jens/qtcreator-4.4.1/lib/qtcreator/plugins \
    -L/home/jens/qtcreator-4.4.1/lib/qtcreator \
    -lrechnerplugin \
    -lCore \
    -lAggregation \
    -lExtensionSystem \
    -lUtils \
    -lgmp \
    -lstdc++

QT += designer widgets core

FORMS += \
    form.ui \
    rechnerpropertypage.ui \
    form.ui

RESOURCES += \
    resources.qrc


