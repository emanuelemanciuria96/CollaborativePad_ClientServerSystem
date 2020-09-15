#ifndef FILESYSTEMGRIDVIEW_H
#define FILESYSTEMGRIDVIEW_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {class FileSystemGridView;}

class FileSystemGridView : public QWidget
{
Q_OBJECT

public:
    explicit FileSystemGridView(QWidget *parent = nullptr,QString fs="..mydoc,doc1,doc2-myfolder1,doc4,doc3-myfolder2,doc5-myfolder3 (empty)");
    ~FileSystemGridView();

public slots:
    void constructFromPaths(const QVector<QString> &paths){};
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void openFile(QString file);
    void insertFile(){};
    void invite(){};
    void deleteFile(QString file);
    void renameFile(QString oldFile,QString newFile);

private:
    QMap<QString,QVector<QString>> fileSystem;
    QString mainFolder="..mydoc";
    QString state=this->mainFolder;
    void itemProperties(QListWidgetItem *item);
    void reload(const QString folder,bool isFolder);
    QString format=".png";
    Ui::FileSystemGridView *ui;

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
