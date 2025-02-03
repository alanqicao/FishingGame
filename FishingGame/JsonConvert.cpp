/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "JsonConvert.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QBuffer>
#include <QByteArray>
#include <QImage>

JsonConvert::JsonConvert() {
}

QImage JsonConvert::convertJsonToQImage(const QString &imagePath) {
    QImage image(imagePath);
    if (imagePath == "") {
        return QImage();
    }
    if (image.isNull()) {
        qWarning()<<"Failed to load image from JSON data.";
    };

    return image;
}

QPoint JsonConvert::convertJsonToQPoint(const QJsonObject &json) {
    if (!json.contains("x") || !json.contains("y")) {
        qWarning()<< "Invalid QPoint JSON data.";
        return QPoint(0,0);
    }

    int x = json["x"].toInt();
    int y = json["y"].toInt();

    return QPoint(x,y);
}

QJsonObject JsonConvert::convertQPointToJson(const QPoint &point) {
    QJsonObject jsonObject;
    jsonObject["x"] = point.x();
    jsonObject["y"] = point.y();

    return jsonObject;
}

// Convert QMap<Lure, int> to JSON
QJsonArray JsonConvert::convertQMapToJson(const QMap<QString, int> &map) {
    QJsonArray jsonArray;
    for (auto it = map.begin(); it != map.end(); ++it) {
        QJsonObject entry;
        entry["LureName"] = it.key();  // Assuming Lure has a toJson() function
        entry["weight"] = it.value();
        jsonArray.append(entry);
    }

    return jsonArray;
}

// Convert JSON to QMap<Lure, int>
QMap<QString, int> JsonConvert::convertJsonToQMap(const QJsonArray &jsonArray) {
    QMap<QString, int> map;

    for (const QJsonValue &value : jsonArray) {
        if (!value.isObject()) {
            qWarning() << "JSON array element is not an object.";
            continue; // Skip invalid elements
        }
        QJsonObject entry = value.toObject();

        // Extract "LureName" as a QString
        QString lureName = entry["LureName"].toString();
        if (lureName.isEmpty()) {
            qWarning() << "LureName is missing or empty.";
            continue;
        }

        // Extract "weight" as an int
        int weight = entry["weight"].toInt();

        // Insert into the QMap
        map.insert(lureName, weight);
    }

    return map;
}
