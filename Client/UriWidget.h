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

private:
    Ui::UriWidget *ui;
};
#endif // URIWIDGET_H
