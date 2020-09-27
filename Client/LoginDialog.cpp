//
// Created by Windows on 22/03/2020.
//

#include <iostream>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include "LoginDialog.h"
#include <QSizePolicy>

LoginDialog::LoginDialog(QWidget *parent) : QWidget(parent){
    abort = true;
    setUpGUI();
}

void LoginDialog::setUpGUI() {
    //imposto il layout
    auto formGridLayout = new QGridLayout(this);
    auto innerWidget = new QWidget(this);
    auto containerLayout = new QVBoxLayout(this);

    //inizializzo la LineEdit dell'username
    editUsername = new QLineEdit(this);
    editUsername->setMaxLength(20);
//    editUsername->setStyleSheet("QLineEdit { background: white; }");
    editUsername->setPlaceholderText("Username");
    //inizializzo la LineEdit della password
    editPassword = new QLineEdit(this);
    editPassword->setMaxLength(16);
//    editPassword->setStyleSheet("QLineEdit { background: white; }");
    editPassword->setEchoMode(QLineEdit::Password);
    editPassword->setPlaceholderText("Password");
    auto sizepol = QSizePolicy();
    sizepol.setVerticalPolicy(QSizePolicy::Maximum);
    sizepol.setHorizontalPolicy(QSizePolicy::Maximum);
    editPassword->setSizePolicy(sizepol);
    auto title = new QLabel("Log in into your account");

    //sezione grafica
    title->setStyleSheet("QLabel {color: black; font: 18pt}");
    auto style = innerWidget->styleSheet();
    style.append("QWidget{background-color: white; }");
    innerWidget->setStyleSheet(style);
    auto effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::lightGray);
    innerWidget->setGraphicsEffect(effect);
    //inizializzo le labels
    labelResult = new QLabel(this);

    //inizializzo buttons
    buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    signInButton = new QPushButton("Sign up", this);
    buttons->addButton(signInButton ,QDialogButtonBox::ActionRole);
    buttons->button(QDialogButtonBox::Ok)->setText("Log in");
    buttons->setSizePolicy(sizepol);
//    signInButton->setStyleSheet("QPushButton {border-style: outset; border-width: 2px; border-color: beige}");
    //connect per chiudere la finestra
    //connect(buttons->button(QDialogButtonBox::cancel),SIGNAL(clicked()), this, SLOT(close()));

    //connect per login
    connect(buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()),this, SLOT(slotAcceptLogin()));

    //connect registrazione
    connect(signInButton,&QPushButton::clicked,this, &LoginDialog::slotSignIn);

    //posiziono gli elementi
    formGridLayout->addWidget(title, 0 ,0,Qt::AlignHCenter);
    formGridLayout->setRowMinimumHeight(1,10);
    formGridLayout->addWidget(editUsername,2,0,Qt::AlignCenter);
    formGridLayout->setRowMinimumHeight(3,10);
    formGridLayout->addWidget(editPassword,4,0,Qt::AlignCenter);
    formGridLayout->setRowMinimumHeight(5,10);
    formGridLayout->addWidget(buttons,6,0,Qt::AlignCenter);
    formGridLayout->addWidget(labelResult, 7, 0);
    formGridLayout->setColumnStretch(0,1);
    //imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
//    innerWidget->setMinimumSize(100,100);
    innerWidget->setFixedSize(size.width()/4, size.height()/3);
//    auto size = QGuiApplication::primaryScreen()->size();
//    this->resize(size.width()*0.1,size.height()*0.1);
//    std::cout << this->size().width() << "x" << this->size().height() << std::endl;
    innerWidget->setLayout(formGridLayout);
    containerLayout->addWidget(innerWidget,0,Qt::AlignCenter);
    setLayout(containerLayout);
}

void LoginDialog::setUsername(QString &username) {
    editUsername->setText(username);
}

void LoginDialog::setPassword(QString &password) {
    editPassword->setText(password);
}

void LoginDialog::slotAcceptLogin() {
    QString username = editUsername->text();
    QString password = editPassword->text();

    //emetto il signal con le credenziali
    emit acceptLogin(username,password);
    abort = false;
}

void LoginDialog::slotSignIn() {
    emit signIn();
}

void LoginDialog::slotLoginError() {
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red);
    labelResult->setPalette(palette);
    labelResult->setText("Username or password is incorrect");
}

void LoginDialog::keyPressEvent(QKeyEvent *e) {
    QWidget::keyPressEvent(e);
    if (e->key() == Qt::Key_Enter || Qt::Key_Escape){
        slotAcceptLogin();
    }
}