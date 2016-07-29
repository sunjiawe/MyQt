#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected slots:
    int onClick();


private:
    QListWidget *m_numberListWidget;
    QPushButton *m_lotteryButton;
    QLabel *m_label;
    QVector<QString> phoneNumbers;
};

#endif // WIDGET_H
