#include "wupgrade.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wupgrade.h"

WUpgrade::WUpgrade(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WUpgrade)
{
    ui->setupUi(this);
    setMinimumSize(640,360);
    setMaximumSize(640,360);
    this -> setStyleSheet("background:White");

    usrLabel = new QLabel(tr("userID:"));
    autLabel = new QLabel(tr("权限:"));

    usrLineEdit = new QLineEdit;
    autLineEdit = new QLineEdit;

    usrLineEdit -> setMaxLength(18);
    autLineEdit -> setMaxLength(3);

    gridlayout = new QGridLayout;
    gridlayout->addWidget(usrLabel,0,0,1,1);
    gridlayout->addWidget(usrLineEdit,0,1,1,1);
    gridlayout->setSpacing(20);
    gridlayout->addWidget(autLabel,1,0,1,1);
    gridlayout->addWidget(autLineEdit,1,1,1,1);

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

void WUpgrade :: accept()
{
    int message;
    queueNum.push(Nios :: StrNum(usrLineEdit -> text().trimmed().toStdString()));
    queueNum.push(Nios :: StrNum(autLineEdit -> text().trimmed().toStdString()));

    message = procFunc(11);
    if (message == 0)
    {
        QMessageBox::warning(this,"","修改完成",QMessageBox::Yes);
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"","用户不存在或其他错误",QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}

WUpgrade::~WUpgrade()
{
    delete ui;
}
