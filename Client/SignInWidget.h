//
// Created by Windows on 26/08/2020.
//

#ifndef CLIENT_SIGNINWIDGET_H
#define CLIENT_SIGNINWIDGET_H


#include <QtWidgets/QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QtWidgets/QDialogButtonBox>
#include <QPushButton>

class SignInWidget : public QWidget{
    Q_OBJECT
private:
    QLineEdit *userEdit;
    QLineEdit *passwordEdit;
    QLineEdit *nameEdit;
    QLineEdit *emailEdit;
    QLabel *imageLabel;
//    QPixmap *profileImage;
    QPushButton *loadImageButton;
    QDialogButtonBox *buttons;
    void openFileDialog();
private slots:
    void cancel();
    void signIn();

signals:
    void backToLogIn();


public:
    SignInWidget(QWidget* parent);
};


#endif //CLIENT_SIGNINWIDGET_H
