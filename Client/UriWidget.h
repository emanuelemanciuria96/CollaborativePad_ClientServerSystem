#ifndef URIWIDGET_H
#define URIWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class UriWidget; }
QT_END_NAMESPACE

class UriWidget : public QMainWindow
{
    Q_OBJECT

public:
    UriWidget(QWidget *parent = nullptr);
    ~UriWidget();
    void closeEvent(QCloseEvent *event);

private:
    Ui::UriWidget *ui;

public slots:
    void checkUri();
    void uriResultArrived(const QVector<QString> &args);

signals:
    void submitUri(const QString& file);
    void setStatusBarText(const QString& text, int timeout);
};
#endif // URIWIDGET_H
