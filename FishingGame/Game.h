/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QPixmap>
#include <QTimer>
#include "Boat.h"
#include "Lure.h"
#include "Fish.h"
#include "Document.h"

///
/// \brief The LureState enum - Represents the different states of the Lure.
///
enum class LureState {
    Ready,       // Lure is ready to be thrown
    InWater,     // Lure is in water, waiting for a fish or reset
    Hooked,      // A fish has caught the lure
    Resetting    // Lure is being reset
};

///
/// \brief The Game class handles the physics simulation and rendering of the game.
///
class Game : public QWidget {
    Q_OBJECT

public:
    ///
    /// \brief Game - Constructor for Game class.
    /// \param parent - The parent widget.
    /// \param document - A pointer to the Document object (default is nullptr).
    ///
    explicit Game(QWidget *parent = nullptr, Document* document = nullptr);  // Constructor

    // Setter and Getters
    ///
    /// \brief getBoat - Retrieves the Boat object.
    /// \return A pointer to the Boat object.
    ///
    Boat* getBoat();

    ///
    /// \brief getLure - Retrieves the Lure object.
    /// \return A pointer to the Lure object.
    ///
    Lure* getLure() ;

    ///
    /// \brief getWaterLine - Retrieves the water line level.
    /// \return The water line level as a float.
    ///
    float getWaterLine() const ;

    ///
    /// \brief getFishes - Retrieves the list of Fish objects.
    /// \return A QVector of shared pointers to Fish objects.
    ///
    QVector<std::shared_ptr<Fish>> getFishes() ;

    // Setter function to modify the lure's starting position
    ///
    /// \brief setLureStartPosition - Sets the starting position of the lure.
    /// \param x - The x-coordinate of the starting position.
    /// \param y - The y-coordinate of the starting position.
    ///
    void setLureStartPosition(float x, float y);

    // Setter function to modify the ground's position
    ///
    /// \brief setGroundPosition Sets the position of the ground.
    /// \param x1 - The x-coordinate of the first point of the ground.
    /// \param y1 - The y-coordinate of the first point of the ground.
    /// \param x2 - The x-coordinate of the second point of the ground.
    /// \param y2 - The y-coordinate of the second point of the ground.
    ///
    void setGroundPosition(float x1, float y1, float x2, float y2);

    ///
    /// \brief getStartingPosition - Retrieves the starting position of the lure.
    /// \return A b2Vec2 representing the starting position.
    ///
    b2Vec2 getStartingPosition() const;

    ///
    /// \brief getInitialVelocity - Retrieves the initial velocity of the lure.
    /// \return A b2Vec2 representing the initial velocity.
    ///
    b2Vec2 getInitialVelocity() const;

    ///
    /// \brief getTrajectoryPoint - Calculates a point in the trajectory of the lure.
    /// \param startPos - The starting position of the trajectory.
    /// \param startVel - The starting velocity of the trajectory.
    /// \param step - The step size for trajectory calculation.
    /// \return A b2Vec2 representing the calculated point in the trajectory.
    ///
    b2Vec2 getTrajectoryPoint(const b2Vec2& startPos, const b2Vec2& startVel, float step) const;

    ///
    /// \brief getThrowableBody  - Retrieves the Lure represented as the throwable object.
    /// \return A pointer to the b2Body representing the throwable object.
    ///
    b2Body* getThrowableBody() const;

    ///
    /// \brief startDragging - Starts dragging the lure.
    /// \param dragStart - The starting point of the drag (mouse press).
    ///
    void startDragging(const b2Vec2& dragStart);

    ///
    /// \brief updateDragging - Updates the drag position.
    /// \param dragEnd - The ending point of the drag (mouse release).
    ///
    void updateDragging(const b2Vec2& dragEnd);

    ///
    /// \brief stopDragging - Stops dragging the lure.
    ///
    void stopDragging();

    ///
    /// \brief isDraggingLure - Checks if the lure is currently being dragged.
    /// \return True if the lure is being dragged, false otherwise.
    ///
    bool isDraggingLure() const;

