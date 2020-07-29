//
// Created by Muska on 28/07/2020.
//

#include "Command.h"

Command::Command(qint32 siteId, cmd_t cmd, QVector<QString> args) : Payload(siteId), _cmd(cmd),
                                                                    _args(std::move(args)) {}

Command::cmd_t Command::getCmd() const {
    return _cmd;
}

void Command::setCmd(Command::cmd_t cmd) {
    _cmd = cmd;
}

const QVector<QString> &Command::getArgs() const {
    return _args;
}

void Command::setArgs(const QVector<QString> &args) {
    _args = args;
}
