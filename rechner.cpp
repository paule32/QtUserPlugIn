#include <QDebug>

#include <coreplugin/coreconstants.h>
#include <coreplugin/modemanager.h>

#include "rechner.h"

#include <gmp.h>
#include <gmpxx.h>

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

    //parent->resize(926, 632);
    verticalLayout_2 = new QVBoxLayout(parent);
    verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
    verticalLayout = new QVBoxLayout();
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

    verticalLayout_2->addLayout(verticalLayout);

    plainTextEdit = new QPlainTextEdit(parent);
    plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
    plainTextEdit->setSizePolicy(sizePolicy);
    plainTextEdit->setMaximumSize(QSize(16777215, 70));
    QFont font;
    font.setPointSize(10);
    plainTextEdit->setFont(font);

    verticalLayout_2->addWidget(plainTextEdit);

    verticalLayout_6 = new QVBoxLayout();
    verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));

    verticalLayout_2->addLayout(verticalLayout_6);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    gridLayout = new QGridLayout();
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    ZahlButton4 = new QPushButton(parent);
    ZahlButton4->setObjectName(QStringLiteral("ZahlButton4"));
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(ZahlButton4->sizePolicy().hasHeightForWidth());
    ZahlButton4->setSizePolicy(sizePolicy1);
    QFont font1;
    font1.setFamily(QStringLiteral("Waree"));
    font1.setPointSize(18);
    font1.setBold(true);
    font1.setWeight(75);
    ZahlButton4->setFont(font1);

    gridLayout->addWidget(ZahlButton4, 1, 0, 1, 1);

    ZahlButton3 = new QPushButton(parent);
    ZahlButton3->setObjectName(QStringLiteral("ZahlButton3"));
    QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(ZahlButton3->sizePolicy().hasHeightForWidth());
    ZahlButton3->setSizePolicy(sizePolicy2);
    ZahlButton3->setFont(font1);

    gridLayout->addWidget(ZahlButton3, 0, 2, 1, 1);

    ZahlButton2 = new QPushButton(parent);
    ZahlButton2->setObjectName(QStringLiteral("ZahlButton2"));
    sizePolicy2.setHeightForWidth(ZahlButton2->sizePolicy().hasHeightForWidth());
    ZahlButton2->setSizePolicy(sizePolicy2);
    ZahlButton2->setFont(font1);
#ifndef QT_NO_TOOLTIP
    ZahlButton2->setToolTip(QStringLiteral("<html><head/><body><p>Zahl 2</p></body></html>"));
#endif // QT_NO_TOOLTIP
    ZahlButton2->setToolTipDuration(0);

    gridLayout->addWidget(ZahlButton2, 0, 1, 1, 1);

    ZahlButton0 = new QPushButton(parent);
    ZahlButton0->setObjectName(QStringLiteral("ZahlButton0"));
    sizePolicy1.setHeightForWidth(ZahlButton0->sizePolicy().hasHeightForWidth());
    ZahlButton0->setSizePolicy(sizePolicy1);
    ZahlButton0->setFont(font1);

    gridLayout->addWidget(ZahlButton0, 3, 0, 1, 1);

    ZahlButton5 = new QPushButton(parent);
    ZahlButton5->setObjectName(QStringLiteral("ZahlButton5"));
    sizePolicy2.setHeightForWidth(ZahlButton5->sizePolicy().hasHeightForWidth());
    ZahlButton5->setSizePolicy(sizePolicy2);
    ZahlButton5->setFont(font1);

    gridLayout->addWidget(ZahlButton5, 1, 1, 1, 1);

    ZahlButton6 = new QPushButton(parent);
    ZahlButton6->setObjectName(QStringLiteral("ZahlButton6"));
    sizePolicy2.setHeightForWidth(ZahlButton6->sizePolicy().hasHeightForWidth());
    ZahlButton6->setSizePolicy(sizePolicy2);
    ZahlButton6->setFont(font1);

    gridLayout->addWidget(ZahlButton6, 1, 2, 1, 1);

    ZahlButton9 = new QPushButton(parent);
    ZahlButton9->setObjectName(QStringLiteral("ZahlButton9"));
    sizePolicy2.setHeightForWidth(ZahlButton9->sizePolicy().hasHeightForWidth());
    ZahlButton9->setSizePolicy(sizePolicy2);
    ZahlButton9->setFont(font1);

    gridLayout->addWidget(ZahlButton9, 2, 2, 1, 1);

    ZahlButton1 = new QPushButton(parent);
    ZahlButton1->setObjectName(QStringLiteral("ZahlButton1"));
    sizePolicy1.setHeightForWidth(ZahlButton1->sizePolicy().hasHeightForWidth());
    ZahlButton1->setSizePolicy(sizePolicy1);
    ZahlButton1->setFont(font1);
