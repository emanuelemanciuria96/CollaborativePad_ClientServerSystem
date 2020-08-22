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
        QPixmap image(fileNames.first());
        auto imgsize = std::min(image.width(), image.height());
        auto rect = QRect((image.width() - imgsize) / 2,(image.height() - imgsize) / 2, imgsize, imgsize);
        auto crop = image.copy(rect);
        crop.save("images/temp.jpg", "JPG", 50);
        ui->immagine->setPixmap(QPixmap("images/temp.jpg"));
        QFile::remove("images/temp.jpg");
    }
}

void InfoWidgetEdit::emitUpdateInfo() {
    emit updateInfo(*(ui->immagine->pixmap()), std::move(ui->editname->text()), std::move(ui->editemail->text()));
}

void InfoWidgetEdit::setImage(const QPixmap *image) {
    ui->immagine->setScaledContents(true);
    ui->immagine->setPixmap(*image);
}

void InfoWidgetEdit::setName(const QString &name) {
    ui->editname->setText(name);
}

void InfoWidgetEdit::setEmail(const QString &email) {
    ui->editemail->setText(email);
}

void InfoWidgetEdit::closeEdit() {
    parentWidget()->show();
    this->close();
}