#include "stage.h"
#include "ui_stage.h"
#include "qbodydef.h"
#include "qfixturedef.h"
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

Stage::Stage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stage)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(ui->graphicsView);
    scene_->setBackgroundBrush(QBrush(QColor(32, 32, 32)));
    ui->graphicsView->setScene(scene_);

    scene_->installEventFilter(this);
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

bool Stage::eventFilter(QObject *obj, QEvent *evt)
{
    if (obj != scene_) return false;

    switch (evt->type()) {
    case QEvent::GraphicsSceneMousePress:
    case QEvent::GraphicsSceneMouseRelease:
    case QEvent::GraphicsSceneMouseMove:
        emit mouseEvent(dynamic_cast<QGraphicsSceneMouseEvent*>(evt));
        break;
    default:
        break;
    }

    return false;
}
