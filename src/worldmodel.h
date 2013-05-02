#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QObject>
#include <QLinkedList>
#include <QSharedPointer>
#include <QScriptValue>
#include "qbodydef.h"

class WorldModel : public QObject
{

    Q_OBJECT
public:
    typedef QSharedPointer<const QBodyDef> SpQBodyDef;

    explicit WorldModel(QObject *parent = 0);

    void addBody(const QBodyDef*);
    QLinkedList<SpQBodyDef> getBodyList() const;

signals:
    void bodyAdded(const QBodyDef*);
    void bodyRemoved(const QBodyDef*);
    
public slots:
    void addBody(const QScriptValue&);

private:
    QLinkedList<SpQBodyDef> bodyList_;
};

#endif // WORLDMODEL_H
