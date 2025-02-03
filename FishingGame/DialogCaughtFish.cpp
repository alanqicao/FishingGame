/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "DialogCaughtFish.h"
#include "ui_DialogCaughtFish.h"
#include <QStandardItemModel>
#include "Document.h"

DialogCaughtFish::DialogCaughtFish(std::shared_ptr<Document> document, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::DialogCaughtFish),
    document(document) {

    ui->setupUi(this);
    std::shared_ptr<Fish> fish = document->getHookedFish();

    // Set Fish Image:
    QImage fishImage = fish->getImage();
    QPixmap fishPixmap = QPixmap::fromImage(fishImage);  // Convert QImage to QPixmap
    QPixmap scaledFishPixmap = fishPixmap.scaled(ui->fishImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); // Scale the Pixmap
    ui->fishImageLabel->setPixmap(scaledFishPixmap);

    // Set Fish Name Label:
    ui->fishNameLabel->setText(fish->getName());

    // Set Fish Description Label:
    QString fishDescription = "- " + fish->getDecription();
    ui->descriptionLabel->setText(fishDescription);

    QString fishFactOne = fish->getFishFact(0);
    QString fishFactTwo = fish->getFishFact(1);
    QString fishFactThree = fish->getFishFact(2);

    ui->fishFactOneLabel->setText("- " + fishFactOne);
    ui->fishFactTwoLabel->setText("- " + fishFactTwo);
    ui->fishFactThreeLabel->setText("- " + fishFactThree);
}

DialogCaughtFish::~DialogCaughtFish() {
    delete ui;
}

void DialogCaughtFish::on_stashFishButton_clicked() {
    close();
}

