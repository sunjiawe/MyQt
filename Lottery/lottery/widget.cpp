#include "widget.h"
#include "lotterywidget.h"

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

    connect(m_lotteryButton,SIGNAL(clicked()),this,SLOT(onClick()));

    //读入数据
    phoneNumbers.push_back("15021297868");
    phoneNumbers.push_back("13584055449");
    phoneNumbers.push_back("15050569614");
    phoneNumbers.push_back("15005154907");
    phoneNumbers.push_back("17778543214");
    phoneNumbers.push_back("13524896482");
    phoneNumbers.push_back("19504632458");
    phoneNumbers.push_back("84095463217");
    phoneNumbers.push_back("15069874352");
    phoneNumbers.push_back("12654138524");
    phoneNumbers.push_back("15965478512");

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



int Widget::onClick()
{
    QStringList numbers;
    QVector<QString>::iterator p;
    for(p=phoneNumbers.begin(); p < phoneNumbers.end(); p++)
    {
        numbers.append(*p);
    }

    //隐藏主界面
    this->hide();


    //进入抽奖界面
    LotteryWidget lotteryWig(&numbers,this);
    lotteryWig.exec();

    //恢复主界面
    this->showNormal();
    this->activateWindow();

    return 0;
}



