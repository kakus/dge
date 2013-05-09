#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <QObject>
#include <QLinkedList>
#include <QSharedPointer>
#include <QScriptValue>
#include <QThread>

#include "qbodydef.h"

class WorldModel;

/*!
 * \brief The WorldSimulation class
 *  This class suppose to run in its own thread, and perform box2d world simulation
 */
class WorldSimulation: public QObject
{
    Q_OBJECT

public:
    explicit WorldSimulation ();
    void setSimulation (
            b2World* world,
            qint32 fps = 30,
            qreal worldStep = 1.0/60.0
    );

public slots:
    void run();

private slots:
    void step();

private:
    b2World *world_;
    QTimer  *timer_;
    qint32  fps_;
    qreal   worldStep_;
};

/*!
 * \brief The WorldModel class
 */
class WorldModel : public QObject
{

    Q_OBJECT
public:
    typedef QSharedPointer<QBodyDef> SpQBodyDef;

    explicit WorldModel(QObject *parent = 0);

    void addBody(QBodyDef*);
    QLinkedList<SpQBodyDef> getBodyList() const;

signals:
    void bodyAdded(const QBodyDef*);
    void bodyRemoved(const QBodyDef*);
    
public slots:
    void addBody(const QScriptValue&);
    /*!
     * \brief start simulation of the world
     * \param fps frames per second
     * \param worldStep the time between world step
     */
    void run(qint32 fps = 30, qreal worldStep = 1.0/60.0f);
    /*!
     * \brief stop
     */
    void stop();

private:
    /*!
     * Create b2World from body list
     */
    void createWorld();
    /// after simulation graphics items are synchronized with b2World rather
    /// than with model, so this function change it.
    void syncGraphicsWithModel();

    b2World *world_;
    QLinkedList<SpQBodyDef> bodyList_;
    QThread simulationThread_;
    WorldSimulation simulation_;
};


#endif // WORLDMODEL_H
