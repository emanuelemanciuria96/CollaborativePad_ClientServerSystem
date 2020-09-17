#include "filesystemgridview.h"
#include "./ui_filesystemgridview.h"
#include <QGridLayout>
#include <QListWidgetItem>
#include <QDebug>
#include <QFont>
#include <QMenu>
#include <QInputDialog>

FileSystemGridView::FileSystemGridView(QWidget *parent,const QVector<QString> &paths) :
        QWidget(parent),
        ui(new Ui::FileSystemGridView)
{

    //constructFromPaths(paths);
    ui->setupUi(this);
    label=this->mainFolder;
    ui->listWidget->setFlow(QListView::LeftToRight);

    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget->setIconSize(QSize(130,130));
    ui->listWidget->setFont(QFont( "Helvetica", 12 ));

    for(auto folder:this->fileSystem.keys()){
        if(folder==this->mainFolder){
            continue;
        }
        QListWidgetItem *item=new QListWidgetItem;
        item->setText(folder);
        item->setIcon(*folderIcon);
        itemProperties(item);
        ui->listWidget->addItem(item);
    }
    for(auto file:this->fileSystem[this->mainFolder]){
        QListWidgetItem *item=new QListWidgetItem;
        item->setText(file);
        item->setIcon(*textIcon);
        itemProperties(item);
        ui->listWidget->addItem(item);
    }
}


FileSystemGridView::~FileSystemGridView()
{
    delete ui;
}

QVector<QString> FileSystemGridView::getVector() {
    QVector<QString> V;
    for(auto folder:this->fileSystem.keys()){
        for(auto file:this->fileSystem[folder]) {
            if(folder==this->mainFolder) {
                V.push_back(file);
                qDebug()<<file;
            }else{
                V.push_back(folder+"/"+file);
                qDebug()<<folder+"/"+file;
            }
        }
    }
    return V;
}

void FileSystemGridView::reload(const QString folder,bool isFolder)
{
    ui->listWidget->clear();
    if(isFolder){
        emit openFolder(folder);
        for(auto file:this->fileSystem[folder]){
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(file);
            item->setIcon(*textIcon);
            item->setSizeHint(QSize(200, 180));
            ui->listWidget->addItem(item);
        }
        this->state=folder;
    }else{
        emit back();
        for(auto folder:this->fileSystem.keys()){
            if(folder==this->mainFolder){
                continue;
            }
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(folder);
            item->setIcon(*folderIcon);
            itemProperties(item);
            ui->listWidget->addItem(item);
        }
        for(auto file:this->fileSystem[this->mainFolder]){
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(file);
            item->setIcon(*textIcon);
            itemProperties(item);
            ui->listWidget->addItem(item);
        }
        state=this->mainFolder;
    }
}

void FileSystemGridView::constructFromPaths(const QVector<QString> &paths){
    this->fileSystem.clear();
    for(auto p:paths){
        QVector<QString> V;
        QString folder;
        if(p.count("/")>0){
            folder=p.split("/")[0];
        }else{
            folder=this->mainFolder;
        }
        this->fileSystem.insert(folder,V);
    }
    for(auto p:paths){
        QVector<QString> V;
        QString folder;
        QString file;
        if(p.count("/")>0){
            folder=p.split("/")[0];
            file=p.split("/")[1];
        }else{
            folder=this->mainFolder;
            file=p;
        }
        fileSystem[folder].push_back(file);
    }
    reload(this->mainFolder,false);
}

void FileSystemGridView::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(fileSystem.keys().count(item->text())>0){
        qDebug()<<"Open folder "<<item->text();
        label=this->mainFolder+"/"+item->text();
        reload(item->text(),true);
    }else{
        if(item->text()==""){
            return;
        }
        openFile(this->state+"/"+item->text());
    }
}

void FileSystemGridView::on_listWidget_itemSelectionChanged(){
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(this->state!=mainFolder){
        emit canInvite(false);
    }else if(fileSystem.keys().count(item->text())==0){
        emit canInvite(true);//file clicked
    }else{
        emit canInvite(false);//folder clicked
    }
}

void FileSystemGridView::reloadBack(){
    qDebug() << "Back";
    label = this->mainFolder;
    reload("", false);
}

