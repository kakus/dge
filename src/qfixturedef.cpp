#include "qfixturedef.h"
#include <QPointF>
#include <QPolygonF>
#include <QGraphicsPolygonItem>

QFixtureDef::QFixtureDef(QObject *parent) :
    QObject(parent)
{
}

void QFixtureDef::setShape(const b2Shape *value)
{
    switch (value->GetType())
    {
    case b2Shape::e_polygon:
    {
        const b2PolygonShape *b2Poly = static_cast<const b2PolygonShape*>(value);
        int i = b2Poly->GetVertexCount() - 1;

        QPolygonF qtPoly;

        for (; i >= 0 ; --i)
        {
            qtPoly << QPointF( b2Poly->GetVertex(i).x,
                               b2Poly->GetVertex(i).y );

        }

        graphicsItem_ = SpQGraphicsItem(new QGraphicsPolygonItem(qtPoly));
    } break;

    case b2Shape::e_circle:
        break;

    }

    fixtureDef_.shape = value;
}

void QFixtureDef::setAsBox(qreal width, qreal height)
{
    b2PolygonShape shape;
    shape.SetAsBox(width, height);

    setShape(&shape);
}
