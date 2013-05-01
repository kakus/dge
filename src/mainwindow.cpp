#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeySequence>
#include "stage.h"
#include "worldmodel.h"
#include "controller.h"

// creazy stuff
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QDebug>
#include "qbodydef.h"
#include "qfixturedef.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize controller
    controller_ = new Controller(this);

    // Create widgets that are dockable widgets
    console_ = new Console(this);
    addDockWidget(Qt::BottomDockWidgetArea, console_);

    // Add actions to main window
    QAction *toggleConsoleAction = console_->toggleViewAction();
    toggleConsoleAction->setText("Show console");
    toggleConsoleAction->setShortcut(QKeySequence::fromString("Ctrl+T"));
    ui->menuView->addAction(toggleConsoleAction);

    // Connect Actions
    connect(ui->actionNew_Project, SIGNAL(triggered()),
            controller_,           SLOT(createNewProject()));

    // Creazy stuff
    connect(ui->actionRectangle, SIGNAL(triggered()),
            controller_,         SLOT(rectangleTEST()));

    QScriptEngine* engine = new QScriptEngine();
    QObject *body = new QFixtureDef();
    QScriptValue bodyVal = engine->newQObject(body);
    engine->globalObject().setProperty("bodyDef", bodyVal);

    QScriptValue x = engine->evaluate("((function() { var str = []; for(var prop in bodyDef) str.push([prop, ' : ', bodyDef[prop]].join('')); return str.join('--'); })())");

    console_->write(x.toString());

}

MainWindow::~MainWindow()
{
    delete ui;
}
