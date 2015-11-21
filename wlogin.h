#ifndef WLOGIN_H
#define WLOGIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WLogin;
}

class WLogin : public QWidget
{
    Q_OBJECT

public:
    explicit WLogin(QWidget *parent = 0);
    ~WLogin();

private:
    Ui::WLogin *ui;
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit;
    QLabel *usrLabel;
    QLabel *pwdLabel;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();

};

#endif // WLOGIN_H
