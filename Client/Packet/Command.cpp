//
// Created by Muska on 28/07/2020.
//

#include "Command.h"

Command::Command(qint32 siteId, qint32 cmd, QVector<QString> args) : Payload(siteId), _cmd(cmd),
                                                                             _args(std::move(args)) {}

const QVector<QString> &Command::getArgs() const {
    return _args;
}

void Command::setArgs(const QVector<QString> &args) {
    _args = args;
}

qint32 Command::getCmd() const {
    return _cmd;
}

void Command::setCmd(qint32 cmd) {
    _cmd = cmd;
}
