#include "AddUserWidget.h"
#include <utility>
#include <iostream>
#include <QtGui/QRegExpValidator>
#include "ui_adduserwidget.h"

AddUserWidget::AddUserWidget(QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::AddUserWidget)
{
    ui->setupUi(this);
    QRegExp expr(R"(^(?!\.)(?!com[0-9]$)(?!con$)(?!lpt[0-9]$)(?!nul$)(?!prn$)[^\|\*\?\\:<>/$"]*[^\.\|\*\?\\:<>/$"]+$)");
    auto *v = new QRegExpValidator(expr, this);
    ui->userEdit->setValidator(v);
    ui->userEdit->setMaxLength(20);
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
    emit closing();

}

void AddUserWidget::setFile(const QString &fileName) {
    file = fileName;
    emit searchFsName(file);
}

void AddUserWidget::closeEvent (QCloseEvent *event){
    ui->userEdit->clear();
    ui->resultLabel->clear();
    ui->submitButton->setDisabled(true);
    emit closing();
}

void AddUserWidget::editFileName(QString& oldName, QString& newName) {
    if (!newName.contains("/"))
        if (oldName == file)
            file = newName;
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
    ui->uri->setText("http://www.collaborativepad.com/"+fsName);
}
