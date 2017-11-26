#ifndef RECHNER_H
#define RECHNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtCore/QPoint>
#include <QString>

#include <QPalette>

#include <QtDesigner/QtDesigner>
#include <QtWidgets/QWidget>

struct elements {
    int x1; int y1;
    int x2; int y2;
    QString name;
    QString fontName;
    QWidget *parent;
    QPushButton *btn;
    QGridLayout *grid;
};

class QDESIGNER_WIDGET_EXPORT Rechner: public QWidget
{
    Q_OBJECT
public:
    Rechner(QWidget *parent = 0);

public slots:
    void btnOnClicked();

public:
    void AddNumPadElement(struct elements pad);
    void btnResultClicked();

    bool first_input;
};

#endif
