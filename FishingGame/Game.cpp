/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Game.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>
#include <QPainterPath>
#include <cmath>
#include "Document.h"

// Constructor: Initializes the Box2D world and game objects
Game::Game(QWidget *parent, Document* documentInstance)
    : QWidget(parent),
    world(b2Vec2(0.0f, -10.0f)), // Initialize the Box2D world with gravity (-10 m/s²)
    throwableBody(nullptr),
    groundBody(nullptr),
    isDragging(false),
    targetDepth(3.0f),
    isInWater(false),
    document(documentInstance) {

    // Water level set to Y = 7.0
    waterLine=document->getWaterLine();

    // Create the throwable object (e.g., a lure)
    createThrowableBody();

    setLureStartPosition(document->getcurrBoat()->getArmLocation().x()/30.0f,document->getcurrBoat()->getArmLocation().y()/30.0f);

    // Timer to update the physics simulation at ~60 FPS
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        if (!isDragging) {                   // Only update the physics when the object is not being dragged
            world.Step(1.0f / 60.0f, 6, 2);  // Step the physics simulation forward by 1/60th of a second
            updateLureInWater();             // Stop the lure at the target depth
            emit stateChanged();             // Notify Drawing of any state changes
        }
    });
    timer->start(16);  // 16 milliseconds per update (60 FPS)

    QTimer *fishMovementTimer = new QTimer(this);
    connect(fishMovementTimer, &QTimer::timeout, this, [this]() {
        if (isSettled) {
            fishChaseLure(throwableBody->GetPosition(), 9.0f);
        } else {
            fishNormalMovement();
        }
    });
    fishMovementTimer->start(16);

    // Connect lureChanged signal to updateLureProperties slot
    connect(document, &Document::lureChanged, this, &Game::updateLureProperties);

    connect(document, &Document::lureUpdated, this, [this](int x, int y) {
        setLureStartPosition(x/30.0f, y/30.0f);
        emit stateChanged();  // Notify the Drawing class of the update
    });
}

// === Water Resistance, Target Depth, and Detection ===
void Game::updateLureInWater() {
    b2Vec2 position = throwableBody->GetPosition();

    // Detect when the lure enters or exits the water
    if (position.y <= waterLine && !isInWater) {
        isInWater = true;  // Mark the lure as in water
    } else if (position.y > waterLine && isInWater) {
        isInWater = false;  // Mark the lure as out of water
    }

    // Apply water resistance if the lure is in water
    if (isInWater) {
        applyWaterResistance();

        // Retrieves the target depth for the current lure
        WaterLevel* lureLevelPtr = document->getCurrentLure()->getLureDepth();

        if (lureLevelPtr) {
            WaterLevel lureLevel = *lureLevelPtr;  // Dereference the pointer
            float lureDepth = getDepthForWaterLevel(lureLevel);

            // Stop the lure if it reaches the target depth
            if (position.y <= waterLine - lureDepth) {
                stopLureAtDepth();
            }
        } else {
            qWarning() << "Error: Lure water level is null.";
        }
    }
}

// Applies water resistance to the lure
void Game::applyWaterResistance() {
    b2Vec2 velocity = throwableBody->GetLinearVelocity();

    // Apply different damping factors for horizontal and vertical motion
    float horizontalDamping = 0.9f;  // Slow down horizontal motion slightly
    float verticalDamping = 0.7f;    // Stronger damping for vertical motion

    b2Vec2 waterDampedVelocity (
        velocity.x * horizontalDamping,  // Reduce horizontal velocity
        velocity.y * verticalDamping     // Reduce vertical velocity
    );

    // Apply the new velocity to the lure
    throwableBody->SetLinearVelocity(waterDampedVelocity);

    // Optionally reduce angular velocity (spinning effect)
    float angularDamping = 0.8f;  // Damping for rotational motion
    float newAngularVelocity = throwableBody->GetAngularVelocity() * angularDamping;
    throwableBody->SetAngularVelocity(newAngularVelocity);
}

void Game::stopLureAtDepth() {
    if (throwableBody == nullptr) {
        return;
    }

    // Stop the lure's motion
    throwableBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    throwableBody->SetAngularVelocity(0.0f);  // Stop spinning
    throwableBody->SetGravityScale(0.0f);     // Neutralize gravity to keep it at the target depth

    // Signals fish to start chasing lure.
    isSettled = true;
}

