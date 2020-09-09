#include "UriWidget.h"
#include "./ui_uriwidget.h"

UriWidget::UriWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UriWidget)
{
    ui->setupUi(this);
}

UriWidget::~UriWidget()
{
    delete ui;
}

