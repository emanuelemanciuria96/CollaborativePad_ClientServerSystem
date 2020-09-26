#include "InviteUserWidgetItem.h"

#include <utility>
#include "./ui_inviteuserwidgetitem.h"

InviteUserWidgetItem::InviteUserWidgetItem(QListWidgetItem* item, QString user, QString fileName, QWidget *parent)
    :_item(item), _user(std::move(user)), _fileName(std::move(fileName)), QWidget(parent)
    , ui(new Ui::InviteUserWidgetItem)
{
    ui->setupUi(this);
    connect(ui->acceptButton, &QPushButton::clicked, this, &InviteUserWidgetItem::emitAcceptInvite);
    connect(ui->rejectButton, &QPushButton::clicked, this, &InviteUserWidgetItem::emitRejectInvite);
    ui->textLabel->setText(QString("User "+_user+" invited you to modify document \""+_fileName+"\"."));
    ui->acceptButton->setIcon(QIcon("./icons/invite_accept_icon.png"));
    ui->acceptButton->setIconSize(QSize(30, 30));
    ui->rejectButton->setIcon(QIcon("./icons/invite_reject_icon.png"));
    ui->rejectButton->setIconSize(QSize(30, 30));
}

InviteUserWidgetItem::~InviteUserWidgetItem()
{
    delete ui;
}

void InviteUserWidgetItem::emitAcceptInvite() {
    emit acceptInvite(_item, "accept", _user, _fileName);
}

void InviteUserWidgetItem::emitRejectInvite() {
    emit rejectInvite(_item, "reject", _user, _fileName);
}

void InviteUserWidgetItem::setFileName(const QString &fileName) {
    _fileName = fileName;
    ui->textLabel->setText(QString("User "+_user+" invited you to modify document \""+_fileName+"\"."));
}

const QString &InviteUserWidgetItem::getUser() const {
    return _user;
}

const QString &InviteUserWidgetItem::getFileName() const {
    return _fileName;
}
