//
// Created by muska on 15/10/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_SYMID_H
#define ES3_PROJ_NETWORKSERVER_SYMID_H

#include <QtGlobal>

class SymId{
private:
    qint32 _siteId;
    quint32 _count;
public:
    SymId(qint32 id,quint32 cnt):_siteId(id),_count(cnt){}
    bool operator==(SymId si) const {
        return _siteId==si._siteId && _count==si._count;}
    //questa comparazione serve dal momento che bisogna che ci sia una
    //regola comune ed imparziale per ordinare i simboli con stessa posizione
    //la regola è:
    //  -un SymId è minore di un altro se ha siteId minore
    //  -a parità di siteId, è minore se ha il count minore
    bool operator<(SymId si) const {
        return _siteId<si._siteId || (_siteId==si._siteId && _count<si._count);}
    bool operator>(SymId si) const {
        return _siteId>si._siteId || (_siteId==si._siteId && _count>si._count);}
    quint32 getCount() { return _count; }
    qint32 getSiteId() { return _siteId; }
};


#endif //ES3_PROJ_NETWORKSERVER_SYMID_H
