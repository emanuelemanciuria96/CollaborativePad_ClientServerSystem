//
// Created by utente on 22/03/2020.
//

#ifndef SHAREDEDITORSERVER_MESSAGEHANDLER_H
#define SHAREDEDITORSERVER_MESSAGEHANDLER_H

/**
 * l'oggetto MessageHandler mi permette di gestire in maniera
 * thread-safe la coda di messaggi. Condividendo questo fra i
 * vai Thread ho l'automatica gestione.
 * - ho un thread privato che si mette in attesa sulla
 *   coda di messaggi, li processa appena ne entra uno
 * - submit() aggiungo messaggi alla coda
 * - ~MessageHandler mi permette di far terminare l'attesa
 *   del thread ma lo distrugge solo quando finiscono i messaggi**/

class MessageHandler {

};


#endif //SHAREDEDITORSERVER_MESSAGEHANDLER_H
