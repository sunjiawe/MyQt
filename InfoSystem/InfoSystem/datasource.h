#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "student.h"
#include <QFile>
#include <QIODevice>

class DataSource
{
public:
    DataSource();
    ~DataSource();

    //加载
    int load();

    //保存
    int save();

    //添加新的学生信息
    int add(const Student& student);

    //返回当前学生列表
    StudentList& list(){return m_list;}

    //移除一个学生信息
    void remove(int id);
    Student* find(int id);

    //第一版只做按姓名查找，后面会添加按学号、按号码等其他匹配方式
    void match(QString name,StudentList& list);
private:
    //QString m_fileName;
    StudentList m_list;

};

#endif // DATASOURCE_H
