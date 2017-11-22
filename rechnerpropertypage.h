#ifndef RECHNERPROPERTYPAGE_H
#define RECHNERPROPERTYPAGE_H

#include <QWidget>
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class RechnerPropertyPage;
}

class RechnerPropertyPage : public QDialog
{
    Q_OBJECT

public:
    explicit RechnerPropertyPage(QWidget *parent = 0);
    ~RechnerPropertyPage();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::RechnerPropertyPage *ui;
};

#endif // RECHNERPROPERTYPAGE_H
