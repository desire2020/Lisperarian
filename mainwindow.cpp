#include "mainwindow.h"
#include "stdincs.hpp"
#include "classes.hpp"
#include "ui_mainwindow.h"

QFont btFont("微软雅黑", 22);
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
    connect(btExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btLogin, SIGNAL(clicked()), this, SLOT(showw2()));
    connect(btSignin, SIGNAL(clicked()), this, SLOT(showw3()));
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
    w2.show();
}
void MainWindow :: showw3()
{
    w3.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
