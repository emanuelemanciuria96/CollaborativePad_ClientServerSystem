//
// Created by Windows on 22/03/2020.
//

#ifndef CLIENT_LOGINDIALOG_H
#define CLIENT_LOGINDIALOG_H


#include <QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>


class LoginDialog: public QWidget {
    Q_OBJECT

public:
    bool abort;
    LoginDialog(QWidget *parent = 0);
    void setUsername(QString& username);
    void setPassword(QString& password);
    QDialogButtonBox* getButtons(){ return buttons; }

private:
    QLabel* labelUsername;
    QLabel* labelPassword;
    QLineEdit* editUsername;
    QLineEdit* editPassword;
    QDialogButtonBox* buttons;
    QPushButton* signInButton;
    void setUpGUI();

signals:
    void acceptLogin(QString& username, QString& password);
    void loginAchieved();
    void signIn();

private slots:
    void slotAcceptLogin();
    void slotSignIn();

};


#endif //CLIENT_LOGINDIALOG_H
