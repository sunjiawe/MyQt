#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "student.h"
#include <datasource.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    int onAdd();
    int onRemove();
    int onFilterChanged();

private:
    void display(Student& student);
    void display(StudentList& list);

    Ui::Widget *widget_ui;
    DataSource m_dataSource;
};

#endif // WIDGET_H
