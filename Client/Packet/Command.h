//
// Created by Muska on 28/07/2020.
//

#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

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
    }cmd_t;

    Command(qint32 siteId, cmd_t cmd, QVector<QString> args);
    cmd_t getCmd() const;
    void setCmd(cmd_t cmd);
    const QVector<QString> &getArgs() const;
    void setArgs(const QVector<QString> &args);

private:
    cmd_t _cmd;
    QVector<QString> _args;
};

#endif //CLIENT_COMMAND_H
