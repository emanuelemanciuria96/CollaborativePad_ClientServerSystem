#include "FileSystemGridView.h"
#include "./ui_filesystemgridview.h"
#include <QGridLayout>
#include <QListWidgetItem>
#include <QDebug>
#include <QFont>
#include <QMenu>
#include <QInputDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QMessageBox>
#include <QMouseEvent>
#include <iostream>

FileSystemGridView::FileSystemGridView(QWidget *parent,const QVector<QString> &paths) :
        QWidget(parent),
        ui(new Ui::FileSystemGridView) {
    ui->setupUi(this);
    ui->label->setStyleSheet("font: 18pt; ");
    ui->label->setText(this->mainFolder.split(".")[1]);
    ui->label_2->setStyleSheet("font: 18pt; color: rgba(0,0,0,1);");
    ui->label_2->hide();
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setMovement(QListView::Static);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget->setIconSize(QSize(130, 130));
    ui->listWidget->setStyleSheet("QListWidget {padding-top: 30px;border-radius: 20px;background-color: rgba(0,0,0,0.1);font: 12pt;}");
    this->constructFromPaths(paths);

    this->installEventFilter(this);
    ui->listWidget->viewport()->installEventFilter(this);
}
bool lastEventisFromBorder=true;
bool FileSystemGridView::eventFilter(QObject *target, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress) {
        if (target == ui->listWidget->viewport()) {
            event->ignore();
            this->clearSelection();
            lastEventisFromBorder = false;
        } else {
            if (lastEventisFromBorder) {
                event->ignore();
                this->clearSelection();
            }
            lastEventisFromBorder = true;
        }
    }
    return false;
}

FileSystemGridView::~FileSystemGridView()
{
    delete ui;
}

void FileSystemGridView::reload(const QString folder,bool isFolder,bool changeToolbar=true)
{
    ui->listWidget->clear();
    if(isFolder){
        if(changeToolbar) {
            emit openFolder(folder);
        }
        ui->label->setStyleSheet("font: 18pt;color: rgba(0,0,0,0.3);");
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
        if(changeToolbar) {
            emit back();
        }
        ui->label->setStyleSheet("font: 18pt;color: rgba(0,0,0,1);");
        ui->label->setText(this->mainFolder.split(".")[1]);
        ui->label_2->hide();
        for(auto folder:this->fileSystem.keys()){
            if(folder==this->mainFolder){
                continue;
            }
            if(fileSystem[folder].size()==0){
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
    bool error=false;
    QListWidgetItem *item=ui->listWidget->currentItem();
    QString tmpName;
    if(item== nullptr) {
        error=true;
    }else {
        tmpName=item->text();
    }
    if (this->state == this->mainFolder) {
        reload(this->mainFolder, false);
    } else {
        reload(this->state, true);
    }
    if(!error) {
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem *item = ui->listWidget->item(i);
            if (item->statusTip() == "file" && item->text() == tmpName) {
                ui->listWidget->setCurrentItem(item);
                break;
            }
        }
    }
}
void FileSystemGridView::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QListWidgetItem *item=ui->listWidget->currentItem();
        if(item!= nullptr){
            on_listWidget_itemDoubleClicked(item);
        }
    }else if (event->key() == Qt::Key_Delete) {
        QListWidgetItem *item=ui->listWidget->currentItem();
        if(item!= nullptr){
            deleteFile(this->state+"/"+item->text());
        }
    }else  if(event->key()==Qt::Key_Escape){
        if(state!=mainFolder){
            reloadBack();
        }
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
    if (item != nullptr) {
        if (item->statusTip() == "file") {
            emit canDelete(true);//file clicked
        } else {
            emit canDelete(false);//folder clicked
        }
        if (state != mainFolder) {
            return;
        }
        if (item->statusTip() == "file") {
            emit canInvite(true);//file clicked
        } else {
            emit canInvite(false);//folder clicked
        }
    }
}

void FileSystemGridView::reloadBack(){
    qDebug() << "Back";
    reload("", false);
}

void FileSystemGridView::invite(){
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item== nullptr){
        return;
    }
    if(this->fileSystem.count(item->text())>0){
        emit canInvite(false);
        return;
    }
    qDebug() << "invite "<<item->text();
    emit inviteRequest(item->text());
}
void FileSystemGridView::deleteCurrent(){
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item==nullptr){
        return;
    }
    deleteFile(this->state+"/"+item->text());
}

