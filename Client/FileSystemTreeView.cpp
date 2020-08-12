//
// Created by utente on 11/08/2020.
//

#include "FileSystemTreeView.h"
#include <QtWidgets/QGridLayout>
#include <iostream>
#include "FileSystemTreeView.h"
#include <QIconEngine>
#include <QApplication>


FileSystemTreeView::FileSystemTreeView( QWidget *parent) :QTreeWidget(parent){

    this->setAnimated(true);
    this->setColumnCount(2);
    QStringList headers;
    headers<<"name"<<"description";
    this->setHeaderLabels(headers);

    home_dir = QIcon("./icons/directory_icon_opened.png");
    dir_open = QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon);
    dir_close = QApplication::style()->standardIcon(QStyle::SP_DirClosedIcon);
    file_icn = QIcon("./icons/text_file_icon.png");

    root = new QTreeWidgetItem(this);
    this->insertTopLevelItem(0,root);
    root->setIcon(0,home_dir);
    root->setExpanded(true);

}

QTreeWidgetItem* FileSystemTreeView::addChild(QTreeWidgetItem *parent, QString name) {

    QTreeWidgetItem *child = new QTreeWidgetItem();

    auto strings = name.split(">");
    child->setText(0, strings[0]);

    auto children = parent->takeChildren();

    if( strings[1] == "F" ) {
        child->setIcon(0,file_icn);
        child->setText(1, "FILE");
    }
    else {
        child->setIcon(0, dir_close);
        child->setText(1, "DIR");
    }

    children.push_back(child);
    parent->addChildren(children);


    return child;

}

void FileSystemTreeView::constructFromPaths(const QVector<QString> &paths) {

    for(auto path: paths){
        QString intermediatePath = "";
        auto itm = root;
        auto strings = path.split("/");

        strings.erase(strings.begin()); // dato che il path inizia con '/' il primo valore è il nome "", e lo elimino

        for(auto str: strings){

            QString suffix = "";

            if( str != strings.last() )
                suffix = ">D";
            else{
                suffix = ">"+str.split(">").last();
                str = str.split(">").first();
            }
            intermediatePath+="/"+str;

            if( isChild( itm, str) ){
                itm = itemFromIndex(model.find(intermediatePath+suffix)->second);
            }
            else{
                itm = addChild(itm,str+suffix);
                model.insert(std::make_pair(intermediatePath+suffix,indexFromItem(itm)));
            }
        }
    }

}

bool FileSystemTreeView::isChild(QTreeWidgetItem *parent, QString name) {

    int i = 0;  // takeChildren non si deve chiamare perchè elimina tutti i children
    for( ; i<parent->childCount(); i++ )
        if(parent->child(i)->text(0) == name)
            return true;

    return false;
}

FileSystemTreeView::~FileSystemTreeView() {
    delete root;
}

