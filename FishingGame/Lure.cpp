/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Lure.h"
#include <QBuffer>
#include <QByteArray>
#include <QDebug>

// Default Constructor
Lure::Lure()
    :name(""),
    description(""),
    lureDepth(WaterLevel::SURFACE),
    posX(0),
    posY(0) {
    image = QImage("://image/testLure.png");
}

// Overloaded Constructor
Lure::Lure(const QString &name, const QString &description, const QImage &image, WaterLevel lureDepth, int posX, int posY)
    : name(name),
    description(description),
    image(image),
    lureDepth(lureDepth),
    posX(posX),
    posY(posY) {};

void Lure::setImage(QString& imagePath) {
    image = QImage(imagePath);
}

QImage* Lure::getImage() {
    return &image;
}

void Lure::setDescription(QString& newDescription) {
    description = newDescription;
}

QString* Lure::getDescription() {
    return &description;
}

void Lure::setName(QString& newName) {
    name = newName;
}

QString* Lure::getName() {
    return &name;
}

void Lure::setPosX(int& newX) {
    posX = newX;
}

int* Lure::getPosX() {
    return &posX;
}

void Lure::setPosY(int& newY) {
    posY = newY;
}

int* Lure::getPosY() {
    return &posY;
}

QString* Lure::getImagePath() {
    return &imagePath;
}

void Lure::setLureDepth(WaterLevel& newDepth) {
    lureDepth = newDepth;
}

WaterLevel* Lure::getLureDepth() {
    return &lureDepth;
}

float* Lure::getDensity() {
    return &density;
}

float* Lure::getFriction() {
    return &friction;
}

float* Lure::getRestitution() {
    return &restitution;
}

// Convert Lure to JSON
QJsonObject Lure::toJson() const {
    QJsonObject json;

    json["name"] = name;
    json["description"] = description;
    json["imagePath"] = imagePath;
    json["lureDepth"] = static_cast<int>(lureDepth);  // Assuming WaterLevel is an enum
    json["posX"] = posX;
    json["posY"] = posY;
    json["density"] = density;
    json["friction"] = friction;
    json["restitution"] = restitution;

    return json;
}

// Populate Lure from JSON
void Lure::fromJson(const QJsonObject &json) {
    if (json.contains("name") && json["name"].isString()) {
        name = json["name"].toString();
    }

    if (json.contains("description") && json["description"].isString()) {
        description = json["description"].toString();
    }

    if (json.contains("imagePath") && json["imagePath"].isString()) {
        imagePath = json["imagePath"].toString();
        setImage(imagePath);
    }

    if (json.contains("lureDepth") && json["lureDepth"].isDouble()) {
        lureDepth = static_cast<WaterLevel>(json["lureDepth"].toInt());
    }

    if (json.contains("posX") && json["posX"].isDouble()) {
        posX = json["posX"].toInt();
    }

    if (json.contains("posY") && json["posY"].isDouble()) {
        posY = json["posY"].toInt();
    }

    if (json.contains("density") && json["density"].isDouble()) {
        density = static_cast<float>(json["density"].toDouble());
    }

    if (json.contains("friction") && json["friction"].isDouble()) {
        friction = static_cast<float>(json["friction"].toDouble());
    }

    if (json.contains("restitution") && json["restitution"].isDouble()) {
        restitution = static_cast<float>(json["restitution"].toDouble());
    }
}

bool Lure::operator<(const Lure& other) const {
    // Compare based on name first
    if (name != other.name) {
        return name < other.name;
    }

    // If names are equal, compare based on lureDepth
    if (lureDepth != other.lureDepth) {
        return lureDepth < other.lureDepth;
    }

    // If lureDepth is also equal, compare based on position (x, then y)
    if (posX != other.posX) {
        return posX < other.posX;
    }

    if(density != other.density){
        return density < other.density;
    }

    if(friction != other.friction){
        return friction < other.friction;
    }

    if(restitution != other.restitution){
        return restitution < other.restitution;
    }

    return posY < other.posY; // Final comparison
}

// Rule Of Three:
Lure::Lure(const Lure& otherLure) {
    name = otherLure.name;
    description = otherLure.description;
    image = otherLure.image;
    imagePath = otherLure.imagePath;
    lureDepth = otherLure.lureDepth;
    posX = otherLure.posX;
    posY = otherLure.posY;
    density = otherLure.density;
    friction = otherLure.friction;
    restitution = otherLure.restitution;
}

Lure& Lure::operator=(Lure otherLure) {
    std::swap(name, otherLure.name);
    std::swap(description, otherLure.description);
    std::swap(image, otherLure.image);
    std::swap(imagePath, otherLure.imagePath);
    std::swap(lureDepth, otherLure.lureDepth);
    std::swap(posX, otherLure.posX);
    std::swap(posY, otherLure.posY);
    std::swap(density, otherLure.density);
    std::swap(friction, otherLure.friction);
    std::swap(restitution, otherLure.restitution);

    return *this;
}

Lure::~Lure() {
    // Nothing to destruct.
}


