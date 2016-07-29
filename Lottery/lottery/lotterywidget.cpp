#include "lotterywidget.h"
#include <QIcon>
#include <QSize>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCloseEvent>
#include <QDateTime>


LotteryWidget::LotteryWidget(QStringList *numbers,QWidget *parent)
    : QDialog(parent),isPressed(false),m_numbers(numbers),current_Index(0)
{
    //主窗口大小
    this->setMinimumSize(QSize(466,128));

    //创建按键，并设置图标
    m_startButton = new QPushButton();
    QSize iconSize(48,48);;
    m_startButton->setToolTip("start");
    m_startButton->setIcon(QIcon(":/start"));
    m_startButton->setIconSize(iconSize);
    connect(m_startButton,SIGNAL(clicked()),this,SLOT(onClick()));

    m_phoneNumberLabel = new QLabel();
    m_phoneNumberLabel->setFont(QFont("System",20, QFont::Black));
    m_phoneNumberLabel->setMinimumSize(QSize(285,110));
    resultList = new QListWidget();
    resultList->setMinimumSize(QSize(125,110));

    //布局管理
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_phoneNumberLabel);
    layout->addSpacing(1);
    layout->addWidget(m_startButton);
    layout->addSpacing(1);
    layout->addWidget(resultList);


    //设置定时器
    timer.setInterval(100);
    connect(&timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    p = m_numbers->begin();
    m_phoneNumberLabel->setText(*p);
}


void LotteryWidget::onClick()
{
    if( m_numbers->isEmpty())
    {
        m_phoneNumberLabel->setText("List is empty.");
        return;
    }

    //开始
    if(isPressed == false)
    {
        timer.start();
        isPressed = true;
        m_startButton->setIcon(QIcon(":/pause"));
    }
    else  //暂停
    {
        timer.stop();
        isPressed = false;

        m_startButton->setIcon(QIcon(":/start"));
        resultList->addItem(*p);
        m_numbers->erase(p);
    }

}

//记录抽奖结果
bool LotteryWidget::saveResult()
{
    QFile file("log.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream ts(&file);

        //获取当前系统时间，用于填写记录文件
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
        ts << current_date <<" lottery log:" << endl;

        //把每一项结果记录到文件中
        for(int i=0; i < resultList->count(); i++)
        {
            ts << resultList->item(i)->text() << endl;
        }

        ts << endl <<endl;
        file.close();
    }
    else
    {
        qDebug() << "can't open the logfile.error-"<< file.errorString();
        return false;
    }
    return true;
}

void LotteryWidget::onTimeout()
{
    p++;
    if(p>= m_numbers->end())
    {
       p = m_numbers->begin();
    }
    m_phoneNumberLabel->setText(*p);
}



void LotteryWidget::closeEvent(QCloseEvent *event)
  {
    if (resultList->count() != 0)
    {
        saveResult();
    }
    event->accept();
  }
