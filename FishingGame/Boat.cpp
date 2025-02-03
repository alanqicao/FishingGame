/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Boat.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QBuffer>
#include <QByteArray>
#include <QImage>
#include "JsonConvert.h"

Boat::Boat()
    : name(""),
    imagePath("://image/testBoat.png"),
    boatX(0),
    boatY(0),
    armLocation(QPoint(0, 0)) {

    image = QImage(imagePath);
}

// Constructor with all fields
Boat::Boat(const QString &name,
           const QString &imagePath,
           int boatX,
           int boatY,
           const QPoint &armLocation)
    : name(name),
    imagePath(imagePath),
    boatX(boatX),
    boatY(boatY),
    armLocation(armLocation) {
    image = QImage(imagePath);
}

QJsonObject Boat::toJson() const {
    QJsonObject json;

    json["name"] = name;
    json["imagePath"] = imagePath;
    json["boatX"] = boatX;
    json["boatY"] = boatY;
    json["armLocation"] = JsonConvert::convertQPointToJson(armLocation);

    return json;
}

void Boat::fromJson(const QJsonObject &json){
    // Load name
    if (json.contains("name") && json["name"].isString()) {
        name = json["name"].toString();
    }

    // Load image
    if (json.contains("imagePath") && json["imagePath"].isString()) {
        imagePath = json["imagePath"].toString();
        setImage(imagePath);

    } else {
        image = QImage(); // Empty image
    }

    // Load boatX
    if (json.contains("boatX") && json["boatX"].isDouble()) {
        boatX = json["boatX"].toInt();
    } else {
        boatX = 0;
    }

    // Load boatY
    if (json.contains("boatY") && json["boatY"].isDouble()) {
        boatY = json["boatY"].toInt();
    } else {
        boatY = 0;
    }

    // Load QPoint
    if (json.contains("armLocation") && json["armLocation"].isObject()) {
        QJsonObject pointJson = json["armLocation"].toObject();
        armLocation = JsonConvert::convertJsonToQPoint(pointJson);
    } else {
        armLocation = QPoint(0,0);
    }
}

QPoint Boat::getArmLocation() {
    return armLocation;
}

void Boat::setArmLocation(QPoint location) {
    armLocation = location;
}

void Boat::setImage(QString imagePath) {
    image = QImage(imagePath);
}

QImage Boat::getImage() {
    return image;
}

void Boat::setBoatX(int xPos) {
    boatX = xPos;
    setArmLocation(QPoint(xPos+280, armLocation.y()));
    emit stateChanged();
    emit armChanged(armLocation.x());
}

int Boat::getBoatx() {
    return boatX;
}

void Boat::setBoaty(int yPos) {
    boatY = yPos;
}

int Boat::getBoaty() {
    return boatY;
}

// Rule Of Three:
Boat::Boat(const Boat& otherBoat) {
    name = otherBoat.name;
    image = otherBoat.image;
    imagePath = otherBoat.imagePath;
    boatX = otherBoat.boatX;
    boatY = otherBoat.boatY;
    armLocation = otherBoat.armLocation;
}

Boat& Boat::operator=(Boat otherBoat) {
    std::swap(name, otherBoat.name);
    std::swap(image, otherBoat.image);
    std::swap(imagePath, otherBoat.imagePath);
    std::swap(boatX, otherBoat.boatX);
    std::swap(boatY, otherBoat.boatY);
    std::swap(armLocation, otherBoat.armLocation);

    return *this;
}

Boat::~Boat() {
    // Nothing to destruct.
}

