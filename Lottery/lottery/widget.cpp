#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //创建控件
    m_label = new QLabel("phone-number list");
    m_lotteryButton = new QPushButton("enter lottery");
    m_numberListWidget = new QListWidget();

    //布局管理
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *actionLayout = new QHBoxLayout();
    actionLayout->addWidget(m_label);
    actionLayout->addStretch(1);
    actionLayout->addWidget(m_lotteryButton);
    actionLayout->addSpacing(1);
    layout->addLayout(actionLayout);
    layout->addWidget(m_numberListWidget);



    //读入数据
    phoneNumbers.push_back("15021297868");
    phoneNumbers.push_back("13584055449");
    phoneNumbers.push_back("15005154907");
    phoneNumbers.push_back("15050569614");

    //使用迭代器遍历QVector
    QVector<QString>::iterator p;
    for(p=phoneNumbers.begin(); p < phoneNumbers.end(); p++)
    {
        m_numberListWidget->addItem(*p);
    }

}

Widget::~Widget()
{

}
