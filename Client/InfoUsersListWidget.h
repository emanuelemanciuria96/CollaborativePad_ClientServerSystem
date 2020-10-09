#ifndef INFOUSERSLISTWIDGET_H
#define INFOUSERSLISTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class InfoUsersListWidget; }
QT_END_NAMESPACE

class InfoUsersListWidget : public QWidget
{
    Q_OBJECT

public:
    InfoUsersListWidget(QWidget *parent = nullptr);
    void setData(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
    ~InfoUsersListWidget();

private:
    Ui::InfoUsersListWidget *ui;

signals:
    void backPressed(const QPixmap& image, const QString& nickname, const QString& name, const QString& email);
};
#endif // INFOUSERSLISTWIDGET_H
