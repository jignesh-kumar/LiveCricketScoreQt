#include "espendata.h"

using QtJson::JsonObject;
using QtJson::JsonArray;

espendata::espendata()
{

}

void espendata::downloadEspenData()
{
    QByteArray jsonString = QString("'Host':\"www.espncricinfo.com\",'User-Agent':\"Mozilla/5.0 (X11; Linux) Firefox\",'Accept':\"text/html;q=0.9,*/*;q=0.8\",'Accept-Encoding':\"gzip,deflate\",'Cookie':\"\",'Connection':\"keep-alive\",'Cache-Control':\"max-age=0\"").toUtf8();
    QUrl reqUrl("http://api.espncricinfo.com/netstorage/summary.json");
    QNetworkRequest request;
    QSslConfiguration sslConfiguration(request.sslConfiguration());
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    
    request.setSslConfiguration(sslConfiguration);
    request.setUrl(reqUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    
    QEventLoop loop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    QNetworkReply* reply = manager->post(request, jsonString);
    loop.exec();

    int nHTTPReturnCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(nHTTPReturnCode != 200)
    {
        qDebug() << reply->errorString();
        qDebug() << nHTTPReturnCode;
    }
    
    QFile file("summary.json");
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug()<<"summary.json not write";
        return;
    }
    
    QTextStream out(&file);
    QByteArray bData = reply->readAll();
    out<<bData;
}
void espendata::read(const QJsonObject json)
{
    QMap<QString, QString> data;
    
    QStringList keys = json.keys();
    
    for(int i = 0; i<keys.count(); i++)
    {
        if(json[keys.at(i)].isObject())
        {
            QJsonObject npcObj = json[keys.at(i)].toObject();
            read(npcObj);
        }
        else if(json[keys.at(i)].isArray())
        {
            QJsonArray npcArray = json[keys.at(i)].toArray();
            for (int npcIndex = 0; npcIndex < npcArray.size(); ++npcIndex)
            {
                QJsonObject npcObject = npcArray[npcIndex].toObject();
                
                if(npcObject.isEmpty())
                {
                    QString key = QString::number(npcIndex);
                    QString value = npcArray.at(npcIndex).toString();
                    data.insert(key, value);
                }
                else
                {
                    read(npcObject);
                }
            }
        }
        else if(json[keys.at(i)].isString())
        {
            QString key = keys.at(i);
            QString value = json.value(json.keys().at(i)).toString();
            data.insert(key, value);
        }
    }
    
    if(!data.isEmpty())
    {
        emit dataArrive(data);
    }
}

void espendata::readJsonFile()
{
    QFile f("summary.json");
    if(f.open(QIODevice::ReadOnly))
    {
        QTextStream in(&f);
        QByteArray jsonData = in.readAll().toLatin1();
        QJsonParseError e;
        QJsonDocument d = QJsonDocument::fromJson(jsonData, &e);

        if(!d.isNull() && e.error == QJsonParseError::NoError)
        {
            read(d.object());
        }
        else
        {
            qDebug()<<"error = "<< e.errorString();
        }
        f.close();
        f.remove();
    }
    else
    {
        qDebug()<<"not open";
    }
}
