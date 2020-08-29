#ifndef ADDUSERWIDGET_H
#define ADDUSERWIDGET_H

#include <QDialog>
#include "Packet/LoginInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AddUserWidget; }
QT_END_NAMESPACE

class AddUserWidget : public QDialog
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

public slots:
    void emitSearchUser();
    void emitSubmit();
    void searchUserResult(LoginInfo::type_t type);
    void closeWindow();

signals:
    void searchUser(const QString& user);
    void submit(const QString& file, const QString& user);
};
#endif // ADDUSERWIDGET_H
