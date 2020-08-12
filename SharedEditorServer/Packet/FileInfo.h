//
// Created by utente on 12/08/2020.
//

#ifndef SHAREDEDITORSERVER_FILEINFO_H
#define SHAREDEDITORSERVER_FILEINFO_H

#include "Payload.h"

class FileInfo: public Payload{

public:
    typedef enum {start = 1, eof = 2} file_info_t;

    FileInfo(file_info_t info, qint32 _siteID):file_info(info),Payload(_siteID){}
    file_info_t getFileInfo(){ return file_info; };
private:
    file_info_t file_info;

};


#endif //SHAREDEDITORSERVER_FILEINFO_H
