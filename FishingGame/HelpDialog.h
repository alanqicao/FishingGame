/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
    class HelpDialog;
}

///
/// \brief The HelpDialog class provides a dialog window that displays information on the best lures for
/// a specific fish.
class HelpDialog : public QDialog {
    Q_OBJECT

public:
    ///
    /// \brief Constructor for HelpDialog class.
    /// \param parent - The parent widget.
    ///
    explicit HelpDialog(QWidget *parent = nullptr);

    /// \brief Destructor for the HelpDialog class.
    /// Cleans up any resources used by the HelpDialog.
    ~HelpDialog();

private:
    Ui::HelpDialog *ui; // Pointer to the UI elements of the HelpDialog.

};

#endif // HELPDIALOG_H
