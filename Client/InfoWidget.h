#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QtWidgets/QGraphicsScene>
#include "InfoWidgetEdit.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class InfoWidget; }
QT_END_NAMESPACE

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();

private:
    Ui::InfoWidget *ui;

public slots:
    void loadData(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void emitOpenInfoEdit();
    void updateInfo(const QPixmap& image, const QString& name, const QString& email);
    void emitBackPressed();

signals:
    void sendUpdatedInfo(const QPixmap& image, const QString& name, const QString& email);
    void imageChanged(const QPixmap& image);
    void backPressed();
    void openInfoEdit(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void logout();
};
#endif // INFOWIDGET_H
