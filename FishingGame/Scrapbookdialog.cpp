/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Scrapbookdialog.h"
#include "ui_Scrapbookdialog.h"
#include "Document.h"

ScrapbookDialog::ScrapbookDialog(Document* document,QWidget *parent)
    : QDialog(parent),
    ui(new Ui::ScrapbookDialog),
    document(document) {

    ui->setupUi(this);
    updateScrapBook();
    // Recived signal from after hooked a fish then call updateScrapBook();
    connect(document, &Document::updateScrapbook, this, &ScrapbookDialog::updateScrapBook);
}

void ScrapbookDialog::updateScrapBook(){
    // Get all the groupBox
    QList<QGroupBox*> groupBoxes = ui->scrollAreaWidgetContents->findChildren<QGroupBox*>();
    QString funfacts = "???";
    QString filePathHolder = "://image/";
    QString pngHolder = ".png";

    for (QGroupBox* groupBox: groupBoxes) {
        // FishName
        QString fishName = groupBox->objectName();

        // Get all the label
        QList<QLabel*> tempLabels = groupBox->findChildren<QLabel*>();

        if (document->getUserFishBucket().contains(fishName)) {

            // Set to fish name
            groupBox->setTitle(fishName);

            for (QLabel* label : tempLabels) {
                QString tempLabelName = label->objectName();

                // Image label
                if (tempLabelName.at(0) == 'i') {
                    QImage image(filePathHolder+fishName+pngHolder);
                    label->setPixmap(QPixmap::fromImage(image));
                }

                // FishFacts label
                if (tempLabelName.at(0) == 'd') {
                    QVector<QString>* fishFacts =document->getOneFish(fishName)->getfishFacts();
                    QString tempFishFacts;
                    for (const QString& fishFact : *fishFacts) {
                        tempFishFacts += fishFact + "\n\n\n";
                    }

                    label->setText(tempFishFacts);
                }
            }
        } else {
            // Set fishName
            groupBox->setTitle("???");

            for (QLabel* label : tempLabels) {
                QString tempLabelName = label->objectName();

                // Image label
                if (tempLabelName.at(0) == 'i') {

                    QString tempStringImage = filePathHolder + fishName + pngHolder;
                    QImage image(tempStringImage);

                    // Convert the image to grayscale
                    QImage grayImage = image.convertToFormat(QImage::Format_Grayscale8);
                    label->setPixmap(QPixmap::fromImage(grayImage));
                }

                // FishFacts label
                if (tempLabelName.at(0) == 'd') {
                    label->setText("???");
                }
            }
        }
    }
}

ScrapbookDialog::~ScrapbookDialog() {
    delete ui;
}
