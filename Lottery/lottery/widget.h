#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "dataloader.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    int onClick();


private:
    //窗口控件
    QListWidget *m_numberListWidget;
    QPushButton *m_lotteryButton;
    QLabel *m_label;

    DataLoader  dataLoader;
    QVector<QString> phoneNumbers;
};

#endif // WIDGET_H