// === Lure Position Handling ===
// Creates the throwable object (e.g., a Lure)
void Game::createThrowableBody() {
    // Define the throwable object's body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;                                                     // Initially kinematic to prevent free-fall
    bodyDef.position.Set(0.0f, document->getcurrentBoat()->getArmLocation().x()/30.0f);  // Default initial position
    throwableBody = world.CreateBody(&bodyDef);                                          // Add the body to the Box2D world

    // Define the shape of the throwable object as a rectangle
    b2PolygonShape shape;
    shape.SetAsBox(0.5f, 0.25f);  // Half-width = 0.5m, Half-height = 0.25m

    // Create a fixture to define the object's physical properties
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = *getLure()->getDensity();          // Density affects mass  Heavier objects (higher density)
    fixtureDef.friction = *getLure()->getFriction();        // Friction affects sliding
    fixtureDef.restitution = *getLure()->getRestitution();  // Restitution affects bounciness
    throwableBody->CreateFixture(&fixtureDef);              // Attach the fixture to the body
}

// Function to set the Lure's starting position
void Game::setLureStartPosition(float x, float y) {
    throwableBody->SetTransform(b2Vec2(x, y), 0.0f);  // Move the lure to the new position
    startingPosition.Set(x, y);                       // Update the starting position
}

b2Vec2 Game::getTrajectoryPoint(const b2Vec2& startPos, const b2Vec2& startVel, float step) const {
    // Time step (60 FPS)
    float t = 1.0f / 60.0f;

    // Calculate velocity and gravity per time step
    b2Vec2 stepVelocity = t * startVel;               // Velocity at each step
    b2Vec2 stepGravity = t * t * world.GetGravity();  // Gravity applied at each step

    // Use the physics formula to calculate the trajectory point
    return startPos + step * stepVelocity + 0.5f * (step * step + step) * stepGravity;
}

Boat* Game::getBoat() {
    return document->getcurrentBoat();  // Delegate to Water class
}

Lure* Game::getLure() {
    return document->getCurrentLure();  // Delegate to Water class
}

float Game::getWaterLine() const {
    return document->getWaterLine();  // Delegate to Water class
}

QVector<std::shared_ptr<Fish>> Game::getFishes() {
    return document->getCurrentFishes();  // Delegate to Water class
}

b2Vec2 Game::getStartingPosition() const {
    return startingPosition;
}

b2Vec2 Game::getInitialVelocity() const {
    return initialVelocity;
}

void Game::startDragging(const b2Vec2& dragStart) {
    if (lureState != LureState::Ready) {
        qWarning() << "Lure cannot be thrown. Current state:" << static_cast<int>(lureState);
        return;  // Do nothing if lure is not ready
    }

    this->dragStart = dragStart;                        // Record drag start position
    startingPosition = throwableBody->GetPosition();    // Record current object position
    isDragging = true;                                  // Set dragging state
    emit stateChanged();                                // Notify Drawing of state change
}

void Game::updateDragging(const b2Vec2& dragEnd) {
    this->dragEnd = dragEnd;                          // Update drag end position
    initialVelocity = 10.0f * (dragEnd - dragStart);  // Calculate velocity based on drag
    emit stateChanged();                              // Notify Drawing of state change
}


void Game::stopDragging() {
    if (!isDragging) return;

    if (lureState != LureState::Ready) {
        return;
    }

    isDragging = false;                                 // Clear dragging state
    throwableBody->SetType(b2_dynamicBody);             // Make the body dynamic
    throwableBody->SetLinearVelocity(initialVelocity);  // Apply calculated velocity
    throwableBody->SetGravityScale(1.0f);               // Reset gravity to its default value
    dragStart.SetZero();                                // Reset drag start
    dragEnd.SetZero();                                  // Reset drag end

    lureState = LureState::InWater;  // Change state to InWater
    emit stateChanged();             // Notify Drawing of state change
    emit lureThrown();               // Notify View to disable key press
}

bool Game::isDraggingLure() const {
    return isDragging;
}

b2Body* Game::getThrowableBody() const {
    return throwableBody;
}

bool Game::checkCollision(b2Vec2 fishScreenPosition, float lureRadius) {
    b2Vec2 fishWorldPosition(fishScreenPosition.x / 30.0f, (height() + fishScreenPosition.y) / 30.0f);
    b2Vec2 lurePosition(throwableBody->GetPosition().x, throwableBody->GetPosition().y);

    // Calculate distance in Box2D world coordinates
    float distance = b2Distance(fishWorldPosition, lurePosition);

    return distance <= (lureRadius * 30.0f + 500);
};

