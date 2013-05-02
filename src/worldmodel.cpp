#include "worldmodel.h"

WorldModel::WorldModel(QObject *parent) :
    QObject(parent)
{
}

QLinkedList<WorldModel::SpQBodyDef> WorldModel::getBodyList() const
{
    return bodyList_;
}

void WorldModel::addBody(const QBodyDef *bodyDef)
{
    bodyList_.append(SpQBodyDef(bodyDef));
    emit bodyAdded(bodyDef);
}

void WorldModel::addBody(const QScriptValue &value)
{
    QObject *obj = value.toQObject();
    QBodyDef *body = dynamic_cast<QBodyDef*>(obj);

    if (body)
        addBody(body);
}
