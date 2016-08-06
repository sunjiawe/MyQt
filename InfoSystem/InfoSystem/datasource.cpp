#include "datasource.h"

DataSource::DataSource()
{

}

int DataSource::load()
{

    return 0;
}

int DataSource::save()
{

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

//��һ��ֻ�����������ң��������Ӱ�ѧ�š������������ƥ�䷽ʽ
void DataSource::match(const char* name,StudentList& list)
{
    for(int i=0; i<m_list.size(); i++)
    {
        if(m_list[i].name == name)
        {
            list.append(m_list[i]);
        }
    }

}
