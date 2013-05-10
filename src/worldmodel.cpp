#include "worldmodel.h"
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QDebug>
#include <QGraphicsItem>

WorldModel::WorldModel(QObject *parent)
    : QObject(parent)
    , simulationThread_(this)
    , world_(nullptr)
{
   simulation_.moveToThread(&simulationThread_);
   simulationThread_.start();
}

WorldModel::~WorldModel()
{
    if (world_)
        delete world_;
}

QLinkedList<WorldModel::SpQBodyDef> WorldModel::getBodyList() const
{
    return bodyList_;
}

void WorldModel::addBody(QBodyDef *bodyDef)
{
    bodyList_.append(SpQBodyDef(bodyDef));
    emit bodyAdded(bodyDef);
}

void WorldModel::addBody(const QScriptValue &value)
{
    QObject *obj = value.toQObject();
    QBodyDef *body = dynamic_cast<QBodyDef*>(obj);

    if (body)
        addBody(body);
}

void WorldModel::run(qint32 fps, qreal worldStep)
{
   createWorld();
   simulation_.setSimulation(world_, fps, worldStep);
   QMetaObject::invokeMethod(&simulation_, "run", Qt::QueuedConnection);
}

void WorldModel::stop()
{
    //simulationThread_.exit();
    QMetaObject::invokeMethod(&simulation_, "stop", Qt::QueuedConnection);
    syncGraphicsWithModel();
}

void WorldModel::createWorld()
{
    if (world_) delete world_;
    world_ = new b2World(b2Vec2(0, 10));

    foreach (const SpQBodyDef &bodyDef, bodyList_)
    {
        b2Body *body = world_->CreateBody(bodyDef->getBodyDef());
        foreach (const QBodyDef::SpQFixtureDef &fixtureDef, *bodyDef->getFixtureList())
        {
            b2Fixture *fix = body->CreateFixture(fixtureDef->getFixtureDef());
            fix->SetUserData(fixtureDef->getGraphicsItem());
        }
    }
}

void WorldModel::syncGraphicsWithModel()
{
    foreach (const SpQBodyDef &bodyDef, bodyList_)
        bodyDef->syncGraphics();
}

//------ WorldSimulation methods ------

WorldSimulation::WorldSimulation()
    : world_(nullptr)
    , fps_(30)
    , worldStep_(1.0/60.0f)
{
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &WorldSimulation::step);
}

void WorldSimulation::setSimulation(b2World *world, qint32 fps, qreal worldStep)
{
    world_ = world;
    fps_ = fps;
    worldStep_ = worldStep;
}

void WorldSimulation::run()
{
    if (world_)
        timer_->start(1000.0/fps_);
}

void WorldSimulation::stop()
{
    timer_->stop();
}

void WorldSimulation::step()
{
    static int i = 0;
    //qDebug() << ++i << "world step";

    if (world_)
    {
        world_->Step(worldStep_, 10, 10);
        b2Body *b = world_->GetBodyList();
        while (b != nullptr)
        {
            b2Fixture *f = b->GetFixtureList();
            while (f != nullptr)
            {
                QGraphicsItem* g = static_cast<QGraphicsItem*>(f->GetUserData());
                if (g)
                {
                    static const qreal PI = 3.1415926535;
                    // update position
                    g->setPos(b->GetWorldCenter().x, b->GetWorldCenter().y);
                    // update rotation
                    g->setRotation((b->GetAngle() * 180)/PI);
                }
                f = f->GetNext();
            }
            b = b->GetNext();
        }
    }
}
