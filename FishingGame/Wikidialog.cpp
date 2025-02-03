/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#include "Wikidialog.h"
#include "ui_wikidialog.h"

WikiDialog::WikiDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::WikiDialog) {

    ui->setupUi(this);
}

WikiDialog::~WikiDialog() {
    delete ui;
}
