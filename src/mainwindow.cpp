#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeySequence>
#include "stage.h"
#include "worldmodel.h"
#include "controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create widgets that are dockable widgets
    console_ = new Console(this);
    addDockWidget(Qt::BottomDockWidgetArea, console_);

    // Add actions to main window
    QAction *toggleConsoleAction = console_->toggleViewAction();
    toggleConsoleAction->setText("Show console");
    toggleConsoleAction->setShortcut(QKeySequence::fromString("Ctrl+T"));
    ui->menuView->addAction(toggleConsoleAction);

    // Initialize controller
    controller_ = new Controller(this);

    // Connect Actions
    connect(ui->actionNew_Project, SIGNAL(triggered()),
            controller_,           SLOT(createNewProject()));

    connect(ui->actionRun_World_Simulation, SIGNAL(triggered()),
            controller_,                    SLOT(runWorldSimultion()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
