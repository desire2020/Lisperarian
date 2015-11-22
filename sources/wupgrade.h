#ifndef WUPGRADE_H
#define WUPGRADE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WUpgrade;
}

class WUpgrade : public QWidget
{
    Q_OBJECT

public:
    explicit WUpgrade(QWidget *parent = 0);
    ~WUpgrade();

private:
    Ui::WUpgrade *ui;
    QLineEdit *usrLineEdit, *autLineEdit;
    QLabel *usrLabel, *autLabel;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();
};

#endif // WUPGRADE_H
