#include <QtWidgets/QFileDialog>
#include <iostream>
#include "InfoWidgetEdit.h"
#include "ui_infowidgetedit.h"

InfoWidgetEdit::InfoWidgetEdit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InfoWidgetEdit)
{
    ui->setupUi(this);
    connect(ui->cambiaimmagine, &QPushButton::clicked, this, &InfoWidgetEdit::openFileDialog);
    connect(ui->salva, &QPushButton::clicked, this, &InfoWidgetEdit::emitUpdateInfo);
    connect(ui->annulla, &QPushButton::clicked, this, &InfoWidgetEdit::closeEdit);
}

InfoWidgetEdit::~InfoWidgetEdit()
{
    delete ui;
}

void InfoWidgetEdit::openFileDialog() {
    QStringList fileNames;
    auto fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter(tr("Images (*.jpg)"));
    fileDialog->show();
    if (fileDialog->exec())
        fileNames = fileDialog->selectedFiles();

    if (!fileNames.isEmpty()){
        ui->immagine->setPixmap(QPixmap(fileNames.first()));
    }
}

void InfoWidgetEdit::emitUpdateInfo() {
    emit updateInfo(*(ui->immagine->pixmap()), std::move(ui->editname->text()));
}

void InfoWidgetEdit::setImage(const QPixmap *image) {
    ui->immagine->setScaledContents(true);
    ui->immagine->setPixmap(*image);
}

void InfoWidgetEdit::setName(const QString &name) {
    ui->editname->setText(name);
}

void InfoWidgetEdit::closeEdit() {
    parentWidget()->show();
    this->close();
    emit backToLogIn();
}
