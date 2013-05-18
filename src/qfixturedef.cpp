#include "qfixturedef.h"

QFixtureDef::QFixtureDef(QObject *parent)
    : QObject(parent)
    , owner_(nullptr)
{
}

QFixtureDef::~QFixtureDef()
{
    if (fixtureDef_.shape)
        delete fixtureDef_.shape;
}

void QFixtureDef::setShape(const b2Shape *value)
{
    switch (value->GetType())
    {
        case b2Shape::e_polygon:
        {
            const b2PolygonShape *b2Poly = static_cast<const b2PolygonShape*>(value);
            if (b2Poly) fixtureDef_.shape = new b2PolygonShape(*b2Poly);
            emit fixtureChanged(this);

        } break;

        case b2Shape::e_circle:
        {
            const b2CircleShape *b2Circle = static_cast<const b2CircleShape*>(value);
            if (b2Circle) fixtureDef_.shape = new b2CircleShape(*b2Circle);
            emit fixtureChanged(this);

        } break;

        default:
            break;
    }
}

void QFixtureDef::setAsBox(qreal width, qreal height)
{
    b2PolygonShape shape;
    shape.SetAsBox(width, height);

    setShape(&shape);
}

void QFixtureDef::setAsCircle(qreal radious)
{
    b2CircleShape shape;
    shape.m_radius = radious;

    setShape(&shape);
}
