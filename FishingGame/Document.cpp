/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Document.h"
#include <QJsonDocument>
#include <QFile>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QMessageBox>

Document::Document(QObject* parent)
    : QObject(parent),
    fishes(),
    lures(),
    currentBoat(),
    currentFishes(),
    currentLure(),
    hookedFish(),
    waterLine(7.0f),
    userCurrentMoney(100),
    userFishBucket(),
    initialNumberOfFish(5){
    loadFromJson("://image/InitData.json");

    connect(&currentBoat, &Boat::armChanged, this, [this](int armX) {
        if (this->getCurrentLure()) { // Ensure the current lure exists
            this->updateCurrentLurePosition(armX, *this->getCurrentLure()->getPosY());
        } else {
            // "No current lure to update!"
        }
    });
}

bool Document::loadFromJson(const QString& filePath) {
    clearDocument();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    if (jsonData.isEmpty()) {
        qWarning() << "File is empty or failed to read:" << filePath;
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return false;
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "JSON document is not an object.";
        return false;
    }
    QJsonObject json = jsonDoc.object();

    // Load Fishes
    if (json.contains("fishes") && json["fishes"].isArray()) {
        QJsonArray fishArray = json["fishes"].toArray();
        loadAllFishes(fishArray);
    } else {
        qWarning() << "Fishes data missing or invalid.";
    }
     populateCurrentFish();

    // Load Lures
    if (json.contains("lures") && json["lures"].isArray()) {
        QJsonArray lureArray = json["lures"].toArray();
        loadAllLures(lureArray);
    } else {
        qWarning() << "Lures data missing or invalid.";
    }

    populateCurrentFish(); // Randomly chooses initialNumberOfFish of available fish to put into currentFishes

    // Load Current Boat
    if (json.contains("currentBoat") && json["currentBoat"].isObject()) {
        currentBoat.fromJson(json["currentBoat"].toObject());
    } else {
        qWarning() << "Current Boat data missing or invalid.";
    }

    // Load array of current fish
    if (json.contains("currentFishes") && json["currentFishes"].isArray()) {
        QJsonArray fishArray = json["currentFishes"].toArray();
        for (const QJsonValue& fishes : fishArray) {
            std::shared_ptr<Fish> fish = std::make_shared<Fish>();
            fish->fromJson(fishes.toObject());
            currentFishes.push_back(fish);
        }
    } else {
        qWarning()<<"current fish data missing or invalid.";
    }

    // Load current lure
    if (json.contains("currentLure") && json["currentLure"].isObject()) {
        QJsonObject lureJson = json["currentLure"].toObject();
        currentLure.fromJson(lureJson);
    } else {
        qWarning()<<"current lure data missing or invalid.";
    }

    // Load waterLine
    if (json.contains("waterLine") && json["waterLine"].isDouble()) {
        double waterLineJson = json["waterLine"].toDouble();
        waterLine = static_cast<float>(waterLineJson);
    } else {
        qWarning()<<"waterLine data missing or invalid.";
    }

    // Load userCurrentMoney
    if (json.contains("userCurrentMoney") && json["userCurrentMoney"].isDouble()) {
        userCurrentMoney = json["userCurrentMoney"].toInt();
    } else {
        qWarning()<<"User current money data missing or invalid.";
    }

    // Load userFishBucket
    if (json.contains("userFishBucket") && json["userFishBucket"].isObject()) {
        QJsonObject fishBucketJson = json["userFishBucket"].toObject();
        userFishBucket.clear();  // Clear the current bucket before loading
        for (auto it = fishBucketJson.begin(); it != fishBucketJson.end(); ++it) {
            QString fishName = it.key();
            int fishCount = it.value().toInt();
            userFishBucket[fishName] = fishCount;  // Add fish name and count to the map
        }
    } else {
        qWarning() << "User fish bucket data missing or invalid.";
        userFishBucket.clear();
    }

    return true;
}

// Setters & Getters
QVector<std::shared_ptr<Fish>> Document::getAllCurrFish() {
    return currentFishes;
}

void Document::addFishToCurrFish(std::shared_ptr<Fish> fish) {
    currentFishes.append(fish);
}

void Document::removeFishFromCurrFish(QString name) {
    for (auto it = currentFishes.begin(); it != currentFishes.end(); ) {
        if ((*it)->getName() == name) {
            it = currentFishes.erase(it);  // Remove the pointer from the list and update the iterator
        } else {
            ++it;  // Move to the next item
        }
    }
}

void Document::setCurrentLure(QString& targetName) {
    bool found = false;

    for (Lure* lure : lures) {
        if (*lure->getName() == targetName) {
            currentLure = *lure; // Set the matching Lure
            found = true;

            // Emit signal with new lure properties
            emit lureChanged(
                *lure->getDensity(),
                *lure->getFriction(),
                *lure->getRestitution(),
                currentBoat.getArmLocation());
            break;
        }
    }

    if (!found) {
        qWarning() << "Failed to set current lure. Lure with name" << targetName << "not found!";
    }
}

