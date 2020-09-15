#include "AddUserWidget.h"
#include <utility>
#include <iostream>
#include "ui_adduserwidget.h"

AddUserWidget::AddUserWidget(QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::AddUserWidget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    connect(ui->searchButton, &QPushButton::clicked, this, &AddUserWidget::emitSearchUser);
    connect(ui->submitButton, &QPushButton::clicked, this, &AddUserWidget::emitSubmit);
    connect(ui->cancelButton, &QPushButton::clicked, this, &AddUserWidget::close);
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
    emit submitInvite(file, user);
    this->close();
}

void AddUserWidget::setFile(const QString &fileName) {
    file = fileName;
    emit searchFsName(file);
}

void AddUserWidget::closeEvent (QCloseEvent *event){
    ui->userEdit->clear();
    ui->resultLabel->clear();
    ui->submitButton->setDisabled(true);
}

void AddUserWidget::editFileName(QString& oldName, QString& newName) {
    if (!newName.contains("/"))
        if (oldName == file)
            file = newName;
}

void AddUserWidget::processFileDeleted(QString fileName) {
    if (!fileName.contains("/"))
        if (fileName == file)
            close();
}

void AddUserWidget::inviteResultArrived(const QString &result) {
    if (result == "ok") {
        this->close();
        emit setStatusBarText("Invite for file "+ file +" sent to user " + user, 0);
    }
    else if (result == "invite-existing") {
        this->close();
        emit setStatusBarText("Invite for file " + file + " to user " + user + " already sent", 0);
    }
    else if (result == "file-existing") {
        this->close();
        emit setStatusBarText("User " + user + " already accepted invite for file " + file, 0);
    }
}

void AddUserWidget::fsNameArrived(const QString& fsName) {
    ui->uri->setText("http://www.sharededitor.com/"+fsName);
}
