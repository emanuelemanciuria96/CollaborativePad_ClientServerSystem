//
// Created by utente on 09/09/2020.
//

#ifndef SHAREDEDITORSERVER_LOGINEXCEPTION_H
#define SHAREDEDITORSERVER_LOGINEXCEPTION_H

#include <exception>
#include <iostream>

class LoginException: public std::exception {
public:
    LoginException(const std::string& msg):_msg(msg){}
    virtual const char* what() const noexcept override{
        return _msg.c_str();
    }

private:
    std::string _msg;

};



#endif //SHAREDEDITORSERVER_LOGINEXCEPTION_H
