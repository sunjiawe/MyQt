#include "widget.h"
#include "ui_widget.h"
#include <dialog.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    widget_ui(new Ui::Widget)
{
    widget_ui->setupUi(this);

    connect(widget_ui->btnAdd, SIGNAL(clicked()), this, SLOT(onAdd()));
    connect(widget_ui->btnRemove, SIGNAL(clicked()), this, SLOT(onRemove()));
    connect(widget_ui->ctlFilter, SIGNAL(returnPressed()), this, SLOT(onFilterChanged()));

    //加载数据
    m_dataSource.load();

    //手动调用槽来显示数据
    onFilterChanged();
}

Widget::~Widget()
{
    delete widget_ui;
}

int Widget::onAdd()
{
    Student student;
    Dialog dlg(&student,this);
    if(QDialog::Accepted == dlg.exec())
    {
        m_dataSource.add(student);
        m_dataSource.save();

        //把新添加的学生显示出来
        display(student);

    }
    return 0;
}

int Widget::onRemove()
{
    QTreeWidgetItem* item = widget_ui->treeWidget->currentItem();
    if(!item) return 0; // 没有选中项

    // 取得行号
    int id = item->data(0, Qt::UserRole).toInt();

    // 从DataSource中删除记录
    m_dataSource.remove(id);
    m_dataSource.save();

    // 从界面中删除该条显示
    int index = widget_ui->treeWidget->indexOfTopLevelItem(item);
    QTreeWidgetItem* which = widget_ui->treeWidget->takeTopLevelItem(index);
    delete which;

    return 0;

}

int Widget::onFilterChanged()
{
    QString filter = widget_ui->ctlFilter->text().trimmed();

    if(filter.length() > 0)
    {
        // 查找匹配
        StudentList list;
        m_dataSource.match(filter, list);

        // 显示匹配的记录
        widget_ui->treeWidget->clear();
        display(list);
    }
    else
    {
        // 显示全部
        widget_ui->treeWidget->clear();
        display(m_dataSource.list());
    }

        return 0;
}


// 显示一条记录
void Widget::display(Student& student)
{
    // 设置数据
    QTreeWidgetItem* item = new QTreeWidgetItem(widget_ui->treeWidget);
    item->setText(0, QString("%1").arg(student.id) );
    item->setText(1, (student.name));
    item->setText(2, student.cellPhone);

    // 设置行号
    item->setData(0, Qt::UserRole, student.id);
}

// 显示多条记录
void Widget::display(StudentList& list)
{
    for(StudentList::iterator iter = list.begin();
        iter != list.end(); iter ++)
    {
        Student& record = *iter;

        display(record);
    }
}
