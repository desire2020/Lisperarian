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
    setMinimumSize(640,360);
    setMaximumSize(640,360);
    this -> setStyleSheet("background:White");
    usrLabel = new QLabel(tr("昵　　称："));
    pwd1Label = new QLabel(tr("密　　码："));
    nameLabel = new QLabel(tr("真实姓名："));
    teleLabel = new QLabel(tr("联系电话："));
    idenLabel = new QLabel(tr("身份证号："));

    usrLineEdit = new QLineEdit;
    pwd1LineEdit = new QLineEdit;
    nameLineEdit = new QLineEdit;
    teleLineEdit = new QLineEdit;
    idenLineEdit = new QLineEdit;

    usrLineEdit -> setMaxLength(12);
    pwd1LineEdit -> setEchoMode(QLineEdit::Password);
    pwd1LineEdit -> setMaxLength(18);
    nameLineEdit -> setMaxLength(10);
    teleLineEdit -> setMaxLength(18);
    idenLineEdit -> setMaxLength(18);

    gridlayout = new QGridLayout;
    gridlayout->addWidget(usrLabel,0,0,1,1);
    gridlayout->addWidget(usrLineEdit,0,1,1,1);
    gridlayout->setSpacing(20);
    gridlayout->addWidget(pwd1Label,1,0,1,1);
    gridlayout->addWidget(pwd1LineEdit,1,1,1,1);
    gridlayout->addWidget(nameLabel,2,0,1,1);
    gridlayout->addWidget(nameLineEdit,2,1,1,1);
    gridlayout->addWidget(teleLabel,3,0,1,1);
    gridlayout->addWidget(teleLineEdit,3,1,1,1);
    gridlayout->addWidget(idenLabel,4,0,1,1);
    gridlayout->addWidget(idenLineEdit,4,1,1,1);

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
    queueStr.push(usrLineEdit -> text().trimmed().toStdString());
    queueStr.push(pwd1LineEdit -> text().trimmed().toStdString());
    queueStr.push(nameLineEdit -> text().trimmed().toStdString());
    queueNum.push(Nios :: StrNum(teleLineEdit -> text().trimmed().toStdString()));
    queueStr.push(idenLineEdit -> text().trimmed().toStdString());

    message = procFunc(0);
    if(message == 0)
    {
        QMessageBox::warning(this,"注册成功",("欢迎您， " + inOperation.userNickname + "请牢记您的userID" + Nios :: NumStr(presentUID - 1)).c_str(),QMessageBox::Yes);
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"未知错误","请联系馆长",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}
WSignin::~WSignin()
{
    delete ui;
}
