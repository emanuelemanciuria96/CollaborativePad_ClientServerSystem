//
// Created by utente on 11/08/2020.
//

#include "FileSystemTreeView.h"
#include <QtWidgets/QGridLayout>
#include <iostream>
#include "FileSystemTreeView.h"
#include <QIconEngine>
#include <QApplication>
#include <QAction>


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

    setupRightClickMenu();

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &FileSystemTreeView::openCustomMenu);

    root = new QTreeWidgetItem(this);
    this->insertTopLevelItem(0,root);
    root->setIcon(0,home_dir);
    root->setExpanded(true);

}

void FileSystemTreeView::setupRightClickMenu() {

    rightClickMenu = new QMenu(this);
    auto newAct = new QAction("edit");
    connect(newAct,&QAction::triggered,[](){
        std::cout<<"hai modificato il nome del file"<<std::endl;
    });

    rightClickMenu->addAction(newAct);
}

void FileSystemTreeView::openCustomMenu(const QPoint &pos) {

    auto nd = this->itemAt(pos);

    rightClickMenu->exec(this->mapToGlobal(pos));

}

QTreeWidgetItem* FileSystemTreeView::addChild(QTreeWidgetItem *parent, QString name, QString description) {

    QTreeWidgetItem *child = new QTreeWidgetItem();

    child->setText(0, name);
    child->setText(1, description);

    if( description == "FILE" )
        child->setIcon(0,file_icn);
    else
        child->setIcon(0, dir_close);

    parent->addChild(child);

    return child;

}

void FileSystemTreeView::constructFromPaths(const QVector<QString> &paths) {

    for(auto path: paths){

        auto strs = path.split("/");
        auto itm = root;
        QString F_D = "DIR";
        QString tmpPath = "";
        int i = 0;

        for( auto name: strs){
            tmpPath += name;

            if( ++i == strs.size() )
                F_D = "FILE";

            if( isChild(itm,name) ){
                itm = itemFromIndex(model.find(tmpPath)->second);
            }else {
                itm = addChild(itm, name, F_D);
                model.insert(std::make_pair(tmpPath, indexFromItem(itm)));
            }

            tmpPath += "/";
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

void FileSystemTreeView::openFile(QTreeWidgetItem *item, int column) {

    if( item->text(1) == "FILE") {
        QString path = "";
        if( item->parent() != root)
            path = item->parent()->text(0)+"/"+item->text(0);
        else
            path = item->text(0);

        emit opnFileRequest(path);
    }

}

FileSystemTreeView::~FileSystemTreeView() {
    delete root;
}
