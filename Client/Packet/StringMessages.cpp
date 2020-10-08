//
// Created by tomma on 20/04/2020.
//

#include <iostream>
#include "StringMessages.h"

StringMessages::StringMessages(std::vector<Message> &vm, qint32 siteID, QString &file):
    Payload(siteID), _fileName(file) {
    storeQueue(vm);
}

void StringMessages::appendMessage(Message &m){
    _messages.push_back(m);
}

int StringMessages::storeQueue(std::vector<Message> &vm) {
    if(vm.empty()) return -1;

    int i = 0;
    auto dim = vm.size();
    QTextCharFormat last{};

    for( ; i<dim && i<maxDim && (last==vm[i].getSymbol().getFormat() || last.isEmpty()); i++) {
        _messages.push_back(vm[i]);
        last = vm[i].getSymbol().getFormat();
    }

    vm.erase(vm.begin(),vm.begin()+i);
    return i;
}
