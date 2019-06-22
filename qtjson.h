#ifndef JSON_H
#define JSON_H

#include <QVariant>
#include <QString>

namespace QtJson
{
    typedef QVariantMap JsonObject;
    typedef QVariantList JsonArray;

    QVariant parse(const QString &json);
    QVariant parse(const QString &json, bool &success);
    QByteArray serialize(const QVariant &data);
    QByteArray serialize(const QVariant &data, bool &success);
    QString serializeStr(const QVariant &data);
    QString serializeStr(const QVariant &data, bool &success);
    void setDateTimeFormat(const QString& format);
    void setDateFormat(const QString& format);
    QString getDateTimeFormat();
    QString getDateFormat();
}

#endif //JSON_H
