#include "mainwindow.h"
#include "ui_mainwindow.h"

QFont btFont("微软雅黑", 22);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    this -> setWindowFlags(Qt :: FramelessWindowHint);
    this -> setStyleSheet("background:CornflowerBlue");
    this -> setGeometry(QRect(0,0,1920,1080));
    btExit = new QPushButton(this);
    btExit -> setText("关闭");
    btExit -> setGeometry(QRect(1280,700,141,91));
    btExit -> setFont(btFont);
    btExit -> setStyleSheet("background:FloralWhite");
    connect(btExit, SIGNAL(clicked()), this, SLOT(close()));
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

MainWindow::~MainWindow()
{
    delete ui;
}
