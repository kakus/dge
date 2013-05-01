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
