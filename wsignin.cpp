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
    usrLabel = new QLabel(tr("userID："));
    pwd1Label = new QLabel(tr("密　码："));
    pwd2Label = new QLabel(tr("确认密码："));
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    usrLineEdit->setMaxLength(12);
    pwdLineEdit->setMaxLength(12);
    gridlayout = new QGridLayout;
    gridlayout->addWidget(usrLabel,0,0,1,1);
    gridlayout->addWidget(usrLineEdit,0,1,1,1);
    gridlayout->setSpacing(20);
    gridlayout->addWidget(pwdLabel,1,0,1,1);
    gridlayout->addWidget(pwdLineEdit,1,1,1,1);
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
{
    int message;
    long long num;
    string str;
    num = Nios :: StrNum(usrLineEdit->text().trimmed().toStdString());
    str = pwdLineEdit -> text().trimmed().toStdString();
    queueNum.push(num);
    queueStr.push(str);
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
    }
}
WSignin::~WSignin()
{
    delete ui;
}
