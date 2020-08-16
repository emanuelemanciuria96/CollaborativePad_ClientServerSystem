//
// Created by Windows on 16/08/2020.
//

#include "AccountView.h"

AccountView::AccountView(QWidget *parent) : QWidget(parent){
    auto formGridLayout = new QGridLayout(this);
    nickLabel = new QLabel(this);
    nickLabel->setText("Nickname:");

    formGridLayout->addWidget(nickLabel,0,0);

    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width()*0.1,size.height()*0.1);
    setLayout(formGridLayout);
}