#ifndef WPASSWD_H
#define WPASSWD_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WPasswd;
}

class WPasswd : public QWidget
{
    Q_OBJECT

public:
    explicit WPasswd(QWidget *parent = 0);
    ~WPasswd();

private:
    Ui::WPasswd *ui;
    QLineEdit *usrLineEdit;
    QLineEdit *pwdLineEdit, *pwrLineEdit;
    QLabel *usrLabel;
    QLabel *pwdLabel, *pwrLabel;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();
};

#endif // WPASSWD_H
