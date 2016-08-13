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
    QString userFriendlyCurrentFile();   //从文件路径中提取出文件名
    QString currentFile(){ return curFile;}

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void documentWasModified();     //文档被更改时，窗口显示更改状态标志

private:
    bool mabeSave();   //弹出是否需要保存对话框
    void setCurrentFile(const QString &fileName);

    QString curFile;     //当前文件路径
    bool  isUntitled;  //文件是否被保存着到硬盘上
};
#endif // MDICHILD_H
