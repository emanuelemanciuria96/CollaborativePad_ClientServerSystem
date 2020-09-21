//
// Created by Windows on 22/03/2020.
//

#include <iostream>
#include "LoginDialog.h"

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

    auto title = new QLabel("Log in into your account");
    title->setStyleSheet("QLabel {color: white; font:14pt}");
    //inizializzo le labels
//    labelUsername = new QLabel(this);
//    labelPassword = new QLabel(this);
//    labelUsername->setText("Username");
//    labelUsername->setBuddy(editUsername);
//    labelPassword->setText("Password");
//    labelPassword->setBuddy(editPassword);
    labelResult = new QLabel(this);

    //inizializzo buttons
    buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    signInButton = new QPushButton("Sign up", this);
    buttons->addButton(signInButton ,QDialogButtonBox::ActionRole);
    buttons->button(QDialogButtonBox::Ok)->setText("Log in");
//    signInButton->setStyleSheet("QPushButton {border-style: outset; border-width: 2px; border-color: beige}");
    //connect per chiudere la finestra
    //connect(buttons->button(QDialogButtonBox::cancel),SIGNAL(clicked()), this, SLOT(close()));

    //connect per login
    connect(buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()),this, SLOT(slotAcceptLogin()));

    //connect registrazione
    connect(signInButton,&QPushButton::clicked,this, &LoginDialog::slotSignIn);

    //posiziono gli elementi
    formGridLayout->addWidget(title, 0 ,0,1,1);
    formGridLayout->setRowMinimumHeight(1,10);
    formGridLayout->addWidget(editUsername,2,0,1,1);
    formGridLayout->setRowMinimumHeight(3,10);
    formGridLayout->addWidget(editPassword,4,0,1,1);
    formGridLayout->setRowMinimumHeight(5,10);
    formGridLayout->addWidget(buttons,6,0,1,1, Qt::AlignCenter);
    formGridLayout->addWidget(labelResult, 7, 0, 1, 8);

    //imposto la grandezza della finestra
    innerWidget->setMinimumSize(100,100);

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