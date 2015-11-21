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
};

#endif // WSEARCH_H
