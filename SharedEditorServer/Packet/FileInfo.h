//
// Created by utente on 12/08/2020.
//

#ifndef SHAREDEDITORSERVER_FILEINFO_H
#define SHAREDEDITORSERVER_FILEINFO_H

#include <QString>
#include "Payload.h"

class FileInfo: public Payload{

public:
    typedef enum {start = 1, eof = 2, err = 3} file_info_t;

    FileInfo(file_info_t info, qint32 _siteID):
            file_info(info),Payload(_siteID){}
    FileInfo(file_info_t info, qint32 _siteID,QString &serverFileName):
        file_info(info),Payload(_siteID),_serverFileName(serverFileName){}
    file_info_t getFileInfo(){ return file_info; }
    QString getServerFileName(){ return _serverFileName;}
private:
    file_info_t file_info;
    QString _serverFileName;

};


#endif //SHAREDEDITORSERVER_FILEINFO_H
