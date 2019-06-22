#ifndef ESPENDATA_H
#define ESPENDATA_H

#include <defines.h>

class espendata : public QObject
{
    Q_OBJECT
public:
    espendata();
    void downloadEspenData();
    void read(const QJsonObject json);
    void readJsonFile();
    QMap<QString, QString> dataFinal;

signals:
    void dataArrive(QMap<QString, QString>);
};

#endif // ESPENDATA_H
