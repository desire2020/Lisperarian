#ifndef WNICKNAME_H
#define WNICKNAME_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WNickName;
}

class WNickName : public QWidget
{
    Q_OBJECT

public:
    explicit WNickName(QWidget *parent = 0);
    ~WNickName();

private:
    Ui::WNickName *ui;
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

#endif // WNICKNAME_H
