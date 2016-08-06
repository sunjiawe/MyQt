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

    //��������
    m_dataSource.load();

    //�ֶ����ò�����ʾ����
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

        //������ӵ�ѧ����ʾ����
        display(student);

    }
    return 0;
}

int Widget::onRemove()
{
    QTreeWidgetItem* item = widget_ui->treeWidget->currentItem();
    if(!item) return 0; // û��ѡ����

    // ȡ���к�
    int id = item->data(0, Qt::UserRole).toInt();

    // ��DataSource��ɾ����¼
    m_dataSource.remove(id);
    m_dataSource.save();

    // �ӽ�����ɾ��������ʾ
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
        // ����ƥ��
        StudentList list;
        m_dataSource.match(filter, list);

        // ��ʾƥ��ļ�¼
        widget_ui->treeWidget->clear();
        display(list);
    }
    else
    {
        // ��ʾȫ��
        widget_ui->treeWidget->clear();
        display(m_dataSource.list());
    }

        return 0;
}


// ��ʾһ����¼
void Widget::display(Student& student)
{
    // ��������
    QTreeWidgetItem* item = new QTreeWidgetItem(widget_ui->treeWidget);
    item->setText(0, QString("%1").arg(student.id) );
    item->setText(1, (student.name));
    item->setText(2, student.cellPhone);

    // �����к�
    item->setData(0, Qt::UserRole, student.id);
}

// ��ʾ������¼
void Widget::display(StudentList& list)
{
    for(StudentList::iterator iter = list.begin();
        iter != list.end(); iter ++)
    {
        Student& record = *iter;

        display(record);
    }
}
