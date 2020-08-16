//
// Created by Windows on 16/08/2020.
//

#ifndef CLIENT_ACCOUNTVIEW_H
#define CLIENT_ACCOUNTVIEW_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QGuiApplication>
#include <QScreen>


class AccountView : public QWidget {
    Q_OBJECT
    QLabel *nickLabel;
public:
    AccountView(QWidget *parent);
};


#endif //CLIENT_ACCOUNTVIEW_H
