//
// Created by utente on 11/08/2020.
//

#ifndef CLIENT_FILESYSTEMTREEVIEW_H
#define CLIENT_FILESYSTEMTREEVIEW_H


#include <QtCore>
#include <QtGui>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>

class FileSystemTreeView : public QTreeWidget{
Q_OBJECT
public:
    explicit FileSystemTreeView( QWidget *parent = 0);
    ~FileSystemTreeView();

public slots:
    void constructFromPaths(const QVector<QString> &paths);
    void openCustomMenu(const QPoint &pos);
    void openFile(QTreeWidgetItem *item, int column);
    void removeFile(QTreeWidgetItem *item);
    void renameFile(QTreeWidgetItem *item, int column);
    void editFileName(QString &oldName, QString &newName);
    void remoteFileDeletion(QString &fileName);
    void inviteUser(QTreeWidgetItem *item);

signals:
    void opnFileRequest(QString& fileName);
    void rmvFileRequest(QString& fileName);
    void newFileAdded(QString& fileName);
    void newFileUpdateGrid(QVector<QString>& path);
    void renFileRequest(QString& before, QString& after);
    void fileNameEdited(QString& oldName, QString& newName);
    void inviteRequest(const QString& fileName);

private:
    QTreeWidgetItem *root;
    std::map<QString,QModelIndex> model;
    bool isRenaming = true;
    QIcon home_dir;
    QIcon dir_open;
    QIcon dir_close;
    QIcon file_icn;
    QMenu *rightClickMenu = nullptr;
    QString previousName;

    void setupRightClickMenu();
    virtual void mousePressEvent(QMouseEvent *ev);
    void insertFile();
    QTreeWidgetItem* addChild(QTreeWidgetItem *parent, QString name,QString description);
    bool isChild(QTreeWidgetItem *parent, QString &name);

};



#endif //CLIENT_FILESYSTEMTREEVIEW_H