#ifndef QT_NO_TOOLTIP
    ZahlButton1->setToolTip(QStringLiteral("<html><head/><body><p>Zahl 1</p></body></html>"));
#endif // QT_NO_TOOLTIP
    ZahlButton1->setToolTipDuration(0);

    gridLayout->addWidget(ZahlButton1, 0, 0, 1, 1);

    ZahlButtonResult = new QPushButton(parent);
    ZahlButtonResult->setObjectName(QStringLiteral("ZahlButtonResult"));
    sizePolicy2.setHeightForWidth(ZahlButtonResult->sizePolicy().hasHeightForWidth());
    ZahlButtonResult->setSizePolicy(sizePolicy2);
    QPalette palette;
    QBrush brush(QColor(0, 0, 0, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(QColor(138, 226, 52, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush1);
    QBrush brush2(QColor(198, 255, 143, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Light, brush2);
    QBrush brush3(QColor(168, 240, 97, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
    QBrush brush4(QColor(69, 113, 26, 255));
    brush4.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
    QBrush brush5(QColor(92, 151, 34, 255));
    brush5.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
    palette.setBrush(QPalette::Active, QPalette::Text, brush);
    QBrush brush6(QColor(255, 255, 255, 255));
    brush6.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Active, QPalette::Base, brush6);
    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
    palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
    QBrush brush7(QColor(196, 240, 153, 255));
    brush7.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
    QBrush brush8(QColor(255, 255, 220, 255));
    brush8.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
    palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
    palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
    palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
    palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
    palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
    palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
    palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
    palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
    palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
    palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
    palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
    ZahlButtonResult->setPalette(palette);
    ZahlButtonResult->setFont(font1);
#ifndef QT_NO_TOOLTIP
    ZahlButtonResult->setToolTip(QStringLiteral("<html><head/><body><p>berechnet einen gegebenen</p><p>Ausdruck.</p></body></html>"));
#endif // QT_NO_TOOLTIP
    ZahlButtonResult->setToolTipDuration(0);

    gridLayout->addWidget(ZahlButtonResult, 3, 1, 1, 1);

    ZahlButton8 = new QPushButton(parent);
    ZahlButton8->setObjectName(QStringLiteral("ZahlButton8"));
    sizePolicy2.setHeightForWidth(ZahlButton8->sizePolicy().hasHeightForWidth());
    ZahlButton8->setSizePolicy(sizePolicy2);
    ZahlButton8->setFont(font1);

    gridLayout->addWidget(ZahlButton8, 2, 1, 1, 1);

    ZahlButton7 = new QPushButton(parent);
    ZahlButton7->setObjectName(QStringLiteral("ZahlButton7"));
    sizePolicy1.setHeightForWidth(ZahlButton7->sizePolicy().hasHeightForWidth());
    ZahlButton7->setSizePolicy(sizePolicy1);
    ZahlButton7->setFont(font1);

    gridLayout->addWidget(ZahlButton7, 2, 0, 1, 1);

    ZahlButtonKomma = new QPushButton(parent);
    ZahlButtonKomma->setObjectName(QStringLiteral("ZahlButtonKomma"));
    sizePolicy2.setHeightForWidth(ZahlButtonKomma->sizePolicy().hasHeightForWidth());
    ZahlButtonKomma->setSizePolicy(sizePolicy2);
    QFont font2;
    font2.setPointSize(18);
    font2.setBold(true);
    font2.setWeight(75);
    ZahlButtonKomma->setFont(font2);
#ifndef QT_NO_TOOLTIP
    ZahlButtonKomma->setToolTip(QStringLiteral("<html><head/><body><p><span style=\" font-weight:600;\">Komma</span>: dient zur Trennung von</p><p>ganzzahligen und gebrochenen</p><p>Teilen von Zahlen.</p><p>Zum Beispiel: Pi = 3,14</p></body></html>"));
#endif // QT_NO_TOOLTIP
    ZahlButtonKomma->setToolTipDuration(0);

    gridLayout->addWidget(ZahlButtonKomma, 3, 2, 1, 1);


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
    sizePolicy2.setHeightForWidth(pushButton_42->sizePolicy().hasHeightForWidth());
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

    gridLayout_4 = new QGridLayout();
    gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
    tabWidget = new QTabWidget(parent);
    tabWidget->setObjectName(QStringLiteral("tabWidget"));
    QPalette palette1;
    palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush9(QColor(238, 238, 236, 255));
    brush9.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::Button, brush9);
    palette1.setBrush(QPalette::Active, QPalette::Light, brush6);
    QBrush brush10(QColor(246, 246, 245, 255));
    brush10.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::Midlight, brush10);
    QBrush brush11(QColor(119, 119, 118, 255));
    brush11.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::Dark, brush11);
    QBrush brush12(QColor(159, 159, 157, 255));
    brush12.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::Mid, brush12);
    palette1.setBrush(QPalette::Active, QPalette::Text, brush);
    palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
    palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
    palette1.setBrush(QPalette::Active, QPalette::Base, brush6);
    palette1.setBrush(QPalette::Active, QPalette::Window, brush9);
    palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
    palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush10);
    palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
    palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::Button, brush9);
    palette1.setBrush(QPalette::Inactive, QPalette::Light, brush6);
    palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
    palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
    palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
    palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
    palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::Base, brush6);
    palette1.setBrush(QPalette::Inactive, QPalette::Window, brush9);
    palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
    palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush10);
    palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
    palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
    palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush11);
    palette1.setBrush(QPalette::Disabled, QPalette::Button, brush9);
    palette1.setBrush(QPalette::Disabled, QPalette::Light, brush6);
    palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
    palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
    palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
    palette1.setBrush(QPalette::Disabled, QPalette::Text, brush11);
    palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
    palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush11);
    palette1.setBrush(QPalette::Disabled, QPalette::Base, brush9);
    palette1.setBrush(QPalette::Disabled, QPalette::Window, brush9);
    palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
    palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush9);
    palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
    palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
    tabWidget->setPalette(palette1);
    tabWidget->setAutoFillBackground(false);
    tabWidget->setTabPosition(QTabWidget::South);
    tabWidget->setElideMode(Qt::ElideNone);
    tab = new QWidget();
    tab->setObjectName(QStringLiteral("tab"));
    verticalLayout_5 = new QVBoxLayout(tab);
    verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    gridLayout_5 = new QGridLayout();
    gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
    ZahlButtonMinus = new QPushButton(tab);
    ZahlButtonMinus->setObjectName(QStringLiteral("ZahlButtonMinus"));
    sizePolicy2.setHeightForWidth(ZahlButtonMinus->sizePolicy().hasHeightForWidth());
    ZahlButtonMinus->setSizePolicy(sizePolicy2);
    ZahlButtonMinus->setFont(font1);

    gridLayout_5->addWidget(ZahlButtonMinus, 0, 1, 1, 1);

    ZahlButtonPlus = new QPushButton(tab);
    ZahlButtonPlus->setObjectName(QStringLiteral("ZahlButtonPlus"));
    sizePolicy1.setHeightForWidth(ZahlButtonPlus->sizePolicy().hasHeightForWidth());
    ZahlButtonPlus->setSizePolicy(sizePolicy1);
    ZahlButtonPlus->setFont(font1);

    gridLayout_5->addWidget(ZahlButtonPlus, 0, 0, 1, 1);

    ZahlButtonModulo = new QPushButton(tab);
    ZahlButtonModulo->setObjectName(QStringLiteral("ZahlButtonModulo"));
    sizePolicy2.setHeightForWidth(ZahlButtonModulo->sizePolicy().hasHeightForWidth());
    ZahlButtonModulo->setSizePolicy(sizePolicy2);
    ZahlButtonModulo->setFont(font1);

    gridLayout_5->addWidget(ZahlButtonModulo, 2, 0, 1, 1);

    ZahlButtonMul = new QPushButton(tab);
    ZahlButtonMul->setObjectName(QStringLiteral("ZahlButtonMul"));
    sizePolicy1.setHeightForWidth(ZahlButtonMul->sizePolicy().hasHeightForWidth());
    ZahlButtonMul->setSizePolicy(sizePolicy1);
    QFont font6;
    font6.setFamily(QStringLiteral("Waree"));
    font6.setPointSize(18);
    ZahlButtonMul->setFont(font6);

    gridLayout_5->addWidget(ZahlButtonMul, 1, 0, 1, 1);

    ZahlButtonDiv = new QPushButton(tab);
    ZahlButtonDiv->setObjectName(QStringLiteral("ZahlButtonDiv"));
    sizePolicy2.setHeightForWidth(ZahlButtonDiv->sizePolicy().hasHeightForWidth());
    ZahlButtonDiv->setSizePolicy(sizePolicy2);
    ZahlButtonDiv->setFont(font1);

    gridLayout_5->addWidget(ZahlButtonDiv, 1, 1, 1, 1);


    horizontalLayout_2->addLayout(gridLayout_5);


    verticalLayout_5->addLayout(horizontalLayout_2);

    tabWidget->addTab(tab, QString());
    tab_2 = new QWidget();
    tab_2->setObjectName(QStringLiteral("tab_2"));
    tabWidget->addTab(tab_2, QString());

    gridLayout_4->addWidget(tabWidget, 1, 0, 1, 1);

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


    gridLayout_4->addWidget(widget_3, 1, 1, 1, 1);

    widget_7 = new QWidget(parent);
    widget_7->setObjectName(QStringLiteral("widget_7"));

    gridLayout_4->addWidget(widget_7, 1, 3, 1, 1);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout_4->addItem(horizontalSpacer_3, 1, 2, 1, 1);


    verticalLayout_2->addLayout(gridLayout_4);


    retranslateUi(parent);

    tabWidget->setCurrentIndex(0);


