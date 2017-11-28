#include <QPainter>
#include "ausgabetextedit.h"
#include "wurzelbox.h"

int WurzelBox::counter = 0;

WurzelBox::WurzelBox(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: red");

    move(5,5);
    resize(130,50);
    show();

    id = ++counter;
}
WurzelBox::~WurzelBox()
{
}

void WurzelBox::mousePressEvent(QMouseEvent *event)
{
    oldpos = event->globalPos();
}

void WurzelBox::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint delta = event->globalPos() - oldpos;
    move(x()+delta.x(),y()+delta.y());

    oldpos = event->globalPos();
}

void WurzelBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.drawText(rect(), Qt::AlignCenter,
    QString("-> %1").arg(id));
}
