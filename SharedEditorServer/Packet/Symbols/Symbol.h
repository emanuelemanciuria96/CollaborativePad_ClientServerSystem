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
    short alignmentType;

public:
    Symbol():_ch(),_symId(-1,-1),_pos(0){};
    Symbol(QChar ch, qint32 id, quint32 cnt,std::vector<quint32> &pos):
        _ch(ch),_symId(id,cnt),_pos(pos){}
    Symbol(QChar ch, qint32 id, quint32 cnt,std::vector<quint32> &pos, QTextCharFormat& frmt):
            _ch(ch),_symId(id,cnt),_pos(pos),_format(frmt){}
    Symbol(QChar ch, qint32 id, quint32 cnt,std::vector<quint32> &pos, QTextCharFormat& frmt, short alignment):
            _ch(ch),_symId(id,cnt),_pos(pos),_format(frmt),alignmentType(alignment){}

    bool operator==(Symbol& s) const {
        return _symId == s._symId && _pos==s._pos;
    }
    bool operator<(const Symbol s) const {
        return _pos<s._pos || (_pos==s._pos && _symId < s._symId); }
    bool operator>(Symbol& s) const {
        return _pos>s._pos || (_pos==s._pos && _symId > s._symId); }
    std::vector<quint32> getPos() const { return _pos; }
    void setPos(std::vector<quint32>& pos) { _pos = pos; }
    QChar getValue() const { return _ch; }
    SymId getSymId() const { return _symId; }
    const QTextCharFormat& getFormat() const {return _format; }
    void setFormat(QTextCharFormat& format) {_format = format; }
    void mergeFormat(const QTextCharFormat& other) {_format.merge(other); }
    void setAlignmentType(short type) {alignmentType=type;};
    short getAlignmentType() const {return alignmentType;};
};


#endif //ES3_PROJ_NETWORKSERVER_SYMBOL_H
