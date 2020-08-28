//
// Created by Windows on 26/08/2020.
//

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <iostream>
#include "SignInWidget.h"

SignInWidget::SignInWidget(QWidget *parent) : QWidget(parent){
    userEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    imageLabel = new QLabel(this);
    buttons = new QDialogButtonBox(this);
    loadImageButton = new QPushButton(this);
//    profileImage = new QPixmap();

    auto middleLayout = new QHBoxLayout();
    auto outerLayout = new QVBoxLayout();
    auto fieldsLayout = new QVBoxLayout();
    auto imageLayout = new QVBoxLayout();

    userEdit->setPlaceholderText("Username");
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    nameEdit->setPlaceholderText("Name");
    emailEdit->setPlaceholderText("E-mail");

    imageLabel->setFixedSize(150,150);
    imageLabel->setText("Profile picture");

    buttons->addButton(QDialogButtonBox::Cancel);
    buttons->addButton(QDialogButtonBox::Ok);
    buttons->button(QDialogButtonBox::Ok)->setText("Sign in");
    connect(buttons->button(QDialogButtonBox::Ok),&QPushButton::clicked, this, &SignInWidget::signIn);
    connect(buttons->button(QDialogButtonBox::Cancel),&QPushButton::clicked, this, &SignInWidget::cancel);

    loadImageButton->setText("Select picture");
    connect(loadImageButton, &QPushButton::clicked, this, &SignInWidget::openFileDialog);

    fieldsLayout->addWidget(userEdit);
    fieldsLayout->addWidget(passwordEdit);
    fieldsLayout->addWidget(nameEdit);
    fieldsLayout->addWidget(emailEdit);

    imageLayout->addWidget(imageLabel);
    imageLayout->addWidget(loadImageButton);

    middleLayout->addSpacing(10);
    middleLayout->addLayout(imageLayout);
    middleLayout->addSpacing(10);
    middleLayout->addLayout(fieldsLayout);
    middleLayout->addSpacing(10);

    outerLayout->addLayout(middleLayout);
    outerLayout->addWidget(buttons);

    setLayout(outerLayout);

    setMaximumSize(400,300);
}

void SignInWidget::openFileDialog() {
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
        imageLabel->setPixmap(QPixmap("images/temp.jpg"));
        QFile::remove("images/temp.jpg");
    }
}

void SignInWidget::cancel() {
    emit backToLogIn();
}

void SignInWidget::signIn() {
    std::cout << "Sign In pressed" << std::endl;
    auto user = userEdit->text();
    auto password = passwordEdit->text();
    auto name = nameEdit->text();
    auto email = emailEdit->text();
    auto image = imageLabel->pixmap();
    emit registerRequest(user, password, name, email, (QPixmap &) image);
}