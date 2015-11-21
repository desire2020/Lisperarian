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
    this -> setStyleSheet("background:FloralWhite");
    this -> setGeometry(QRect(0, 0, 800, 600));
    btExit = new QPushButton(this);
    btExit -> setText("关闭");
    btExit -> setGeometry(QRect(600, 500, 141, 91));
    btExit -> setFont(btFont);
    btExit -> setStyleSheet("background:FloralWhite");
    welcomeWord = new QLabel(this);
    welcomeWord -> setFont(btFont);
    welcomeWord -> setText("欢迎使用Lisperarian");
    welcomeWord -> setGeometry(QRect(10, 0, 800, 91));
    userName = new QLabel(this);
    userName -> setFont(btFont);
    userName -> setGeometry(QRect(10, 100, 800, 91));
    userName -> setText("游客");
    btLogin = new QPushButton(this);
    btLogin -> setText("登录");
    btLogin -> setGeometry(QRect(600, 400, 141, 91));
    btLogin -> setFont(btFont);
    btLogin -> setStyleSheet("background:FloralWhite");
    connect(btExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btLogin, SIGNAL(clicked()), this, SLOT(showw2()));
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

MainWindow::~MainWindow()
{
    delete ui;
}
