#include "controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stage.h"
#include "worldmodel.h"

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    mainWindow_(mainWindow)
{
}

void Controller::createNewProject()
{
    Stage *stage = new Stage(mainWindow_->ui->tabWidget);
    mainWindow_->ui->tabWidget->addTab(stage, "new project");

    WorldModel *model = new WorldModel(this);
    stage->connectToModel(stage, model);

    viewMap_.insert(stage, model);
}

void Controller::rectangleTEST()
{
    QBodyDef *body = new QBodyDef;
    QFixtureDef *fix = new QFixtureDef;

    b2PolygonShape shape;
    shape.SetAsBox(20, 20);
    fix->setShape(&shape);

    body->addFixtureDef(fix);

    WorldModel* model = getActiveModel();
    if (model)
        model->addBody(body);
}

WorldModel* Controller::getActiveModel() const
{
    return viewMap_.value(mainWindow_->ui->tabWidget->currentWidget());
}
