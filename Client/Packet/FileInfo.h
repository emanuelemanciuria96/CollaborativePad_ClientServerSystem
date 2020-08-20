//
// Created by utente on 12/08/2020.
//

#ifndef CLIENT_FILEINFO_H
#define CLIENT_FILEINFO_H

#include "Payload.h"

class FileInfo: public Payload{

public:
    typedef enum {start = 1, eof = 2} file_info_t;

    FileInfo(qint32 _siteID, file_info_t info):file_info(info),Payload(_siteID){}
    file_info_t getFileInfo(){ return file_info; };
private:
    file_info_t file_info;

};

#endif //CLIENT_FILEINFO_H
