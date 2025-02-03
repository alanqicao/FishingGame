/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef FISH_H
#define FISH_H

#include <QObject>
#include <QMap>
#include <QImage>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QPoint>
#include <QVector>
#include <QString>
#include "WaterLevel.h"

///
/// \brief The Fish class represents a fish object in the game, storing its attributes and behaviors.
/// It includes properties such as the fish's position, image, description, swimming depth, speed, and facts.
/// This class also provides functionality for serializing and deserializing the fish object using JSON.
///
class Fish {

public:
    ///
    /// \brief Fish - Default constructor for Fish class.
    ///
    Fish();

    ///
    /// \brief Fish - Constructor with parameters to initialize the fish with specific values.
    /// \param name - The name of the fish.
    /// \param imagePath - The path to the fish's image file.
    /// \param description - A description of the fish.
    /// \param lureToWeight - A map that associates lure names with the fish's attraction (weighted).
    /// \param swimmingDepth - The depth at which the fish swims.
    /// \param posX - The X coordinate of the fish's position.
    /// \param posY - The Y coordinate of the fish's position.
    ///
    Fish(const QString &name,
         QString imagePath,
         const QString &description,
         const QMap<QString, int> &lureToWeight,
         WaterLevel swimmingDepth,
         int posX,
         int posY);

    ///
    /// \brief getFishPosition - Gets the position of the fish.
    /// \return A QPoint representing the fish's position.
    ///
    QPoint getFishPosition();

    ///
    /// \brief setFishPosition - Sets the position of the fish.
    /// \param newPosition - The new position of the fish as a QPoint.
    ///
    void setFishPosition(QPoint newPosition);

    ///
    /// \brief getfishFacts - Gets a list of facts about the fish.
    /// \return A vector of strings containing fish facts.
    ///
    QVector<QString>* getfishFacts();

    ///
    /// \brief setSwimmingDepth - Sets the swimming depth of the fish.
    /// \param depth The new swimming depth.
    ///
    void setSwimmingDepth(WaterLevel);

    ///
    /// \brief getSwimmingDepth - Gets the swimming depth of the fish.
    /// \return The current swimming depth of the fish.
    ///
    WaterLevel getSwimmingDepth() const;

    ///
    /// \brief setName - Sets the name of the fish.
    /// \param fishName - The new name of the fish.
    ///
    void setName(QString);

    ///
    /// \brief getName - Gets the name of the fish.
    /// \return The name of the fish.
    ///
    QString getName() const;

    ///
    /// \brief setImage - Sets the image of the fish given the filepath.
    /// \param path The path to the fish's image file.
    ///
    void setImage(QString);

    ///
    /// \brief getImage - Gets the image of the fish.
    /// \return The QImage representing the fish's image.
    ///
    QImage getImage() const;

    ///
    /// \brief Sets the description of the fish.
    /// \param fishDescription The new description of the fish.
    ///
    void setDecription(QString fishDescription);

    ///
    /// \brief Gets the description of the fish.
    /// \return The description of the fish.
    ///
    QString getDecription() const;

    ///
    /// \brief addLureToWeight -  Adds a lure name and weight to the fish's lure-to-weight map.
    /// \param lureName - The name of the lure.
    /// \param weight - The weight associated with the lure.
    ///
    void addLureToWeight(const QString &lureName, int weight);

    ///
    /// \brief removeLureToWeight - Removes a lure from the fish's lure-to-weight map.
    /// \param lureName - The name of the lure to be removed.
    ///
    void removeLureToWeight(const QString &lureName);

    ///
    /// \brief setPosX - Sets the X coordinate of the fish's position.
    /// \param x The new X coordinate of the fish.
    ///
    void setPosX(int x);

    ///
    /// \brief getPosX - Gets the X coordinate of the fish's position.
    /// \return The X coordinate of the fish's position.
    ///
    int getPosX() const;

    ///
    /// \brief setPosY - Sets the Y coordinate of the fish's position.
    /// \param y - The new Y coordinate of the fish.
    ///
    void setPosY(int);

    ///
    /// \brief getPosY - Gets the Y coordinate of the fish's position.
    /// \return The Y coordinate of the fish's position.
    ///
    int getPosY() const;

    ///
    /// \brief setSpeed - Sets the speed of the fish.
    ///
    void setSpeed(int);

    ///
    /// \brief getSpeed - Gets the speed of the fish.
    /// \return The speed of the fish.
    ///
    int getSpeed() const;

    ///
    /// \brief setWaterLevel - Sets the water level at which the fish swims.
    /// \param level The new water level.
    ///
    void setWaterLevel(WaterLevel);

    ///
    /// \brief getWaterLevel - Gets the water level at which the fish swims.
    /// \return The water level at which the fish swims.
    ///
    WaterLevel getWaterLevel() const;

    ///
    /// \brief toggleSwimmingDirection - Toggles the swimming direction of the fish.
    ///
    void toggleSwimmingDirection();

    ///
    /// \brief getSwimmingDirection - Gets the swimming direction of the fish.
    /// \return The swimming direction of the fish.
    ///
    bool getSwimmingDirection();

    ///
    /// \brief setSwimmingDirection - Sets the swimming direction of the fish.
    /// \param swimmingDirection - The new swimming direction.
    ///
    void setSwimmingDirection(bool swimmingDirection);

    ///
    /// \brief getFishFact - Gets a specific fact about the fish.
    /// \param index - The index of the fact.
    /// \return The fact at the specified index.
    ///
    QString getFishFact(int index) const;

    // Json Functionality
    ///
    /// \brief toJson - Converts the fish object to a JSON representation.
    /// \return A QJsonObject containing the fish's data.
    ///
    QJsonObject toJson() const;

    ///
    /// \brief fromJson - Initializes the fish object from a JSON representation.
    /// \param json - A QJsonObject containing the fish's data.
    ///
    void fromJson(const QJsonObject& json);

    // Rule Of Three:
    ///
    /// \brief Fish - Copy constructor for the Fish class.
    /// \param otherFish - The fish object to copy.
    ///
    Fish(const Fish& otherFish);

    ///
    /// \brief operator= - Assignment operator for the Fish class.
    /// \param otherFish - The fish object to assign.
    /// \return - A reference to this fish object.
    ///
    Fish& operator=(Fish otherFish);

    ///
    /// \brief Destructor for the Fish class.
    ~Fish();

private:
    QString name;                    // The name of the fish.
    QString imagePath;               // The path to the image of the fish.
    QImage image;                    // The image of the fish.
    QString description;             // The description of the fish.
    QMap<QString, int> lureToWeight; // A map associating lures with the fish's weight.
    WaterLevel swimmingDepth;        // The swimming depth of the fish.
    int posX;                        // The X coordinate of the fish's position.
    int posY;                        // The Y coordinate of the fish's position.
    int speed;                       // The speed of the fish.
    bool swimmingDirection;          // The swimming direction: False = Left, True = Right.
    QVector<QString> fishFacts;      // Stores the facts about the fish.

};

#endif // FISH_H
