#ifndef WGENERAL1NUM_H
#define WGENERAL1NUM_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WGeneral1Num;
}

class WGeneral1Num : public QWidget
{
    Q_OBJECT

public:
    explicit WGeneral1Num(QWidget *parent = 0);
    ~WGeneral1Num();

private:
    Ui::WGeneral1Num *ui;
    QLineEdit *numLineEdit;
    QLabel *numLabel;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();
};

#endif // WGENERAL1NUM_H
