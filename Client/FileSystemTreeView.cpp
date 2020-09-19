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
    this->setColumnCount(1);
    this->setEditTriggers(QAbstractItemView::SelectedClicked);
    this->setHeaderHidden(true);
    this->setIndentation(10);

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
    connect(this, &FileSystemTreeView::itemDoubleClicked, [this](QTreeWidgetItem *itm, int column){ previousName=itm->text(0);} );
    connect(this, &FileSystemTreeView::itemClicked, [this](QTreeWidgetItem *itm, int column){ previousName=itm->text(0);} );
    connect(this, &QWidget::customContextMenuRequested, this, &FileSystemTreeView::openCustomMenu);
    connect(this, &FileSystemTreeView::itemChanged, this, &FileSystemTreeView::renameFile);

}

void FileSystemTreeView::setupRightClickMenu() {

    rightClickMenu = new QMenu(this);

    rightClickMenu->addAction(new QAction("Rename"));
    rightClickMenu->addAction(new QAction("Delete"));
    rightClickMenu->addAction(new QAction("Invite"));
    rightClickMenu->addAction(new QAction("New File"));

}

void FileSystemTreeView::openCustomMenu(const QPoint &pos) {

    auto rightClickedNode = this->itemAt(pos);

    if(rightClickedNode == nullptr ){
        rightClickMenu->actions().at(0)->setDisabled(true);
        rightClickMenu->actions().at(1)->setDisabled(true);
        rightClickMenu->actions().at(2)->setDisabled(true);
    }
    else {
        if (rightClickedNode->parent() != root)
            rightClickMenu->actions().at(2)->setDisabled(true);

        if (!(rightClickedNode->flags() & Qt::ItemIsEditable)) {
            rightClickMenu->actions().at(0)->setDisabled(true);
            rightClickMenu->actions().at(1)->setDisabled(true);
        }
    }

    auto selectedAction = rightClickMenu->exec(this->mapToGlobal(pos));

    if( selectedAction == nullptr){} // senza questo crasha dopo due right-click consecutivi
    else if( selectedAction->text() == "Delete" ){
        removeFile(rightClickedNode);
    }
    else if( selectedAction->text() == "Rename" ){
        previousName = rightClickedNode->text(0);
        this->editItem(rightClickedNode,0);
    }
    else if ( selectedAction->text() == "Invite" ) {
        inviteUser(rightClickedNode);
    }
    else if( selectedAction->text() == "New File" ){
        insertFile();
    }

    for(auto act:rightClickMenu->actions())
        act->setDisabled(false);

}

QTreeWidgetItem* FileSystemTreeView::addChild(QTreeWidgetItem *parent, QString name, QString description) {

    isRenaming = false;

    auto child = new QTreeWidgetItem();

    child->setText(0, name);

    if( description == "FILE" ) {
        child->setIcon(0, file_icn);
        child->setFlags(child->flags() | Qt::ItemIsEditable );
    }
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

    this->sortItems(0,Qt::AscendingOrder);

}

bool FileSystemTreeView::isChild(QTreeWidgetItem *parent, QString &name) {

    int i = 0;  // takeChildren non si deve chiamare perchè elimina tutti i children
    for( ; i<parent->childCount(); i++ )
        if(parent->child(i)->text(0) == name)
            return true;

    return false;
}

void FileSystemTreeView::insertFile(){

    QString defaultName = "new_file";
    QVector<QString> vec;

    int i = 0;
    auto tmp = defaultName;
    while( isChild(root, tmp) )
        tmp = defaultName+"("+QString::number(++i)+")";
    defaultName = tmp;

    auto newFile = addChild(root,defaultName,"FILE");
    model.insert( std::make_pair(defaultName,indexFromItem(newFile)) );

    emit newFileAdded(defaultName);
    vec.push_back(defaultName);
    emit newFileUpdateGrid(vec);

    previousName = defaultName;
    this->editItem(newFile,0);

    this->sortItems(0,Qt::AscendingOrder);

}

void FileSystemTreeView::openFile(QTreeWidgetItem *item, int column) {

    if( item->flags() & Qt::ItemIsEditable ) {
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

    emit renFileRequest(previousName, actualName);
    auto node = model.find(previousName);
    model.insert(std::make_pair(actualName, node->second));
    model.erase(node);
    emit fileNameEdited(previousName, actualName);

    this->sortItems(0,Qt::AscendingOrder);

}


void FileSystemTreeView::removeFile(QTreeWidgetItem *item) {

    QString name = item->text(0);

    auto parent = item->parent();
    if( parent != root )
        name = parent->text(0)+"/"+name;

    parent->removeChild(item);
    if( parent->childCount()==0 && parent!=root )
        parent->parent()->removeChild(parent);
    model.erase(name);

    emit rmvFileRequest(name);
}

void FileSystemTreeView::editFileName(QString &oldName, QString &newName) {

    std::cout<<"renamed file from <"<<oldName.toStdString()<<"> to <"<<newName.toStdString()<<">"<<std::endl;

    if(model.empty()) return;

    auto node = model.find(oldName);
    if( node == model.end() ){
        std::cout<<" ---Il file che si sta rinominando da remoto non è presente!!!";
        return;
    }

    auto itm = itemFromIndex(node->second);
    isRenaming = false;
    itm->setText(0,newName.split("/").last());
    isRenaming = true;

    model.insert(std::make_pair(newName,node->second));
    model.erase(node);
}

void FileSystemTreeView::remoteFileDeletion(QString &fileName) {

    auto i = model.find(fileName);
    if(i == model.end() )
        return;

    auto item = itemFromIndex(i->second);
    auto parent = item->parent();
    parent->removeChild(item);
    if( parent->childCount()==0 && parent!=root )
        parent->parent()->removeChild(parent);
    model.erase(fileName);
}

void FileSystemTreeView::inviteUser(QTreeWidgetItem *item) {
        emit inviteRequest(item->text(0));
}

FileSystemTreeView::~FileSystemTreeView() {
    delete root;
}
