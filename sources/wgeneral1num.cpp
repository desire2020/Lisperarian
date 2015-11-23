#include "wgeneral1num.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wgeneral1num.h"

WGeneral1Num::WGeneral1Num(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WGeneral1Num)
{
    ui->setupUi(this);
    this -> setStyleSheet("background:White");
    setMinimumSize(800,100);
    setMaximumSize(800,100);
    setWindowTitle("");
    numLabel = new QLabel(tr("目标编号"));
    numLineEdit = new QLineEdit;
    numLineEdit -> setMaxLength(35);

    gridlayout = new QGridLayout;
    gridlayout -> addWidget(numLabel,0,0,1,1);
    gridlayout -> addWidget(numLineEdit,0,1,1,1);
    gridlayout -> setSpacing(20);

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

void WGeneral1Num :: accept()
{
    int message;
    queueNum.push(Nios :: StrNum(numLineEdit -> text().trimmed().toStdString()));
    message = procFunc(workingModeGer);
    if (message == 0)
    {
        if (workingModeGer == -4)
            QMessageBox::warning(this,"",Nios :: ShowOneBookRequired().c_str(),QMessageBox::Yes);
        else
            if (workingModeGer == -10)
                QMessageBox::warning(this,"",Nios :: ShowUserRequired().c_str(),QMessageBox::Yes);
        else
            QMessageBox::warning(this,"成功","成功完成",QMessageBox::Yes);
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"失败","此对象不存在或者您没有权限访问",QMessageBox::Yes);
        numLineEdit->setFocus();
    }
}

WGeneral1Num::~WGeneral1Num()
{
    delete ui;
}
