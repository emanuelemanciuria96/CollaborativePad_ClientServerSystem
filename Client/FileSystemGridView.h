#ifndef FILESYSTEMGRIDVIEW_H
#define FILESYSTEMGRIDVIEW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QlistWidget>
#include <iostream>
#include <QDebug>


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
    void deleteCurrent();
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
    void canDelete(bool state);

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
    int count=0;
    bool eventFilter(QObject *target, QEvent *event);

    QIcon* textIcon=new QIcon("./icons/grid_text_icon"+this->format);
    QIcon* folderIcon=new QIcon("./icons/grid_folder_icon"+this->format);
    QIcon* backIcon=new QIcon("./icons/grid_back_icon"+this->format);

    QIcon* contextOpenFile=new QIcon("./icons/context_open_file"+this->format);
    QIcon* contextDelete=new QIcon("./icons/context_delete"+this->format);
    QIcon* contextInvite=new QIcon("./icons/context_invite"+this->format);
    QIcon* contextRename=new QIcon("./icons/context_rename"+this->format);
    QIcon* contextAddFile=new QIcon("./icons/context_add_file"+this->format);
    QIcon* contextOpenFolder=new QIcon("./icons/context_open_folder"+this->format);
};

#endif // FILESYSTEMGRIDVIEW_H
