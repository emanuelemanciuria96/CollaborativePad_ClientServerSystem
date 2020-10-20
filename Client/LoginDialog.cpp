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
    auto formGridLayout = new QVBoxLayout(this);
    auto innerWidget = new QWidget(this);
    auto containerLayout = new QVBoxLayout(this);

    //inizializzo la LineEdit dell'username
    editUsername = new QLineEdit(this);
    editUsername->setMaxLength(20);
    editUsername->setPlaceholderText("Username");
    //inizializzo la LineEdit della password
    editPassword = new QLineEdit(this);
    editPassword->setMaxLength(16);
    editPassword->setEchoMode(QLineEdit::Password);
    editPassword->setPlaceholderText("Password");
    editPassword->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    auto title = new QLabel("Log in");

    //inizializzo le labels
    labelResult = new QLabel(this);

    //inizializzo buttons
    buttons = new QDialogButtonBox(this);
    buttons->addButton(QDialogButtonBox::Ok);
    signInButton = new QPushButton("Sign up", this);
    buttons->addButton(signInButton ,QDialogButtonBox::ActionRole);
    buttons->button(QDialogButtonBox::Ok)->setText("Log in");
    buttons->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    buttons->setBaseSize(innerWidget->size());

    //connect per login
    connect(buttons->button(QDialogButtonBox::Ok), SIGNAL(clicked()),this, SLOT(slotAcceptLogin()));

    //connect registrazione
    connect(signInButton,&QPushButton::clicked,this, &LoginDialog::slotSignIn);

    //posiziono gli elementi
    formGridLayout->addWidget(title,5,Qt::AlignVCenter);
    formGridLayout->addSpacing(25);
    formGridLayout->addWidget(editUsername,5,Qt::AlignVCenter);
    formGridLayout->addSpacing(25);
    formGridLayout->addWidget(editPassword,5,Qt::AlignVCenter);
    formGridLayout->addSpacing(25);
    formGridLayout->addWidget(labelResult, 1, Qt::AlignLeft);
    formGridLayout->addWidget(buttons,5,Qt::AlignVCenter);

    formGridLayout->setContentsMargins(50,50,50,50);

    //sezione grafica
    title->setStyleSheet("QLabel {color: black; font: 18pt}");
    auto style = innerWidget->styleSheet();
    style.append("QWidget{background-color: #FAFAFA;}"
                 "QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}"
                 "QLineEdit{font:9pt; padding:5; border-style: solid; border-width:1px; border-radius: 8px; border-color:lightgray; background:#FAFAFA}");
    innerWidget->setStyleSheet(style);
    auto effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(30);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::lightGray);
    innerWidget->setGraphicsEffect(effect);
//    buttons->setStyleSheet("QPushButton {font: 10pt; padding: 8; padding-right:25; padding-left:25; border-style: none; background:#3A70D5; color:white}");

    //imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
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

void LoginDialog::slotLoginErrorAlreadyConn() {
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::red);
    labelResult->setPalette(palette);
    labelResult->setText("User already connected");
}

void LoginDialog::keyPressEvent(QKeyEvent *e) {
    QWidget::keyPressEvent(e);
    if (e->key() == Qt::Key_Return){
        slotAcceptLogin();
    }
}