Lure* Document::getCurrentLure() {
     return &currentLure;
}

void Document::setCurrentBoat(Boat& boat) {
    currentBoat = boat;
}

Boat* Document::getcurrentBoat() {
    return &currentBoat;
}

void Document::setHookedFish(std::shared_ptr<Fish> fish) {
    hookedFish = *fish;
    emit updateScrapbook();
}

std::shared_ptr<Fish> Document::getHookedFish() {
    return std::make_shared<Fish>(hookedFish);
}

float Document::getWaterLine() const {
    return waterLine;  // Return the water level managed by Water
}

QVector<std::shared_ptr<Fish>> Document::getCurrentFishes() const{
    return currentFishes;  // Return the list of fish managed by Water
}

void Document::addOneFishToUserFishBucket(QString* fishName) {
    if (fishName && !fishName->isEmpty()) {  // Check if fishName is valid
        QString fishKey = *fishName;  // Dereference the QString pointer to get the name

        if (userFishBucket.contains(fishKey)) {
            userFishBucket[fishKey] += 1;  // Increment count if fish exists
        } else {
            userFishBucket[fishKey] = 1;  // Add fish with an initial count of 1
        }

    } else {
        qWarning() << "Invalid fish name. No fish added.";
    }
}

QMap<QString,int> Document::getUserFishBucket() {
    return userFishBucket;
}

Boat* Document::getcurrBoat() {
    return &currentBoat;
}

QJsonObject Document::saveToJson() const {
    QJsonObject json;

    // Save Fishes
    QJsonArray fishArray;
    for (const std::shared_ptr<Fish> &fish : fishes) {
        if (fish) {
            fishArray.append(fish->toJson());
        }
    }
    json["fishes"] = fishArray;

    // Save Lures
    QJsonArray lureArray;
    for (const Lure* lure : lures) {
        if (lure) {
            lureArray.append(lure->toJson());
        }
    }
    json["lures"] = lureArray;


    // Save Current Boat
    json["currentBoat"] = currentBoat.toJson();

    // Save CurrentFishes
    QJsonArray currentFishArray;
    for (const std::shared_ptr<Fish> &fish : currentFishes) {
        if (fish) {
            currentFishArray.append(fish->toJson());
        }
    }
    json["currentFishes"] = currentFishArray;

    // Save CurrentLure
    json["currentLure"] = currentLure.toJson();

    // Save hookedFish
    json["hookedFish"] = hookedFish.toJson();

    // WaterLine
    json["waterLine"] = waterLine;

    // Money
    json["userCurrentMoney"] = userCurrentMoney;

    // Fish Bucket
    QJsonObject fishBucket;
    for (auto it = userFishBucket.cbegin(); it != userFishBucket.cend(); ++it) {
        fishBucket[it.key()] = it.value();  // Add each fish name and count to the JSON object
    }
    json["userFishBucket"] = fishBucket;

    return json;
}

void Document::clearDocument() {
    fishes.clear();

    qDeleteAll(lures);  // Deletes all Lure* in the QVector
    lures.clear();

    // Reset pointers
    currentFishes.clear();  // Do NOT delete these, they should be part of `fishes`
    userFishBucket.clear();

    // Reset current objects to safe defaults
    currentLure = Lure();
    hookedFish = Fish();
    currentBoat = Boat();
}

void Document::loadAllFishes(const QJsonArray &jsonArray) {
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            std::shared_ptr<Fish> fish = std::make_shared<Fish>();
            fish->fromJson(value.toObject());
            fishes.append(fish);
        }
    }
}

void Document::loadAllLures(const QJsonArray &jsonArray) {
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            Lure* lure = new Lure();
            lure->fromJson(value.toObject());
            lures.append(lure);
        }
    }
}

// Other setter and getter methods
void Document::addFish(std::shared_ptr<Fish> fish) {
    fishes.append(fish);
}

void Document::removeFish(QString name) {
    for (auto it = fishes.begin(); it != fishes.end(); ) {
        if ((*it)->getName() == name) {
            it = fishes.erase(it);  // Remove the pointer from the list and update the iterator
        } else {
            ++it;  // Move to the next item
        }
    }
}

QVector<std::shared_ptr<Fish>> Document::getAllFish() const {
    return fishes;
}

std::shared_ptr<Fish> Document::getRandomFish() const {
    if (fishes.isEmpty()) {
        return nullptr;
    }

    int randomIndex = QRandomGenerator::global()->bounded(fishes.size()); // Random index in range [0, fishes.size() - 1]
    return fishes[randomIndex];
}

void Document::addLure(Lure* lure) {
    lures.append(lure);
}

