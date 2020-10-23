//
// Created by utente on 23/10/2020.
//

#ifndef SHAREDEDITORSERVER_RENCOMMANDEXCEPTION_H
#define SHAREDEDITORSERVER_RENCOMMANDEXCEPTION_H

#include "CommandException.h"

class RenCommandException: public CommandException{
public:
    RenCommandException(const std::string& msg):
    CommandException(msg){}
    virtual const char* what() const noexcept {
        return _msg.c_str();
    }

};

#endif //SHAREDEDITORSERVER_RENCOMMANDEXCEPTION_H