//        QMetaObject::connectSlotsByName(parent);
}

void Rechner::retranslateUi(QWidget *parent)
{
    parent->setWindowTitle(QApplication::translate("parent", "Form", Q_NULLPTR));
    plainTextEdit->setPlainText(QApplication::translate("parent", "Bitte Eingabe machen", Q_NULLPTR));
    ZahlButton4->setText(QApplication::translate("parent", "4", Q_NULLPTR));
    ZahlButton3->setText(QApplication::translate("parent", "3", Q_NULLPTR));
    ZahlButton2->setText(QApplication::translate("parent", "2", Q_NULLPTR));
    ZahlButton0->setText(QApplication::translate("parent", "0", Q_NULLPTR));
    ZahlButton5->setText(QApplication::translate("parent", "5", Q_NULLPTR));
    ZahlButton6->setText(QApplication::translate("parent", "6", Q_NULLPTR));
    ZahlButton9->setText(QApplication::translate("parent", "9", Q_NULLPTR));
    ZahlButton1->setText(QApplication::translate("parent", "1", Q_NULLPTR));
    ZahlButtonResult->setText(QApplication::translate("parent", "=", Q_NULLPTR));
    ZahlButton8->setText(QApplication::translate("parent", "8", Q_NULLPTR));
    ZahlButton7->setText(QApplication::translate("parent", "7", Q_NULLPTR));
    ZahlButtonKomma->setText(QApplication::translate("parent", ",", Q_NULLPTR));
    pushButton_13->setText(QApplication::translate("parent", "cos", Q_NULLPTR));
    pushButton_19->setText(QApplication::translate("parent", "Prozent", Q_NULLPTR));
    pushButton_42->setText(QApplication::translate("parent", "ln", Q_NULLPTR));
    pushButton_45->setText(QApplication::translate("parent", "DEL", Q_NULLPTR));
    pushButton_39->setText(QApplication::translate("parent", "n!", Q_NULLPTR));
    pushButton_15->setText(QApplication::translate("parent", "Wurzel^2", Q_NULLPTR));
    pushButton_18->setText(QApplication::translate("parent", "Pi", Q_NULLPTR));
    pushButton_16->setText(QApplication::translate("parent", "Wurzel^n", Q_NULLPTR));
    pushButton_44->setText(QApplication::translate("parent", "AC", Q_NULLPTR));
    pushButton_20->setText(QApplication::translate("parent", "Promille", Q_NULLPTR));
    pushButton_40->setText(QApplication::translate("parent", "(", Q_NULLPTR));
    pushButton_43->setText(QApplication::translate("parent", "log", Q_NULLPTR));
    pushButton_38->setText(QApplication::translate("parent", "e", Q_NULLPTR));
    pushButton_14->setText(QApplication::translate("parent", "tan", Q_NULLPTR));
    pushButton_25->setText(QApplication::translate("parent", "x^y", Q_NULLPTR));
    pushButton_41->setText(QApplication::translate("parent", ")", Q_NULLPTR));
    pushButton_17->setText(QApplication::translate("parent", "x^2", Q_NULLPTR));
    radioButton->setText(QApplication::translate("parent", "RadioButton", Q_NULLPTR));
    ZahlButtonMinus->setText(QApplication::translate("parent", "-", Q_NULLPTR));
    ZahlButtonPlus->setText(QApplication::translate("parent", "+", Q_NULLPTR));
    ZahlButtonModulo->setText(QApplication::translate("parent", "modulo", Q_NULLPTR));
    ZahlButtonMul->setText(QApplication::translate("parent", "*", Q_NULLPTR));
    ZahlButtonDiv->setText(QApplication::translate("parent", "/", Q_NULLPTR));
    tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("parent", "Standard", Q_NULLPTR));
    tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("parent", "Tab 2", Q_NULLPTR));
    pushButton_27->setText(QApplication::translate("parent", "A", Q_NULLPTR));
    pushButton_33->setText(QApplication::translate("parent", "< OOO", Q_NULLPTR));
    pushButton_28->setText(QApplication::translate("parent", "B", Q_NULLPTR));
    pushButton_34->setText(QApplication::translate("parent", "> OOO", Q_NULLPTR));
    pushButton_29->setText(QApplication::translate("parent", "C", Q_NULLPTR));
    comboBox->setItemText(1, QApplication::translate("parent", "Ganzzahliger Anteil", Q_NULLPTR));
    comboBox->setItemText(2, QApplication::translate("parent", "Gebrochener Anteil", Q_NULLPTR));
    comboBox->setItemText(3, QApplication::translate("parent", "Runden", Q_NULLPTR));
    comboBox->setItemText(4, QApplication::translate("parent", "Abrunden", Q_NULLPTR));
    comboBox->setItemText(5, QApplication::translate("parent", "Aufrunden", Q_NULLPTR));

    comboBox->setCurrentText(QApplication::translate("parent", "f(x)", Q_NULLPTR));
    pushButton_30->setText(QApplication::translate("parent", "D", Q_NULLPTR));
    pushButton_31->setText(QApplication::translate("parent", "E", Q_NULLPTR));
    pushButton_32->setText(QApplication::translate("parent", "F", Q_NULLPTR));
    pushButton_35->setText(QApplication::translate("parent", "dez", Q_NULLPTR));
    pushButton_36->setText(QApplication::translate("parent", "hex", Q_NULLPTR));
    pushButton_37->setText(QApplication::translate("parent", "bin", Q_NULLPTR));


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

    connect(ZahlButtonResult, SIGNAL(clicked()), this, SLOT(btnResultClicked()));
    connect(ZahlButtonKomma, SIGNAL(clicked()), this, SLOT(btnKommaClicked()));
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



#if 0
void Rechner::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    if (ZahlButton1->underMouse()) { btn1Clicked(); } else
    if (ZahlButton2->underMouse()) { btn2Clicked(); } else
    if (ZahlButton3->underMouse()) { btn3Clicked(); }
}
#endif
