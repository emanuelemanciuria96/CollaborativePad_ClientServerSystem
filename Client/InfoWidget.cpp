#include <iostream>
#include <QtGui/QPainter>
#include "InfoWidget.h"
#include "ui_infowidget.h"
#include "InfoWidgetEdit.h"

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    QPixmap orig("images/profile.jpg");
    int size = qMax(orig.width(), orig.height());
    QPixmap rounded = QPixmap(size, size);
    rounded.fill(Qt::transparent);
    QPainterPath path;
    path.addEllipse(rounded.rect());
    QPainter painter(&rounded);
    painter.setClipPath(path);
    painter.fillRect(rounded.rect(), Qt::black);
    int x = qAbs(orig.width() - size) / 2;
    int y = qAbs(orig.height() - size) / 2;
    painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(rounded);
    connect(ui->editButton, &QPushButton::clicked, this, &InfoWidget::emitOpenInfoEdit);
    connect(ui->backButton, &QPushButton::clicked, this, &InfoWidget::emitBackPressed);

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
        int size = qMax(orig.width(), orig.height());
        QPixmap rounded = QPixmap(size, size);
        rounded.fill(Qt::transparent);
        QPainterPath path;
        path.addEllipse(rounded.rect());
        QPainter painter(&rounded);
        painter.setClipPath(path);
        painter.fillRect(rounded.rect(), Qt::black);
        int x = qAbs(orig.width() - size) / 2;
        int y = qAbs(orig.height() - size) / 2;
        painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
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
        ui->imageLabel->setPixmap(orig);
        int size = qMax(orig.width(), orig.height());
        QPixmap rounded = QPixmap(size, size);
        rounded.fill(Qt::transparent);
        QPainterPath path;
        path.addEllipse(rounded.rect());
        QPainter painter(&rounded);
        painter.setClipPath(path);
        painter.fillRect(rounded.rect(), Qt::black);
        int x = qAbs(orig.width() - size) / 2;
        int y = qAbs(orig.height() - size) / 2;
        painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
        ui->imageLabel->setPixmap(rounded);
        ui->nameLabel->setText(name);
        ui->emailLabel->setText(email);
        emit sendUpdatedInfo(orig, name, email);
    }
}

void InfoWidget::emitBackPressed() {
    emit backPressed();
}
