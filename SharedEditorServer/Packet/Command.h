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
    /** qui sono elencati alcuni dei possibili comandi
     * che il client può inviare al server, non sono così
     * sicuro che servano tutti, nè che non manchi nulla,
     * in ogni caso basta venire a modificare qui.
     * ogni operatore avrà massimo 2 parametri, entrambe
     * saranno stringhe, ma una potrebbe essere inutilizzata. **/
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
    }cmd_t;

    Command(qint32 siteId, cmd_t cmd, QVector<QString> args);
    const QVector<QString> &getArgs() const;
    void setArgs(const QVector<QString> &args);
    cmd_t getCmd() const;
    void setCmd(cmd_t cmd);
    bool cdCommand(QString& connectionId);
    bool mkdirCommand(QString& connectionId);
    bool rmCommand(QString& connectionId);
    bool opnCommand(QString &connectionId);
    bool treeCommand(QString &connectionId);

    bool lsCommand(QString &connectionId);

private:
    cmd_t _cmd;
    QVector<QString> _args;
    bool rmDir(QString& connectionId);
    bool rmFile(QString& connectionId);
};


#endif //SHAREDEDITORSERVER_COMMAND_H
