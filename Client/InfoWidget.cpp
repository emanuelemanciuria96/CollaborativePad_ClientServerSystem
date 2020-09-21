#include <iostream>
#include "InfoWidget.h"
#include "ui_infowidget.h"
#include "InfoWidgetEdit.h"

InfoWidget::InfoWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    infoWidgetEdit = new InfoWidgetEdit(this);
    QPixmap image("images/profile.jpg");
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(image);
}

void InfoWidget::loadData(const QPixmap& image, const QString& nickname, const QString& name, const QString& email) {
    if(!image.isNull())
        ui->imageLabel->setPixmap(image);
    if (!name.isNull())
        ui->nameLabel->setText(name);
    if (!email.isNull())
        ui->emailLabel->setText(email);
    ui->nicknameLabel->setText(nickname);
    connect(ui->editButton, &QPushButton::clicked, this, &InfoWidget::openInfoEdit);
    connect(infoWidgetEdit, &InfoWidgetEdit::updateInfo, this, &InfoWidget::updateInfo);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QWidget::close);
}

void InfoWidget::openInfoEdit() {
    infoWidgetEdit->setImage(ui->imageLabel->pixmap());
    infoWidgetEdit->setName(ui->nameLabel->text());
    infoWidgetEdit->setEmail(ui->emailLabel->text());
    this->hide();
    infoWidgetEdit->show();
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

const QPixmap *InfoWidget::getImage() {
    return ui->imageLabel->pixmap();
}

QString InfoWidget::getNickname() {
    return std::move(ui->nicknameLabel->text());
}

QString InfoWidget::getName() {
    return std::move(ui->nameLabel->text());
}

void InfoWidget::updateInfo(const QPixmap& image, const QString& name, const QString& email) {
    if (*(ui->imageLabel->pixmap()) != image || ui->nameLabel->text() != name || ui->emailLabel->text() != email) {
        ui->imageLabel->setPixmap(image);
        ui->nameLabel->setText(name);
        ui->emailLabel->setText(email);
        emit sendUpdatedInfo(image, name, email);
    }
    infoWidgetEdit->close();
    this->show();
}
