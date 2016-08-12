#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdichild.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    MdiChild *childe = new MdiChild;
    ui->mdiArea->addSubWindow(childe);

    //�½��ļ�
    childe->newFile();

    //��ʾ�Ӵ���
    childe->show();
}
