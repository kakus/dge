#include "tabview.h"
#include "ui_tabview.h"

TabView::TabView(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::TabView)
{
    ui->setupUi(this);
}

TabView::~TabView()
{
    delete ui;
}
