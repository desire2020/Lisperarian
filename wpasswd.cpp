#include "wpasswd.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wpasswd.h"

WPasswd::WPasswd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WPasswd)
{
    ui->setupUi(this);
    setMinimumSize(480,270);
    setMaximumSize(480,270);
    this -> setStyleSheet("background:Azure");
    usrLabel = new QLabel(tr("userID："));
    pwdLabel = new QLabel(tr("新密码："));
    pwrLabel = new QLabel(tr("重复密码："));
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    pwrLineEdit = new QLineEdit;
    pwrLineEdit->setEchoMode(QLineEdit::Password);
    usrLineEdit->setMaxLength(12);
    pwdLineEdit->setMaxLength(24);
    pwrLineEdit->setMaxLength(24);
    gridlayout = new QGridLayout;
    gridlayout->addWidget(usrLabel,0,0,1,1);
    gridlayout->addWidget(usrLineEdit,0,1,1,1);
    gridlayout->setSpacing(20);
    gridlayout->addWidget(pwdLabel,1,0,1,1);
    gridlayout->addWidget(pwdLineEdit,1,1,1,1);
    gridlayout->addWidget(pwrLabel,2,0,1,1);
    gridlayout->addWidget(pwrLineEdit,2,1,1,1);
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
void WPasswd :: accept()
{
    int message;
    long long num;
    string str, strr;
    num = Nios :: StrNum(usrLineEdit->text().trimmed().toStdString());
    str = pwdLineEdit -> text().trimmed().toStdString();
    strr = pwrLineEdit -> text().trimmed().toStdString();
    queueNum.push(num);
    queueStr.push(str);
    queueStr.push(strr);
    message = procFunc(6);
    if (message == 0)
    {
        QMessageBox::warning(this,"","修改成功",QMessageBox::Yes);
        inOperation = EUsers.GetUser(inOperation.userID);
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"","两次密码不一致或没有找到这个用户。",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}

WPasswd::~WPasswd()
{
    delete ui;
}
