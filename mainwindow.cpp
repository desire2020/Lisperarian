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
    connect(btExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btLogin, SIGNAL(clicked()), this, SLOT(showw2()));
    connect(btSignin, SIGNAL(clicked()), this, SLOT(showw3()));
    connect(btRefresh, SIGNAL(clicked()), this, SLOT(Refresh()));
    connect(btBorBook, SIGNAL(clicked()), this, SLOT(Borrow()));
    connect(btRetBook, SIGNAL(clicked()), this, SLOT(GiveBack()));
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
MainWindow::~MainWindow()
{
    delete ui;
}
