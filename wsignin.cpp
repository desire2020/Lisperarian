#include "wsignin.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wsignin.h"

WSignin::WSignin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WSignin)
{
    ui->setupUi(this);
    setMinimumSize(280,150);
    setMaximumSize(280,150);
    this -> setStyleSheet("background:Azure");
    usrLabel = new QLabel(tr("英文昵称："));
    pwd1Label = new QLabel(tr("密　　码："));
    pwd2Label = new QLabel(tr("确认密码："));
    usrLineEdit = new QLineEdit;
    usrLineEdit->setMaxLength(12);
    pwd1LineEdit = new QLineEdit;
    pwd1LineEdit->setEchoMode(QLineEdit::Password);
    pwd2LineEdit = new QLineEdit;
    pwd2LineEdit->setEchoMode(QLineEdit::Password);
    pwd1LineEdit->setMaxLength(12);
    pwd2LineEdit->setMaxLength(12);
    gridlayout = new QGridLayout;
    gridlayout->addWidget(usrLabel,0,0,1,1);
    gridlayout->addWidget(usrLineEdit,0,1,1,1);
    gridlayout->setSpacing(20);
    gridlayout->addWidget(pwd1Label,1,0,1,1);
    gridlayout->addWidget(pwd1LineEdit,1,1,1,1);
    gridlayout->addWidget(pwd2Label,2,0,1,1);
    gridlayout->addWidget(pwd2LineEdit,2,1,1,1);
    okBtn = new QPushButton(tr("确定"));
    cancelBtn = new QPushButton(tr("取消"));
    connect(okBtn,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->setSpacing(60);
    hboxLayout->addWidget(okBtn);
    hboxLayout->addWidget(cancelBtn);
    vboxLayout = new QVBoxLayout;
    vboxLayout->addLayout(gridlayout);
    vboxLayout->addLayout(hboxLayout);
    this->setLayout(vboxLayout);



}
void WSignin :: accept()
{/*
    int message;
    queueStr.push(pwdLineEdit -> text().trimmed().toStdString());
    message = procFunc(1);
    if(message == 0)
    {
        www -> userName -> setText(("当前用户 " + inOperation.userNickname).c_str());
        QMessageBox::warning(this,"登录成功",("欢迎您， " + inOperation.userNickname).c_str(),QMessageBox::Yes);
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"","",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }*/
}
WSignin::~WSignin()
{
    delete ui;
}
