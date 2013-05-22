#include "qbodydef.h"
#include <QPen>
#include <QBrush>

QBodyDef::QBodyDef(QObject *parent)
    : QObject(parent)
    , wasSaved_(false)
    , isSelected_(false)
{
}

void QBodyDef::createFixture(const QFixtureDef *fix)
{
    QFixtureDef *copy = new QFixtureDef();
    copy->fixtureDef_ = fix->fixtureDef_;
    copy->fixtureDef_.shape = nullptr;
    copy->setShape(fix->getShape());
    copy->owner_ = this;

    fixtureList_.append(copy);
    qObjectFixtureList_.append(copy);

    // signal propagation
    connect(copy, &QFixtureDef::fixtureChanged, this, &QBodyDef::fixtureChanged,
            Qt::QueuedConnection);

    emit bodyChanged(this);
}

const QLinkedList<QFixtureDef*>& QBodyDef::getFixtureList() const
{
    return fixtureList_;
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

QBodyDef* QBodyDef::clone() const
{
    QBodyDef *clone = new QBodyDef;
    clone->bodyDef_ = this->bodyDef_;
    foreach (const QFixtureDef *fix, fixtureList_)
        clone->createFixture(fix);

    return clone;
}

// slot
void QBodyDef::createFixture(const QScriptValue &fixtureDef)
{
    QObject *obj = fixtureDef.toQObject();
    QFixtureDef *fix = dynamic_cast<QFixtureDef*>(obj);

    if (fix != nullptr)
        createFixture(fix);
}