void FileSystemGridView::addFile(){
    bool ok;
    QInputDialog d();

    QString newNameFile = QInputDialog::getText(nullptr, "New file",
                                                "Add new file", QLineEdit::Normal,
                                                "", &ok);
    if(!ok){
        return;
    }
    QRegularExpression expr(R"(^(?!\.)(?!com[0-9]$)(?!con$)(?!lpt[0-9]$)(?!nul$)(?!prn$)[^\|\*\?\\:<>/$"]*[^\.\|\*\?\\:<>/$"]+$)");

    if(!expr.match(newNameFile).hasMatch() || newNameFile.length() > 20) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Rename file");
        msgBox.setText("Invalid name.");
        msgBox.setStandardButtons(QMessageBox::Ok );
        msgBox.exec();
        return;
    }
    for(auto file:fileSystem[this->mainFolder]){
        if(file==newNameFile){
            QMessageBox msgBox;
            msgBox.setWindowTitle("New File");
            msgBox.setText("This name already exists.");
            msgBox.setStandardButtons(QMessageBox::Ok );
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


    qDebug() << "addFile";
    emit newFileAdded(newNameFile);
    QVector<QString> newFile{newNameFile};
    this->constructFromPaths(newFile);
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        if(item->statusTip()=="file" && item->text()==newNameFile){
            ui->listWidget->setCurrentItem(item);
            break;
        }
    }
    emit newFileUpdateTree(newFile);
}
void FileSystemGridView::selectFile(QString &file) {
    QString folder=this->mainFolder;
    QString filename=file.split("/")[1];
    for(auto fol:fileSystem.keys()){
        if(fol==file.split("/")[0]){
            folder=file.split("/")[0];
            break;
        }
    }
    if(state!=folder){
        if(folder==mainFolder) {
            reload(folder,false);
        }else{
            reload(folder,true);
        }
    }
    for(int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        if(item->statusTip()=="file" && item->text()==filename){
            ui->listWidget->setCurrentItem(item);
            break;
        }
    }
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
        this->clearSelection();
        return;
    }
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item== nullptr || item->text()==""){
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
        QString newNameFile;
        bool sameName=false;
        do {
            newNameFile = QInputDialog::getText(0, "Rename file",
                                                "Rename " + oldNameFile, QLineEdit::Normal,
                                                "", &ok);
            if (!ok) {
                return;
            }
            item=ui->listWidget->currentItem();
            if(item== nullptr){
                return;
            }
            oldNameFile=item->text();
            if(oldNameFile==newNameFile){
                return;
            }
            for (int i = 0; i < ui->listWidget->count(); ++i) {
                QListWidgetItem *item = ui->listWidget->item(i);
                if (item->text() == newNameFile) {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Rename file");
                    msgBox.setText("A file with this name already exists.");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.exec();
                    sameName=true;
                    break;
                }
            }
        }while(sameName);
        if(newNameFile.size()==0){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Rename file");
            msgBox.setText("Empty name.");
            msgBox.setStandardButtons(QMessageBox::Ok );
            msgBox.exec();
            return;
        }

        QRegularExpression expr(R"(^(?!\.)(?!com[0-9]$)(?!con$)(?!lpt[0-9]$)(?!nul$)(?!prn$)[^\|\*\?\\:<>/$"]*[^\.\|\*\?\\:<>/$"]+$)");

        if(!expr.match(newNameFile).hasMatch() || newNameFile.length() > 20) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Rename file");
            msgBox.setText("Invalid name.");
            msgBox.setStandardButtons(QMessageBox::Ok );
            msgBox.exec();
            return;
        }

        QMessageBox msgBox;
        msgBox.setWindowTitle("Rename file");
        msgBox.setText("Do you want to rename "+oldNameFile+" with "+newNameFile+"?");
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
    int index=0;
    QListWidgetItem *item=ui->listWidget->currentItem();
    if(item== nullptr){
        return;
    }
    nameFile=item->text();
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
        if(fileSystem[folder].size()==0){
            reload(this->mainFolder,false);
        }else {
            reload(folder, true);
        }
        emit rmvFileRequest(file);
    }
}

void FileSystemGridView::remoteDeleteFile(const QString& file)
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
    bool error=false;
    QListWidgetItem *item=ui->listWidget->currentItem();
    QString tmpName="";
    if(item== nullptr) {
        error=true;
    }else {
        tmpName=item->text();
    }
    if (this->state == this->mainFolder) {
        reload(this->mainFolder, false);
    } else {
        if(fileSystem[folder].size()==0){
            reload(this->mainFolder,false);
        }else {
            reload(folder, true);
        }
    }
    if(!error) {
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem *item = ui->listWidget->item(i);
            if (item->statusTip() == "file" && item->text() == tmpName) {
                ui->listWidget->setCurrentItem(item);
                break;
            }
        }
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
    this->fileSystem[folder].sort();
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

void FileSystemGridView::remoteRenameFile(const QString& oldFile,const QString& newFile) {
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
    this->fileSystem[folder].sort();
    bool error=false;
    QListWidgetItem *item=ui->listWidget->currentItem();
    QString tmpName;
    if(item== nullptr) {
        error=true;
    }else {
        tmpName=item->text();
    }
    if (this->state == this->mainFolder) {
        reload(this->mainFolder, false);
    } else {
        reload(this->state, true);
    }
    if(!error) {
        if(folder==this->state && tmpName==oldNameFile){
            tmpName=newNameFile;
        }
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            QListWidgetItem *item = ui->listWidget->item(i);
            if (item->statusTip() == "file" && item->text() == tmpName) {
                ui->listWidget->setCurrentItem(item);
                break;
            }
        }
    }
}

void FileSystemGridView::clearSelection() {
    ui->listWidget->selectionModel()->clear();
    ui->listWidget->clearSelection();
    emit canInvite(false);
    emit canDelete(false);
}