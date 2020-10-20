#include <iostream>
#include <QtGui/QPainter>
#include "InfoWidget.h"
#include "ui_infowidget.h"
#include "MainWindow.h"

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    QPixmap orig("images/profile.jpg");
    auto rounded = MainWindow::roundImage(orig);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(rounded);
    connect(ui->editButton, &QPushButton::clicked, this, &InfoWidget::emitOpenInfoEdit);
    connect(ui->backButton, &QPushButton::clicked, this, &InfoWidget::emitBackPressed);
    connect(ui->logoutButton, &QPushButton::clicked, this, [this](){emit logout();});

    ui->label_3->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->label_5->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->label_7->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->logoutButton->setStyleSheet("QPushButton {font: 9pt; padding: 8; padding-right:15; padding-left:15; border-style: solid; border-width:1px; "
                                    "border-color:#D63A3A; background:#D63A3A; color:white}");
    ui->backButton->setStyleSheet("QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}");
    ui->editButton->setStyleSheet("QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}");

}

void InfoWidget::loadData(const QPixmap& orig, const QString& nickname, const QString& name, const QString& email) {
    if(!orig.isNull()) {
        auto rounded = MainWindow::roundImage(orig);
        ui->imageLabel->setPixmap(rounded);
        emit imageChanged(orig);
    }
    if (!name.isNull())
        ui->nameLabel->setText(name);
    if (!email.isNull())
        ui->emailLabel->setText(email);
    ui->nicknameLabel->setText(nickname);
}

void InfoWidget::emitOpenInfoEdit() {
    emit openInfoEdit(*(ui->imageLabel->pixmap()), ui->nicknameLabel->text(), ui->nameLabel->text(), ui->emailLabel->text());
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::updateInfo(const QPixmap& orig, const QString& name, const QString& email) {
    if (*(ui->imageLabel->pixmap()) != orig || ui->nameLabel->text() != name || ui->emailLabel->text() != email) {
        if(*(ui->imageLabel->pixmap()) != orig){
            emit imageChanged(orig);
        }
        auto rounded = MainWindow::roundImage(orig);
        ui->imageLabel->setPixmap(rounded);
        ui->nameLabel->setText(name);
        ui->emailLabel->setText(email);
        emit sendUpdatedInfo(orig, name, email);
    }
}

void InfoWidget::emitBackPressed() {
    emit backPressed();
}
