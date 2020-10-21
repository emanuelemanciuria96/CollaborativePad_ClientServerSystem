//
// Created by utente on 17/03/2020.
//

#ifndef SHAREDEDITORSERVER_DATAPACKET_H
#define SHAREDEDITORSERVER_DATAPACKET_H

#include <QtGlobal>
#include <memory>
#include <QtCore/QObject>
#include "Payload.h"

class DataPacket : public QObject{
    Q_OBJECT
public:
    typedef enum Constants
    {
        textTyping = 1,
        login = 2,
        command = 3,
        file_info = 4,
        cursorPos = 5,
        user_info = 6,
        error = 7,
    }data_t;

    DataPacket();
    DataPacket(qint32 source, quint32 errcode, data_t typeOfData,std::shared_ptr<Payload> pl= nullptr,QObject *parent = 0);
    DataPacket(const DataPacket& packet);
    ~DataPacket() = default;

    qint32 getSource() const;
    void setSource(qint32 source);
    quint32 getErrcode() const;
    void setErrcode(quint32 errcode);
    quint32 getTypeOfData() const;
    void setTypeOfData(data_t typeOfData);
    std::shared_ptr<Payload> getPayload();
    void setPayload(std::shared_ptr<Payload> pl);
private:
    qint32 source;   //questo campo sarà riempito con il siteID nel caso in cui si conosca, -1 altrimenti
    quint32 errcode;
    data_t type_of_data;
    std::shared_ptr<Payload> payload;
};

Q_DECLARE_METATYPE(DataPacket);

#endif //SHAREDEDITORSERVER_DATAPACKET_H
