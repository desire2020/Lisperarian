#include "wlogin.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wlogin.h"

WLogin::WLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WLogin)
{
    ui->setupUi(this);
    setMinimumSize(280,150);
    setMaximumSize(280,150);
    usrLabel = new QLabel(tr("userID："));
    pwdLabel = new QLabel(tr("密　码："));
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
void WLogin :: accept()
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
        www -> userName -> setText(inOperation.userNickname.c_str());
        QWidget::close();
    }
    else
    {
        if (str != "admin")
        QMessageBox::warning(this,"警告","用户名或密码错误!!!",QMessageBox::Yes);
        else
            QMessageBox::warning(this,"警告","用户名 错误!!!",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}
WLogin::~WLogin()
{
    delete ui;
}