void Document::removeLure(QString name) {
    for (auto it = lures.begin(); it != lures.end();) {
        QString* lureName = (*it)->getName(); // Assuming getName() returns a QString*
        if (lureName && *lureName == name) {  // Dereference the pointer to compare the value
            delete *it; // Free the memory of the Lure object
            it = lures.erase(it); // Remove the pointer from the list and update the iterator
        } else {
            ++it; // Move to the next item
        }
    }
}

QVector<Lure*> Document::getAllLures() const {
    return lures;
}

Lure* Document::getOneLure(QString name) const {
    for (auto it = lures.begin(); it != lures.end(); ++it) {
        QString* lureName = (*it)->getName(); // Assuming getName() returns a QString*
        if (lureName && *lureName == name) {
            return *it; // Dereference the iterator to get the actual Lure*
        }
    }
    return nullptr; // Return nullptr if no match is found
}

void Document::populateCurrentFish() {
    for (int count = 0; count < initialNumberOfFish; count++) {
        // Retrieve new fish:
        std::shared_ptr<Fish> newFish = getRandomFish();

        // Set fish swimming direction:
        newFish->setSwimmingDirection(QRandomGenerator::global()->bounded(0, 2));

        // Allocate fish random speed:
        newFish->setSpeed(QRandomGenerator::global()->bounded(1, 2));

        // Calculate fish swimming depth:
        float scale = 30.0f;
        float waterLineY = 650 - waterLine * scale;
        int minY = waterLineY + 10;
        int waterDepthArea = (650 - minY) / 3;

        switch(newFish->getSwimmingDepth()) {
            case WaterLevel::SURFACE:
                newFish->setPosX(QRandomGenerator::global()->bounded(300, 800));
                newFish->setPosY(QRandomGenerator::global()->bounded(300, 434)); // 400
                qDebug() << "Fish Swimming Surface";
                break;
            case WaterLevel::MIDWATER:
                newFish->setPosX(QRandomGenerator::global()->bounded(300, 800));
                newFish->setPosY(QRandomGenerator::global()->bounded(434, 535)); // 500
                qDebug() << "Fish Swimming Mid Water";
                break;
            case WaterLevel::DEEPWATER:
                newFish->setPosX(QRandomGenerator::global()->bounded(300, 800));
                newFish->setPosY(QRandomGenerator::global()->bounded(535, 636)); // 600
                qDebug() << "Fish Swimming Deep Water";
                break;
        }

        addFishToCurrFish(newFish);
    }
}

// Rule Of Three:
Document::Document(const Document& otherDocument) {
    for(std::shared_ptr<Fish> otherFish : otherDocument.fishes) {
        std::shared_ptr<Fish> newFish = std::make_shared<Fish>(*otherFish);
        fishes.append(newFish);
    }

    for(Lure* otherLure : otherDocument.lures) {
        Lure* newLure = new Lure(*otherLure);
        lures.append(newLure);
    }

    currentBoat = otherDocument.currentBoat;
}

Document& Document::operator=(Document otherDocument) {
    std::swap(fishes, otherDocument.fishes);
    std::swap(lures, otherDocument.lures);
    std::swap(currentBoat, otherDocument.currentBoat);

    return *this;
}

Document::~Document() {
    // Delete all the lures in lures:
    for(Lure* lure: lures) {
        delete lure;
    }

    currentFishes.clear();
    userFishBucket.clear();
    fishes.clear();
    lures.clear();
}

// Writes JSON to file
bool Document::saveToFile() {
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save Data", "", "JSON Files (*.json)");

    // Convert object to JSON
    QJsonObject json = saveToJson();

    // Convert to JSON document
    QJsonDocument jsonDoc(json);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(jsonDoc.toJson());
    file.close();

    return true;
}

bool Document::loadFromFile() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Load Data", "", "JSON Files (*.json)");

    if (filePath.isEmpty()) {
        qWarning() << "No file selected; user canceled the operation.";
        return false;
    }

    qWarning() << "Attempting to load JSON file: " << filePath;

    if (loadFromJson(filePath)) {
        QMessageBox::information(nullptr, "Load", "File loaded successfully.");
        qWarning() << "JSON file loaded successfully: " << filePath;
        return true;
    } else {
        qWarning() << "Failed to load JSON file: " << filePath;
        QMessageBox::warning(nullptr, "Load", "Failed to load file.");
        return false;
    }
}

void Document::updateCurrentLurePosition(int x, int y) {
    currentLure.setPosX(x);
    currentLure.setPosY(y);
    emit lureUpdated(x, y);  // Notify listeners of the new position
}

std::shared_ptr<Fish> Document::getOneFish(const QString& fishName) {
    for (std::shared_ptr<Fish> fish : fishes) {  // Simplified loop
        if (fish->getName() == fishName) {
            return fish;
        }
    }
    return nullptr;  // Return nullptr if no matching fish is found
}
