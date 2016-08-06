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

    //����
    int load();

    //����
    int save();

    //����µ�ѧ����Ϣ
    int add(const Student& student);

    //���ص�ǰѧ���б�
    StudentList& list(){return m_list;}

    //�Ƴ�һ��ѧ����Ϣ
    void remove(int id);
    Student* find(int id);

    //��һ��ֻ�����������ң��������Ӱ�ѧ�š������������ƥ�䷽ʽ
    void match(QString name,StudentList& list);
private:
    //QString m_fileName;
    StudentList m_list;

};

#endif // DATASOURCE_H
