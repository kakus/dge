#include "qbodydef.h"

QBodyDef::QBodyDef(QObject *parent) :
    QObject(parent)
{
}

void QBodyDef::addFixtureDef(const QFixtureDef *fixtureDef)
{
    fixtureList_.append(SpQFixtureDef(fixtureDef));
}

const QLinkedList<QBodyDef::SpQFixtureDef>* QBodyDef::getFixtureList() const
{
    return &fixtureList_;
}
