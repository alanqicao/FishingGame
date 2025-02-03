/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef DIALOGCAUGHTFISH_H
#define DIALOGCAUGHTFISH_H

#include "Document.h"
#include <QDialog>

namespace Ui {
    class DialogCaughtFish;
}

///
/// \brief The DialogCaughtFish class represents a dialog window that displays information about a caught fish.
///
///
class DialogCaughtFish : public QDialog {
    Q_OBJECT

public:
    ///
    /// \brief DialogCaughtFish - Constructor for DialogCaughtFish class.
    /// \param document - A shared pointer to the Document object, used to access fish data.
    /// \param parent - The parent widget (default is nullptr).
    ///
    explicit DialogCaughtFish(std::shared_ptr<Document> document, QWidget *parent = nullptr);
    ~DialogCaughtFish();

private slots:
    ///
    /// \brief on_stashFishButton_clicked handles the event when the "Stash Fish" button is clicked.
    ///
    void on_stashFishButton_clicked();

private:
    Ui::DialogCaughtFish *ui;           // UI object for class DialogCaughtFish.
    std::shared_ptr<Document> document; // Shared pointer to the Document class.

};

#endif // DIALOGCAUGHTFISH_H
