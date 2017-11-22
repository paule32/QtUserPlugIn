#include "rechnerpropertypage.h"
#include "ui_rechnerpropertypage.h"

RechnerPropertyPage::RechnerPropertyPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechnerPropertyPage)
{
    ui->setupUi(this);
}

RechnerPropertyPage::~RechnerPropertyPage()
{
    delete ui;
}

void RechnerPropertyPage::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text() == "OK") {

    }
    if (button->text() == "Abbrechen") {

    }
    if (button->text() == "Schließen") {
        close();
    }
}
