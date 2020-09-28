//
// Created by Windows on 26/08/2020.
//

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFileDialog>
#include <iostream>
#include <QtGui/QRegExpValidator>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtGui/QGuiApplication>
#include "SignInWidget.h"
#include <QScreen>

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

    outerLayout->addWidget(title, 1 , Qt::AlignLeft);
    outerLayout->addSpacing(15);
    outerLayout->addLayout(middleLayout,2);
    outerLayout->addSpacing(15);
    outerLayout->addWidget(buttons,1, Qt::AlignRight);
    innerWidget->setLayout(outerLayout);
    innerWidget->setContentsMargins(40,40,40,40);

    //imposto grandezza widget
    auto size = QGuiApplication::primaryScreen()->size();
    innerWidget->setFixedSize(size.width()/3, size.height()/2.3);

    containerLayout->addWidget(innerWidget,0, Qt::AlignCenter);
    setLayout(containerLayout);

    //sezione grafica
    title->setStyleSheet("QLabel {color: black; font: 18pt}");
    auto style = innerWidget->styleSheet();
    style.append("QWidget{background-color: #FAFAFA; font-family:helvetica }"
                 "QLineEdit{font:9pt; padding:5; border-style: solid; border-width:1px; border-radius: 8px; border-color:lightgray}"
                 "QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}");
    innerWidget->setStyleSheet(style);
    loadImageButton->setStyleSheet("font: 9pt; padding: 8; padding-right:15; padding-left:15; border-style: solid; border-width:1px; "
                                   "border-color:#3A70D5; background:white; color:#3A70D5}");
    auto effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::lightGray);
    innerWidget->setGraphicsEffect(effect);
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