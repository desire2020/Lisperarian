#include "wsearch.h"
#include "interface.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "ui_wsearch.h"

WSearch::WSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WSearch)
{
    ui->setupUi(this);
}

WSearch::~WSearch()
{
    delete ui;
}
