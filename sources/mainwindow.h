#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include "wlogin.h"
#include "wsignin.h"
#include "wgeneral1num.h"
#include "wsearch.h"
#include "wnickname.h"
#include "wpasswd.h"
#include "wbookedit.h"
#include "wupgrade.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QLabel *welcomeWord, *userName;
    QPushButton *btLogin, *btExit, *btSignin, *btRefresh;
    QPushButton *btBorBook, *btRetBook, *btSearchBook, *btDetail, *btAdd, *btDel, *btEditf;
    QPushButton *btNickName, *btPasswd, *btDelUser, *btUpgrade, *btShowUsr;
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    Ui::MainWindow *ui;
    WLogin w2;
    WSignin w3;
    WGeneral1Num w4;
    WSearch w5;
    WNickName w6;
    WPasswd w7;
    WBookEdit w8;
    WUpgrade w9;
    QPoint last;
private slots:
    void showw2();
    void showw3();
    void Refresh();
    void Borrow();
    void GiveBack();
    void SearchB();
    void Details();
    void NickName();
    void Passwd();
    void AddBk();
    void EditBk();
    void DelBk();
    void DelUr();
    void Upgrade();
    void ShowUsr();
};

#endif // MAINWINDOW_H
