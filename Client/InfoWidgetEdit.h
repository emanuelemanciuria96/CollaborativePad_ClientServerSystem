#ifndef INFOWIDGETEDIT_H
#define INFOWIDGETEDIT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class InfoWidgetEdit; }
QT_END_NAMESPACE

class InfoWidgetEdit : public QWidget
{
    Q_OBJECT

public:
    InfoWidgetEdit(QWidget *parent = nullptr);
    ~InfoWidgetEdit();
    void setImage(const QPixmap* image);
    void setName(const QString& name);
    void setEmail(const QString& email);

private:
    Ui::InfoWidgetEdit *ui;

public slots:
    void openFileDialog();
    void emitUpdateInfo();
    void closeEdit();

signals:
    void updateInfo(QPixmap image, QString name, QString email);
    void backToLogIn();
};
#endif // INFOWIDGETEDIT_H
