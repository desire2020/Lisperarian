#include "mainwindow.h"
#include "stdincs.hpp"
#include "classes.hpp"
#include "ui_mainwindow.h"

QFont btFont("微软雅黑", 17);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    this -> setWindowFlags(Qt :: FramelessWindowHint);
    this -> setStyleSheet("background:Azure");
    //this -> setGeometry(QRect(500, 300, 800, 600));
    btExit = new QPushButton(this);
    btExit -> setText("关闭");
    btExit -> setGeometry(QRect(600, 500, 141, 91));
    btExit -> setFont(btFont);
    btExit -> setStyleSheet("background:LightCyan");
    welcomeWord = new QLabel(this);
    welcomeWord -> setFont(btFont);
    welcomeWord -> setText("欢迎使用Lisperarian");
    welcomeWord -> setGeometry(QRect(70, 10, 500, 91));
    welcomeWord -> setStyleSheet("background:Azure; border:0 double Black");
    userName = new QLabel(this);
    userName -> setFont(btFont);
    userName -> setGeometry(QRect(70, 120, 500, 91));
    userName -> setText("游客");
    userName -> setStyleSheet("background:Azure; border:0 double Black");
    btLogin = new QPushButton(this);
    btLogin -> setText("登录");
    btLogin -> setGeometry(QRect(600, 400, 141, 91));
    btLogin -> setFont(btFont);
    btLogin -> setStyleSheet("background:LightCyan");
    btSignin = new QPushButton(this);
    btSignin -> setText("注册");
    btSignin -> setGeometry(QRect(600, 100, 141, 91));
    btSignin -> setFont(btFont);
    btSignin -> setStyleSheet("background:LightCyan");
    btRefresh = new QPushButton(this);
    btRefresh -> setText("刷新");
    btRefresh -> setGeometry(QRect(690, 20, 90, 70));
    btRefresh -> setFont(btFont);
    btRefresh -> setStyleSheet("background:LightCyan");
    btBorBook = new QPushButton(this);
    btBorBook -> setGeometry(QRect(380, 140, 151, 61));
    btBorBook -> setText("借阅图书");
    btBorBook -> setFont(btFont);
    btBorBook -> setStyleSheet("background:LightCyan");
    btRetBook = new QPushButton(this);
    btRetBook -> setGeometry(QRect(380, 210, 151, 61));
    btRetBook -> setText("归还图书");
    btRetBook -> setFont(btFont);
    btRetBook -> setStyleSheet("background:LightCyan");
    btSearchBook = new QPushButton(this);
    btSearchBook -> setGeometry(QRect(380, 70, 151, 61));
    btSearchBook -> setText("搜索图书");
    btSearchBook -> setFont(btFont);
    btSearchBook -> setStyleSheet("background:LightCyan");
    btDetail = new QPushButton(this);
    btDetail -> setText("图书详情");
    btDetail -> setGeometry(QRect(380, 280, 151, 61));
    btDetail -> setFont(btFont);
    btDetail -> setStyleSheet("background:LightCyan");
    btNickName = new QPushButton(this);
    btNickName -> setText("更改昵称");
    btNickName -> setGeometry(QRect(200, 210, 151, 61));
    btNickName -> setFont(btFont);
    btNickName -> setStyleSheet("background:LightCyan");
    btPasswd = new QPushButton(this);
    btPasswd -> setText("更改密码");
    btPasswd -> setGeometry(QRect(200, 280, 151, 61));
    btPasswd -> setFont(btFont);
    btPasswd -> setStyleSheet("background:LightCyan");
    btAdd = new QPushButton(this);
    btAdd -> setText("录入书籍");
    btAdd -> setGeometry(QRect(380, 350, 151, 61));
    btAdd -> setFont(btFont);
    btAdd -> setStyleSheet("background:LightCyan");

    btEditf = new QPushButton(this);
    btEditf -> setText("更正图书信息");
    btEditf -> setGeometry(QRect(380, 420, 151, 61));
    btEditf -> setFont(btFont);
    btEditf -> setStyleSheet("background:LightCyan");

    btDel = new QPushButton(this);
    btDel -> setText("删除书籍");
    btDel -> setGeometry(QRect(380, 490, 151, 61));
    btDel -> setFont(btFont);
    btDel -> setStyleSheet("background:LightCyan");

    btDelUser = new QPushButton(this);
    btDelUser -> setText("删除用户");
    btDelUser -> setGeometry(QRect(200, 350, 151, 61));
    btDelUser -> setFont(btFont);
    btDelUser -> setStyleSheet("background:LightCyan");

    btUpgrade = new QPushButton(this);
    btUpgrade -> setText("更改用户权限");
    btUpgrade -> setGeometry(QRect(200, 420, 151, 61));
    btUpgrade -> setFont(btFont);
    btUpgrade -> setStyleSheet("background:LightCyan");

    connect(btExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btLogin, SIGNAL(clicked()), this, SLOT(showw2()));
    connect(btSignin, SIGNAL(clicked()), this, SLOT(showw3()));
    connect(btRefresh, SIGNAL(clicked()), this, SLOT(Refresh()));
    connect(btBorBook, SIGNAL(clicked()), this, SLOT(Borrow()));
    connect(btRetBook, SIGNAL(clicked()), this, SLOT(GiveBack()));
    connect(btSearchBook, SIGNAL(clicked()), this, SLOT(SearchB()));
    connect(btDetail, SIGNAL(clicked()), this, SLOT(Details()));
    connect(btNickName, SIGNAL(clicked()), this, SLOT(NickName()));
    connect(btPasswd, SIGNAL(clicked()), this, SLOT(Passwd()));
    connect(btAdd, SIGNAL(clicked()), this, SLOT(AddBk()));
    connect(btEditf, SIGNAL(clicked()), this, SLOT(EditBk()));
    connect(btDel, SIGNAL(clicked()), this, SLOT(DelBk()));
    connect(btDelUser, SIGNAL(clicked()), this, SLOT(DelUr()));
    connect(btUpgrade, SIGNAL(clicked()), this, SLOT(Upgrade()));
}
void MainWindow :: mousePressEvent(QMouseEvent *e)
{
    last = e -> globalPos();
}
void MainWindow :: mouseMoveEvent(QMouseEvent *e)
{
    int dx = e -> globalX() - last.x();
    int dy = e -> globalY() - last.y();
    last = e -> globalPos();
    move(x() + dx, y() + dy);
}
void MainWindow :: mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e -> globalX() - last.x();
    int dy = e -> globalY() - last.y();
    move(x() + dx, y() + dy);
}
void MainWindow :: showw2()
{
    if (CheckAuthority(1, inOperation))
        w2.show();
    else
    {
        Logout();
        QMessageBox::warning(this,"成功","您已经登出 欢迎下次再来",QMessageBox::Yes);
        btLogin -> setText("登录");
        userName -> setText("游客");
    }
}
void MainWindow :: showw3()
{
    if (CheckAuthority(0, inOperation))
        w3.show();
    else
        QMessageBox::warning(this,"错误","您已经登录 不能注册",QMessageBox::Yes);
}
void MainWindow :: Refresh()
{
    Finalization();
}
void MainWindow :: Borrow()
{
    workingModeGer = 3;

    if (CheckAuthority(3, inOperation))
        w4.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: GiveBack()
{
    workingModeGer = 4;

    if (CheckAuthority(4, inOperation))
        w4.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: SearchB()
{
    if (CheckAuthority(-3, inOperation))
        w5.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: Details()
{
    workingModeGer = -4;
    if (CheckAuthority(-4, inOperation))
        w4.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: NickName()
{
    if (CheckAuthority(5, inOperation))
        w6.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: Passwd()
{
    if (CheckAuthority(6, inOperation))
        w7.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: AddBk()
{
    workingModeGer = 7;
    if (CheckAuthority(7, inOperation))
        w8.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: DelBk()
{
    workingModeGer = 8;
    if (CheckAuthority(8, inOperation))
        w4.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);
}
void MainWindow :: EditBk()
{
    workingModeGer = 9;
    if (CheckAuthority(9, inOperation))
        w8.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}
void MainWindow :: DelUr()
{
    workingModeGer = 10;
    if (CheckAuthority(10, inOperation))
        w4.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);
}
void MainWindow :: Upgrade()
{
    if (CheckAuthority(11, inOperation))
        w9.show();
    else
        QMessageBox::warning(this,"错误","您没有权限进行这个操作",QMessageBox::Yes);

}

MainWindow::~MainWindow()
{
    delete ui;
}
