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
    this -> setStyleSheet("background:Azure");
    usrLabel = new QLabel(tr("userID："));
    pwdLabel = new QLabel(tr("密　码："));
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    usrLineEdit->setMaxLength(12);
    pwdLineEdit->setMaxLength(24);
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
string level(long long auth)
{
    switch(auth)
    {
    case 3 : return string("馆长"); break;
    case 2 : return string("管理员"); break;
    case -1 : return string("被封禁的普通用户"); break;
    case 1 : return string("普通用户"); break;
    case 0 : return string("游客"); break;
    }
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
        www -> btLogin -> setText("登出");
        QMessageBox::warning(this,"登录成功",("欢迎您， " + inOperation.userNickname).c_str(),QMessageBox::Yes);
        if ((inOperation.authority <= 1) && (EUsers.KeepingTimedOut(inOperation.userID)))
        {
            QMessageBox::warning(this,"警告","由于逾期未归还书籍，您已经被封禁，请联系馆长或代馆长",QMessageBox::Yes);
            if (inOperation.authority > 0)
                EUsers.SetUserAuthority(inOperation.userID, -inOperation.authority);
        }
        www -> userName -> setText(("当前用户 " + level(inOperation.authority) + inOperation.userNickname).c_str());
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"","用户名或密码错误",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}
WLogin::~WLogin()
{
    delete ui;
}
