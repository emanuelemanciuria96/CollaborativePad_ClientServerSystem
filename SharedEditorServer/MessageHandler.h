//
// Created by utente on 22/03/2020.
//

#ifndef SHAREDEDITORSERVER_MESSAGEHANDLER_H
#define SHAREDEDITORSERVER_MESSAGEHANDLER_H

#include <thread>
#include "Packet/Message.h"
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

/**
 * l'oggetto MessageHandler mi permette di gestire in maniera
 * thread-safe la coda di messaggi. Condividendo questo fra i
 * vai Thread ho l'automatica gestione.
 * - ho un thread privato che si mette in attesa su una coda
 *   di funzioni che mi gestiscono il messaggio, li processa
 *   appena ne entra uno
 * - submit() aggiungo messaggi alla coda
 * - ~MessageHandler() mi permette di far terminare l'attesa
 *   del thread ma lo distrugge solo quando finiscono i messaggi
 * - elimino il costruttore di copia
 * **/


class MessageHandler {
private:
    std::thread looper;
    std::queue<std::pair<std::function<void(Message)>,Message>> _queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished;

    void startLooper();
public:
    MessageHandler():finished(false){
        looper = std::move(std::thread(&MessageHandler::startLooper,this));
    }
    void submit(std::function<void(Message)> f,Message msg);
};



#endif //SHAREDEDITORSERVER_MESSAGEHANDLER_H
