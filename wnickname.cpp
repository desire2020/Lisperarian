#include "wnickname.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wnickname.h"

WNickName::WNickName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WNickName)
{
    ui->setupUi(this);
    setMinimumSize(280,150);
    setMaximumSize(280,150);
    this -> setStyleSheet("background:Azure");
    usrLabel = new QLabel(tr("userID："));
    pwdLabel = new QLabel(tr("新的昵称："));
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
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
void WNickName :: accept()
{
    int message;
    queueNum.push(Nios :: StrNum(usrLineEdit -> text().trimmed().toStdString()));
    queueStr.push(pwdLineEdit -> text().trimmed().toStdString());

    message = procFunc(5);
    if(message == 0)
    {
        QMessageBox::warning(this,"","修改成功",QMessageBox::Yes);
        inOperation = EUsers.GetUser(inOperation.userID);
        www -> userName -> setText(("当前用户 " + Nios :: level(inOperation.authority) + inOperation.userNickname).c_str());
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"操作越界","非管理员以上请勿试图修改他人昵称。此外请检查目标ID的合法性！",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}
WNickName::~WNickName()
{
    delete ui;
}
