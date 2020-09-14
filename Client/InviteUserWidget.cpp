#include <iostream>
#include "InviteUserWidget.h"
#include "./ui_inviteuserwidget.h"

InviteUserWidget::InviteUserWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InviteUserWidget)
{
    ui->setupUi(this);
}

InviteUserWidget::~InviteUserWidget()
{
    delete ui;
}

void InviteUserWidget::inviteListArrived(const QVector<QString> &args) {
    ui->listWidget->clear();
    map.clear();
    for (auto& a: args) {
        auto list = a.split("/");
        auto *item = new QListWidgetItem(ui->listWidget);
        auto *widget = new InviteUserWidgetItem(item, list.first(), list.last(), ui->listWidget);
        connect(widget, &InviteUserWidgetItem::acceptInvite, this, &InviteUserWidget::emitSendInviteAnswer);
        connect(widget, &InviteUserWidgetItem::rejectInvite, this, &InviteUserWidget::emitSendInviteAnswer);
        item->setSizeHint(widget->minimumSizeHint());
        ui->listWidget->setItemWidget(item, widget);
        map.insert(item, widget);
    }
}

void InviteUserWidget::emitSendInviteAnswer(QListWidgetItem* item, const QString &mode, const QString &user, const QString &filename) {
    emit sendInviteAnswer(mode, user, filename);
    auto row = ui->listWidget->row(item);
    ui->listWidget->takeItem(row);
}

void InviteUserWidget::editFileName(QString &oldName, QString &newName) {
    if (newName.contains("/")) {
        auto list1 = oldName.split("/");
        auto list2 = newName.split("/");
        auto user = list1.first();
        auto oldFileName = list1.last();
        auto newFileName = list2.last();
        for (int i = 0; i < ui->listWidget->count(); i++) {
            QListWidgetItem *item = ui->listWidget->item(i);
            auto widget = map[item];

            if (widget->getUser() == user && widget->getFileName() == oldFileName) {
                widget->setFileName(newFileName);
                return;
            }
        }
    }
}

void InviteUserWidget::processFileDeleted(QString &fileName) {
    if (fileName.contains("/")) {
        auto list = fileName.split("/");
        auto user = list.first();
        auto file = list.last();

        for (int i = 0; i < ui->listWidget->count(); i++) {
            QListWidgetItem *item = ui->listWidget->item(i);
            auto widget = map[item];

            if (widget->getUser() == user && widget->getFileName() == file) {
                auto row = ui->listWidget->row(item);
                ui->listWidget->takeItem(row);
                return;
            }
        }
    }
}
