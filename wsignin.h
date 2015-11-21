#ifndef WSIGNIN_H
#define WSIGNIN_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WSignin;
}

class WSignin : public QWidget
{
    Q_OBJECT

public:
    explicit WSignin(QWidget *parent = 0);
    ~WSignin();

private:
    Ui::WSignin *ui;
    QLineEdit *usrLineEdit;
    QLineEdit *pwd1LineEdit, *pwd2LineEdit;
    QLabel *usrLabel;
    QLabel *pwd1Label, *pwd2Label;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();
};

#endif // WSIGNIN_H
