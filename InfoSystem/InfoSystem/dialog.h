#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "student.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
     Dialog(Student* student,QWidget *parent = 0);
    ~Dialog();
private slots:
    int onBtnOK();
    int onBtnCancel();


private:
    Ui::Dialog *ui;
    Student* m_student;
};

#endif // DIALOG_H
