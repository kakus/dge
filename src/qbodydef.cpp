#include "qbodydef.h"
#include <QPen>
#include <QBrush>

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
    static const qreal PI = 3.1415926535;
    foreach(const SpQFixtureDef &fixture, fixtureList_ )
    {
        fixture->graphicsItem_->setPos(bodyDef_.position.x,
                                       bodyDef_.position.y);
        fixture->graphicsItem_->setRotation(bodyDef_.angle*180/PI);

        switch (fixture->graphicsItem_->type())
        {
        case QGraphicsPolygonItem::Type: {
            QGraphicsPolygonItem *item =
                    static_cast<QGraphicsPolygonItem*>(fixture->graphicsItem_);

            if (bodyDef_.type == b2BodyType::b2_staticBody)
            {
                item->setBrush(QBrush(QColor(0, 255, 0, 64)));
                item->setPen(QPen(QColor(0, 255, 0)));
            }
            else if (bodyDef_.type == b2BodyType::b2_dynamicBody)
            {
                item->setBrush(QBrush(QColor(255, 255, 150, 64)));
                item->setPen(QPen(QColor(255, 255, 150)));
            }
        } break;
        }
    }
}
