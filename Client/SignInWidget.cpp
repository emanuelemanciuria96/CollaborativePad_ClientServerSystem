//
// Created by Windows on 26/08/2020.
//

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <iostream>
#include <QtGui/QRegExpValidator>
#include "SignInWidget.h"

SignInWidget::SignInWidget(QWidget *parent) : QWidget(parent){
    auto innerWidget = new QWidget(this);
    userEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    imageLabel = new QLabel(this);
    errorLabel = new QLabel(this);
    buttons = new QDialogButtonBox(this);
    loadImageButton = new QPushButton(this);
    auto title = new QLabel("Create Account");
    title->setStyleSheet("QLabel {color: white; font:14pt}");

    QRegExp stdExpr(R"(^(?!\.)(?!com[0-9]$)(?!con$)(?!lpt[0-9]$)(?!nul$)(?!prn$)[^\|\*\?\\:<>/$"]*[^\.\|\*\?\\:<>/$"]+$)");
    auto *v = new QRegExpValidator(stdExpr, this);
    userEdit->setValidator(v);
    userEdit->setMaxLength(20);
    nameEdit->setValidator(v);
    nameEdit->setMaxLength(20);

    auto middleLayout = new QHBoxLayout();
    auto outerLayout = new QVBoxLayout();
    auto fieldsLayout = new QVBoxLayout();
    auto imageLayout = new QVBoxLayout();
    auto containerLayout = new QHBoxLayout();

    userEdit->setPlaceholderText("Username");
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    nameEdit->setPlaceholderText("Name");
    emailEdit->setPlaceholderText("E-mail");
    errorLabel->setStyleSheet("color: red");
    errorLabel->setAlignment(Qt::AlignCenter);

    imageLabel->setFixedSize(150,150);
    imageLabel->setPixmap(QPixmap("images/profile.jpg"));
    imageLabel->setScaledContents(true);

    buttons->addButton(QDialogButtonBox::Cancel);
    buttons->addButton(QDialogButtonBox::Ok);
    buttons->button(QDialogButtonBox::Ok)->setText("Sign up");
    connect(buttons->button(QDialogButtonBox::Ok),&QPushButton::clicked, this, &SignInWidget::signIn);
    connect(buttons->button(QDialogButtonBox::Cancel),&QPushButton::clicked, this, &SignInWidget::cancel);

    loadImageButton->setText("Select picture");
    connect(loadImageButton, &QPushButton::clicked, this, &SignInWidget::openFileDialog);

    fieldsLayout->addWidget(userEdit);
    fieldsLayout->addSpacing(10);
    fieldsLayout->addWidget(passwordEdit);
    fieldsLayout->addSpacing(10);
    fieldsLayout->addWidget(nameEdit);
    fieldsLayout->addSpacing(10);
    fieldsLayout->addWidget(emailEdit);
    fieldsLayout->addSpacing(10);
    fieldsLayout->addWidget(errorLabel);
    fieldsLayout->addSpacing(10);
    fieldsLayout->setAlignment(Qt::AlignTop);

    imageLayout->addWidget(imageLabel);
    imageLayout->addSpacing(10);
    imageLayout->addWidget(loadImageButton,0, Qt::AlignCenter);
    imageLayout->setAlignment(Qt::AlignTop);

    middleLayout->addSpacing(10);
    middleLayout->addLayout(imageLayout,0);
    middleLayout->addSpacing(40);
    middleLayout->addLayout(fieldsLayout);
    middleLayout->addSpacing(10);

    outerLayout->addWidget(title, 0 , Qt::AlignCenter);
    outerLayout->addLayout(middleLayout);
    outerLayout->addWidget(buttons,0, Qt::AlignCenter);
    innerWidget->setLayout(outerLayout);
    innerWidget->setFixedSize(450,350);

    containerLayout->addWidget(innerWidget,0, Qt::AlignCenter);
    setLayout(containerLayout);

//    QPalette p1{};
//    QImage loginBackground = QImage("./textures/texture_clouds_background.png");
//    QBrush brush1(loginBackground);
//    QRgb rgbColor = loginBackground.pixel(0,0);
//    QLinearGradient grad(0,100,0,0);
//    grad.setColorAt(0,rgbColor);
//    grad.setColorAt(1, Qt::white);
//    QBrush b(grad);
//    p1.setBrush(QPalette::Window,b);
//    setAutoFillBackground(true);
//    setPalette(p1);
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
    if (user.isEmpty() || password.isEmpty() || name.isEmpty() || email.isEmpty()){
        errorLabel->setText("Please fill all fields");
        return;
    }
    QRegularExpression emailExpr("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!emailExpr.match(email).hasMatch()) {
        errorLabel->setText("Invalid email address");
        return;
    }

    if (password.length() < 8 || password.length() > 16) {
        errorLabel->setText("Password must be 8-12 characters");
        return;
    }

    QPixmap image{};
    if (*(imageLabel->pixmap()) != QPixmap("images/profile.jpg"))
        image = *(imageLabel->pixmap());
    emit registerRequest(user, password, name, email, image);
}