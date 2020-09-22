#ifndef FILESYSTEMGRIDVIEW_H
#define FILESYSTEMGRIDVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QlistWidget>
#include <iostream>
#include <QMouseEvent>
#include <QDebug>

class MyListWidget: public QListWidget{
    Q_OBJECT
public:
    MyListWidget(QWidget *parent = nullptr):QListWidget(parent){}

protected:
    virtual void mousePressEvent(QMouseEvent *ev){
        std::cout<<"mouse is pressed"<<std::endl;
    }
};

namespace Ui {class FileSystemGridView;}

class FileSystemGridView : public QWidget{
Q_OBJECT

public:
    explicit FileSystemGridView(QWidget *parent = nullptr,const QVector<QString> &paths=QVector<QString>());
    ~FileSystemGridView();

public slots:
    void constructFromPaths(const QVector<QString> &paths);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_itemSelectionChanged();
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void openFile(QString file);
    void addFile();
    void invite();
    void deleteFile(QString file);
    void remoteDeleteFile(const QString& file);
    void renameFile(QString oldFile,QString newFile);
    void remoteRenameFile(const QString& oldFile,const QString& newFile);
    void selectFile(QString& file);
    void reloadBack();
    QString getState();
    QString getMainFolder();

signals:
    void opnFileRequest(QString& fileName);
    void openFolder(QString folder);
    void back();
    void inviteRequest(QString file);
    void newFileAdded(QString& fileName);
    void newFileUpdateTree(QVector<QString>& fileName);
    void rmvFileRequest(QString& fileName);
    void renFileRequest(QString& before, QString& after);
    void canInvite(bool state);

private:
    QMap<QString,QStringList> fileSystem;
    QString mainFolder="-.My files ";
    QString state=this->mainFolder;
    void itemProperties(QListWidgetItem *item);
    void clearSelection();
    QString format=".png";
    Ui::FileSystemGridView *ui;
    void reload(const QString folder,bool isFolder,bool changeToolbar);
    void keyPressEvent(QKeyEvent *event) override;
/*
    QIcon* textIcon=new QIcon("D:/Desktop/untitled/icons/grid_text_icon"+this->format);
    QIcon* folderIcon=new QIcon("D:/Desktop/untitled/icons/grid_folder_icon"+this->format);
    QIcon* backIcon=new QIcon("D:/Desktop/untitled/icons/grid_back_icon"+this->format);
*/
    QIcon* textIcon=new QIcon("./icons/grid_text_icon"+this->format);
    QIcon* folderIcon=new QIcon("./icons/grid_folder_icon"+this->format);
    QIcon* backIcon=new QIcon("./icons/grid_back_icon"+this->format);

};

#endif // FILESYSTEMGRIDVIEW_H
