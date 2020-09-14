#ifndef INVITEUSERWIDGETITEM_H
#define INVITEUSERWIDGETITEM_H

#include <QWidget>
#include <QtWidgets/QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class InviteUserWidgetItem; }
QT_END_NAMESPACE

class InviteUserWidgetItem : public QWidget
{
    Q_OBJECT

public:
    InviteUserWidgetItem(QListWidgetItem* item, QString user, QString fileName, QWidget *parent = nullptr);
    ~InviteUserWidgetItem();
    void setFileName(const QString &fileName);
    const QString &getUser() const;
    const QString &getFileName() const;

private:
    Ui::InviteUserWidgetItem *ui;
    QString _user;

private:
    QString _fileName;
    QListWidgetItem* _item;

public slots:
    void emitAcceptInvite();
    void emitRejectInvite();

signals:
    void acceptInvite(QListWidgetItem* item, const QString& mode, const QString& user, const QString& filename);
    void rejectInvite(QListWidgetItem* item, const QString& mode, const QString& user, const QString& filename);
};
#endif // INVITEUSERWIDGETITEM_H
