//
// Created by utente on 01/04/2020.
//

#include "Command.h"

Command::Command(qint32 siteID, Command::cmd_t cmd, QString& arg1, QString& arg2):Payload(siteID),
                cmd(cmd),arg1(arg1){
    /// Visto che penso sia quasi impossibile che  si possa inviare il valore
    /// nullptr attraverso il socket, penso che per segnalare che non ci sia
    /// nessun secondo argomento, sia opportuno ideare una stringa che non possa
    /// essere un argomento come, ad esempio, "\!\" o robe del genere
    if(arg2 == "\\!\\")
        this->arg2 = nullptr;
    else this->arg2 = arg2;
}
