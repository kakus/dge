#include "qbodydef.h"
#include <QPen>
#include <QBrush>

QBodyDef::QBodyDef(QObject *parent)
    : QObject(parent)
    , wasSaved_(false)
{
}

void QBodyDef::createFixture(const QFixtureDef *fix)
{
    QFixtureDef *copy = new QFixtureDef();
    copy->fixtureDef_ = fix->fixtureDef_;
    copy->setShape(fix->getShape());
    copy->owner_ = this;

    fixtureList_.append(copy);
    qObjectFixtureList_.append(copy);

    // signal propagation
    connect(copy, &QFixtureDef::fixtureChanged, this, &QBodyDef::fixtureChanged,
            Qt::QueuedConnection);

    emit bodyChanged(this);
}

const QLinkedList<QFixtureDef*>* QBodyDef::getFixtureList() const
{
    return &fixtureList_;
}

void QBodyDef::save()
{
    wasSaved_ = true;
    saveState_ = bodyDef_;
}

void QBodyDef::restore()
{
    if (wasSaved_)
        bodyDef_ = saveState_;

    emit bodyChanged(this);
}

// slot
void QBodyDef::createFixture(const QScriptValue &fixtureDef)
{
    QObject *obj = fixtureDef.toQObject();
    QFixtureDef *fix = dynamic_cast<QFixtureDef*>(obj);

    if (fix != nullptr)
        createFixture(fix);
}
