/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef SCRAPBOOKDIALOG_H
#define SCRAPBOOKDIALOG_H

#include <QDialog>
#include "Document.h"

namespace Ui {
    class ScrapbookDialog;
}

///
/// \brief The ScrapbookDialog class - a dialog window that represents a scrapbook of all the fishes the user has caught.
/// Displays the fishes in grayscale if the user has not caught that specific fish otherwise, displays the fish
/// in color and gives facts about the fish caught.
///
class ScrapbookDialog : public QDialog {
    Q_OBJECT

public:
    ///
    /// \brief Constructor for ScrapbookDialog class.
    /// \param document - Pointer to the Document object, which holds fish data relating to the scrapbook.
    /// \param parent - The parent widget.
    ///
    explicit ScrapbookDialog(Document* document,QWidget *parent = nullptr);

    /// \brief Destructor for ScrapbookDialog.
    /// Cleans up any resources used by the dialog.
    ~ScrapbookDialog();

    ///
    /// \brief updateScrapBook - Updates the scrapbook contents when a fish has been caught.
    ///
    void updateScrapBook();

private:
    Ui::ScrapbookDialog *ui;    // Pointer to the UI elements for the ScrapbookDialog.
    Document* document;         // Pointer to the Document object associated with the scrapbook.

};

#endif // SCRAPBOOKDIALOG_H
