#ifndef WURZELBOX_H
#define WURZELBOX_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QLineEdit>

class WurzelBox: public QWidget
{
public:
    explicit WurzelBox(QWidget *parent = 0);
    ~WurzelBox();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void paintEvent(QPaintEvent *event);

private:
    QPoint oldpos;
    int    id;
    static int counter;
};

#endif // WURZELBOX_H
