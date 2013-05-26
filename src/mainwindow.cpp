#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeySequence>
#include <QFileDialog>
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::openFile(QString filename)
{
    if (filename.isEmpty())
        filename = QFileDialog::getOpenFileName(this);

    if (filename.isEmpty()) return "";

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QString content = file.readAll();
    QApplication::restoreOverrideCursor();

    return content;
}

QString MainWindow::saveFile(const QString &content, QString filename)
{
    if (filename.isEmpty())
        filename = QFileDialog::getSaveFileName(this);

    if (filename.isEmpty()) return "";

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
        return "";

    file.write(content.toUtf8());
    QApplication::restoreOverrideCursor();

    return filename;
}
