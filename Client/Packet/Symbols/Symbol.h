//
// Created by muska on 15/10/2019.
//

#ifndef ES3_PROJ_NETWORKSERVER_SYMBOL_H
#define ES3_PROJ_NETWORKSERVER_SYMBOL_H


#include <vector>
#include <QtGlobal>
#include <QChar>
#include <QtGui/QTextCharFormat>
#include "SymId.h"

class Symbol {
private:
    QChar _ch;
    SymId _symId;
    std::vector<quint32> _pos;
    QTextCharFormat _format;
    short alignmentType=0;
public:
    Symbol():_ch(),_symId(-1,-1),_pos(0), _format(QTextCharFormat()){};
    Symbol(QChar ch, qint32 id, quint32 cnt,std::vector<quint32> &pos):
    _ch(ch),_symId(id,cnt),_pos(pos), _format(QTextCharFormat()){};
    Symbol(QChar ch, qint32 id, quint32 cnt,std::vector<quint32> &pos, QTextCharFormat& format):
        _ch(ch),_symId(id,cnt),_pos(pos), _format(format){}
    bool operator==(Symbol s){
        return _symId == s._symId  && _pos == s._pos;
    }
    bool operator<(Symbol s){
        return _pos<s._pos || (_pos==s._pos && _symId < s._symId); }
    bool operator>(Symbol s){
        return _pos>s._pos || (_pos==s._pos && _symId > s._symId); }
    std::vector<quint32> getPos(){ return _pos; }
    void setPos(std::vector<quint32>& pos){ _pos = pos; }
    QChar getValue() { return _ch; }
    SymId getSymId() const { return _symId; }
    QTextCharFormat& getFormat() {return _format;};
    void setFormat(QTextCharFormat& format) {_format = format;};
    void setAlignmentType(short type) {alignmentType=type;};
    short getAlignmentType() {return alignmentType;};
//    Symbol& operator=(const Symbol& s){
//        if(this != &s){
//            this->_ch =s._ch;
//            this->_symId = s._symId;
//            this->_pos = s._pos;
//        }
//        return *this;
//    }
};


#endif //ES3_PROJ_NETWORKSERVER_SYMBOL_H
