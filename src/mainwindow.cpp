#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"

#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create widgets that are dockable widgets
    Console *console = new Console(this);
    addDockWidget(Qt::BottomDockWidgetArea, console);

    // Add actions to main window
    QAction *toggleConsoleAction = console->toggleViewAction();
    toggleConsoleAction->setText("Show console");
    toggleConsoleAction->setShortcut(QKeySequence::fromString("Ctrl+T"));
    ui->menuView->addAction(toggleConsoleAction);

    // Connect Actions
}

MainWindow::~MainWindow()
{
    delete ui;
}
