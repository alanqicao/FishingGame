/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Luresboxdialog.h"
#include "ui_Luresboxdialog.h"
#include <QStandardItemModel>
#include "Document.h"

LuresBoxDialog::LuresBoxDialog(Document* document,QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LuresBoxDialog),
    document(document) {

    ui->setupUi(this);

    QListView* listView = ui->listView;
    QStandardItemModel* model = new QStandardItemModel(listView);

    QVector<Lure*> lures= document->getAllLures(); // Get all the lures

    for (int i = 0; i < lures.count(); ++i) {
        Lure* lure = lures[i]; // Get the current lure

        QStandardItem* item = new QStandardItem();
        item->setText(*lure->getName());  // name
        item->setIcon(QIcon(*lure->getImagePath()));  // Image path
        item->setData(*lure->getDescription(), Qt::UserRole);
        model->appendRow(item);
    }

    // Set the model
    listView->setModel(model);

    // Configure the QListView for larger icons and responsive layout
    listView->setViewMode(QListView::IconMode);
    listView->setFlow(QListView::LeftToRight);
    listView->setResizeMode(QListView::Adjust);

    // Set the size of each item in the QListView
    QSize iconSize(200, 200);         // Example size, you can adjust
    listView->setIconSize(iconSize);  // Set the icon size
    listView->setSpacing(30);         // Spacing

    // Optimize the grid layout to fit the QListView size
    listView->setGridSize(QSize(iconSize.width() + 20, iconSize.height() + 40));  // Ensure icons fit well

    connect(listView, &QListView::clicked, this, [this](const QModelIndex& index) {
        ui->lureDescriptionLabel->setText(index.data(Qt::UserRole).toString());
        selectedLureName = index.data(Qt::DisplayRole).toString();
    });

    listView->setStyleSheet(R"(
        QListView::item {
            border: 1px solid gray;
            margin: 5px;
            padding: 5px;
        }
        QListView::item:hover {
            background: #f0f0f0;  /* Light gray on hover */
            border: 2px solid blue;  /* Thicker border for hover */
        }
        QListView::item:selected {
            background: #d0e9ff;  /* Light blue for selected item */
            border: 2px solid darkblue;
        }
    )");

    QLabel* label = ui->lureDescriptionLabel;
    QFont font("Arial", 14, QFont::Bold);  // Font family, size, and weight
    label->setFont(font);
}

LuresBoxDialog::~LuresBoxDialog() {
    delete ui;
}

void LuresBoxDialog::on_buttonBox_accepted() {
    document->setCurrentLure(selectedLureName);
}

