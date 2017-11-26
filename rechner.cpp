#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QPalette>
#include <QPushButton>
#include <QLayout>
#include <QGridLayout>

#include <coreplugin/coreconstants.h>
#include <coreplugin/modemanager.h>

#include "rechner.h"

#include <gmp.h>
#include <gmpxx.h>

struct elements element[12] = {
   { 0, 1, 2, 3, "1", nullptr, nullptr, nullptr },
   { 0, 1, 1, 1, "2", nullptr, nullptr, nullptr },
   { 0, 2, 1, 1, "3", nullptr, nullptr, nullptr },
   { 1, 0, 1, 1, "4", nullptr, nullptr, nullptr },
   { 1, 1, 1, 1, "5", nullptr, nullptr, nullptr },
   { 1, 2, 1, 1, "6", nullptr, nullptr, nullptr },
   { 2, 0, 1, 1, "7", nullptr, nullptr, nullptr },
   { 2, 1, 1, 1, "8", nullptr, nullptr, nullptr },
   { 2, 2, 1, 1, "9", nullptr, nullptr, nullptr },
   { 3, 0, 1, 1, "0", nullptr, nullptr, nullptr },
   { 3, 2, 1, 1, ",", nullptr, nullptr, nullptr },
   { 3, 1, 1, 1, "=", nullptr, nullptr, nullptr }
};

void Rechner::AddNumPadElement(struct elements *pad)
{
    QPushButton *btn = qobject_cast<QPushButton*>(pad->btn);

    btn->sizePolicy().setHeightForWidth(
    btn->sizePolicy().hasHeightForWidth());
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    QFont f;
    f.setBold(true);
    f.setPointSize(18);
    f.setWeight(75);
    f.setFamily("Arial");

    btn->setFont(f);

    pad->grid->addWidget(btn,
    pad->x1, pad->y1,
    pad->x2, pad->y2);
}

