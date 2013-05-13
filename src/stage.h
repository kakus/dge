#ifndef STAGE_H
#define STAGE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMap>
#include "worldview.h"

class QBodyDef;

namespace Ui {
class Stage;
}

/*!
 * \brief The Stage Widget - Display bodies and other box2d stuff.
 * \author Kamil Misiowiec
 */
class Stage : public QWidget, public WorldView
{
    Q_OBJECT
    Q_INTERFACES(WorldView)
    
public:
    explicit Stage(QWidget *parent = 0);
    ~Stage();

signals:
    void mouseEvent(QGraphicsSceneMouseEvent*);

public slots:
    void bodyAdded(const QBodyDef *);
    void bodyRemoved(const QBodyDef *);
    void bodyChanged(const QBodyDef *);

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::Stage *ui;
    QGraphicsScene *scene_;
    QMap<const QBodyDef*, QGraphicsItem*> bodyMap_;
};

#endif // STAGE_H
