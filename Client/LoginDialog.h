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

class LoginDialog: public QDialog {
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = 0);
    void setUsername(QString& username);
    void setPassword(QString& password);

private:
    QLabel* labelUsername;
    QLabel* labelPassword;
    QLineEdit* editUsername;
    QLineEdit* editPassword;
    QDialogButtonBox* buttons;
    void setUpGUI();

signals:
    void acceptLogin(QString& username, QString& password);

public slots:
    void slotAcceptLogin();

};


#endif //CLIENT_LOGINDIALOG_H
