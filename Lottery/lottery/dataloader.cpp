#include "dataloader.h"
#include <QVector>
#include <QDebug>

DataLoader::DataLoader(QObject *parent) : QObject(parent)
{

}

bool DataLoader::load(DataFomat dataFormat)
{
    QFile loadFile(dataFormat == Json
              ? QStringLiteral("phoneNumbers.json")
              : QStringLiteral("phoneNumbers.dat"));

          if (!loadFile.open(QIODevice::ReadOnly)) {
              qWarning("Couldn't open save file.");
              return false;
          }

          QByteArray saveData = loadFile.readAll();

          QJsonDocument loadDoc(dataFormat == Json
              ? QJsonDocument::fromJson(saveData)
              : QJsonDocument::fromBinaryData(saveData));

          QJsonObject json = loadDoc.object();
          numberArray = json["phoneNumbers"].toArray();

          return true;
}

void DataLoader::output(QVector<QString>& vector)
{
    for (int levelIndex = 0; levelIndex < numberArray.size(); ++levelIndex) {
            QJsonObject person = numberArray[levelIndex].toObject();
            QString phone = person["phone"].toString();
            vector.push_back(phone);
            //qDebug() << phone << endl;
        }
}
