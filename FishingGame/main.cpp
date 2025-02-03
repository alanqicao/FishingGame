/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "View.h"
#include <QApplication>
#include "Game.h"
#include "Luresboxdialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Document document;
    Game game(nullptr, &document);
    LuresBoxDialog luresBox(&document);
    ScrapbookDialog popupScrapbook(&document);
    View w(&game, &document, &luresBox, &popupScrapbook);
    w.show();

    return a.exec();
}
