#ifndef LOTTERYWIDGET_H
#define LOTTERYWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTimer>

class LotteryWidget : public QDialog
{
    Q_OBJECT
public:
     LotteryWidget(QStringList *numbers,QWidget *parent = 0);
     ~LotteryWidget(){}
signals:

public slots:
    void onTimeout();
    void onClick();

private:
    //窗口控件
    QPushButton *m_startButton;
    QLabel *m_phoneNumberLabel;
    QListWidget *resultList;
    QTimer timer;

    QStringList *m_numbers;

    bool isPressed;   //按键状态
    int current_Index = 0;  //当前号码索引
    QList<QString>::iterator p;  //迭代器
};

#endif // LOTTERYWIDGET_H
