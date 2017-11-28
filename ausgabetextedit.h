#ifndef AUSGABETEXTEDIT_H
#define AUSGABETEXTEDIT_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QPlainTextEdit>

#include <QKeyEvent>

class AusgabeTextEdit: public QScrollArea
{
    Q_OBJECT

public:
    AusgabeTextEdit(QWidget *parent = 0);
    ~AusgabeTextEdit();

    virtual void keyPressEvent(QKeyEvent *e);
};

#endif // AUSGABETEXTEDIT_H
