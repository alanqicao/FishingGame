/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef LURESBOXDIALOG_H
#define LURESBOXDIALOG_H

#include "Document.h"
#include <QDialog>

namespace Ui {
    class LuresBoxDialog;
}

///
/// \brief The LuresBoxDialog class represents a dialog window for selecting lures in the application.
///
class LuresBoxDialog : public QDialog {
    Q_OBJECT

public:
    ///
    /// \brief Constructor for LuresBoxDialog class - Initializes the dialog with document and parent widget.
    /// \param document - Pointer to Document object.
    /// \param parent - The parent widget.
    ///
    explicit LuresBoxDialog(Document* document, QWidget *parent = nullptr);

    /// \brief Destructor for LuresBoxDialog.
    /// Cleans up any resources used by the dialog.
    ~LuresBoxDialog();

private slots:
    ///
    /// \brief on_buttonBox_accepted - Handles when the 'Accept' button is clicked in the LuresBoxDialog.
    /// Function is triggered when the user confirms the dialog box.
    ///
    void on_buttonBox_accepted();

private:
    Ui::LuresBoxDialog *ui;     // Pointer to the UI elements for the LuresBoxDialog.
    QString selectedLureName;   // Stores the name of the selected lure.
    Document* document;         // Pointer to the Document object associated with the dialog.

};

#endif // LURESBOXDIALOG_H
