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
    void closeEvent(QCloseEvent *event);

public slots:
    void emitSearchUser();
    void emitSubmit();
    void searchUserResult(LoginInfo::type_t type);
    void closeWindow();
    void editFileName(QString& oldName, QString& newName);
    void processFileDeleted(QString fileName);

signals:
    void searchUser(const QString& user);
    void submitInvite(const QString& file, const QString& user);
};
#endif // ADDUSERWIDGET_H
