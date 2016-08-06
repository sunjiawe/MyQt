#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Student* student,QWidget *parent)
    :QDialog(parent),
     m_student(student),
     dialog_ui(new Ui::Dialog)
{
    dialog_ui->setupUi(this);
    connect(dialog_ui->BtnOK, SIGNAL(clicked()), this, SLOT(onBtnOK()));
    connect(dialog_ui->BtnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancel()));

    // 正则表达式: 限制输入数字
    QValidator *v1 = new QRegExpValidator(QRegExp("^\\d{11}$"), this);
    dialog_ui->ctlCellPhone->setValidator(v1);

    QValidator *v2 = new QRegExpValidator(QRegExp("^\\d{9}$"), this);
    dialog_ui->ctlId->setValidator(v2);
}

Dialog::~Dialog()
{
    delete dialog_ui;
}

int Dialog::onBtnOK()
{
    m_student->name = dialog_ui->ctlName->text();
    m_student->id = dialog_ui->ctlId->text().toInt();
    m_student->cellPhone = dialog_ui->ctlCellPhone->text();

    //关闭对话框
    accept();
    return 0;
}

int Dialog::onBtnCancel()
{

    reject();
    return 0;
}
