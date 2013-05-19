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

    /*!
     * \brief  Returns the topmost visible body at the specified position,
     *         or null if there are no bodies at this position.
     */
    const QBodyDef* bodyAt(qreal x, qreal y) const;

signals:
    void mouseEvent(QGraphicsSceneMouseEvent*);

public slots:
    void bodyAdded(const QBodyDef *);
    void bodyRemoved(const QBodyDef *);
    void simulationStart();
    void simulationStop();

    void bodyChanged(const QBodyDef *);
    void fixtureChanged(const QFixtureDef*);

protected:
    bool eventFilter(QObject *, QEvent *);

private:
    typedef QPair<QPen, QBrush> BodyColor;

    /// updates fixtures that are in body, that means their creation, position,
    /// rotation
    void updateFixtures(const QBodyDef*);
    BodyColor getBodyColor(const QBodyDef*);

    Ui::Stage *ui;
    QGraphicsScene *scene_;
    QMap<const QFixtureDef*, QGraphicsItem*> qGraphicsItemsMap_;
    QMap<b2BodyType, QColor> bodyColor_;
};

#endif // STAGE_H
