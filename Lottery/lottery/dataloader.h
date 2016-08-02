#ifndef DATALOADER_H
#define DATALOADER_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class DataLoader : public QObject
{
    Q_OBJECT

public:
    enum DataFomat{
        Json,Binary
    };

    explicit DataLoader(QObject *parent = 0);
    bool load(DataFomat saveFormat);
    void output(QVector<QString>& vector);
signals:

public slots:
private:
    QJsonArray numberArray;
};

#endif // DATALOADER_H
