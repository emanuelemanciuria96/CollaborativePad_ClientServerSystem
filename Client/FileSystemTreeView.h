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

signals:
    void opnFileRequest(QString fileName);

private:
    QTreeWidgetItem *root;
    std::map<QString,QModelIndex> model;
    QIcon home_dir;
    QIcon dir_open;
    QIcon dir_close;
    QIcon file_icn;
    QMenu *rightClickMenu;

    void setupRightClickMenu();
    QTreeWidgetItem* addChild(QTreeWidgetItem *parent, QString name,QString description);
    bool isChild(QTreeWidgetItem *parent, QString name);

};



#endif //CLIENT_FILESYSTEMTREEVIEW_H
