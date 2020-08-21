//
// Created by Windows on 22/03/2020.
//

#include <iostream>
#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QWidget(parent){
    abort = true;
    setUpGUI();
    //setWindowTitle("User login");

}

void LoginDialog::setUpGUI() {
    //imposto il layout
    auto formGridLayout = new QGridLayout(this);

    //inizializzo la LineEdit dell'username
    editUsername = new QLineEdit(this);
    editUsername->setStyleSheet("QLineEdit { background: white; }");
    //inizializzo la LineEdit della password
    editPassword = new QLineEdit(this);
    editPassword->setStyleSheet("QLineEdit { background: white; }");
    editPassword->setEchoMode(QLineEdit::Password);

    //inizializzo le labels
    labelUsername = new QLabel(this);
    labelPassword = new QLabel(this);
    labelUsername->setText("Username");
    labelUsername->setBuddy(editUsername);
    labelPassword->setText("Password");
    labelPassword->setBuddy(editPassword);

    //inizializzo buttons
    buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    signInButton = new QPushButton("Sign in", this);
    buttons->addButton(signInButton ,QDialogButtonBox::ActionRole);
    buttons->button(QDialogButtonBox::Ok)->setText("Login");

    //connect per chiudere la finestra
    //connect(buttons->button(QDialogButtonBox::Cancel),SIGNAL(clicked()), this, SLOT(close()));

    //connect per login
    connect(buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()),this, SLOT(slotAcceptLogin()));

    //connect registrazione
    connect(signInButton,&QPushButton::clicked,this, &LoginDialog::slotSignIn);

    //posiziono gli elementi
    formGridLayout->addWidget(labelUsername,0,0);
    formGridLayout->addWidget(editUsername,0,1);
    formGridLayout->addWidget(labelPassword,1,0);
    formGridLayout->addWidget(editPassword,1,1);
    formGridLayout->addWidget(buttons,2,0,1,2);

    //imposto la grandezza della finestra
    //setMinimumSize(222,125);
    setMinimumSize(100,100);
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.1,size.height()*0.1);
    std::cout << this->size().width() << "x" << this->size().height() << std::endl;
    setLayout(formGridLayout);

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

