/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef DRAWING_H
#define DRAWING_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "Game.h"

///
/// \brief The Drawing class handles rendering the game's graphical interface.
/// It interacts with the game state to visually represent the current state of
/// the game, for example, the fishes, lures, and boat. The class uses QPainter
/// to draw the graphical elements to the screen, and it is responsible for
/// updating the view whenever needed.
///
class Drawing : public QWidget {
    Q_OBJECT

public:
    ///
    /// \brief Drawing - Constructor for the Drawing class.
    /// \param gameContext -  A pointer to the Game object, which holds the game state and logic.
    /// \param parent - The parent QWidget.
    ///
    explicit Drawing(Game* gameContext, QWidget* parent = nullptr);

    ///
    /// \brief update - Custom update function for drawing the world.
    ///
    void update();

protected:
    ///
    /// \brief paintEvent - Overridden to handle custom drawing.
    /// \param event - The event object that updates the area that needs to be repainted.
    ///
    void paintEvent(QPaintEvent* event) override;

private:
    Game* game; // Pointer to the game context for accessing game state.

};

#endif // DRAWING_H
