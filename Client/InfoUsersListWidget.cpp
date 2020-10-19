#include <QtGui/QPainter>
#include "MainWindow.h"
#include "InfoUsersListWidget.h"
#include "./ui_infouserslistwidget.h"

InfoUsersListWidget::InfoUsersListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InfoUsersListWidget)
{
    ui->setupUi(this);
    ui->imageLabel->setScaledContents(true);
    connect(ui->backButton, &QPushButton::clicked, this, [this](){emit backPressed(QPixmap(), nullptr, nullptr, nullptr);});
}

InfoUsersListWidget::~InfoUsersListWidget()
{
    delete ui;
}

void InfoUsersListWidget::setData(const QPixmap &orig, const QString &nickname, const QString &name, const QString &email) {
    if (!orig.isNull()){
        auto rounded = MainWindow::roundImage(orig);
        ui->imageLabel->setPixmap(rounded);
    } else {
        QPixmap defaultImg("./images/profile.jpg");
        auto rounded = MainWindow::roundImage(defaultImg);
        ui->imageLabel->setPixmap(rounded);
    }
    ui->nicknameLabel->setText(nickname);
    ui->nameLabel->setText(name);
    ui->emailLabel->setText(email);
    setStyleSheet("QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}");
    ui->label_5->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->label_3->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->label_7->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");

}

