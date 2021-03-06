#ifndef STAGE_H
#define STAGE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QHash>
#include <QSet>
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

    /*!
     * \brief getBodiesAt
     * \param area
     * \return
     */
    QList<const QBodyDef*> getBodiesAt(QRectF area) const;

signals:
    void mouseEvent(QGraphicsSceneMouseEvent*);
    void keyEvent(QKeyEvent*);

public slots:
    void bodyAdded(const QBodyDef *);
    void bodyRemoved(const QBodyDef *);
    void simulationStart();
    void simulationStop();

    void bodyChanged(const QBodyDef *);
    void fixtureChanged(const QFixtureDef*);

    void setSelection(QRectF area);
    void setSelection(qreal x1, qreal y1, qreal width, qreal height);
    void clearSelection();

    void zoomIn();
    void zoomOut();
    void resetZoom();

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
    QGraphicsRectItem selectionArea_;
    QHash<const QFixtureDef*, QGraphicsItem*> qGraphicsItemsMap_;
    QHash<b2BodyType, QColor> bodyColor_;
    QHash<const QBodyDef*, QGraphicsRectItem*> aabb_;
    QSet<const QBodyDef*> bodiesOnStage_;

};

#endif // STAGE_H
