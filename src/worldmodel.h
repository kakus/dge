#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QObject>
#include <QLinkedList>
#include <QSharedPointer>
#include "qbodydef.h"

class WorldModel : public QObject
{

    Q_OBJECT
public:
    typedef QSharedPointer<const QBodyDef> SpQBodyDef;

    explicit WorldModel(QObject *parent = 0);

    QLinkedList<SpQBodyDef> getBodyList() const;
    
signals:
    void bodyAdded(const QBodyDef*);
    void bodyRemoved(const QBodyDef*);
    
public slots:
    void addBody(const QBodyDef*);

private:
    QLinkedList<SpQBodyDef> bodyList_;
};

#endif // WORLDMODEL_H
