#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include "worldmodel.h"
#include <QObject>

class QBodyDef;

class WorldView;
Q_DECLARE_INTERFACE(WorldView, "dge.WorldView/1.0")

/*!
 * \brief Interface for classes that want observe WorldModel.
 *        Look at stage class for example.
 */
class WorldView
{
public slots:
    virtual void bodyAdded(const QBodyDef*) = 0;
    virtual void bodyRemoved(const QBodyDef*) = 0;

    virtual void simulationStart() = 0;
    virtual void simulationStop() = 0;

public:
    static void connectToModel(QObject *view, const WorldModel *model)
    {
        WorldView *worldView = qobject_cast<WorldView*>(view);
        if (worldView)
        {
            QObject::connect(model, SIGNAL(bodyAdded(const QBodyDef*)),
                             view,  SLOT(bodyAdded(const QBodyDef*)));

            QObject::connect(model, SIGNAL(bodyRemoved(const QBodyDef*)),
                             view,  SLOT(bodyRemoved(const QBodyDef*)));

            QObject::connect(model, SIGNAL(simulationStart()),
                             view,  SLOT(simulationStart()));

            QObject::connect(model, SIGNAL(simulationStop()),
                             view,  SLOT(simulationStop()));
        }
    }

};


#endif // WORLDVIEW_H
