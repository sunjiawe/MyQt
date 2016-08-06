#ifndef DATASOURCE_H
#define DATASOURCE_H

#include "student.h"

class DataSource
{
public:
    DataSource();
    ~DataSource();

    int load();
    int save();
    int add(const Student& student);
    StudentList& list(){return m_list;}

    void remove(int id);
    Student* find(int id);

    //第一版只做按姓名查找，后面会添加按学号、按号码等其他匹配方式
    void match(const char* name,StudentList& list);
private:
    char m_fileName[256];
    StudentList m_list;

};

#endif // DATASOURCE_H
