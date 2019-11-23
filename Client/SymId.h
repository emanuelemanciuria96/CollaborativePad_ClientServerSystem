//
// Created by Emanuele on 26/08/2019.
//

#ifndef ES3_PROJ_SYMID_H
#define ES3_PROJ_SYMID_H


class SymId{
private:
    qint32 _siteId;
    qint32 _count;
public:
    SymId(qint32 id,qint32 cnt):_siteId(id),_count(cnt){}
    bool operator==(SymId si){
        return _siteId==si._siteId && _count==si._count;}
    qint32 getCount() { return _count; }
    qint32 getSiteId() { return _siteId; }
};

#endif //ES3_PROJ_SYMID_H
