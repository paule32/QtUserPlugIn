#include <QObject>

#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerPropertySheetExtension>

#include <coreplugin/coreconstants.h>
#include <coreplugin/modemanager.h>

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
        Core::ModeManager::activateMode(Core::Constants::MODE_EDIT);
        close();
    }
    if (button->text() == "Abbrechen") {

    }
    if (button->text() == "Schließen") {
        close();
    }
}
