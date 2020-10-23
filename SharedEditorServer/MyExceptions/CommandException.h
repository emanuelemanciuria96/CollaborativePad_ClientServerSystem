//
// Created by Muska on 21/10/2020.
//

#ifndef SHAREDEDITORSERVER_COMMANDEXCEPTION_H
#define SHAREDEDITORSERVER_COMMANDEXCEPTION_H

#include <exception>
#include <iostream>

class CommandException: public std::exception {
public:
    CommandException(const std::string& msg):_msg(msg){}
    virtual const char* what() const noexcept override{
        return _msg.c_str();
    }

protected:
    std::string _msg;

};


#endif //SHAREDEDITORSERVER_COMMANDEXCEPTION_H
