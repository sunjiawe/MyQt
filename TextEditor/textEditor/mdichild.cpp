#include "mdichild.h"

MdiChild::MdiChild(QWidget *parent)
    :isUntitled(true)
{
    //���Ӵ��ڹر�ʱ�����������Ķ���
    setAttribute(Qt::WA_DeleteOnClose);

}

void MdiChild::newFile()
{
    static int sequenceNumber = 1;
    isUntitled = true;

    curFile = QString::fromLocal8Bit("δ�����ĵ�%1.txt").arg(sequenceNumber++);

    setWindowTitle(curFile +"[*]" + QString::fromLocal8Bit(" - ���ĵ��༭��"));
    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));
}

bool MdiChild::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if( !file.open(QFile::ReadOnly | QFile::Text))
    {
        //qDebug() << "open file failed." << endl;
        QMessageBox::warning(this,QString::fromLocal8Bit("���ĵ��༭��"),
                             QString::fromLocal8Bit("�޷���ȡ�ļ�&1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);  //�����ʾΪ�ȴ�״̬
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    connect(document(),SIGNAL(contentsChanged()),
            this,SLOT(documentWasModified()));

    return true;

}

void MdiChild::documentWasModified()
{
    //QWidget�Դ��ĺ���
    //����ĵ���δ����ĸ��ģ���������[*]�ĵط���ʾ*��
    setWindowModified(document()->isModified());
}


//�����ص��ļ�·�����浽curFile��
void MdiChild::setCurrentFile(const QString &fileName)
{
    //canonicalFilePath()����ȡ��·���е�"."��".."
    curFile = QFileInfo(fileName).canonicalFilePath();

    isUntitled = false;
    document()->setModified(false);

    //���ڲ���ʵ�����ı�־
    setWindowModified(false);

    setWindowTitle(userFriendlyCurrentFile() + "[*]");

}

QString MdiChild::userFriendlyCurrentFile()
{
    return QFileInfo(curFile).fileName();
}


bool MdiChild::save()
{
    //�ж��ļ��Ƿ񱣴��
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
    QString fileName = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("���Ϊ"),curFile);

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
        QMessageBox::warning(this,QString::fromLocal8Bit("���ĵ��༭��"),
                             QString::fromLocal8Bit("�޷�д���ļ�&1:\n%2.")
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
        box.setWindowTitle(QString::fromLocal8Bit("���ĵ��༭��"));
        box.setText(QString::fromLocal8Bit("�Ƿ񱣴�ԡ�%1���ĸ���?")
                    .arg(userFriendlyCurrentFile()));
        box.setIcon(QMessageBox::Warning);

        QPushButton *yesBtn = box.addButton(QString::fromLocal8Bit("��"),QMessageBox::YesRole);
        box.addButton(QString::fromLocal8Bit("��"),QMessageBox::NoRole);

        QPushButton *cancelBtn = box.addButton(QString::fromLocal8Bit("ȡ��"),QMessageBox::RejectRole);

        //�����Ի���
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

    //����ĵ�û�и��Ĺ���ֱ�ӷ���True
    return true;
}








