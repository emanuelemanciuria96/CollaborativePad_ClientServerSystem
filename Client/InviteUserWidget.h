#ifndef INVITEUSERWIDGET_H
#define INVITEUSERWIDGET_H

#include <QMainWindow>
#include "InviteUserWidgetItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class InviteUserWidget; }
QT_END_NAMESPACE

class InviteUserWidget : public QWidget
{
    Q_OBJECT

public:
    InviteUserWidget(QWidget *parent = nullptr);
    ~InviteUserWidget();

private:
    Ui::InviteUserWidget *ui;
    QMap<QListWidgetItem*, InviteUserWidgetItem*> map;

public slots:
    void inviteListArrived(const QVector<QString> &args);
    void emitSendInviteAnswer(QListWidgetItem* item, const QString& mode, const QString& user, const QString& filename);
    void editFileName(QString& oldName, QString& newName);
    void processFileDeleted(QString& fileName);

signals:
    void sendInviteAnswer(const QString& mode, const QString& user, const QString& filename);
    void inviteNumberModified(int n);
};
#endif // INVITEUSERWIDGET_H
