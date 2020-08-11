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
    }cmd_t;

    Command(qint32 siteId, cmd_t cmd, QVector<QString> args);
    const QVector<QString> &getArgs() const;
    void setArgs(QVector<QString>& args){ _args = args; }
    void setArgs(const QVector<QString> &args);
    cmd_t getCmd() const;
    void setCmd(cmd_t cmd);
    qint32 getSiteId(){ return _siteID; }

    bool cdCommand(QString& connectionId, QString& user);
    bool mkdirCommand(QString& connectionId, QString& user);
    bool rmCommand(QString& connectionId, QString& user);
    QString opnCommand(QString &connectionId, QString& user);
    /*QVector<QString> openCommand(QString& connectionId, QString& user, QString& directory);
    bool copyFile(QString& connectionId, QString& user, QString& src, QString& dest);
    bool moveFile(QString& connectionId, QString& user, QString& src, QString& dest);*/

private:
    cmd_t _cmd;
    QVector<QString> _args;
    bool rmDir(QString& connectionId, QString& user);
    bool rmFile(QString& connectionId, QString& user);
};


#endif //SHAREDEDITORSERVER_COMMAND_H
