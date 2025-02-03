/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Fish.h"
#include "JsonConvert.h"
#include <QRandomGenerator>
#include <QDebug>

Fish::Fish()
    : name(),
    imagePath(),
    image(),
    description(),
    lureToWeight(),
    swimmingDepth(),
    posX(),
    posY(),
    speed() {
    setSwimmingDirection(true);
}

Fish::Fish(const QString &name,
           QString imagePath,
           const QString &description,
           const QMap<QString, int> &lureToWeight,
           WaterLevel swimmingDepth,
           int posX,
           int posY)
    : name(name),
    imagePath(imagePath),
    image(QImage(imagePath)),
    description(description),
    lureToWeight(lureToWeight),
    swimmingDepth(swimmingDepth),
    posX(posX),
    posY(posY),
    speed(QRandomGenerator::global()->bounded(1, 3)) {
    setSwimmingDirection(true);
    fishFacts.push_back("");
    fishFacts.push_back("");
    fishFacts.push_back("");
}

// Json Functionality
QJsonObject Fish::toJson() const {
    QJsonObject json;

    json["name"] = name;
    json["description"] = description;
    json["imagePath"] = imagePath;
    json["swimmingDepth"] = static_cast<int>(swimmingDepth);  // Assuming WaterLevel is an enum
    json["posX"] = posX;
    json["posY"] = posY;
    json["lureToWeight"] = JsonConvert::convertQMapToJson(lureToWeight);
    json["speed"] = speed;

    // Convert QVector<QString> to QJsonArray
    QJsonArray factsArray;
    for (const QString& fact : fishFacts) {
        factsArray.append(fact);
    }
    json["fishFacts"] = factsArray;

    return json;
}

void Fish::fromJson(const QJsonObject &json) {
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

    if (json.contains("swimmingDepth") && json["swimmingDepth"].isDouble()) {
        swimmingDepth = static_cast<WaterLevel>(json["swimmingDepth"].toInt());
    }

    if (json.contains("posX") && json["posX"].isDouble()) {
        posX = json["posX"].toInt();
    }

    if (json.contains("posY") && json["posY"].isDouble()) {
        posY = json["posY"].toInt();
    }

    if (json.contains("lureToWeight") && json["lureToWeight"].isArray()) {
        lureToWeight = JsonConvert::convertJsonToQMap(json["lureToWeight"].toArray());
    }

    if (json.contains("speed") && json["speed"].isDouble()) {
        speed = json["speed"].toInt();
    }

    // Load fishFacts from QJsonArray
    if (json.contains("fishFacts") && json["fishFacts"].isArray()) {
        QJsonArray factsArray = json["fishFacts"].toArray();
        fishFacts.clear();  // Clear any existing data
        for (const QJsonValue& fact : factsArray) {
            if (fact.isString()) {
                fishFacts.append(fact.toString());
            }
        }
    }
}

QPoint Fish::getFishPosition() {
    return QPoint(posX, posY);
}

void Fish::setFishPosition(QPoint newPosition) {
    posX = newPosition.x();
    posY = newPosition.y();
}

void Fish::setSwimmingDepth(WaterLevel waterLevel) {
    swimmingDepth = waterLevel;
}

WaterLevel Fish::getSwimmingDepth() const {
    return swimmingDepth;
}

void Fish::setName(QString fishName) {
    name = fishName;
}

QString Fish::getName() const {
    if (this == nullptr) {
        return QString();
    }
    return name;
}

void Fish::setImage(QString imagePath) {
    image = QImage(imagePath);
}

QImage Fish::getImage() const {
    return image;
}

void Fish::setDecription(QString d) {
    description = d;
}

QString Fish::getDecription() const {
    return description;
}

void Fish::addLureToWeight(const QString &lureName, int weight) {
    lureToWeight.insert(lureName, weight);
}

void Fish::removeLureToWeight(const QString &lureName) {
    lureToWeight.remove(lureName);
}

void Fish::setPosX(int x) {
    posX = x;
}

int Fish::getPosX() const {
    return posX;
}

void Fish::setPosY(int y) {
    posY = y;
}

int Fish::getPosY() const {
    return posY;
}

void Fish::setSpeed(int s) {
    speed = s;
}

int Fish::getSpeed() const {
    return speed;
}

QVector<QString>* Fish::getfishFacts() {
    return &fishFacts;
}

void Fish::toggleSwimmingDirection() {
    swimmingDirection = !swimmingDirection;
    image.mirror(true, false);
}

// Only used for initial direction! Call toggle direction after
void Fish::setSwimmingDirection(bool newSwimmingDirection) {
    // Only modify if swimming direction is a new one:
    if (swimmingDirection != newSwimmingDirection) {
        swimmingDirection = newSwimmingDirection;
        image.mirror(true, false);
    }
}

bool Fish::getSwimmingDirection() {
    return swimmingDirection;
}

QString Fish::getFishFact(int index) const {
    if (index >= 0 && index < fishFacts.size()) {
        return fishFacts[index];
    }

    return "Information Not Provided.";
}

// Rule Of Three:
Fish::Fish(const Fish& otherFish) {
    name = otherFish.name;
    image = otherFish.image;
    imagePath = otherFish.imagePath;
    description = otherFish.description;
    lureToWeight = otherFish.lureToWeight;
    swimmingDepth = otherFish.swimmingDepth;
    posX = otherFish.posX;
    posY = otherFish.posY;
    speed = otherFish.speed;
    swimmingDirection = otherFish.swimmingDirection;
    fishFacts = otherFish.fishFacts;
}

Fish& Fish::operator=(Fish otherFish) {
    name = otherFish.name;
    image = otherFish.image;
    imagePath = otherFish.imagePath;
    description = otherFish.description;
    lureToWeight = otherFish.lureToWeight;
    swimmingDepth = otherFish.swimmingDepth;
    posX = otherFish.posX;
    posY = otherFish.posY;
    speed = otherFish.speed;
    swimmingDirection = otherFish.swimmingDirection;
    fishFacts = otherFish.fishFacts;

    return *this;
}

Fish::~Fish() {
    // Nothing to Destruct.
}

void Fish::setWaterLevel(WaterLevel waterLevel) {
    swimmingDepth = waterLevel;
}

WaterLevel Fish::getWaterLevel() const {
    return swimmingDepth;
}

