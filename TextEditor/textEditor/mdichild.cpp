#include "mdichild.h"

MdiChild::MdiChild(QWidget *parent)
    :isUntitled(true)
{
    //在子窗口关闭时，销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);

}

void MdiChild::newFile()
{
    static int sequenceNumber = 1;
    isUntitled = true;

    curFile = QString::fromLocal8Bit("未命名文档%1.txt").arg(sequenceNumber++);

    setWindowTitle(curFile +"[*]" + QString::fromLocal8Bit(" - 多文档编辑器"));
    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));
}

bool MdiChild::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if( !file.open(QFile::ReadOnly | QFile::Text))
    {
        //qDebug() << "open file failed." << endl;
        QMessageBox::warning(this,QString::fromLocal8Bit("多文档编辑器"),
                             QString::fromLocal8Bit("无法读取文件&1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);  //鼠标显示为等待状态
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    connect(document(),SIGNAL(contentsChanged()),
            this,SLOT(documentWasModified()));

    return true;

}

void MdiChild::documentWasModified()
{
    //QWidget自带的函数
    //如果文档有未保存的更改，则在设置[*]的地方显示*号
    setWindowModified(document()->isModified());
}


//将加载的文件路径保存到curFile中
void MdiChild::setCurrentFile(const QString &fileName)
{
    //canonicalFilePath()可以取出路径中的"."和".."
    curFile = QFileInfo(fileName).canonicalFilePath();

    isUntitled = false;
    document()->setModified(false);

    //窗口不现实被更改标志
    setWindowModified(false);

    setWindowTitle(userFriendlyCurrentFile() + "[*]");

}

QString MdiChild::userFriendlyCurrentFile()
{
    return QFileInfo(curFile).fileName();
}


bool MdiChild::save()
{
    //判断文件是否保存过
    if(isUntitled)
    {
        return saveAs();
    }else
    {
        return saveFile(curFile);
    }
}


bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("另存为"),curFile);

    if(fileName.isEmpty())
    {
        return false;
    }

    return saveFile(fileName);
}



bool MdiChild::saveFile(const QString &fileName)
{
    QFile file(fileName);

    if( !file.open(QFile::WriteOnly | QFile::Text))
    {
        //qDebug() << "open file failed." << endl;
        QMessageBox::warning(this,QString::fromLocal8Bit("多文档编辑器"),
                             QString::fromLocal8Bit("无法写入文件&1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    return true;
}


void MdiChild::closeEvent(QCloseEvent *event)
{
    if(mabeSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}


bool MdiChild::mabeSave()
{
    if(document()->isModified())
    {
        QMessageBox box;
        box.setWindowTitle(QString::fromLocal8Bit("多文档编辑器"));
        box.setText(QString::fromLocal8Bit("是否保存对“%1”的更改?")
                    .arg(userFriendlyCurrentFile()));
        box.setIcon(QMessageBox::Warning);

        QPushButton *yesBtn = box.addButton(QString::fromLocal8Bit("是"),QMessageBox::YesRole);
        box.addButton(QString::fromLocal8Bit("否"),QMessageBox::NoRole);

        QPushButton *cancelBtn = box.addButton(QString::fromLocal8Bit("取消"),QMessageBox::RejectRole);

        //弹出对话框
        box.exec();

        if(box.clickedButton() == yesBtn)
        {
            return save();
        }
        else if(box.clickedButton() == cancelBtn)
        {
            return false;
        }


    }

    //如果文档没有更改过，直接返回True
    return true;
}








