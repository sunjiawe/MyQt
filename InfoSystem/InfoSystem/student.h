#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QList>

class Student
{  
public:
     Student():id(0){}
     ~Student(){}

public:
    int id;
    QString name;
    QString cellPhone;
};

typedef QList<Student> StudentList;

#endif // STUDENT_H
