#include "wbookedit.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wbookedit.h"

WBookEdit::WBookEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WBookEdit)
{
    ui->setupUi(this);
    setMinimumSize(800,360);
    setMaximumSize(600,360);
    this -> setStyleSheet("background:Azure");
    titLabel = new QLabel(tr("书　名："));
    ISBNLabel = new QLabel(tr("ISBN  :"));
    autLabel = new QLabel(tr("作　者："));
    desLabel = new QLabel(tr("简　介："));
    avaLabel = new QLabel(tr("库存量："));
    lboLabel = new QLabel(tr("仅限于："));

    titLineEdit = new QLineEdit;
    ISBNLineEdit = new QLineEdit;
    autLineEdit = new QLineEdit;
    desLineEdit = new QLineEdit;
    avaLineEdit = new QLineEdit;
    lboLineEdit = new QLineEdit;

    titLineEdit -> setMaxLength(40);
    ISBNLineEdit -> setMaxLength(18);
    autLineEdit -> setMaxLength(40);
    avaLineEdit -> setMaxLength(18);
    lboLineEdit -> setMaxLength(18);;

    gridlayout = new QGridLayout;
    gridlayout->setSpacing(20);
    gridlayout->addWidget(titLabel,0,0,1,1);
    gridlayout->addWidget(titLineEdit,0,1,1,1);
    gridlayout->addWidget(ISBNLabel,1,0,1,1);
    gridlayout->addWidget(ISBNLineEdit,1,1,1,1);
    gridlayout->addWidget(autLabel,2,0,1,1);
    gridlayout->addWidget(autLineEdit,2,1,1,1);
    gridlayout->addWidget(desLabel,3,0,1,1);
    gridlayout->addWidget(desLineEdit,3,1,1,1);
    gridlayout->addWidget(avaLabel,4,0,1,1);
    gridlayout->addWidget(avaLineEdit,4,1,1,1);
    gridlayout->addWidget(lboLabel,5,0,1,1);
    gridlayout->addWidget(lboLineEdit,5,1,1,1);

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

void WBookEdit :: accept()
{
    int message;
    queueStr.push(titLineEdit -> text().trimmed().toStdString());
    queueNum.push(Nios :: StrNum(ISBNLineEdit -> text().trimmed().toStdString()));
    queueStr.push(autLineEdit -> text().trimmed().toStdString());
    queueStr.push(desLineEdit -> text().trimmed().toStdString());
    queueNum.push(Nios :: StrNum(avaLineEdit -> text().trimmed().toStdString()));
    queueNum.push(Nios :: StrNum(lboLineEdit -> text().trimmed().toStdString()));
    message = procFunc(workingModeGer);
    if (message == 0)
    {
        QMessageBox::warning(this,"","修改/添加完成",QMessageBox::Yes);
        QWidget::close();
    }
    else
    {
        QMessageBox::warning(this,"","书籍不存在或其他错误",QMessageBox::Yes);
        ISBNLineEdit->setFocus();
    }
}

WBookEdit::~WBookEdit()
{
    delete ui;
}
