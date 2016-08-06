#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(Student* student,QWidget *parent)
    :QDialog(parent),
     m_student(student),
     ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->BtnOK, SIGNAL(clicked()), this, SLOT(onBtnOK()));
    connect(ui->BtnCancel, SIGNAL(clicked()), this, SLOT(onBtnCancel()));

    // ������ʽ: ������������
    QValidator *v1 = new QRegExpValidator(QRegExp("^\\d{11}$"), this);
    ui->ctlCellPhone->setValidator(v1);

    QValidator *v2 = new QRegExpValidator(QRegExp("^\\d{6}$"), this);
    ui->ctlId->setValidator(v2);
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::onBtnOK()
{
    m_student->name = ui->ctlName->text();
    m_student->id = ui->ctlId->text().toInt();
    m_student->cellPhone = ui->ctlCellPhone->text();

    //�رնԻ���
    accept();
    return 0;
}

int Dialog::onBtnCancel()
{

    reject();
    return 0;
}
