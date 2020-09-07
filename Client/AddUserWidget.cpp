#include "AddUserWidget.h"

#include <utility>
#include "ui_adduserwidget.h"

AddUserWidget::AddUserWidget(QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::AddUserWidget)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QPushButton::clicked, this, &AddUserWidget::emitSearchUser);
    connect(ui->submitButton, &QPushButton::clicked, this, &AddUserWidget::emitSubmit);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddUserWidget::closeWindow);
    ui->submitButton->setDisabled(true);
}

AddUserWidget::~AddUserWidget()
{
    delete ui;
}

void AddUserWidget::emitSearchUser() {
    user = ui->userEdit->text();
    if (!user.isEmpty())
        emit searchUser(user);
    else {
        ui->resultLabel->clear();
        ui->submitButton->setDisabled(true);
    }
}

void AddUserWidget::searchUserResult(LoginInfo::type_t type) {
    QPalette palette;

    if (type == LoginInfo::search_user_ok){
        palette.setColor(QPalette::WindowText, Qt::darkGreen);
        ui->resultLabel->setPalette(palette);
        ui->resultLabel->setText("User found!");
        ui->submitButton->setDisabled(false);
    } else if (type == LoginInfo::search_user_error) {
        palette.setColor(QPalette::WindowText, Qt::red);
        ui->resultLabel->setPalette(palette);
        ui->resultLabel->setText("User not found!");
        ui->submitButton->setDisabled(true);
    }
}

void AddUserWidget::emitSubmit() {
    emit submit(file, user);
    ui->userEdit->clear();
    ui->resultLabel->clear();
    ui->submitButton->setDisabled(true);
    this->close();
}

void AddUserWidget::setFile(const QString &fileName) {
    file = fileName;
}

void AddUserWidget::closeWindow() {
    ui->userEdit->clear();
    ui->resultLabel->clear();
    ui->submitButton->setDisabled(true);
    this->close();
}

void AddUserWidget::closeEvent (QCloseEvent *event){
    ui->userEdit->clear();
    ui->resultLabel->clear();
    ui->submitButton->setDisabled(true);
    this->close();
}

void AddUserWidget::editFileName(QString& oldName, QString& newName) {
    if (!newName.contains("/"))
        if (oldName == file)
            file = newName;
}
