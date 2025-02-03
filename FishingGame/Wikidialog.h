/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef WIKIDIALOG_H
#define WIKIDIALOG_H

#include <QDialog>

namespace Ui {
    class WikiDialog;
}

///
/// \brief The WikiDialog class represents a dialog window for displaying Wiki-related content of each fish.
///
class WikiDialog : public QDialog {
    Q_OBJECT

public:
    ///
    /// \brief Constructor for the WikiDialog class.
    /// \param parent - The parent widget.
    ///
    explicit WikiDialog(QWidget *parent = nullptr);

    /// \brief Destructor for the WikiDialog class.
    /// Cleans up resources used by the dialog.
    ~WikiDialog();

private:
    Ui::WikiDialog *ui;

};

#endif // WIKIDIALOG_H
