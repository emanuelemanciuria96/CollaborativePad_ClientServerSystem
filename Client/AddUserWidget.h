#ifndef ADDUSERWIDGET_H
#define ADDUSERWIDGET_H

#include <QtWidgets/QMainWindow>
#include "Packet/LoginInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddUserWidget; }
QT_END_NAMESPACE

class AddUserWidget : public QMainWindow
{
    Q_OBJECT

public:
    AddUserWidget(QWidget *parent = nullptr);
    void setFile(const QString &fileName);
    ~AddUserWidget();

private:
    Ui::AddUserWidget *ui;
    QString file;
    QString user;
    void closeEvent(QCloseEvent *event) override;

public slots:
    void emitSearchUser();
    void emitSubmit();
    void searchUserResult(LoginInfo::type_t type);
    void editFileName(QString& oldName, QString& newName);
    void inviteResultArrived(const QString& result);
    void fsNameArrived(const QString& fsName);

signals:
    void searchUser(const QString& user);
    void submitInvite(const QString& file, const QString& user);
    void setStatusBarText(const QString& text, int timeout);
    void searchFsName(const QString& name);
    void closing();
};
#endif // ADDUSERWIDGET_H
