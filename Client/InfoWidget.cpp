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

void InfoWidget::loadData(const QPixmap& image, const QString& nickname, const QString& name, const QString& email) {
    if(!image.isNull())
        ui->immagine->setPixmap(image);
    if (!name.isNull())
        ui->nome->setText(name);
    if (!email.isNull())
        ui->email->setText(email);
    ui->nickname->setText(nickname);
    connect(ui->modifica, &QPushButton::clicked, this, &InfoWidget::openInfoEdit);
    connect(infoWidgetEdit, &InfoWidgetEdit::updateInfo, this, &InfoWidget::updateInfo);
    infoWidgetEdit->setImage(ui->immagine->pixmap());
    infoWidgetEdit->setName(ui->nome->text());
    infoWidgetEdit->setEmail(ui->email->text());
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

void InfoWidget::updateInfo(const QPixmap& image, const QString& name, const QString& email) {
    if (*(ui->immagine->pixmap()) != image || ui->nome->text() != name || ui->email->text() != email) {
        ui->immagine->setPixmap(image);
        ui->nome->setText(name);
        ui->email->setText(email);
        emit sendUpdatedInfo(image, name, email);
    }
    infoWidgetEdit->close();
    this->show();
}
