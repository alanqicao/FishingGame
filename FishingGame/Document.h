/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include "Lure.h"
#include "Fish.h"
#include "Boat.h"

///
/// \brief The Document class is responsible for managing the fishing game data, including the fish,
/// lures, and boat state. It handles adding, removing, and retrieving fish and lures, as well as
/// saving and loading game data from JSON files. This class serves as the central model for
/// managing the game's state and its functionalities.
///
class Document : public QObject {
    Q_OBJECT

public:
    ///
    /// \brief Document - The constructor for Document class.
    /// \param parent - The parent class.
    ///
    explicit Document(QObject* parent = nullptr);

    ///
    /// \brief addFish - Adds a fish to a QVector of fishes.
    /// \param fish - The fish to add.
    ///
    void addFish(std::shared_ptr<Fish> fish);

    ///
    /// \brief removeFish - Removes a fish from a QVector of fishes.
    /// \param name - The name of the fish in which to remove.
    ///
    void removeFish(QString name);

    ///
    /// \brief getOneFish - Retrieves a fish by its name.
    /// \param fishName - The name of the fish to retrieve.
    /// \return A shared pointer to the fish object.
    ///
    std::shared_ptr<Fish> getOneFish(const QString& fishName);

    ///
    /// \brief getAllFish - Retrieves all the fish.
    /// \return A QVector of shared pointers to all fish.
    ///
    QVector<std::shared_ptr<Fish>> getAllFish() const;

    ///
    /// \brief getRandomFish - Retrieves a random fish.
    /// \return A shared pointer to a random fish.
    ///
    std::shared_ptr<Fish> getRandomFish() const;

    ///
    /// \brief loadAllFishes - Loads all fish data from a JSON array.
    /// \param jsonArray - The JSON array containing fish data.
    ///
    void loadAllFishes(const QJsonArray &jsonArray);

    ///
    /// \brief addLure - Adds a lure.
    /// \param lure - The lure to add.
    ///
    void addLure(Lure* lure);

    ///
    /// \brief removeLure - Removes a lure by its name.
    /// \param name - The name of the lure to be removed.
    ///
    void removeLure(QString name);

    ///
    /// \brief getAllLures - Retrieves all  the lures.
    /// \return A QVector of pointers to all lures.
    ///
    QVector<Lure*> getAllLures() const;

    ///
    /// \brief getOneLure - Retrieves a lure by its name.
    /// \param name - The name of the lure to retrieve.
    /// \return A pointer to the lure object.
    ///
    Lure* getOneLure(QString name) const;

    ///
    /// \brief loadAllLures - Loads all lure data from a JSON array.
    /// \param jsonArray - The JSON array containing lure data.
    ///
    void loadAllLures(const QJsonArray &jsonArray);

    ///
    /// \brief setCurrentBoat - Sets the current boat for the game.
    /// \param boat - The boat to set as the current boat.
    ///
    void setCurrentBoat(Boat& boat);

    ///
    /// \brief getcurrentBoat - Retrieves the current boat in the game.
    /// \return A pointer to the current boat.
    ///
    Boat* getcurrentBoat();

    ///
    /// \brief setcurrentFishes - Sets the current fishes in the game.
    ///
    void setcurrentFishes(QVector<std::shared_ptr<Fish>>);

    ///
    /// \brief getCurrentFishes - Retrieves the current fishes in the game.
    /// \return A QVector of shared pointers to the current fishes.
    ///
    QVector<std::shared_ptr<Fish>> getCurrentFishes() const;

    ///
    /// \brief setCurrentLure - Sets the current lure by name.
    /// \param targetName - The name of the target lure to set.
    ///
    void setCurrentLure(QString& targetName);

    ///
    /// \brief getCurrentLure - Retrieves the current lure in the game.
    /// \return A pointer to the current lure.
    ///
    Lure* getCurrentLure();

    ///
    /// \brief updateCurrentLurePosition - Updates the current lure position.
    /// \param x - The new x position of the lure.
    /// \param y - The new y position of the lure.
    ///
    void updateCurrentLurePosition(int x, int y);

    ///
    /// \brief setHookedFish - Sets the hooked fish.
    /// \param fish A shared pointer to the fish that has been hooked.
    ///
    void setHookedFish(std::shared_ptr<Fish> fish);// set hookedFish = null and check if water is empty: add new set of fish to water

    ///
    /// \brief getHookedFish - Retrieves the hooked fish.
    /// \return A shared pointer to the currently hooked fish.
    ///
    std::shared_ptr<Fish> getHookedFish();

    ///
    /// \brief loadFromJson - Loads game data from a JSON file.
    /// \param filePath - The path to the JSON file to load.
    /// \return True if the data was loaded successfully.
    ///
    bool loadFromJson(const QString& filePath);

    ///
    /// \brief saveToJson - Saves the current game data to a JSON object.
    /// \return A JSON object representing the current game data.
    ///
    QJsonObject saveToJson() const;

