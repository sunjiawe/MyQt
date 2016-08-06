#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QList>

class Student
{  
public:
     Student():id(0){}
     ~Student(){}

private:
    int id;
    QString name;
    QString cellPhone;
    friend class DataSource;
};

typedef QList<Student> StudentList;

#endif // STUDENT_H
