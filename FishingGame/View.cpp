/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "View.h"
#include "qboxlayout.h"
#include "ui_View.h"
#include "Drawing.h"
#include "Game.h"
#include "Document.h"
#include "QLabel"
#include <QFileDialog>

View::View(Game* gameInstance, Document* document, LuresBoxDialog* popupLuresBox, ScrapbookDialog* popupScrapbook, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::View),
    game(gameInstance),  // Store the passed Game object
    document(document),
    popupLuresBox(popupLuresBox),
    popupScrapbook(popupScrapbook) {

    ui->setupUi(this);

    // SetUp UI
    Drawing* drawing = new Drawing(game, this);
    QVBoxLayout* layout = new QVBoxLayout(ui->drawingWidget);
    ui->drawingWidget->setLayout(layout);
    layout->addWidget(drawing);

    // Save data
    connect(ui->saveButton,
            &QPushButton::clicked,
            this,
            [&document]() {
                document->saveToFile();
            });

    // Load data
    connect(ui->loadButton,
            &QPushButton::clicked,
            this,
            [&document,&popupScrapbook]() {
                document->loadFromFile();
                popupScrapbook->updateScrapBook();
            });

    // Reset Lure Button
    connect(ui->resetLureButton, &QPushButton::clicked, game, &Game::resetLure);

    // Disable keyPress after throw lure
    connect(game,
            &Game::lureThrown,
            this,
            [this]() {
                this->setKeyPressEnabled(false);
                ui->lureBoxButton->setEnabled(false);
    });

    connect(game,
            &Game::lureReset,
            this,
            [this]() {
                this->setKeyPressEnabled(true);
                ui->lureBoxButton->setEnabled(true);
    });

    // Popup Fish Caught
    connect(game, &Game::fishCaught, this, &View::on_fishCaught);

    // Reset the application
    connect(ui->userGuideButton, &QPushButton::clicked, this, &View::on_userGuideButton_clicked);
}

View::~View() {
    delete ui;
}

void View::keyPressEvent(QKeyEvent* event) {
    if (!keyPressEnabled) {
        return;  // Ignore the event
    }

    Boat* boat = document->getcurrentBoat();
    Lure* currentLure = document->getCurrentLure();
    if (event->key() == Qt::Key::Key_A) {

        // If-Statement to ensure boat is within bounds
        if (boat->getBoatx() > 1 || boat->getBoatx() < this->width() - 1) {
            boat->setBoatX(boat->getBoatx() - 100);

            int tempLureX = boat->getArmLocation().x();
            int tempLureY = boat->getArmLocation().y();
            currentLure->setPosX(tempLureX);
            currentLure->setPosY(tempLureY);
        }

    } else if (event->key() == Qt::Key::Key_D) {

        // If-Statement to ensure boat is within bounds
        if (boat->getBoatx() > 1 || boat->getBoatx() < this->width() - 1) {
            boat->setBoatX(boat->getBoatx() + 100);
            int tempLureX = boat->getArmLocation().x();
            int tempLureY = boat->getArmLocation().y();
            currentLure->setPosX(tempLureX);
            currentLure->setPosY(tempLureY);
        }
    }
}

void View::mousePressEvent(QMouseEvent* event) {
    if (game) {
        float scale = 30.0f;  // Convert pixels to Box2D meters
        b2Vec2 dragStart(event->pos().x() / scale, (height() - event->pos().y()) / scale);

        game->startDragging(dragStart);  // Forward drag start to Game
    }
}

void View::mouseMoveEvent(QMouseEvent* event) {
    if (game && game->isDraggingLure()) {  // Only process if dragging is active
        float scale = 30.0f;
        b2Vec2 dragEnd(event->pos().x() / scale, (height() - event->pos().y()) / scale);

        game->updateDragging(dragEnd);  // Forward drag end to Game
    }
}

void View::mouseReleaseEvent(QMouseEvent* event) {
    if (game) {
        game->stopDragging();  // Notify Game to stop dragging
    }
}

void View::on_wikiButton_clicked() {
    popupWiki.show();
}

void View::on_lureBoxButton_clicked() {
    popupLuresBox->show();
}

void View::on_fishCaught() {
    DialogCaughtFish caughtFishPopup(std::shared_ptr<Document>(document), nullptr);
    caughtFishPopup.exec();
}

void View::setKeyPressEnabled(bool enabled) {
    keyPressEnabled = enabled;
}

void View::on_userGuideButton_clicked() {
    popupHelp.show();
}

void View::on_newButton_clicked() {
    QDialog popup;
    popup.setWindowTitle("Start a New Game");

    QLabel *messageBox = new QLabel("Would you like to start a new game?\nAny unsaved changes will be discarded.");
    messageBox->setAlignment(Qt::AlignCenter);

    QFont font = messageBox->font();
    font.setPointSize(11);  // Set the font size to 12 (adjust as needed)
    messageBox->setFont(font);

    QPushButton confirmButton("Confirm");
    QPushButton cancelButton("Cancel");

    QVBoxLayout mainLayout(&popup);
    mainLayout.addWidget(messageBox);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(&confirmButton);
    buttonLayout->addWidget(&cancelButton);

    mainLayout.addLayout(buttonLayout);

    // New button
    QObject::connect(&confirmButton, &QPushButton::clicked, this, [this, &popup]() {
        document->clearDocument();
        document->loadFromJson("://image/InitData.json");
        game->resetLure();

        popup.close();
    });

    QObject::connect(&cancelButton, &QPushButton::clicked, &popup, &QDialog::close);
    popup.resize(350, 150);
    popup.exec();
}

void View::on_fishBucketButton_clicked() {
    popupScrapbook->show();
}

