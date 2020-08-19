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
    ui->immagine->setScaledContents(true);
    ui->immagine->setPixmap(image);
}

void InfoWidget::loadData(const QPixmap& image, const QString& nickname, const QString& name) {
    ui->immagine->setScaledContents(true);
    if(!image.isNull())
        ui->immagine->setPixmap(image);
    ui->nickname->setText(nickname);
    if (!name.isNull())
        ui->nome->setText(name);
    connect(ui->pushButton, &QPushButton::clicked, this, &InfoWidget::openInfoEdit);
    connect(infoWidgetEdit, &InfoWidgetEdit::updateInfo, this, &InfoWidget::updateInfo);
    infoWidgetEdit->setImage(ui->immagine->pixmap());
    infoWidgetEdit->setName(ui->nome->text());
}

void InfoWidget::openInfoEdit() {
    this->hide();
    infoWidgetEdit->show();
}

InfoWidget::~InfoWidget()
{
    delete ui;
}

const QPixmap *InfoWidget::getImage() {
    return ui->immagine->pixmap();
}

QString InfoWidget::getNickname() {
    return std::move(ui->nickname->text());
}

QString InfoWidget::getName() {
    return std::move(ui->nome->text());
}

void InfoWidget::updateInfo(const QPixmap& image, const QString& name) {
    if (*(ui->immagine->pixmap()) != image || ui->nome->text() != name) {
        ui->immagine->setScaledContents(true);
        ui->immagine->setPixmap(image);
        ui->nome->setText(name);
        emit sendUpdatedInfo(image, name);
    }
    infoWidgetEdit->close();
    this->show();
}
