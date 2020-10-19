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
#include <QtWidgets/QMessageBox>


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
    root->setFlags(root->flags() & (~Qt::ItemIsSelectable));
    this->setRootIsDecorated(false);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &FileSystemTreeView::itemDoubleClicked, this, &FileSystemTreeView::openFile);
    connect(this, &FileSystemTreeView::itemDoubleClicked, [this](QTreeWidgetItem *itm, int column){ previousName=itm->text(0);} );
    connect(this, &FileSystemTreeView::itemClicked, [this](QTreeWidgetItem *itm, int column){ previousName=itm->text(0);} );
    connect(this, &FileSystemTreeView::itemCollapsed, [this](QTreeWidgetItem *itm){ if(itm == root) root->setExpanded(true);} );
    connect(this, &QWidget::customContextMenuRequested, this, &FileSystemTreeView::openCustomMenu);
    connect(this, &FileSystemTreeView::itemChanged, this, &FileSystemTreeView::renameFile);
    auto p = palette();
    p.setColor(QPalette::Highlight,Qt::red);
    setPalette(p);

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
        isEditing = true;
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
        child->setText(1, "FILE");
        child->setIcon(0, file_icn);
        child->setFlags(child->flags() | Qt::ItemIsEditable );
    }
    else {
        child->setIcon(0, dir_close);
        child->setText(1, "DIR");
    }

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

    sort();
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
    isEditing = true;
    this->editItem(newFile,0);

}

void FileSystemTreeView::openFile(QTreeWidgetItem *item, int column) {

    if( item->flags() & Qt::ItemIsEditable ) {
        QString path = "";
        if( item->parent() != root) {
            path = item->parent()->text(0) + "/" + item->text(0);
        }else {
            path = item->text(0);
        }
        emit opnFileRequest(path);
        emit canInvite( item->parent()==root );
    }

}

void FileSystemTreeView::renameFile(QTreeWidgetItem *item, int column) {

    isEditing = false;

    if( !isRenaming ) return;

    QString actualName = item->text(0);
    QRegularExpression expr(R"(^(?!\.)(?!com[0-9]$)(?!con$)(?!lpt[0-9]$)(?!nul$)(?!prn$)[^\|\*\?\\:<>/$"]*[^\.\|\*\?\\:<>/$"]+$)");

    if(!expr.match(actualName).hasMatch() || actualName.length() > 20 || actualName.isEmpty() || model.find(actualName) != model.end()) {
        isRenaming = false;
        item->setText(0,previousName);
        isRenaming = true;
        previousName = "";
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
    previousName = "";

    sort();

}

void FileSystemTreeView::removeFile(QTreeWidgetItem *item) {

    QString name = item->text(0);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete file");
    msgBox.setText("Do you want to delete "+name+"?");
    msgBox.setStandardButtons(QMessageBox::Ok  | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setMinimumSize(600, 1000);
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Ok:
            break;
        case QMessageBox::Cancel:
            return;
        default:
            return;
    }

    auto parent = item->parent();
    if( parent != root )
        name = parent->text(0)+"/"+name;

    parent->removeChild(item);
    if( parent->childCount()==0 && parent!=root )
        parent->parent()->removeChild(parent);
    model.erase(name);

    emit rmvFileRequest(name);
}

void FileSystemTreeView::editFileName(const QString &oldName, const QString &newName) {

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

    sort();

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

void FileSystemTreeView::mousePressEvent(QMouseEvent *ev) {
    auto item = this->itemAt(ev->pos());
    if( item == nullptr) {
        this->clearSelection();
        previousName="";
    }
    QTreeView::mousePressEvent(ev);
}

void FileSystemTreeView::keyPressEvent(QKeyEvent *ev) {
    if( ev->key() == Qt::Key_Delete){
        auto items = this->selectedItems();
        for(auto i : items) {
            removeFile(i);
        }
    }

    if(ev->key() == Qt::Key_Return && !isEditing){

        auto items = this->selectedItems();
        if( items.size() == 1 )
            openFile(items.first(),0);
    }
    QTreeView::keyPressEvent(ev);
}

void FileSystemTreeView::sort() {
    auto children  = root->takeChildren();
    int i = 0;
    for( ;i<children.size();i++){
        int j = 0;
        for( ; j<children.size()-i-1; j++){
            if(children[j]->text(1)>children[j+1]->text(1) ||
                (children[j]->text(1)==children[j+1]->text(1) && children[j]->text(0)>children[j+1]->text(0)) ) {
                children.swap(j,j+1);
            }
        }
    }

    for(auto c: children)
        if( c->text(1)=="DIR")
            c->sortChildren(0,Qt::AscendingOrder);


    root->insertChildren(0,children);

}

