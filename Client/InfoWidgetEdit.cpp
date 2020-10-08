#include <QtWidgets/QFileDialog>
#include <iostream>
#include <QtGui/QRegExpValidator>
#include <QtGui/QPainter>
#include "InfoWidgetEdit.h"
#include "ui_infowidgetedit.h"

InfoWidgetEdit::InfoWidgetEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InfoWidgetEdit)
{
    ui->setupUi(this);
    QRegExp expr(R"(^(?!\.)(?!com[0-9]$)(?!con$)(?!lpt[0-9]$)(?!nul$)(?!prn$)[^\|\*\?\\:<>/$"]*[^\.\|\*\?\\:<>/$"]+$)");
    auto *v = new QRegExpValidator(expr, this);
    ui->editName->setValidator(v);
    ui->editName->setMaxLength(20);
    connect(ui->changeImageButton, &QPushButton::clicked, this, &InfoWidgetEdit::openFileDialog);
    connect(ui->saveButton, &QPushButton::clicked, this, &InfoWidgetEdit::emitUpdateInfo);
    connect(ui->cancelButton, &QPushButton::clicked, this, &InfoWidgetEdit::closeEdit);
    ui->label_3->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->label_5->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->label_7->setStyleSheet("QLabel{color:#3A70D5; font: 12pt}");
    ui->changeImageButton->setStyleSheet("QPushButton {font: 9pt; padding: 8; padding-right:15; padding-left:15; border-style: solid; border-width:1px; "
                                         "border-color:#3A70D5; background:white; color:#3A70D5}");
    ui->editEmail->setStyleSheet("QLineEdit{font:12pt; padding:5; border-style: solid; border-width:1px; border-radius: 8px; border-color:lightgray; background:#FAFAFA}");
    ui->editName->setStyleSheet("QLineEdit{font:12pt; padding:5; border-style: solid; border-width:1px; border-radius: 8px; border-color:lightgray; background:#FAFAFA}");
    ui->editUser->setStyleSheet("QLineEdit{font:12pt; padding:5; border-style: solid; border-width:1px; border-radius: 8px; border-color:lightgray; background:#FAFAFA}");

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
        crop.save("images/temp.jpg", "JPG", 10);
        QPixmap orig("images/temp.jpg");
        int size = qMax(orig.width(), orig.height());
        QPixmap rounded = QPixmap(size, size);
        rounded.fill(Qt::transparent);
        QPainterPath path;
        path.addEllipse(rounded.rect());
        QPainter painter(&rounded);
        painter.setClipPath(path);
        painter.fillRect(rounded.rect(), Qt::black);
        int x = qAbs(orig.width() - size) / 2;
        int y = qAbs(orig.height() - size) / 2;
        painter.drawPixmap(x, y, orig.width(), orig.height(), orig);
        ui->imageLabel->setPixmap(rounded);
        QFile::remove("images/temp.jpg");
    }
}

void InfoWidgetEdit::emitUpdateInfo() {
    auto name = ui->editName->text();
    auto email = ui->editEmail->text();
    if (name.isEmpty() || email.isEmpty()){
        ui->errorLabel->setText("Please fill all fields");
        return;
    }
    QRegularExpression emailExpr("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!emailExpr.match(email).hasMatch()) {
        ui->errorLabel->setText("Invalid email address");
        return;
    }
    ui->errorLabel->clear();
    emit updateInfo(*(ui->imageLabel->pixmap()), std::move(ui->editName->text()), std::move(ui->editEmail->text()));
    emit backToInfoWidget();
}

void InfoWidgetEdit::setImage(const QPixmap *image) {
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setPixmap(*image);
}

void InfoWidgetEdit::setName(const QString &name) {
    ui->editName->setText(name);
}

void InfoWidgetEdit::setEmail(const QString &email) {
    ui->editEmail->setText(email);
}

void InfoWidgetEdit::setUser(const QString &user) {
    ui->editUser->setText(user);
}

void InfoWidgetEdit::closeEdit() {
    ui->errorLabel->clear();
    emit backToInfoWidget();
}