#ifndef URIWIDGET_H
#define URIWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class UriWidget; }
QT_END_NAMESPACE

class UriWidget : public QWidget
{
    Q_OBJECT

public:
    UriWidget(QWidget *parent = nullptr);
    ~UriWidget();
    void hideEvent(QHideEvent *event) override;

private:
    Ui::UriWidget *ui;
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void checkUri();
    void uriResultArrived(const QVector<QString> &args);

signals:
    void submitUri(const QString& file);
    void setStatusBarText(const QString& text, int timeout);
    void closeUriDock();
};
#endif // URIWIDGET_H