//Rechner::~Rechner() { }
Rechner::Rechner(QWidget *parent) : QWidget(parent)
{
    if (parent == nullptr) {
        QMessageBox::warning(0,"Warnung !!!","Plugin konnte nicht erstellt werden.");
        return;
    }

    first_input = false;
    parent = this;
    setMouseTracking(true);

    parent->resize(926, 632);

    QVBoxLayout * mainLayout  = new QVBoxLayout(parent);
    QVBoxLayout * upperLayout = new QVBoxLayout();
    QHBoxLayout * lowerLayout = new QHBoxLayout();

    QPlainTextEdit  *
    ausgabeTextEdit = new QPlainTextEdit(parent);
    ausgabeTextEdit->move(5,5);
    ausgabeTextEdit->resize(1024, 70);
    ausgabeTextEdit->setFont(QFont("Arial",10));

    upperLayout->addWidget(ausgabeTextEdit);


    numpadGridLayout = new QGridLayout();
    lowerLayout->addLayout(numpadGridLayout);

    for (int i = 0; i < 9; i++) {
        element[i].btn = new QPushButton(
        element[i].name, parent);
        element[i].parent = this;
        element[i].grid   = numpadGridLayout;
    }

#if 0
    numpadobj = new TPadObject;
    numpadobj->name   = "2";
    numpadobj->object = new QPushButton("2", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(0,1);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "3";
    numpadobj->object = new QPushButton("3", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(0,2);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "4";
    numpadobj->object = new QPushButton("4", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(1,0);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "5";
    numpadobj->object = new QPushButton("5", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(1,1);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "6";
    numpadobj->object = new QPushButton("6", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(1,2);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "7";
    numpadobj->object = new QPushButton("7", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(2,0);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "8";
    numpadobj->object = new QPushButton("8", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(2,1);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "9";
    numpadobj->object = new QPushButton("9", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(2,2);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "0";
    numpadobj->object = new QPushButton("0", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(3,0);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = ",";
    numpadobj->object = new QPushButton(",", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(3,2);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);

    numpadobj = new TPadObject;
    numpadobj->name   = "=";
    numpadobj->object = new QPushButton("=", parent);
    numpadobj->grid   = numpadGridLayout;
    numpadobj->ptA    = new QPoint(3,1);
    numpadobj->ptB    = new QPoint(1,1); AddNumPadElement(numpadobj);
#endif

    QHBoxLayout * eingabeLayout = new QHBoxLayout();
    lowerLayout->addLayout(eingabeLayout);

    QPlainTextEdit *
    eingabeTextEdit = new QPlainTextEdit(parent);
    eingabeTextEdit->move(5,5);
    eingabeTextEdit->resize(1024, 70);
    eingabeTextEdit->setFont(QFont("Arial",10));

    eingabeLayout->addWidget(eingabeTextEdit);

    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);


#if 0

    horizontalLayout->addLayout(gridLayout);

    widget = new QWidget(parent);
    widget->setObjectName(QStringLiteral("widget"));
    gridLayout_3 = new QGridLayout(widget);
    gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
    gridLayout_2 = new QGridLayout();
    gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
    pushButton_13 = new QPushButton(widget);
    pushButton_13->setObjectName(QStringLiteral("pushButton_13"));
    pushButton_13->setFont(font);

    gridLayout_2->addWidget(pushButton_13, 2, 0, 1, 1);

    pushButton_19 = new QPushButton(widget);
    pushButton_19->setObjectName(QStringLiteral("pushButton_19"));
    pushButton_19->setFont(font);

    gridLayout_2->addWidget(pushButton_19, 6, 0, 1, 1);

    widget_5 = new QWidget(widget);
    widget_5->setObjectName(QStringLiteral("widget_5"));
    sizePolicy.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
    widget_5->setSizePolicy(sizePolicy);
    widget_5->setMaximumSize(QSize(80, 16777215));

    gridLayout_2->addWidget(widget_5, 10, 1, 1, 1);

    pushButton_42 = new QPushButton(widget);
    pushButton_42->setObjectName(QStringLiteral("pushButton_42"));
    //sizePolicy2.setHeightForWidth(pushButton_42->sizePolicy().hasHeightForWidth());
    pushButton_42->setSizePolicy(sizePolicy2);

    gridLayout_2->addWidget(pushButton_42, 1, 4, 1, 1);

    pushButton_45 = new QPushButton(widget);
    pushButton_45->setObjectName(QStringLiteral("pushButton_45"));

    gridLayout_2->addWidget(pushButton_45, 11, 0, 1, 1);

    pushButton_12 = new QPushButton(widget);
    pushButton_12->setObjectName(QStringLiteral("pushButton_12"));
    QFont font3;
    font3.setPointSize(10);
    font3.setBold(false);
    font3.setWeight(50);
    pushButton_12->setFont(font3);
#ifndef QT_NO_TOOLTIP
    pushButton_12->setToolTip(QStringLiteral("<html><head/><body><p><span style=\" font-size:10pt;\">berechnet den Sinus</span></p></body></html>"));
#endif // QT_NO_TOOLTIP
    pushButton_12->setToolTipDuration(1);
    pushButton_12->setText(QStringLiteral("sin"));

    gridLayout_2->addWidget(pushButton_12, 1, 0, 1, 1);

    pushButton_39 = new QPushButton(widget);
    pushButton_39->setObjectName(QStringLiteral("pushButton_39"));
    QFont font4;
    font4.setPointSize(10);
    font4.setBold(true);
    font4.setWeight(75);
    pushButton_39->setFont(font4);

    gridLayout_2->addWidget(pushButton_39, 2, 3, 1, 1);

    pushButton_15 = new QPushButton(widget);
    pushButton_15->setObjectName(QStringLiteral("pushButton_15"));
    sizePolicy.setHeightForWidth(pushButton_15->sizePolicy().hasHeightForWidth());
    pushButton_15->setSizePolicy(sizePolicy);
    pushButton_15->setMinimumSize(QSize(0, 0));
    pushButton_15->setMaximumSize(QSize(16777215, 16777215));
    pushButton_15->setSizeIncrement(QSize(0, 0));
    pushButton_15->setFont(font);
#ifndef QT_NO_TOOLTIP
    pushButton_15->setToolTip(QStringLiteral("<html><head/><body><p>berechnet den Sinus</p></body></html>"));
#endif // QT_NO_TOOLTIP
    pushButton_15->setToolTipDuration(0);

    gridLayout_2->addWidget(pushButton_15, 1, 1, 1, 1);

    pushButton_18 = new QPushButton(widget);
    pushButton_18->setObjectName(QStringLiteral("pushButton_18"));
    pushButton_18->setFont(font);

    gridLayout_2->addWidget(pushButton_18, 5, 0, 1, 1);

    pushButton_16 = new QPushButton(widget);
    pushButton_16->setObjectName(QStringLiteral("pushButton_16"));
    sizePolicy.setHeightForWidth(pushButton_16->sizePolicy().hasHeightForWidth());
    pushButton_16->setSizePolicy(sizePolicy);
    pushButton_16->setMaximumSize(QSize(80, 16777215));
    pushButton_16->setFont(font);

    gridLayout_2->addWidget(pushButton_16, 2, 1, 1, 1);

    pushButton_44 = new QPushButton(widget);
    pushButton_44->setObjectName(QStringLiteral("pushButton_44"));
    sizePolicy.setHeightForWidth(pushButton_44->sizePolicy().hasHeightForWidth());
    pushButton_44->setSizePolicy(sizePolicy);
    pushButton_44->setMaximumSize(QSize(80, 16777215));
    QFont font5;
    font5.setBold(true);
    font5.setWeight(75);
    pushButton_44->setFont(font5);

    gridLayout_2->addWidget(pushButton_44, 11, 1, 1, 1);

    pushButton_20 = new QPushButton(widget);
    pushButton_20->setObjectName(QStringLiteral("pushButton_20"));
    sizePolicy.setHeightForWidth(pushButton_20->sizePolicy().hasHeightForWidth());
    pushButton_20->setSizePolicy(sizePolicy);
    pushButton_20->setMaximumSize(QSize(80, 16777215));
    pushButton_20->setFont(font);

    gridLayout_2->addWidget(pushButton_20, 6, 1, 1, 1);

    pushButton_40 = new QPushButton(widget);
    pushButton_40->setObjectName(QStringLiteral("pushButton_40"));
    sizePolicy2.setHeightForWidth(pushButton_40->sizePolicy().hasHeightForWidth());
    pushButton_40->setSizePolicy(sizePolicy2);
    pushButton_40->setFont(font4);

    gridLayout_2->addWidget(pushButton_40, 3, 3, 1, 1);

    pushButton_43 = new QPushButton(widget);
    pushButton_43->setObjectName(QStringLiteral("pushButton_43"));
    sizePolicy2.setHeightForWidth(pushButton_43->sizePolicy().hasHeightForWidth());
    pushButton_43->setSizePolicy(sizePolicy2);

    gridLayout_2->addWidget(pushButton_43, 2, 4, 1, 1);

    pushButton_38 = new QPushButton(widget);
    pushButton_38->setObjectName(QStringLiteral("pushButton_38"));
    pushButton_38->setFont(font);

    gridLayout_2->addWidget(pushButton_38, 1, 3, 1, 1);

    pushButton_14 = new QPushButton(widget);
    pushButton_14->setObjectName(QStringLiteral("pushButton_14"));
    pushButton_14->setFont(font);

    gridLayout_2->addWidget(pushButton_14, 3, 0, 1, 1);

    pushButton_25 = new QPushButton(widget);
    pushButton_25->setObjectName(QStringLiteral("pushButton_25"));
    sizePolicy.setHeightForWidth(pushButton_25->sizePolicy().hasHeightForWidth());
    pushButton_25->setSizePolicy(sizePolicy);
    pushButton_25->setMaximumSize(QSize(80, 16777215));
    pushButton_25->setFont(font);

    gridLayout_2->addWidget(pushButton_25, 5, 1, 1, 1);

    pushButton_41 = new QPushButton(widget);
    pushButton_41->setObjectName(QStringLiteral("pushButton_41"));
    sizePolicy2.setHeightForWidth(pushButton_41->sizePolicy().hasHeightForWidth());
    pushButton_41->setSizePolicy(sizePolicy2);
    pushButton_41->setFont(font4);

    gridLayout_2->addWidget(pushButton_41, 3, 4, 1, 1);

    widget_6 = new QWidget(widget);
    widget_6->setObjectName(QStringLiteral("widget_6"));

    gridLayout_2->addWidget(widget_6, 0, 4, 1, 1);

    pushButton_17 = new QPushButton(widget);
    pushButton_17->setObjectName(QStringLiteral("pushButton_17"));
    sizePolicy.setHeightForWidth(pushButton_17->sizePolicy().hasHeightForWidth());
    pushButton_17->setSizePolicy(sizePolicy);
    pushButton_17->setMaximumSize(QSize(80, 16777215));
    pushButton_17->setFont(font);

    gridLayout_2->addWidget(pushButton_17, 3, 1, 1, 1);

    verticalLayout_3 = new QVBoxLayout();
    verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));

    gridLayout_2->addLayout(verticalLayout_3, 9, 1, 1, 1);

    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
    verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

    horizontalLayout_6->addItem(verticalSpacer);


    gridLayout_2->addLayout(horizontalLayout_6, 8, 0, 1, 1);


    gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
    radioButton = new QRadioButton(widget);
    radioButton->setObjectName(QStringLiteral("radioButton"));

    horizontalLayout_5->addWidget(radioButton);

    horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_2);


    gridLayout_3->addLayout(horizontalLayout_5, 1, 1, 1, 1);


    horizontalLayout->addWidget(widget);


    verticalLayout_2->addLayout(horizontalLayout);

    verticalLayout_7 = new QVBoxLayout();
    verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));

    verticalLayout_2->addLayout(verticalLayout_7);

    widget_2 = new QWidget(parent);
    widget_2->setObjectName(QStringLiteral("widget_2"));
    widget_2->setMinimumSize(QSize(0, 70));
    widget_2->setMaximumSize(QSize(16777215, 70));
    verticalLayout_8 = new QVBoxLayout(widget_2);
    verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
    verticalLayout_8->setContentsMargins(1, 2, 2, 2);
    plainTextEdit_2 = new QPlainTextEdit(widget_2);
    plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));

    verticalLayout_8->addWidget(plainTextEdit_2, 0, Qt::AlignTop);


    verticalLayout_2->addWidget(widget_2, 0, Qt::AlignTop);


    StandardTabWidget = new QTabWidget(parent);
    StandardTabWidget->setObjectName(QStringLiteral("standardTabWidget"));
    StandardTabWidget->setTabPosition(QTabWidget::South);
    StandardTabWidget->setStyleSheet("background-color: lime;");
    StandardTab = new QWidget();
    StandardTab->setObjectName(QStringLiteral("standardTab"));

    StandardTabLayout = new QGridLayout(StandardTab);

    //gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));

    /*
    ZahlButtonMinus = new QPushButton(StandardTab);
    ZahlButtonMinus->setObjectName(QStringLiteral("ZahlButtonMinus"));
    sizePolicy2.setHeightForWidth(ZahlButtonMinus->sizePolicy().hasHeightForWidth());
    ZahlButtonMinus->setSizePolicy(sizePolicy2);
    ZahlButtonMinus->setFont(font1);*/

    //gridLayout_5->addWidget(ZahlButtonMinus, 0, 1, 1, 1);
/*
    ZahlButtonPlus = new QPushButton(StandardTab);
    ZahlButtonPlus->setObjectName(QStringLiteral("ZahlButtonPlus"));
    sizePolicy1.setHeightForWidth(ZahlButtonPlus->sizePolicy().hasHeightForWidth());
    ZahlButtonPlus->setSizePolicy(sizePolicy1);
    ZahlButtonPlus->setFont(font1);
*/
    //gridLayout_5->addWidget(ZahlButtonPlus, 0, 0, 1, 1);

    ZahlButtonModulo = new QPushButton(StandardTab);
    ZahlButtonModulo->setObjectName(QStringLiteral("ZahlButtonModulo"));
//    sizePolicy2.setHeightForWidth(ZahlButtonModulo->sizePolicy().hasHeightForWidth());
    //ZahlButtonModulo->setSizePolicy(sizePolicy2);
    //ZahlButtonModulo->setFont(font1);

    //gridLayout_5->addWidget(ZahlButtonModulo, 2, 0, 1, 1);

    ZahlButtonMul = new QPushButton("*",StandardTab);

//    sizePolicy1.setHeightForWidth(ZahlButtonMul->sizePolicy().hasHeightForWidth());
    //ZahlButtonMul->setSizePolicy(sizePolicy1);

    QFont font6;
    font6.setFamily(QStringLiteral("Waree"));
    font6.setPointSize(18);
    ZahlButtonMul->setFont(font6);

    //gridLayout_5->addWidget(ZahlButtonMul, 1, 0, 1, 1);

    ZahlButtonDiv = new QPushButton(StandardTab);
    ZahlButtonDiv->setObjectName(QStringLiteral("ZahlButtonDiv"));
//    sizePolicy2.setHeightForWidth(ZahlButtonDiv->sizePolicy().hasHeightForWidth());
    ZahlButtonDiv->setSizePolicy(sizePolicy2);
    ZahlButtonDiv->setFont(font1);

    //gridLayout_5->addWidget(ZahlButtonDiv, 1, 1, 1, 1);


    //horizontalLayout_2->addLayout(gridLayout_5);


    ///verticalLayout_5->addLayout(horizontalLayout_2);

    StandardTabWidget->addTab(StandardTab, QString());
    AllgemeinTab = new QWidget();
    AllgemeinTab->setObjectName(QStringLiteral("allgemeinTab"));

    StandardTabWidget->addTab(AllgemeinTab, QString());

    //gridLayout_4->addWidget(StandardTabWidget, 1, 0, 1, 1);

    widget_3 = new QWidget(parent);
    widget_3->setObjectName(QStringLiteral("widget_3"));
    formLayout = new QFormLayout(widget_3);
    formLayout->setObjectName(QStringLiteral("formLayout"));
    gridLayout_6 = new QGridLayout();
    gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
    pushButton_27 = new QPushButton(widget_3);
    pushButton_27->setObjectName(QStringLiteral("pushButton_27"));
    sizePolicy.setHeightForWidth(pushButton_27->sizePolicy().hasHeightForWidth());
    pushButton_27->setSizePolicy(sizePolicy);
    pushButton_27->setMaximumSize(QSize(40, 16777215));
    pushButton_27->setFont(font5);

    gridLayout_6->addWidget(pushButton_27, 1, 0, 1, 1);


    formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_6);

    pushButton_33 = new QPushButton(widget_3);
    pushButton_33->setObjectName(QStringLiteral("pushButton_33"));
    pushButton_33->setFont(font5);

    formLayout->setWidget(0, QFormLayout::FieldRole, pushButton_33);

    pushButton_28 = new QPushButton(widget_3);
    pushButton_28->setObjectName(QStringLiteral("pushButton_28"));
    pushButton_28->setMaximumSize(QSize(40, 16777215));
    pushButton_28->setFont(font5);

    formLayout->setWidget(1, QFormLayout::LabelRole, pushButton_28);

    pushButton_34 = new QPushButton(widget_3);
    pushButton_34->setObjectName(QStringLiteral("pushButton_34"));
    pushButton_34->setFont(font5);

    formLayout->setWidget(1, QFormLayout::FieldRole, pushButton_34);

    pushButton_29 = new QPushButton(widget_3);
    pushButton_29->setObjectName(QStringLiteral("pushButton_29"));
    pushButton_29->setMaximumSize(QSize(40, 16777215));
    pushButton_29->setFont(font5);

    formLayout->setWidget(3, QFormLayout::LabelRole, pushButton_29);

    widget_4 = new QWidget(widget_3);
    widget_4->setObjectName(QStringLiteral("widget_4"));
    horizontalLayout_3 = new QHBoxLayout(widget_4);
    horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    comboBox = new QComboBox(widget_4);
    comboBox->addItem(QStringLiteral("f(x)"));
    comboBox->addItem(QString());
    comboBox->addItem(QString());
    comboBox->addItem(QString());
    comboBox->addItem(QString());
    comboBox->addItem(QString());
    comboBox->setObjectName(QStringLiteral("comboBox"));
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
    comboBox->setSizePolicy(sizePolicy3);
    comboBox->setMaximumSize(QSize(80, 16777215));
    comboBox->setFont(font5);
    comboBox->setMaxCount(10);

    horizontalLayout_3->addWidget(comboBox);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer);


    formLayout->setWidget(3, QFormLayout::FieldRole, widget_4);

    pushButton_30 = new QPushButton(widget_3);
    pushButton_30->setObjectName(QStringLiteral("pushButton_30"));
    pushButton_30->setMaximumSize(QSize(40, 16777215));
    pushButton_30->setFont(font5);

    formLayout->setWidget(4, QFormLayout::LabelRole, pushButton_30);

    pushButton_31 = new QPushButton(widget_3);
    pushButton_31->setObjectName(QStringLiteral("pushButton_31"));
    pushButton_31->setMaximumSize(QSize(40, 16777215));
    pushButton_31->setFont(font5);

    formLayout->setWidget(6, QFormLayout::LabelRole, pushButton_31);

    pushButton_32 = new QPushButton(widget_3);
    pushButton_32->setObjectName(QStringLiteral("pushButton_32"));
    pushButton_32->setMaximumSize(QSize(40, 16777215));
    pushButton_32->setFont(font5);

    formLayout->setWidget(7, QFormLayout::LabelRole, pushButton_32);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
    pushButton_35 = new QPushButton(widget_3);
    pushButton_35->setObjectName(QStringLiteral("pushButton_35"));
    sizePolicy2.setHeightForWidth(pushButton_35->sizePolicy().hasHeightForWidth());
    pushButton_35->setSizePolicy(sizePolicy2);

    horizontalLayout_4->addWidget(pushButton_35);

    pushButton_36 = new QPushButton(widget_3);
    pushButton_36->setObjectName(QStringLiteral("pushButton_36"));
    sizePolicy2.setHeightForWidth(pushButton_36->sizePolicy().hasHeightForWidth());
    pushButton_36->setSizePolicy(sizePolicy2);

    horizontalLayout_4->addWidget(pushButton_36);

    pushButton_37 = new QPushButton(widget_3);
    pushButton_37->setObjectName(QStringLiteral("pushButton_37"));
    sizePolicy2.setHeightForWidth(pushButton_37->sizePolicy().hasHeightForWidth());
    pushButton_37->setSizePolicy(sizePolicy2);

    horizontalLayout_4->addWidget(pushButton_37);


    formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_4);


    //gridLayout_4->addWidget(widget_3, 1, 1, 1, 1);

    widget_7 = new QWidget(parent);
    widget_7->setObjectName(QStringLiteral("widget_7"));

    //gridLayout_4->addWidget(widget_7, 1, 3, 1, 1);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    //gridLayout_4->addItem(horizontalSpacer_3, 1, 2, 1, 1);


    //verticalLayout_2->addLayout(gridLayout_4);


    retranslateUi(parent);

    StandardTabWidget->setCurrentIndex(0);

