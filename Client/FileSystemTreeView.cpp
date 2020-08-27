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

    root = new QTreeWidgetItem(this);
    this->insertTopLevelItem(0,root);
    root->setIcon(0,home_dir);
    root->setExpanded(true);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &FileSystemTreeView::itemDoubleClicked, this, &FileSystemTreeView::openFile);
    connect(this, &QWidget::customContextMenuRequested, this, &FileSystemTreeView::openCustomMenu);
    connect(this, &FileSystemTreeView::itemChanged, this, &FileSystemTreeView::renameFile);

}

void FileSystemTreeView::setupRightClickMenu() {

    rightClickMenu = new QMenu(this);
    auto actRn = new QAction("Rename");
    auto actRm = new QAction("Delete");

    rightClickMenu->addAction(actRm);
    rightClickMenu->addAction(actRn);
}

void FileSystemTreeView::openCustomMenu(const QPoint &pos) {

    auto rightClickedNode = this->itemAt(pos);
    auto selectedAction = rightClickMenu->exec(this->mapToGlobal(pos));

    if( selectedAction == nullptr) return;

    if( selectedAction->text() == "Delete" ){
        removeFile(rightClickedNode);
    }
    else if( selectedAction->text() == "Rename" ){
        previousName = rightClickedNode->text(0);
        this->editItem(rightClickedNode,0);
    }

}

QTreeWidgetItem* FileSystemTreeView::addChild(QTreeWidgetItem *parent, QString name, QString description) {

    isRenaming = false;

    auto child = new QTreeWidgetItem();

    child->setText(0, name);
    child->setText(1, description);
    child->setFlags(child->flags() | Qt::ItemIsEditable );

    if( description == "FILE" )
        child->setIcon(0,file_icn);
    else
        child->setIcon(0, dir_close);

    parent->addChild(child);

    isRenaming = true;

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

void FileSystemTreeView::renameFile(QTreeWidgetItem *item, int column) {

    if( !isRenaming ) return;

    QString actualName = item->text(0);

    if(actualName == ""){
        isRenaming = false;
        item->setText(0,previousName);
        isRenaming = true;
        return;
    }

    auto parent = item->parent();
    if( parent != root ){
        previousName = parent->text(0)+"/"+previousName;
        actualName = parent->text(0)+"/"+actualName;
    }

    if( previousName != actualName )
        emit renFileRequest(previousName,actualName);

    auto node = model.find(previousName);
    model.insert(std::make_pair(actualName,node->second));
    model.erase(node);

}

void FileSystemTreeView::removeFile(QTreeWidgetItem *item) {
    //TODO: da capire se deve essere eliminato per tutti o solo per il client corrente
}

void FileSystemTreeView::editFileName(QString &oldName, QString &newName) {

    std::cout<<"renamed file from <"<<oldName.toStdString()<<"> to <"<<newName.toStdString()<<">"<<std::endl;

    auto node = model.find(oldName);
    if( node == model.end() ){
        std::cout<<"-----Il file che si sta rinominando da remoto non è presente!!!";
        return;
    }

    auto itm = itemFromIndex(node->second);
    isRenaming = false;
    itm->setText(0,newName.split("/").last());
    isRenaming = true;

    model.insert(std::make_pair(newName,node->second));
    model.erase(node);

}

FileSystemTreeView::~FileSystemTreeView() {
    delete root;
}
