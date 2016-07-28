#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //�����ؼ�
    m_label = new QLabel("phone-number list");
    m_lotteryButton = new QPushButton("enter lottery");
    m_numberListWidget = new QListWidget();

    //���ֹ���
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *actionLayout = new QHBoxLayout();
    actionLayout->addWidget(m_label);
    actionLayout->addStretch(1);
    actionLayout->addWidget(m_lotteryButton);
    actionLayout->addSpacing(1);
    layout->addLayout(actionLayout);
    layout->addWidget(m_numberListWidget);

}

Widget::~Widget()
{

}
