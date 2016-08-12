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

    //新建文件
    childe->newFile();

    //显示子窗口
    childe->show();
}
