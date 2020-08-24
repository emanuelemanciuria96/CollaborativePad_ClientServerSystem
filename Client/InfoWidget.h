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
    const QPixmap *getImage();
    QString getNickname();
    QString getName();
    ~InfoWidget();

private:
    Ui::InfoWidget *ui;
    InfoWidgetEdit *infoWidgetEdit;

public slots:
    void loadData(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    void openInfoEdit();
    void updateInfo(const QPixmap& image, const QString& name, const QString& email);

signals:
    void sendUpdatedInfo(const QPixmap& image, const QString& name, const QString& email);
};
#endif // INFOWIDGET_H