    // Clear data
    ///
    /// \brief clearDocument - Clears the document by removing all fish, lures, and other data.
    ///
    void clearDocument();

    // Setters and Getters
    ///
    /// \brief getAllCurrFish
    /// \return
    ///
    QVector<std::shared_ptr<Fish>> getAllCurrFish();

    ///
    /// \brief addFishToCurrFish - Adds a fish to the current list of fish.
    /// \param fish A shared pointer to the fish to add.
    ///
    void addFishToCurrFish(std::shared_ptr<Fish> fish);

    ///
    /// \brief removeFishFromCurrFish - Removes a fish from the current list of fish by its name.
    /// \param name The name of the fish to remove.
    ///
    void removeFishFromCurrFish(QString name);

    ///
    /// \brief setCurrBoat - Sets the current boat for the game.
    /// \param boat - The boat to set as the current boat.
    ///
    void setCurrBoat(Boat& boat);

    ///
    /// \brief getcurrBoat - Retrieves the current boat.
    /// \return A pointer to the current boat.
    ///
    Boat* getcurrBoat();

    ///
    /// \brief setWaterLine - Sets the water line value.
    ///
    void setWaterLine();

    ///
    /// \brief getWaterLine - Retrieves the water line value.
    /// \return The water line height (surface level).
    ///
    float getWaterLine() const;

    ///
    /// \brief addOneFishToUserFishBucket - Adds a fish to the user's fish bucket.
    /// \param fishName - The name of the fish to add.
    ///
    void addOneFishToUserFishBucket(QString* fishName);

    ///
    /// \brief getUserFishBucket - Retrieves the user's fish bucket as a map of fish names and quantities.
    /// \return A QMap of fish names and quantities.
    ///
    QMap<QString,int> getUserFishBucket();

    ///
    /// \brief addOneLureToUserLureBox - Adds a lure to the user's lure box.
    /// \param lure - A pointer to the lure to add.
    ///
    void addOneLureToUserLureBox(Lure* lure);

    ///
    /// \brief getUserLureBox - Retrieves the user's lure box.
    /// \return A QVector of lures in the user's lure box.
    ///
    QVector<Lure*> getUserLureBox();

    ///
    /// \brief toJson - Converts the document data into a JSON object for saving.
    /// \return A JSON object representing the document data.
    ///
    QJsonObject toJson() const;

    ///
    /// \brief fromJson - Loads data from a JSON object.
    /// \param json - The JSON object containing the data to load.
    ///
    void fromJson(const QJsonObject& json);

    ///
    /// \brief populateCurrentFish - Populates the current fish.
    ///
    void populateCurrentFish();

    // Rule Of Three:
    ///
    /// \brief Document - Copy constructor for the Document class.
    /// \param otherDocument - Another document to copy from.
    ///
    Document(const Document& otherDocument);

    ///
    /// \brief operator= - Assignment operator for the Document class.
    /// \param otherDocument - Another document to assign from.
    /// \return A reference to this document.
    ///
    Document& operator=(Document otherDocument);

    ///
    /// Destructor for the Document class.
    ~Document();

    // Load and Save Data
    ///
    /// \brief saveToFile - Saves the current game state to a file.
    /// \return True if the file was saved successfully.
    ///
    bool saveToFile();

    ///
    /// \brief loadFromFile - Loads the game state from a file.
    /// \return True if the file was loaded successfully.
    ///
    bool loadFromFile();

signals:
    ///
    /// \brief lureChanged - Emits when lure is updated.
    /// \param density - The density of the lure.
    /// \param friction - The friction of the lure.
    /// \param restitution - The restitution of the lure.
    /// \param armLocation - The location of the arm on the boat.
    ///
    void lureChanged(float density, float friction, float restitution, QPoint armLocation);

    ///
    /// \brief lureUpdated - Emitted when the lure's position is updated.
    /// \param x - The new x position of the lure.
    /// \param y - The new y position of the lure.
    ///
    void lureUpdated(int x, int y);

    ///
    /// \brief updateScrapbook - Emitted when the scrapbook needs to be updated.
    ///
    void updateScrapbook();

private:
    QVector<std::shared_ptr<Fish>> fishes;          // QVector of all fishes in game world.
    QVector<Lure*> lures;                           // QVector of all lures in game world.
    Boat currentBoat;                               // Object of the current boat.
    QVector<std::shared_ptr<Fish>> currentFishes;   // QVector of current fishes in water.
    Lure currentLure;                               // Object of the current lure.
    Fish hookedFish;                                // Object of caught fish or null.
    float waterLine;                                // Where waterline (surface) begins.
    int userCurrentMoney;                           // User's current money.
    QMap<QString, int> userFishBucket;              // Represents user's caught fish in the scrabook
    int initialNumberOfFish;                        // The initial number of fish in the water.

};

#endif // DOCUMENT_H
