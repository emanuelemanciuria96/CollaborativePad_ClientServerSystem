//
// Created by Windows on 30/09/2020.
//

#ifndef CLIENT_USERSLISTITEM_H
#define CLIENT_USERSLISTITEM_H


#include <QtWidgets/QListWidgetItem>

class UsersListItem : public QListWidgetItem{
    Q_PROPERTY(QString name READ name WRITE setName)
public:
    explicit UsersListItem(QString text);
    void setName(QString& name);
    QString name() const;

private:
    QString m_name;
};


#endif //CLIENT_USERSLISTITEM_H
