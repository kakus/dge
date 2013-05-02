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

// slot
void QBodyDef::addFixtureDef(const QFixtureDef &fixtureDef) {
    addFixtureDef(&fixtureDef);
}

// slot
void QBodyDef::addFixtureDef(const QScriptValue &value)
{
    QObject *obj = value.toQObject();
    QFixtureDef *fix = dynamic_cast<QFixtureDef*>(obj);

    if (fix)
        addFixtureDef(fix);
}
