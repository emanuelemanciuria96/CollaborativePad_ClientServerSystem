//
// Created by utente on 17/03/2020.
//

#include "DataPacket.h"
#include "LoginInfo.h"

DataPacket::DataPacket(qint32 source, quint32 errcode, quint32 typeOfData)
        : source(source), errcode(errcode), type_of_data(typeOfData) {}

qint32 DataPacket::getSource() const {
    return source;
}

void DataPacket::setSource(qint32 source) {
    DataPacket::source = source;
}

quint32 DataPacket::getErrcode() const {
    return errcode;
}

void DataPacket::setErrcode(quint32 errcode) {
    DataPacket::errcode = errcode;
}

quint32 DataPacket::getTypeOfData() const {
    return type_of_data;
}

void DataPacket::setTypeOfData(quint32 typeOfData) {
    type_of_data = typeOfData;
}

std::shared_ptr<Payload> &DataPacket::getPayload(){
    return payload;
}
