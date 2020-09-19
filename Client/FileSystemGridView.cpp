#include "filesystemgridview.h"
#include "./ui_filesystemgridview.h"
#include <QGridLayout>
#include <QListWidgetItem>
#include <QDebug>
#include <QFont>
#include <QMenu>
#include <QInputDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QMessageBox>

FileSystemGridView::FileSystemGridView(QWidget *parent,const QVector<QString> &paths) :
        QWidget(parent),
        ui(new Ui::FileSystemGridView) {


    ui->setupUi(this);
    ui->label->setStyleSheet("font: 18pt; ");
    ui->label->setText(this->mainFolder.split(".")[1]);
    ui->label_2->setStyleSheet("font: 18pt; color: rgba(0,0,0,1);font-family: 'Consolas'");
    ui->label_2->hide();
    ui->listWidget->setFlow(QListView::LeftToRight);

    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget->setIconSize(QSize(130, 130));
    ui->listWidget->setStyleSheet(" padding-top: 30px;border-radius: 20px;background-color: rgba(0,0,0,0.1);font: 12pt;font-family: 'Verdana';");
    constructFromPaths(paths);
}
FileSystemGridView::~FileSystemGridView()
{
    delete ui;
}

void FileSystemGridView::reload(const QString folder,bool isFolder)
{
    ui->listWidget->clear();
    if(isFolder){
        emit openFolder(folder);
        ui->label->setStyleSheet("font: 18pt;color: rgba(0,0,0,0.3);font-family: 'Consolas'");
        ui->label->setText(this->mainFolder.split(".")[1]+"> ");
        ui->label_2->setText(" "+folder);
        ui->label_2->show();
        for(auto file:this->fileSystem[folder]){
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(file);
            item->setIcon(*textIcon);
            item->setStatusTip("file");
            item->setSizeHint(QSize(200, 180));
            ui->listWidget->addItem(item);
        }
        this->state=folder;
    }else{
        emit back();
        ui->label->setStyleSheet("font: 18pt;color: rgba(0,0,0,1);font-family: 'Consolas'");
        ui->label->setText(this->mainFolder.split(".")[1]);
        ui->label_2->hide();
        for(auto folder:this->fileSystem.keys()){
            if(folder==this->mainFolder){
                continue;
            }
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(folder);
            item->setIcon(*folderIcon);
            item->setStatusTip("folder");
            itemProperties(item);
            ui->listWidget->addItem(item);
        }
        for(auto file:this->fileSystem[this->mainFolder]){
            QListWidgetItem *item=new QListWidgetItem;
            item->setText(file);
            item->setIcon(*textIcon);
            item->setStatusTip("file");
            itemProperties(item);
            ui->listWidget->addItem(item);
        }
        state=this->mainFolder;
    }
}

void FileSystemGridView::constructFromPaths(const QVector<QString> &paths){
    QStringList folders;
    for(auto p:paths){
        QString folder;
        if(p.count("/")>0){
            folder=p.split("/")[0];
        }else{
            folder=this->mainFolder;
        }
        folders.push_back(folder);
    }
    folders.sort();
    for(auto folder:folders){
        if(this->fileSystem.keys().count(folder)>0){
            continue;
        }
        QStringList V;
        this->fileSystem.insert(folder,V);
    }
    for(auto p:paths){
        QStringList V;
        QString folder;
        QString file;
        if(p.count("/")>0){
            folder=p.split("/")[0];
            file=p.split("/")[1];
        }else{
            folder=this->mainFolder;
            file=p;
        }
        if(this->fileSystem[folder].count(file)>0){
            return;
        }
        fileSystem[folder].push_back(file);
    }

    for(auto folder:folders){
        this->fileSystem[folder].sort();
    }
    if(this->state==this->mainFolder) {
        reload(this->mainFolder, false);
    }else{
        reload(this->state, true);
    }
}

