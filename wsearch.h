#ifndef WSEARCH_H
#define WSEARCH_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

namespace Ui {
class WSearch;
}

class WSearch : public QWidget
{
    Q_OBJECT

public:
    explicit WSearch(QWidget *parent = 0);
    ~WSearch();

private:
    Ui::WSearch *ui;
    QLineEdit *wd1LineEdit, *wd2LineEdit, *wd3LineEdit;
    QLabel *wd1Label, *wd2Label, *wd3Label;
    QGridLayout *gridlayout;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QVBoxLayout *vboxLayout;
private slots:
    virtual void accept();
};

#endif // WSEARCH_H
