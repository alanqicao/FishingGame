/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef LURE_H
#define LURE_H

#include <QImage>
#include <QObject>
#include <QJsonObject>
#include <QString>
#include "WaterLevel.h"

///
/// \brief The Lure class represents a lure with a name, description, image representation,
/// and it's x and y coordinate, as well as it's depth.
///
class Lure {

public:
    ///
    /// \brief Default Constructor for Lure class.
    ///
    Lure();

    ///
    /// \brief Lure - Overloaded constructor for Lure class.
    /// \param name - The name of the lure.
    /// \param description - The description of the lure.
    /// \param image - The image of the lure.
    /// \param lureDepth - The depth at which the lure is most effective.
    /// \param posX - The X position of the lure.
    /// \param posY - The Y position of the lure.
    ///
    Lure(const QString &name,
         const QString &description,
         const QImage &image,
         WaterLevel lureDepth,
         int posX,
         int posY);

    ///
    /// \brief setImage - Sets the image of the lure.
    /// \param image - The image to set for the lure.
    ///
    void setImage(QString& image);

    ///
    /// \brief getImage - Gets the image associated with the lure.
    /// \return A pointer to the image of the lure.
    ///
    QImage* getImage();

    ///
    /// \brief getImagePath - Gets the file path of the image.
    /// \return The file path of the lure image.
    ///
    QString* getImagePath();

    ///
    /// \brief setDescription - Sets the description of the lure.
    /// \param string - The description to set for the lure.
    ///
    void setDescription(QString& string);

    ///
    /// \brief getDescription - Gets the description of the lure.
    /// \return A pointer to the description of the lure.
    ///
    QString* getDescription() ;

    ///
    /// \brief setName - Sets the name of the lure.
    /// \param name - The name to set for the lure.
    ///
    void setName(QString& name);

    ///
    /// \brief getName - Gets the name of the lure.
    /// \return A pointer to the name of the lure.
    ///
    QString* getName();

    ///
    /// \brief setPosX - Sets the X position of the lure.
    /// \param posX - The X position to set for the lure.
    ///
    void setPosX(int&);

    ///
    /// \brief getPosX - Gets the X position of the lure.
    /// \return A pointer to the X position of the lure.
    ///
    int* getPosX();

    ///
    /// \brief setPosY - Sets the Y position of the lure.
    /// \param posY - The Y position to set for the lure.
    ///
    void setPosY(int&);

    ///
    /// \brief getPosY - Gets the Y position of the lure.
    /// \return A pointer to the Y position of the lure.
    ///
    int* getPosY();

    ///
    /// \brief setLureDepth - Sets the depth of the lure where it is most effective.
    /// \param newDepth  - The new depth to set for the lure.
    ///
    void setLureDepth(WaterLevel& newDepth);

    ///
    /// \brief getLureDepth - Gets the depth of the lure.
    /// \return A pointer of the waterlevel in which the lure could be found.
    ///
    WaterLevel* getLureDepth();

    ///
    /// \brief getDensity - Gets the density of the lure.
    /// \return A pointer to the density of the lure.
    ///
    float* getDensity();

    ///
    /// \brief getFriction - Gets the friction of the lure.
    /// \return A pointer to the friction of the lure.
    ///
    float* getFriction();

    ///
    /// \brief getRestitution - Gets the restitution of the lure (bounciness).
    /// \return A pointer to the restitution of the lure.
    ///
    float* getRestitution();

    ///
    /// \brief toJson - Converts the lure object into a QJsonObject.
    /// \return The QJsonObject representation of the lure.
    ///
    QJsonObject toJson() const;

    ///
    /// \brief fromJson - Converts a QJsonObject into a lure object.
    /// \param json - The QJsonObject to convert.
    ///
    void fromJson(const QJsonObject& json);

    ///
    /// \brief operator< - Comparison operator to compare two lures.
    /// \param other - The other lure to compare to.
    /// \return True if the current lure is less than the other lure based on its name.
    ///
    bool operator<(const Lure& other) const;

    // Rule Of Three:
    ///
    /// \brief Lure - Copy constructor for the Lure class.
    /// \param otherLure - The other lure to copy from.
    ///
    Lure(const Lure& otherLure);

    ///
    /// \brief operator= - Assignment operator for the Lure class.
    /// \param otherLure - The lure to assign.
    /// \return - A reference to the current Lure object.
    ///
    Lure& operator=(Lure otherLure);

    ///
    /// \brief ~Lure - Destructor for the Lure class.
    ~Lure();

private:
    QString name;           // Name of the lure.
    QString description;    // Description of the lure.
    QImage image;           // Image of the lure.
    QString imagePath;      // File path to the image of the lure.
    WaterLevel lureDepth;   // Depth where the lure is effective.
    int posX;               // X position of the lure.
    int posY;               // Y position of the lure.
    float density;          // Density of the lure.
    float friction;         // Friction of the lure.
    float restitution;      // Restitution of the lure (bounciness).

};

#endif // LURE_H
