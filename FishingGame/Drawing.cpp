/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Drawing.h"
#include "Game.h"
#include <QPainter>
#include <QPainterPath>

Drawing::Drawing(Game* gameContext, QWidget* parent)
    : QWidget(parent), game(gameContext) {

     // Redraw when Game changes state
     connect(game, &Game::stateChanged,this, &Drawing::update);
     connect(game->getBoat(), &Boat::stateChanged, this, &Drawing::update);
     connect(game, &Game::stateChanged, this, &Drawing::update);
}

void Drawing::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPixmap background(":/image/backGround.png"); // Load the image

    // Draw the image scaled to the widget size
    painter.drawPixmap(this->rect(), background);

    // Convert Box2D meters to pixels
    float scale = 30.0f;

    // === DRAW THE BOAT ===
    Boat* boat = game->getBoat();
    if (boat) {
        QImage boatImage = boat->getImage();
        QPixmap boatPixmap = QPixmap::fromImage(boatImage);  // Convert QImage to QPixmap

        float rectWidth  = 10.0f * scale;  // Width in pixels (2x half-width)
        float rectHeight = 5.0f * scale;  // Height in pixels (2x half-height)

        // Calculate the top-left corner of the rectangle
        QPointF topLeft (
            boat->getBoatx(),  // X coordinate of the top-left corner
            boat->getBoaty()  // Y coordinate of the top-left corner
        );

        // Draw the image
        painter.drawPixmap (
            QRectF(topLeft, QSizeF(rectWidth, rectHeight)).toRect(),  // Rectangle to draw the image
            boatPixmap  // Source image
        );
    }

    // === DRAW THE FISH ===
    QVector<std::shared_ptr<Fish>> fishes = game->getFishes();
    for (std::shared_ptr<Fish> fish : fishes) {
        QImage fishImage = fish->getImage();
        QPixmap fishPixmap = QPixmap::fromImage(fishImage);  // Convert QImage to QPixmap

        float rectWidth  = 5.0f * scale;  // Width in pixels (2x half-width)
        float rectHeight = 2.5f * scale;  // Height in pixels (2x half-height)

        // Calculate the top-left corner of the rectangle
        QPointF fishPosition (
            fish->getPosX(),  // X coordinate of the top-left corner
            fish->getPosY()  // Y coordinate of the top-left corner
        );

        // Draw the image
        painter.drawPixmap (
            QRectF(fishPosition, QSizeF(rectWidth, rectHeight)).toRect(),   // Rectangle to draw the image
            fishPixmap  // Source image
        );
    }

    // === DRAW THE LURE ===
    Lure* lure = game->getLure();  // Get the lure object from Game
    if (lure) {
        b2Vec2 position = game->getThrowableBody()->GetPosition(); // Lure's Box2D position
        QImage* lureImage = lure->getImage();  // Lure image
        QPixmap pixmap = QPixmap::fromImage(*lureImage);

        float rectWidth  = 1.0f * scale;  // Width in pixels (2x half-width)
        float rectHeight = 0.5f * scale;  // Height in pixels (2x half-height)

        // Calculate the top-left corner of the rectangle
        QPointF topLeft (
            position.x * scale - rectWidth / 2,  // X coordinate of the top-left corner
            height() - position.y * scale - rectHeight / 2  // Y coordinate of the top-left corner
        );

        // Draw the image
        painter.drawPixmap (
            QRectF(topLeft, QSizeF(rectWidth, rectHeight)).toRect(),  // Rectangle to draw the image
            pixmap  // Source image
        );
    }

    // === Draw the Lure State ===
    LureState state = game->getLureState();
    QString stateText;
    switch (state) {
        case LureState::Ready: stateText = "Lure Ready"; break;
        case LureState::InWater: stateText = "Fishing"; break;
        case LureState::Hooked: stateText = "Lure Hooked!"; break;
        case LureState::Resetting: stateText = "Resetting Lure"; break;
    }

    painter.setPen(Qt::black);
    painter.drawText(10, 20, stateText);  // Display state at the top-left corner

    // === DRAW THE FISHING LINE (DYNAMIC TENSION) ===
    painter.setPen(QPen(Qt::black, 2));  // Black line with thickness 2

    // Get the start and end points of the fishing line
    QPointF startPoint (
        game->getStartingPosition().x * scale,
        height() - game->getStartingPosition().y * scale
    );

    b2Vec2 lurePosition = game->getThrowableBody()->GetPosition();  // Use Box2D position
    QPointF endPoint (
        lurePosition.x * scale,
        height() - lurePosition.y * scale
    );

    // Calculate the distance between start and end points
    float distance = std::hypot(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y());

    // Adjust sag based on distance and velocity
    float maxSag = 50.0f;          // Maximum sag (pixels)
    float sagDivider = 5.0f;       // Controls how quickly sag increases with distance
    float sagFactor = std::min(maxSag, distance / sagDivider);

    float maxSpeed = 10.0f;                                                    // Speed at which the line becomes completely taut
    float lureSpeed = game->getThrowableBody()->GetLinearVelocity().Length();  // Lure's velocity
    float velocityFactor = std::max(0.1f, 1.0f - lureSpeed / maxSpeed);        // Scale sag by velocity
    float dynamicSag = sagFactor * velocityFactor;                             // Dynamic Sag

    // Control point for Bézier curve
    QPointF controlPoint (
        (startPoint.x() + endPoint.x()) / 2,              // Midpoint X
        (startPoint.y() + endPoint.y()) / 2 + dynamicSag  // Midpoint Y with sag
    );

    // Create a path for the curve
    QPainterPath path(startPoint);
    path.quadTo(controlPoint, endPoint);  // Add a quadratic Bézier curve
    painter.drawPath(path);               // Draw the fishing line

    // === DRAW TRAJECTORY (IF THROWING) ===
    if (game->isDraggingLure()) {
        painter.setPen(QPen(Qt::red, 2));

        b2Vec2 startPos = game->getStartingPosition();  // Retrieve starting position from Game
        b2Vec2 startVel = game->getInitialVelocity();

        // Retrieve initial velocity from Game
        for (int i = 0; i < 180; ++i) {
            b2Vec2 trajectoryPoint = game->getTrajectoryPoint(startPos, startVel, i);

            QPointF trajectoryPosition (
                trajectoryPoint.x * scale,
                height() - trajectoryPoint.y * scale
            );
            painter.drawPoint(trajectoryPosition);
        }
    }
}

// Inside Drawing::update
void Drawing::update() {
    QWidget::update();  // Call the base class update
}

