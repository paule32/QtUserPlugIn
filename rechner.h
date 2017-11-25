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
#include <QtWidgets/QVBoxLayout>

#include <QtDesigner/QtDesigner>
#include <QtWidgets/QWidget>

class QDESIGNER_WIDGET_EXPORT Rechner: public QWidget
{
    Q_OBJECT
public:
    Rechner(QWidget *parent = 0);
    //~Rechner();

    void retranslateUi(QWidget *parent);

public slots:
    void btn1Clicked();  void btn2Clicked();  void btn3Clicked();
    void btn4Clicked();  void btn5Clicked();  void btn6Clicked();
    void btn7Clicked();  void btn8Clicked();  void btn9Clicked();
    void btn0Clicked();

    void btnResultClicked();
    void btnKommaClicked();

public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *ZahlButton4;
    QPushButton *ZahlButton3;
    QPushButton *ZahlButton2;
    QPushButton *ZahlButton0;
    QPushButton *ZahlButton5;
    QPushButton *ZahlButton6;
    QPushButton *ZahlButton9;
    QPushButton *ZahlButton1;
    QPushButton *ZahlButtonResult;
    QPushButton *ZahlButton8;
    QPushButton *ZahlButton7;
    QPushButton *ZahlButtonKomma;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_13;
    QPushButton *pushButton_19;
    QWidget *widget_5;
    QPushButton *pushButton_42;
    QPushButton *pushButton_45;
    QPushButton *pushButton_12;
    QPushButton *pushButton_39;
    QPushButton *pushButton_15;
    QPushButton *pushButton_18;
    QPushButton *pushButton_16;
    QPushButton *pushButton_44;
    QPushButton *pushButton_20;
    QPushButton *pushButton_40;
    QPushButton *pushButton_43;
    QPushButton *pushButton_38;
    QPushButton *pushButton_14;
    QPushButton *pushButton_25;
    QPushButton *pushButton_41;
    QWidget *widget_6;
    QPushButton *pushButton_17;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *radioButton;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_8;
    QPlainTextEdit *plainTextEdit_2;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_5;
    QPushButton *ZahlButtonMinus;
    QPushButton *ZahlButtonPlus;
    QPushButton *ZahlButtonModulo;
    QPushButton *ZahlButtonMul;
    QPushButton *ZahlButtonDiv;
    QWidget *tab_2;
    QWidget *widget_3;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_6;
    QPushButton *pushButton_27;
    QPushButton *pushButton_33;
    QPushButton *pushButton_28;
    QPushButton *pushButton_34;
    QPushButton *pushButton_29;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_30;
    QPushButton *pushButton_31;
    QPushButton *pushButton_32;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_35;
    QPushButton *pushButton_36;
    QPushButton *pushButton_37;
    QWidget *widget_7;
    QSpacerItem *horizontalSpacer_3;

    bool first_input;
};

#endif