// All fish swim towards lure according to weight
void Game::fishChaseLure(const b2Vec2 lurePosition, float lureRadius) {
    for (std::shared_ptr<Fish> fish : document->getCurrentFishes()) {

        b2Vec2 fishPosition (fish->getPosX() / 30.0f, (height() - fish->getPosY()) / 30.0f);
        b2Vec2 direction = lurePosition - fishPosition;

        float distance = direction.Length();
        if (distance <= lureRadius) {  // Only move fish within the lure's radius of influence
            direction.Normalize();
            fish->setPosX(fish->getPosX() + (direction.x * fish->getSpeed()));
            fish->setPosY(fish->getPosY() + (direction.y * fish->getSpeed()));

            b2Vec2 updatePosition(fish->getPosX() / 30.0f, (height() - fish->getPosY()) / 30.0f);
            if (checkCollision(updatePosition, lureRadius)) {
                // Stash fish to scrapbook:
                QString fishName = fish->getName();
                document->addOneFishToUserFishBucket(&fishName);
                document->setHookedFish(fish);
                document->removeFishFromCurrFish(fish->getName());
                lureState = LureState::Hooked;

                // Reset lure and Reset Hooked Fish:
                resetLure();
                emit stateChanged();  // Notify Drawing to update

                // Popup display of the Caught Fish:
                emit fishCaught();
                document->setHookedFish(std::make_shared<Fish>());
                break;
            }
        } else {
            // Do normal fish movement if it is not within lure's radius:
            if (fish->getSwimmingDirection()) {
                // Check if fish is within bounds:
                if (fish->getPosX() < 1100) {
                    fish->setPosX(fish->getPosX() + fish->getSpeed());
                } else {
                    fish->toggleSwimmingDirection();
                }
            } else {
                // Check if fish is within bounds:
                if (fish->getPosX() > 1) {
                    fish->setPosX(fish->getPosX() - fish->getSpeed());
                } else {
                    fish->toggleSwimmingDirection();
                }
            }
        }
    }
    if (document->getCurrentFishes().size() == 0) {
        document->populateCurrentFish();
    }
    emit stateChanged();
}

// Should be called in intervals to move the fish incrementally while bait has not settled.
void Game::fishNormalMovement() {
    for (std::shared_ptr<Fish> fish : document->getCurrentFishes()) {
        // Fish Swimming Right-Direction:
        if (fish->getSwimmingDirection()) {

            // Check if fish is within bounds:
            if (fish->getPosX() < 1100) {
                fish->setPosX(fish->getPosX() + fish->getSpeed());
            } else {
                fish->toggleSwimmingDirection();
            }
        } else { // Fish Swimming Left-Direction:
            // Check if fish is within bounds:
            if (fish->getPosX() > 1) {
                fish->setPosX(fish->getPosX() - fish->getSpeed());
            } else {
                fish->toggleSwimmingDirection();
            }
        }
    }
    emit stateChanged();
}

// Update lure properties
void Game::updateLureProperties(float density, float friction, float restitution,QPoint armLocation) {
    // Update throwableBody's fixture if it exists
    if (throwableBody) {
        // Remove old fixture
        b2Fixture* fixture = throwableBody->GetFixtureList();
        while (fixture) {
            b2Fixture* nextFixture = fixture->GetNext();
            throwableBody->DestroyFixture(fixture);
            fixture = nextFixture;
        }

        // Define new fixture with updated properties
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.25f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        throwableBody->CreateFixture(&fixtureDef);
    }
}

LureState Game::getLureState() const {
    return lureState;
}

void Game::resetLure() {
    // Reset the lure and set state back to Ready
    setLureStartPosition(document->getcurrBoat()->getArmLocation().x() / 30.0f, document->getcurrBoat()->getArmLocation().y() / 30.0f);

    throwableBody->SetType(b2_kinematicBody);              // Make the lure kinematic to stop falling
    throwableBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));  // Stop any movement
    throwableBody->SetGravityScale(0.0f);                  // Neutralize gravity for kinematic body

    isSettled = false;
    lureState = LureState::Ready;  // Set state to Ready

    emit stateChanged();  // Notify Drawing to update
    emit lureReset();     // Notify View to enable key press
}

float Game::getDepthForWaterLevel(WaterLevel level) {
    switch (level) {
        case WaterLevel::SURFACE:
            return 1.0f;      // Surface depth
        case WaterLevel::MIDWATER:
            return 7.0f;      // Midwater depth
        case WaterLevel::DEEPWATER:
            return 14.0f;     // Deepwater depth
        default:
            return 8.0f;      // Default to surface depth
    }
}


