#include "UriWidget.h"
#include "./ui_uriwidget.h"

UriWidget::UriWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UriWidget)
{
    ui->setupUi(this);
    ui->uriEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    connect(ui->submitButton, &QPushButton::clicked, this, &UriWidget::checkUri);
}

UriWidget::~UriWidget()
{
    delete ui;
}

void UriWidget::checkUri() {
    auto input = ui->uriEdit->text();

    if (input.isEmpty() || !input.contains("http://www.sharededitor.com/")){
        ui->errorLabel->setText("Please insert a valid URI");
        return;
    }

    emit submitUri(input.replace("http://www.sharededitor.com/", ""));
}

void UriWidget::hideEvent (QHideEvent *event){
    ui->uriEdit->clear();
    ui->errorLabel->clear();
}

void UriWidget::uriResultArrived(const QVector<QString> &args) {
    const auto& result = args.first();
    const auto& fileName = args.last();
    if (result == "valid" || result == "invite-existing") {
        emit setStatusBarText("File "+fileName+" added to the list", 0);
    }
    else if (result == "invalid")
        ui->errorLabel->setText("File not found");
    else if (result == "file-existing") {
        emit setStatusBarText("File " + fileName + " is already on the list", 0);
    }
}
