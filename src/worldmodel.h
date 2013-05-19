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

    bool isRunning() const;

signals:
    void updateBody(QBodyDef*, b2Body*);

public slots:
    void run();
    void stop();

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
    explicit WorldModel(QObject *parent = 0);
    virtual ~WorldModel();

    void removeBody(QBodyDef*);
    // QLinkedList<QBodyDef*> getBodyList() const;

    /*!
     * \brief createBody
     * \return
     */
    QBodyDef* createBody(const QFixtureDef*);
    QBodyDef* createBody();

    /*!
     * \brief clone body given
     */
    QBodyDef* createBody(const QBodyDef*);

    /*!
     * \brief true if physic simulation is running
     */
    bool isSimulationRunning() const;

signals:
    void bodyAdded(const QBodyDef*);
    void bodyRemoved(const QBodyDef*);

    void simulationStart();
    void simulationStop();
    
public slots:

    /*!
     * \brief removeBody
     * \param body
     */
    void removeBody(const QScriptValue& body);

    /*!
     * \brief start simulation of the world
     * \param fps frames per second
     * \param worldStep the time between world step
     */

    void run(qint32 fps = 30, qreal worldStep = 1.0/30.0f);

    /*!
     * \brief stop simulation
     */
    void stop();

private:
    /// Create b2World from body list
    void createWorld();

    b2World *world_;
    QLinkedList<QBodyDef*> bodyList_;
    QThread simulationThread_;
    WorldSimulation simulation_;
};


#endif // WORLDMODEL_H
