//
// Created by Windows on 19/10/2020.
//

#include <QtWidgets/QVBoxLayout>
#include "LostConnectionWidget.h"

LostConnectionWidget::LostConnectionWidget(QWidget *parent) : QWidget(parent){
    button = new QPushButton(this);

    connect(button,&QPushButton::clicked, [this]{emit reconnect();});

    auto layout = new QVBoxLayout(this);
    layout->addWidget(button,1,Qt::AlignCenter);
}