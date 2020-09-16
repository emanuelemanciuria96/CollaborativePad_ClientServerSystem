#ifndef FILESYSTEMGRIDVIEW_H
#define FILESYSTEMGRIDVIEW_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {class FileSystemGridView;}

class FileSystemGridView : public QWidget
{
Q_OBJECT

public:
    explicit FileSystemGridView(QWidget *parent = nullptr,const QVector<QString> &paths=QVector<QString>());
    ~FileSystemGridView();

public slots:
    void constructFromPaths(const QVector<QString> &paths);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    //void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemSelectionChanged();
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void openFile(QString file);
    void addFile();
    void invite();
    void deleteFile(QString file);
    void renameFile(QString oldFile,QString newFile);
    void reloadBack();
    QVector<QString> getVector();
    QString getState();
    QString getMainFolder();

signals:
    void opnFileRequest(QString fileName);
    void openFolder(QString folder);
    void back();
    void inviteRequest(QString file);
    void newFileAdded(QString fileName);
    void rmvFileRequest(QString fileName);
    void renFileRequest(QString before, QString after);
    void canInvite(bool state);

private:
    QMap<QString,QVector<QString>> fileSystem;
    QString mainFolder="..mydoc";
    QString state=this->mainFolder;
    void itemProperties(QListWidgetItem *item);
    QString format=".png";
    Ui::FileSystemGridView *ui;
    QString label;
    void reload(const QString folder,bool isFolder);

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
