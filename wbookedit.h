#ifndef WBOOKEDIT_H
#define WBOOKEDIT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WBookEdit;
}

class WBookEdit : public QWidget
{
    Q_OBJECT

public:
    explicit WBookEdit(QWidget *parent = 0);
    ~WBookEdit();

private:
    Ui::WBookEdit *ui;
    QLabel *titLabel, *ISBNLabel, *autLabel, *desLabel, *avaLabel, *lboLabel;
    QLineEdit *titLineEdit, *ISBNLineEdit, *autLineEdit, *desLineEdit, *avaLineEdit, *lboLineEdit;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();
};

#endif // WBOOKEDIT_H
