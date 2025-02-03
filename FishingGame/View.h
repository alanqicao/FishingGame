/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef VIEW_H
#define VIEW_H

#include "Document.h"
#include <QMainWindow>
#include <QKeyEvent>
#include "Game.h"
#include "Document.h"
#include "Wikidialog.h"
#include "Luresboxdialog.h"
#include "DialogCaughtFish.h"
#include "HelpDialog.h"
#include "Scrapbookdialog.h"
#include "DialogCaughtFish.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class View;
}
QT_END_NAMESPACE

///
/// \brief The View class represents the main window of the application and handles user interactions.
/// It provides the interface for displaying the game, allowing the user to interact with various UI elements.
///
class View : public QMainWindow {
    Q_OBJECT

public:
    ///
    /// \brief Constructor for the View class.
    /// \param game - Pointer to the Game object, which contains the game logic.
    /// \param document - Shared pointer to the Document object, which contains data management related to the game.
    /// \param popupLuresBox - Pointer to the LuresBoxDialog, a dialog for selecting lures.
    /// \param popupScrapbook - Pointer to the ScrapbookDialog, a dialog for displaying a scrapbook of the user's hooked fish.
    /// \param parent - The parent widget.
    ///
    explicit View(Game* game, Document* document, LuresBoxDialog* popupLuresBox, ScrapbookDialog* popupScrapbook, QWidget *parent = nullptr);  // Pass Game object here

    /// \brief Destructor for the View class.
    /// Cleans up the view and its resources.
    ~View();

    ///
    /// \brief setKeyPressEnabled - Method to enable or disable key press events.
    /// \param enabled - A boolean value indicating whether key press events should be enabled or not.
    ///
    void setKeyPressEnabled(bool enabled);  // Method to enable/disable key press events

protected:
    ///
    /// \brief keyPressEvent - Handles key press events.
    /// Function is called when a key is pressed in the main window, which handles specific keys.
    /// \param event - The key event data.
    ///
    void keyPressEvent(QKeyEvent* event) override;

    ///
    /// \brief mousePressEvent - Handles mouse press events.
    /// \param event - The mouse event data.
    ///
    void mousePressEvent(QMouseEvent* event) override;

    ///
    /// \brief mouseMoveEvent - Handles mouse move events.
    /// \param event - The mouse event data.
    ///
    void mouseMoveEvent(QMouseEvent* event) override;

    ///
    /// \brief mouseReleaseEvent -Handles mouse release events.
    /// \param event - The mouse event data.
    ///
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    ///
    /// \brief on_wikiButton_clicked - Triggers when the wiki-button is clicked.
    ///
    void on_wikiButton_clicked();

    ///
    /// \brief on_lureBoxButton_clicked - Triggers when the lure box button is clicked
    /// Opens the lure box dialog and allows users to select a lure.
    ///
    void on_lureBoxButton_clicked();

    ///
    /// \brief on_fishCaught - Triggers when a fish is caught.
    ///
    void on_fishCaught();

    ///
    /// \brief on_newButton_clicked - Triggers when the new button is clicked.
    /// Starts a new game and clears all current data.
    ///
    void on_newButton_clicked();

    ///
    /// \brief on_userGuideButton_clicked - Triggers when the Help button is clicked.
    /// Contains a brief guide on lure selection given the specific fish.
    ///
    void on_userGuideButton_clicked();

    ///
    /// \brief on_fishBucketButton_clicked - Triggers when the Scrapbook button is clicked.
    /// Opens the scrapbook and allows users to see which fish they have caught.
    ///
    void on_fishBucketButton_clicked();

private:
    Ui::View *ui;                       // Pointer to the UI elements for the View.
    Game* game;                         // Pointer to the Game object, which handles the game logic and physics.
    std::shared_ptr<Document> document; // Shared pointer to the Document object that contains the management of data.
    WikiDialog popupWiki;               // Wiki dialog for displaying information about the game.
    LuresBoxDialog* popupLuresBox;      // LuresBoxDialog pointer to handle the lures dialog box.
    ScrapbookDialog* popupScrapbook;    // ScrapbookDialog pointer to manage the scrapbook.
    HelpDialog popupHelp;               // Help dialog to provide user guidance.
    bool keyPressEnabled = true;        // Default state: Key press is enabled

};

#endif // VIEW_H
