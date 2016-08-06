#include "datasource.h"
#include <QDebug>

DataSource::DataSource()
    :m_fileName("info.bin")
{

}

DataSource::~DataSource()
{

}

int DataSource::load()
{
    QFile *file = new QFile(m_fileName);
    if ( file->open(QFile::ReadOnly))
    {
        m_list.clear();

        while(!file->atEnd())
        {
            Student student;
            file->read((char*)&student,sizeof(Student));
            m_list.push_back(student);
        }


        file->close();
    }
    else
    {
        qDebug() << "open file error-" << file->errorString();
        delete file;
        file = 0;
    }
    return 0;
}

int DataSource::save()
{
    QFile *file = new QFile(m_fileName);
    if ( file->open(QFile::WriteOnly))
    {
        for(StudentList::iterator iter = m_list.begin();
            iter != m_list.end(); iter++)
        {
            Student student = *iter;
            file->write((char*)&student,sizeof(Student));
        }

        file->close();
    }
    else
    {
        qDebug() << "open file error-" << file->errorString();
        delete file;
        file = 0;
    }
    return 0;
}

int DataSource::add(const Student& student)
{
    bool isMore = false;
    for(int i=0; i<m_list.size(); i++)
    {
        if(m_list[i].name == student.name)
        {
            isMore = true;
            break;
        }
    }

    if(!isMore)
    {
        m_list.append(student);
    }
    return 0;
}


void DataSource::remove(int id)
{
    for(int i=0; i<m_list.size(); i++)
    {
        if(m_list[i].id == id)
        {
            m_list.removeAt(i);
            break;
        }
    }

}

Student* DataSource::find(int id)
{
    for(int i=0; i<m_list.size(); i++)
    {
        if(m_list[i].id == id)
        {
            return &m_list[i];
        }
    }
    return NULL;
}

//第一版只做按姓名查找，后面会添加按学号、按号码等其他匹配方式
void DataSource::match(QString name,StudentList& list)
{
    for(int i=0; i<m_list.size(); i++)
    {
        if(m_list[i].name == name)
        {
            list.append(m_list[i]);
        }
    }

}
