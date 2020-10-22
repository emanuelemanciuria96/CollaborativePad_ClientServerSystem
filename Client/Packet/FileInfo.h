//
// Created by utente on 12/08/2020.
//

#ifndef CLIENT_FILEINFO_H
#define CLIENT_FILEINFO_H

#include "Payload.h"
#include <QString>

class FileInfo: public Payload{

public:
    typedef enum {start = 1, eof = 2, err = 3} file_info_t;

    FileInfo( qint32 _siteID,file_info_t info,QString &serverFileName):
            file_info(info),Payload(_siteID),_serverFileName(serverFileName){}
    file_info_t getFileInfo(){ return file_info; }
    QString getServerFileName(){ return _serverFileName;}
private:
    file_info_t file_info;
    QString _serverFileName;

};

#endif //CLIENT_FILEINFO_H
