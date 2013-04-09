#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Console* console = new Console(this);
    addDockWidget(Qt::BottomDockWidgetArea, console);
}

MainWindow::~MainWindow()
{
    delete ui;
}
