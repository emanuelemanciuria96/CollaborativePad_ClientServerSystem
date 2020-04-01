//
// Created by utente on 17/03/2020.
//

#include "DataPacket.h"
#include "LoginInfo.h"

DataPacket::DataPacket(qint32 source, quint32 errcode, data_t typeOfData, Payload* pl)
        : source(source), errcode(errcode), type_of_data(typeOfData),payload(pl) {}

qint32 DataPacket::getSource() const {
    return source;
}

void DataPacket::setSource(qint32 source) {
    this->source = source;
}

quint32 DataPacket::getErrcode() const {
    return errcode;
}

void DataPacket::setErrcode(quint32 errcode) {
    this->errcode = errcode;
}

quint32 DataPacket::getTypeOfData() const {
    return type_of_data;
}

void DataPacket::setTypeOfData(data_t typeOfData) {
    this->type_of_data = typeOfData;
}

std::shared_ptr<Payload> DataPacket::getPayload(){
    return payload;
}

void DataPacket::setPayload(std::shared_ptr<Payload> pl) {
    payload = pl;
}


