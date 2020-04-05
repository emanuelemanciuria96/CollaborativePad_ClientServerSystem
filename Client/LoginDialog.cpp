//
// Created by Windows on 22/03/2020.
//

#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent){
    setUpGUI();
    setWindowTitle("User login");
    setModal(true);
}

void LoginDialog::setUpGUI() {
    //imposto il layout
    auto formGridLayout = new QGridLayout(this);

    //inizializzo la LineEdit dell'username
    editUsername = new QLineEdit(this);
    //inizializzo la LineEdit della password
    editPassword = new QLineEdit(this);
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
    buttons->addButton(QDialogButtonBox::Cancel);
    buttons->button(QDialogButtonBox::Ok)->setText("Login");
    buttons->button(QDialogButtonBox::Cancel)->setWindowIconText("Abort");

    //connect per chiudere la finestra
    connect(buttons->button(QDialogButtonBox::Cancel),SIGNAL(clicked()), this, SLOT(close()));

    //connect per login
    connect(buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()),this, SLOT(slotAcceptLogin()));

    //posiziono gli elementi
    formGridLayout->addWidget(labelUsername,0,0);
    formGridLayout->addWidget(editUsername,0,1);
    formGridLayout->addWidget(labelPassword,1,0);
    formGridLayout->addWidget(editPassword,1,1);
    formGridLayout->addWidget(buttons,2,0,1,2);

    //imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.1,size.height()*0.1);

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

    close();
}
