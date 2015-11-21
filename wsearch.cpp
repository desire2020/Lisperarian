#include "wsearch.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wsearch.h"

WSearch::WSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WSearch)
{
    ui->setupUi(this);
    this -> setStyleSheet("background:Azure");
    wd1Label = new QLabel(tr("关键词1:"));
    wd2Label = new QLabel(tr("关键词2:"));
    wd3Label = new QLabel(tr("关键词3:"));

    wd1LineEdit = new QLineEdit;
    wd2LineEdit = new QLineEdit;
    wd3LineEdit = new QLineEdit;

    gridlayout = new QGridLayout;
    gridlayout -> setSpacing(20);
    gridlayout -> addWidget(wd1Label, 0, 0, 1, 1);
    gridlayout -> addWidget(wd1LineEdit, 0, 1, 1, 1);
    gridlayout -> addWidget(wd2Label, 1, 0, 1, 1);
    gridlayout -> addWidget(wd2LineEdit, 1, 1, 1, 1);
    gridlayout -> addWidget(wd3Label, 2, 0, 1, 1);
    gridlayout -> addWidget(wd3LineEdit, 2, 1, 1, 1);

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

void WSearch :: accept()
{
    int message;
    queueStr.push(wd1LineEdit -> text().trimmed().toStdString());
    queueStr.push(wd2LineEdit -> text().trimmed().toStdString());
    queueStr.push(wd3LineEdit -> text().trimmed().toStdString());
    message = procFunc(-3);
    QMessageBox::warning(this,"查询结果",Nios :: ShowBookRequired().c_str(),QMessageBox::Yes);
}

WSearch::~WSearch()
{
    delete ui;
}
