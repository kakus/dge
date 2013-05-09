#include "qbodydef.h"

QBodyDef::QBodyDef(QObject *parent) :
    QObject(parent)
{
}

void QBodyDef::syncGraphics()
{
    updateFixtures();
}

void QBodyDef::addFixtureDef(const QFixtureDef *fixtureDef)
{
    fixtureList_.append(SpQFixtureDef(fixtureDef));
}

const QLinkedList<QBodyDef::SpQFixtureDef>* QBodyDef::getFixtureList() const
{
    return &fixtureList_;
}

// slot
void QBodyDef::createFixture(const QScriptValue &fixtureDef)
{
    QObject *obj = fixtureDef.toQObject();
    QFixtureDef *fix = dynamic_cast<QFixtureDef*>(obj);

    if (fix == nullptr)
        return;

    QFixtureDef *copy = new QFixtureDef();
    copy->fixtureDef_ = fix->fixtureDef_;
    copy->setShape(fix->getShape());

    addFixtureDef(copy);
}

void QBodyDef::updateFixtures()
{
    foreach(const SpQFixtureDef &fixture, fixtureList_ )
        fixture->graphicsItem_->setPos(bodyDef_.position.x,
                                       bodyDef_.position.y);
}
