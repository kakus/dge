#include "stage.h"
#include "ui_stage.h"
#include "qbodydef.h"
#include "qfixturedef.h"

Stage::Stage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stage)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene_);
}

Stage::~Stage()
{
    delete ui;
}

void Stage::bodyAdded(const QBodyDef *bodyDef)
{
    foreach(const QBodyDef::SpQFixtureDef &fixtureDef, *(bodyDef->getFixtureList()))
    {
       scene_->addItem(fixtureDef->getGraphicsItem());
       bodyMap_.insert(bodyDef, fixtureDef->getGraphicsItem());
    }
}

void Stage::bodyRemoved(const QBodyDef *)
{

}

void Stage::bodyChanged(const QBodyDef *)
{

}
