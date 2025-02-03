/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef BOAT_H
#define BOAT_H

#include <QObject>
#include <QWidget>
#include <QImage>

///
/// \brief The Boat class models a boat object in the application. It provides name and position in QPoint and
/// allows the user to move the boat in the horizontal x-axis.
///
class Boat : public QWidget {
    Q_OBJECT

public:
    // Default constructor for Boat class:
    Boat();

    // Constructor with all fields
    Boat(const QString &name,
         const QString &imagePath,
         int boatX,
         int boatY,
         const QPoint &armLocation);

    ///
    /// \brief getArmLocation - Retrieves the arm's location on the boat as a QPoint from which the lure is thrown.
    /// \return A QPoint - Representing the x and y coordinates of the arm location, which remains fixed relative to the boat.
    ///
    QPoint getArmLocation();

    ///
    /// \brief setArmLocation - Sets the arm's location relative to the boat from which the lure is thrown.
    /// \param location - The x and y position of the arm location as a QPoint.
    ///
    void setArmLocation(QPoint location);

    ///
    /// \brief setImage - Updates the boat's image.
    /// \param imagePath - The filepath to the boat image.
    ///
    void setImage(QString imagePath);

    ///
    /// \brief getImage - Retrieves the current image of the boat.
    /// \return A QImage object representing the boat's image.
    ///
    QImage getImage();

    ///
    /// \brief setBoatX - Sets the x-coordinate of the boat's position.
    /// \param xPos - The x-coordinate value to set.
    ///
    void setBoatX(int xPos);

    ///
    /// \brief getBoatx - Retrieves the x-coordinate of the boat's position.
    /// \return - The current x-coordinate of the boat.
    ///
    int getBoatx();

    ///
    /// \brief setBoaty - Sets the y-coordinate of the boat's position.
    /// \param yPos - The y-coordinate value to set.
    ///
    void setBoaty(int yPos);

    ///
    /// \brief getBoaty - Retrieves the y-coordinate of the boat's position.
    /// \return - The current y-coordinate of the boat.
    ///
    int getBoaty();

    ///
    /// \brief toJson - Serializes the boat's state to a JSON object.
    /// \return - A QJsonObject representing the boat's state.
    ///
    QJsonObject toJson() const;

    ///
    /// \brief fromJson - Deserializes the boat's state from a JSON object.
    /// \param json - A QJsonObject containing the boat's state data.
    ///
    void fromJson(const QJsonObject &json);

    // Rule Of Three:
    ///
    /// \brief Boat - Copy constructor for the Boat class. Creates a new boat by copying the
    /// state of another boat.
    /// \param otherBoat - The boat object to be copied.
    ///
    Boat(const Boat& otherBoat);

    ///
    /// \brief operator= - Assignment operator for the Boat class. Assigns the state of another Boat object to this one.
    /// \param otherBoat - The Boat object to copy from.
    /// \return - A reference to this Boat object.
    ///
    Boat& operator=(Boat otherBoat);

    ///
    /// Destructor for the Boat class. Cleans up resources associated with the Boat object.
    ///
    ~Boat();

private:
    QString name;           // The name of the boat.
    QImage image;           // The image respresentation of the boat.
    QString imagePath;      // The filepath to the boat's image.
    int boatX;              // The x-coordinate of the boat's position.
    int boatY;              // The y-coordinate of the boat's position.
    QPoint armLocation;     // The fixed location relative to the boat where the lure is cast.

signals:
    ///
    /// \brief stateChanged - Emits a signal when the boat's position has changed.
    ///
    void stateChanged();

    ///
    /// \brief armChanged - Emits when the arm location has changed.
    /// \param x - The new x-position of the arm location.
    ///
    void armChanged(int x);

};

#endif // BOAT_H
