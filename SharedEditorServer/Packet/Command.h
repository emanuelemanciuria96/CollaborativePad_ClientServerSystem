//
// Created by utente on 01/04/2020.
//

#ifndef SHAREDEDITORSERVER_COMMAND_H
#define SHAREDEDITORSERVER_COMMAND_H

#include <QtCore/QString>
#include <QtCore/QVector>
#include "Payload.h"

class Command: public Payload {
public:
    typedef enum _cmd{
        cd = 0,
        rm = 1,
        cp = 2,
        mv = 3,
        mkdir = 4,
        chmod = 5,
        opn = 6,
        cls = 7,
        sv = 8,
        find = 9,
        tree = 10,
        ls = 11,
        ren = 12,
        invite = 13,
        lsInvite = 14,
        ctrlInvite = 15,
        uri = 16,
        fsName = 17,
    }cmd_t;

    Command(qint32 siteId, cmd_t cmd, QVector<QString> args);
    const QVector<QString> &getArgs() const;
    void addArg(QString &arg);
    void setArgs(const QVector<QString> &args);
    cmd_t getCmd() const;
    void setCmd(cmd_t cmd);
    bool rmCommand(QString& connectionId);
    QVector<qint32> rmAllCommand(QString& connectionId);
    bool srcCommand(QString &connectionId);
    QVector<qint32> renCommand(QString& connectionId);
    bool lsCommand(QString &connectionId);
    bool svCommand(QString &connectionId);
    bool inviteCommand(QString &connectionId);
    bool lsInviteCommand(QString &connectionId);
    bool ctrlInviteCommand(QString &connectionId);
    bool uriCommand(QString &connectionId);
    bool fsNameCommand(QString &connectionId);

private:
    cmd_t _cmd;
    QVector<QString> _args;
};


#endif //SHAREDEDITORSERVER_COMMAND_H