    ///
    /// \brief fishChaseLure - Makes a fish chase the lure.
    /// \param lurePosition - The position of the lure.
    /// \param lureRadius - The radius of the lure.
    ///
    void fishChaseLure(const b2Vec2 lurePosition, float lureRadius);

    ///
    /// \brief fishNormalMovement - Handles the movement of the fish.
    ///
    void fishNormalMovement();

    ///
    /// \brief checkCollision - Checks if the fish collides with the lure.
    /// \param fishScreenPosition - The screen position of the fish.
    /// \param lureRadius - The radius of the lure.
    /// \return True if a collision is detected, false otherwise.
    ///
    bool checkCollision(b2Vec2 fishScreenPosition, float lureRadius);

    ///
    /// \brief getLureState - Retrieves the current state of the lure.
    /// \return The current LureState.
    ///
    LureState getLureState() const;

    ///
    /// \brief resetLure - Resets the lure to its ready state.
    ///
    void resetLure();

    ///
    /// \brief screenToWorld - Converts screen coordinates to world coordinates.
    /// \param screenX - The x-coordinate on the screen.
    /// \param screenY - The y-coordinate on the screen.
    /// \return The world coordinates as a b2Vec2.
    ///
    b2Vec2 screenToWorld(int screenX, int screenY);

    ///
    /// \brief worldToScreen - Converts world coordinates to screen coordinates.
    /// \param worldPos - The world position as a b2Vec2.
    /// \return The screen position as a QPoint.
    ///
    QPoint worldToScreen(b2Vec2 worldPos);

private:
    b2World world;                                              // The Box2D world where physics simulation happens.
    b2Body* throwableBody;                                      // The throwable object (e.g., a lure).
    b2Body* groundBody;                                         // The static ground object.
    b2Vec2 startingPosition;                                    // Starting position of the throwable object.
    b2Vec2 initialVelocity;                                     // Initial velocity when the object is thrown.
    b2Vec2 dragStart;                                           // Starting point of the drag (mouse press).
    b2Vec2 dragEnd;                                             // Ending point of the drag (mouse release).
    QPixmap lureImage;                                          // Image to represent the lure.
    bool isDragging;                                            // Flag to check if the user is currently dragging.
    void createThrowableBody();                                 // Function to create the throwable object.
    void createGround(float x1, float y1, float x2, float y2);  // Function to create the static ground.

    // Helper methods to calculate the trajectory points
    float waterLine;             // Water level line.
    float targetDepth;           // Target depth where the lure will stop.
    void updateLureInWater();    // Updates Water resistance of lure.
    void applyWaterResistance(); // Applies water resistance.
    void stopLureAtDepth();      // Stops the lure at specified depth.
    bool isInWater;              // Determines if lure is in water.
    bool isSettled = false;      // Determines if Lure is settled in water.

    QTimer fishMovementTimer;                // Timer for controlling the fish's movement.
    Document* document;                      // Manage water-related logic (boat, lure, fish, etc.)
    LureState lureState = LureState::Ready;  // Initialize LureState to Ready.

    // Helper method to convert waterlevel to float
    float getDepthForWaterLevel(WaterLevel level); // Retrieves the water level as a float.

signals:
    ///
    /// \brief stateChanged - Emits when the game state changes.
    ///
    void stateChanged();

    ///
    /// \brief lureReset - Signals to reset the lure.
    ///
    void lureReset();

    ///
    /// \brief lureThrown - Signals that the lure has been thrown.
    ///
    void lureThrown();

    ///
    /// \brief fishCaught - Signals that a fish has been caught.
    ///
    void fishCaught();

    ///
    /// \brief updateScrapbook - Signals to update the scrapbook.
    ///
    void updateScrapbook();

public slots:
    ///
    /// \brief updateLureProperties - Updates the properties of the lure.
    /// \param density - The density of the lure.
    /// \param friction - The friction of the lure.
    /// \param restitution - The restitution (bounce) of the lure.
    /// \param armLocation - The location of the arm used to throw the lure.
    ///
     void updateLureProperties(float density, float friction, float restitution,QPoint armLocation);

};

#endif // GAME_H
