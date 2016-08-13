#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QPushButton>
#include <QFileDialog>
#include <QCloseEvent>
#include <QString>

class MdiChild : public QTextEdit
{
    Q_OBJECT

public:
    explicit MdiChild(QWidget *parent = 0);
    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();   //���ļ�·������ȡ���ļ���
    QString currentFile(){ return curFile;}

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void documentWasModified();     //�ĵ�������ʱ��������ʾ����״̬��־

private:
    bool mabeSave();   //�����Ƿ���Ҫ����Ի���
    void setCurrentFile(const QString &fileName);

    QString curFile;     //��ǰ�ļ�·��
    bool  isUntitled;  //�ļ��Ƿ񱻱����ŵ�Ӳ����
};
#endif // MDICHILD_H