void FileSystemGridView::invite(){
    QListWidgetItem *item=ui->listWidget->currentItem();
    qDebug() << "invite "<<item->text();
    emit inviteRequest(item->text());
}

void FileSystemGridView::addFile(){
    bool ok;
    QString newNameFile = QInputDialog::getText(0, "",
                                                "Add new file", QLineEdit::Normal,
                                                "", &ok);
    if(!ok || newNameFile.size()==0){
        return;
    }
    qDebug() << "addFile";
    emit newFileAdded(newNameFile);
}

void FileSystemGridView::itemProperties(QListWidgetItem *item)
{
    item->setSizeHint(QSize(200, 180));
}

void FileSystemGridView::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex t = ui->listWidget->indexAt(pos);
    if(t.row()<0){
        return;
    }
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item->text()==""){
        return;
    }
    if(fileSystem.keys().count(item->text())>0){
        QPoint globalPos = ui->listWidget->mapToGlobal(pos);
        QMenu* myMenu=new QMenu();

        myMenu->addAction("Open "+item->text());
        auto selectedAction = myMenu->exec(globalPos);
        if( selectedAction == nullptr){} // senza questo crasha dopo due right-click consecutivi
        else if( selectedAction->text() == "Open "+item->text() ){
            reload(item->text(),true);
        }
        return;
    }
    QPoint globalPos = ui->listWidget->mapToGlobal(pos);

    QMenu* myMenu=new QMenu();

    myMenu->addAction("Open "+item->text());
    if(this->state==mainFolder){
        myMenu->addAction("Invite");
    }
    myMenu->addAction("Rename");
    myMenu->addAction("Delete");

    auto selectedAction = myMenu->exec(globalPos);
    if( selectedAction == nullptr){} // senza questo crasha dopo due right-click consecutivi
    else if( selectedAction->text() == "Delete" ){
        deleteFile(this->state+"/"+item->text());
    }else if( selectedAction->text() == "Rename" ){
        QString nameFolder=this->state;
        QString oldNameFile=item->text();
        bool ok;
        QString newNameFile = QInputDialog::getText(0, "",
                                                    "Rename "+oldNameFile, QLineEdit::Normal,
                                                    "", &ok);
        if(!ok || oldNameFile==newNameFile || newNameFile.size()==0){
            return;
        }
        renameFile(this->state+"/"+oldNameFile,this->state+"/"+newNameFile);
    }else if( selectedAction->text() == "Open "+item->text()){
        openFile(this->state+"/"+item->text());
    }else if( selectedAction->text() == "Invite"){
        invite();
    }
}
QString FileSystemGridView::getState() {
    return this->state;
}
QString FileSystemGridView::getMainFolder() {
    return this->mainFolder;
}
void FileSystemGridView::openFile(QString file)
{
    QString nameFile=file.split("/")[1];
    QString folder=file.split("/")[0];
    qDebug()<<"Open "+nameFile;
    if(folder==mainFolder){
        emit opnFileRequest(nameFile);
    }else {
        emit opnFileRequest(file);
    }
}

void FileSystemGridView::deleteFile(QString file)
{
    QString nameFile=file.split("/")[1];
    QString folder=file.split("/")[0];

    int index=0;
    for(auto f:fileSystem[folder]){
        if(f==nameFile){
            fileSystem[folder].removeAt(index);
            break;
        }
        index++;
    }
    if(folder!=this->state){
        return;
    }
    if(folder==this->mainFolder){
        reload(folder,false);
        emit rmvFileRequest(nameFile);
    }else{
        reload(folder,true);
        emit rmvFileRequest(file);
    }
}
void FileSystemGridView::renameFile(QString oldFile,QString newFile)
{
    QString oldNameFile=oldFile.split("/")[1];
    QString newNameFile=newFile.split("/")[1];
    QString folder=newFile.split("/")[0];
    int index=0;
    for(auto file:fileSystem[folder]){
        if(file==oldNameFile){
            fileSystem[folder][index]=newNameFile;
            break;
        }
        index++;
    }
    if(folder!=this->state){
        return;
    }
    if(folder==this->mainFolder){
        reload(folder,false);
        emit renFileRequest(oldNameFile, newNameFile);
    }else{
        reload(folder,true);
        emit renFileRequest(oldFile, newFile);
    }
}