void FileSystemGridView::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->statusTip()=="folder"){
        qDebug()<<"Open folder "<<item->text();
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
    if(item->statusTip()=="file"){
        emit canInvite(true);//file clicked
    }else{
        emit canInvite(false);//folder clicked
    }
}

void FileSystemGridView::reloadBack(){
    qDebug() << "Back";
    reload("", false);
}

void FileSystemGridView::invite(){
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(this->fileSystem.count(item->text())>0){
        emit canInvite(false);
        return;
    }
    qDebug() << "invite "<<item->text();
    emit inviteRequest(item->text());
}

void FileSystemGridView::addFile(){
    bool ok;
    QString newNameFile = QInputDialog::getText(0, "New file",
                                                "Add new file", QLineEdit::Normal,
                                                "", &ok);
    if(!ok){
        return;
    }
    for(auto file:fileSystem[this->mainFolder]){
        if(file==newNameFile){
            QMessageBox msgBox;
            msgBox.setWindowTitle("New File");
            msgBox.setText("This name already exists.");
            msgBox.setStandardButtons(QMessageBox::Ok  );
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            return;
        }
    }
    if(newNameFile.size()==0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("New File");
        msgBox.setText("Empty name. No files have been added.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle("New File");
    msgBox.setText("Do you want to create a new file named "+newNameFile+"?");
    msgBox.setStandardButtons(QMessageBox::Ok  | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
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


    qDebug() << "addFile";
    emit newFileAdded(newNameFile);
    QVector<QString> newFile{newNameFile};
    this->constructFromPaths(newFile);
    emit newFileUpdateTree(newFile);
}

void FileSystemGridView::itemProperties(QListWidgetItem *item)
{
    item->setSizeHint(QSize(200, 180));
}

void FileSystemGridView::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex t = ui->listWidget->indexAt(pos);
    if(t.row()<0){
        if(this->state!=this->mainFolder){
            return;
        }
        QPoint globalPos = ui->listWidget->mapToGlobal(pos);
        QMenu* myMenu=new QMenu();

        myMenu->addAction("New file");
        auto selectedAction = myMenu->exec(globalPos);
        if( selectedAction == nullptr){} // senza questo crasha dopo due right-click consecutivi
        else if( selectedAction->text() == "New file"){
            addFile();
        }
        return;
    }
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item->text()==""){
        return;
    }
    if(item->statusTip()=="folder"){
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
        QString newNameFile = QInputDialog::getText(0, "Rename file",
                                                    "Rename "+oldNameFile, QLineEdit::Normal,
                                                    "", &ok);
        if(!ok){
            return;
        }
        if(oldNameFile==newNameFile){
            return;
        }
        if(newNameFile.size()==0){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Rename file");
            msgBox.setText("Empty name.");
            msgBox.setStandardButtons(QMessageBox::Ok );
            return;
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("Rename file");
        msgBox.setText("Do you want to rename "+oldNameFile+" with "+newNameFile+"?");
        msgBox.setStandardButtons(QMessageBox::Ok  | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
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
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete file");
    msgBox.setText("Do you want to delete "+nameFile+"?");
    msgBox.setStandardButtons(QMessageBox::Ok  | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
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
void FileSystemGridView::localDeleteFile(QString file)
{
    QString nameFile;
    QString folder;
    if(file.count("/")>0){
        nameFile=file.split("/")[1];
        folder=file.split("/")[0];
    }else{
        nameFile=file;
        folder=this->mainFolder;
    }


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
    }else{
        reload(folder,true);
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
void FileSystemGridView::localRenameFile(QString oldFile,QString newFile) {
    QString oldNameFile;
    QString newNameFile;
    QString folder;
    if(oldFile.count("/")>0){
        oldNameFile=oldFile.split("/")[1];
        newNameFile=newFile.split("/")[1];
        folder=newFile.split("/")[0];
    }else{
        oldNameFile=oldFile;
        newNameFile=newFile;
        folder=this->mainFolder;
    }

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
    }else{
        reload(folder,true);
    }
}



