#include "qfixturedef.h"
#include <QPointF>

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

int QFixtureDef::getShapeType() const
{
    return fixtureDef_.shape->GetType();
}

QVariantList QFixtureDef::getShapeData() const
{
    QVariantList data;

    switch(fixtureDef_.shape->GetType())
    {
        case b2Shape::e_polygon: {
            const b2PolygonShape *b2Poly = static_cast<const b2PolygonShape*>(fixtureDef_.shape);

            for (int i = 0; i < b2Poly->GetVertexCount(); ++i)
            {
                const b2Vec2 &v = b2Poly->GetVertex(i);
                data.push_back(QVariant(v.x));
                data.push_back(QVariant(v.y));
            }
        } break;

        case b2Shape::e_circle: {
            const b2CircleShape *b2Circle = static_cast<const b2CircleShape*>(fixtureDef_.shape);

            data.push_back(b2Circle->m_p.x);
            data.push_back(b2Circle->m_p.y);
            data.push_back(b2Circle->m_radius);

        } break;

        default:
          break;
    }

    return data;
}

void QFixtureDef::setShape(const b2Shape *value)
{
    switch (value->GetType())
    {
        case b2Shape::e_polygon:
        {
            const b2PolygonShape *b2Poly = static_cast<const b2PolygonShape*>(value);
            if (b2Poly)
            {
                if (fixtureDef_.shape)
                    delete fixtureDef_.shape;
                fixtureDef_.shape = new b2PolygonShape(*b2Poly);
            }
            emit fixtureChanged(this);

        } break;

        case b2Shape::e_circle:
        {
            const b2CircleShape *b2Circle = static_cast<const b2CircleShape*>(value);
            if (b2Circle)
            {
                if (fixtureDef_.shape)
                    delete fixtureDef_.shape;
                fixtureDef_.shape = new b2CircleShape(*b2Circle);
            }
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
