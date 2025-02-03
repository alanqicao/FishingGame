/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef JSONCONVERT_H
#define JSONCONVERT_H

#include <QObject>

///
/// \brief The JsonConvert class provides utility functions for converting
/// various Qt types (such as QImage, QPoint, and QMap) to JSON format and vice versa.
/// This allows for easy serialization and deserialization of Qt objects.
///
class JsonConvert {

public:
    ///
    /// \brief Default constructor for the JsonConvert class.
    ///
    JsonConvert();

    ///
    /// \brief convertQImageToJson - Converts a QImage object to a QJsonObject.
    /// \param image - The QImage to be converted.
    /// \return A QJsonObject representing the image.
    ///
    static QJsonObject convertQImageToJson(const QImage &image);

    ///
    /// \brief convertJsonToQImage - Converts a JSON representation of an image (via image path) back to a QImage object.
    /// \param imagePath - The path to the image file (represented as a QString).
    /// \return A QImage object created from the given path.
    ///
    static QImage convertJsonToQImage(const QString &imagePath);

    ///
    /// \brief convertQPointToJson - Converts a QPoint object to a QJsonObject.
    /// \param point - The QPoint to be converted.
    /// \return A QJsonObject representing the point.
    ///
    static QJsonObject convertQPointToJson(const QPoint &point);

    ///
    /// \brief convertJsonToQPoint - Converts a QJsonObject representing a point back into a QPoint object.
    /// \param json - The QJsonObject representing the point.
    /// \return A QPoint object created from the JSON data.
    ///
    static QPoint convertJsonToQPoint(const QJsonObject &json);

    ///
    /// \brief convertQMapToJson - Converts a QMap object with QString keys and int values to a QJsonArray.
    /// \param map - The QMap to be converted.
    /// \return A QJsonArray representing the key-value pairs in the map.
    ///
    static QJsonArray convertQMapToJson(const QMap<QString, int> &map);

    ///
    /// \brief convertJsonToQMap - Converts a QJsonArray representing key-value pairs back into a QMap object.
    /// \param jsonArray - The QJsonArray containing the key-value pairs.
    /// \return A QMap with QString keys and int values, created from the JSON data.
    ///
    static QMap<QString, int> convertJsonToQMap(const QJsonArray &jsonArray);

};

#endif // JSONCONVERT_H
