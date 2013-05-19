#include "worldmodel.h"
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QDebug>
#include <QGraphicsItem>

WorldModel::WorldModel(QObject *parent)
    : QObject(parent)
    , world_(nullptr)
    , simulationThread_(this)
{
    simulation_.moveToThread(&simulationThread_);
    simulationThread_.start();
}

WorldModel::~WorldModel()
{
    simulationThread_.exit();

    if (world_)
        delete world_;
}

QBodyDef* WorldModel::createBody(const QFixtureDef *fixtureDef)
{
    if (isSimulationRunning())
        return nullptr;

    QBodyDef *body = new QBodyDef();
    if (fixtureDef) body->createFixture(fixtureDef);

    bodyList_.append(body);
    emit bodyAdded(body);

    return body;
}

QBodyDef* WorldModel::createBody()
{
    return createBody(static_cast<QFixtureDef*>(nullptr));
}

QBodyDef* WorldModel::createBody(const QBodyDef *qbody)
{
    QBodyDef* clone = createBody();
    clone->bodyDef_ = qbody->bodyDef_;

    foreach (const QFixtureDef* fix, qbody->getFixtureList())
        clone->createFixture(fix);

    return clone;
}

bool WorldModel::isSimulationRunning() const
{
    return simulation_.isRunning();
}

// -------- slots --------

void WorldModel::removeBody(QBodyDef *body)
{
    if (isSimulationRunning())
        return;

    if (bodyList_.removeOne(body))
    {
        emit bodyRemoved(body);
        body->deleteLater();
    }
}

void WorldModel::removeBody(const QScriptValue &value)
{
    QObject *obj = value.toQObject();
    QBodyDef *body = dynamic_cast<QBodyDef*>(obj);

    if (body)
        removeBody(body);

}

void WorldModel::run(qint32 fps, qreal worldStep)
{
    // TODO try to make nicer soultion
    QMetaObject::invokeMethod(&simulation_, "stop", Qt::QueuedConnection);

    createWorld();
    simulation_.setSimulation(world_, fps, worldStep);
    QMetaObject::invokeMethod(&simulation_, "run", Qt::QueuedConnection);
    emit simulationStart();
}

void WorldModel::stop()
{
    QMetaObject::invokeMethod(&simulation_, "stop", Qt::QueuedConnection);

    // restore all bodies to the state before simulation was started
    foreach (QBodyDef *bodyDef, bodyList_)
        bodyDef->restore();

    emit simulationStop();
}

void WorldModel::createWorld()
{
    if (world_) delete world_;
    world_ = new b2World(b2Vec2(0, 10));

    foreach (QBodyDef *bodyDef, bodyList_)
    {
        // save the current state of object
        bodyDef->save();
        // create body
        b2Body *body = world_->CreateBody(bodyDef->getBodyDef());
        // save pointer to the object that can be displayed
        body->SetUserData(bodyDef);
        // create all fixtures that belong to this body
        foreach (const QFixtureDef *fixtureDef, bodyDef->getFixtureList())
            body->CreateFixture(fixtureDef->getb2FixtureDef());
    }
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

inline bool WorldSimulation::isRunning() const
{
    return timer_->isActive();
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
    if (world_ == nullptr) return;

    world_->Step(worldStep_, 10, 10);
    b2Body *b = world_->GetBodyList();
    for (; b != nullptr; b = b->GetNext())
    {
        QBodyDef* qbody = static_cast<QBodyDef*>(b->GetUserData());
        if (qbody == nullptr)
            continue;

        qbody->setPosition(b->GetWorldCenter());
        qbody->setAngle(b->GetAngle());
    }
}