#endif
//        QMetaObject::connectSlotsByName(parent);
}

void Rechner::retranslateUi(QWidget *parent)
{
    Q_UNUSED(parent);
#if 0
    parent->setWindowTitle(QApplication::translate("parent", "Form", Q_NULLPTR));
    plainTextEdit->setPlainText(QApplication::translate("parent", "Bitte Eingabe machen", Q_NULLPTR));
    ZahlButtonResult->setText("=");
    ZahlButtonKomma->setText(",");
    pushButton_13->setText("cos");
    pushButton_19->setText("Prozent");
    pushButton_42->setText("ln");
    pushButton_45->setText("DEL");
    pushButton_39->setText("n!");
    pushButton_15->setText("Wurzel^2");
    pushButton_18->setText("Pi");
    pushButton_16->setText("Wurzel^n");
    pushButton_44->setText("AC");
    pushButton_20->setText("Promille");
    pushButton_40->setText("(");
    pushButton_43->setText("log");
    pushButton_38->setText("e");
    pushButton_14->setText("tan");
    pushButton_25->setText("x^y");
    pushButton_41->setText(")");
    pushButton_17->setText("x^2");
    radioButton->setText("RadioButton");
    ZahlButtonMinus->setText("-");
    ZahlButtonPlus->setText("+");
    ZahlButtonModulo->setText("modulo");
    ZahlButtonMul->setText("*");
    ZahlButtonDiv->setText("/");

    StandardTabWidget->setTabText(StandardTabWidget->indexOf(StandardTab) , "Standard");
    StandardTabWidget->setTabText(StandardTabWidget->indexOf(AllgemeinTab), "Allgemein");

    pushButton_27->setText("A");
    pushButton_33->setText("< OOO");
    pushButton_28->setText("B");
    pushButton_34->setText("> OOO");
    pushButton_29->setText("C");

    comboBox->setItemText(1, "Ganzzahliger Anteil");
    comboBox->setItemText(2, "Gebrochener Anteil");
    comboBox->setItemText(3, "Runden");
    comboBox->setItemText(4, "Abrunden");
    comboBox->setItemText(5, "Aufrunden");
    comboBox->setCurrentText("f(x)");

    pushButton_30->setText("D");
    pushButton_31->setText("E");
    pushButton_32->setText("F");
    pushButton_35->setText("dez");
    pushButton_36->setText("hex");
    pushButton_37->setText("bin");
#endif

    connect(ZahlButton1, SIGNAL(clicked()), this, SLOT(btn1Clicked()));
    connect(ZahlButton2, SIGNAL(clicked()), this, SLOT(btn2Clicked()));
    connect(ZahlButton3, SIGNAL(clicked()), this, SLOT(btn3Clicked()));

    connect(ZahlButton4, SIGNAL(clicked()), this, SLOT(btn4Clicked()));
    connect(ZahlButton5, SIGNAL(clicked()), this, SLOT(btn5Clicked()));
    connect(ZahlButton6, SIGNAL(clicked()), this, SLOT(btn6Clicked()));

    connect(ZahlButton7, SIGNAL(clicked()), this, SLOT(btn7Clicked()));
    connect(ZahlButton8, SIGNAL(clicked()), this, SLOT(btn8Clicked()));
    connect(ZahlButton9, SIGNAL(clicked()), this, SLOT(btn9Clicked()));

    connect(ZahlButton0, SIGNAL(clicked()), this, SLOT(btn0Clicked()));

    //connect(ZahlButtonResult, SIGNAL(clicked()), this, SLOT(btnResultClicked()));
    //connect(ZahlButtonKomma, SIGNAL(clicked()), this, SLOT(btnKommaClicked()));
}

void Rechner::btnKommaClicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += ".";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btnResultClicked()
{
    char buffer[100];

    mpf_t x, y, z;

    mpf_init2(x,6);
    mpf_init2(y,6);
    mpf_init2(z,6);

    mpf_set_d(x,100.220);
    mpf_set_d(y,200.010);

    mpf_add(z,x,y);

    gmp_sprintf(buffer,"==> %F.f", z);
    plainTextEdit->document()->setPlainText(buffer);

    mpf_clear(x);
    mpf_clear(y);
    mpf_clear(z);
}

void Rechner::btn1Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "1";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn2Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "2";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn3Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "3";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn4Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "4";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn5Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "5";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn6Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "6";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn7Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "7";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn8Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "8";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn9Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "9";
    plainTextEdit->document()->setPlainText(arg);
}

void Rechner::btn0Clicked()
{
    QString arg;
    if (!first_input) {
        first_input = true;
        plainTextEdit->document()->clear();}
    arg  = plainTextEdit->document()->toPlainText();
    arg += "0";
    plainTextEdit->document()->setPlainText(arg);
}
