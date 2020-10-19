//
// Created by Windows on 19/10/2020.
//

#ifndef CLIENT_LOSTCONNECTIONWIDGET_H
#define CLIENT_LOSTCONNECTIONWIDGET_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

class LostConnectionWidget : public QWidget {
    Q_OBJECT
private:
    QPushButton* button;

public:
    LostConnectionWidget(QWidget* parent);

signals:
    void reconnect();

};


#endif //CLIENT_LOSTCONNECTIONWIDGET_H
