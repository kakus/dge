#include "stage.h"
#include "ui_stage.h"
#include "qbodydef.h"
#include "qfixturedef.h"
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>
#include <QPen>
#include <QBrush>

Stage::Stage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stage)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(ui->graphicsView);
    scene_->setBackgroundBrush(QBrush(QColor(32, 32, 32)));
    // todo remove magick numbers and add control of stage size
    scene_->setSceneRect(-400, -400, 800, 800);
    ui->graphicsView->setScene(scene_);

    scene_->installEventFilter(this);

    // area selection
    selectionArea_.setVisible(false);
    QColor highlight = QApplication::palette().highlight().color();
    QPen pen(QBrush(highlight), 2, Qt::DotLine);
    selectionArea_.setPen(pen);
    highlight.setAlphaF(0.3);
    selectionArea_.setBrush(highlight);
    scene_->addItem(&selectionArea_);

    // here are mappings : object_type -> color
    bodyColor_[b2BodyType::b2_staticBody] = QColor(0, 255, 0);
    bodyColor_[b2BodyType::b2_kinematicBody] = QColor(0, 0, 255);
    bodyColor_[b2BodyType::b2_dynamicBody] = QColor(255, 255, 160);
}

Stage::~Stage()
{
    delete ui;
}

const QBodyDef* Stage::bodyAt(qreal x, qreal y) const
{
    QGraphicsItem* item = scene_->itemAt(x, y, ui->graphicsView->transform());

    if (item == nullptr)
        return nullptr;

    const QFixtureDef* fixture = qGraphicsItemsMap_.key(item);
    if (fixture)
        return fixture->getOwner();
    else
        return nullptr;
}

QList<const QBodyDef*> Stage::getBodiesAt(QRectF area) const
{
    QList<const QBodyDef*> bodies;
    foreach (QGraphicsItem* item, scene_->items(area))
    {
        if (qGraphicsItemsMap_.key(item) != nullptr)
            bodies.push_back(qGraphicsItemsMap_.key(item)->getOwner());
    }
    return bodies;
}

void Stage::bodyAdded(const QBodyDef *qbody)
{
    updateFixtures(qbody);

    connect(qbody, &QBodyDef::bodyChanged, this, &Stage::bodyChanged,
            Qt::QueuedConnection);

    connect(qbody, &QBodyDef::fixtureChanged, this, &Stage::fixtureChanged,
            Qt::QueuedConnection);
}

void Stage::bodyRemoved(const QBodyDef *qbody)
{
    foreach (const QFixtureDef *fixture, qbody->getFixtureList())
    {
        disconnect(qbody, &QBodyDef::fixtureChanged, this, &Stage::fixtureChanged);
        scene_->removeItem(qGraphicsItemsMap_[fixture]);
    }

    disconnect(qbody, &QBodyDef::bodyChanged, this, &Stage::bodyChanged);
}

void Stage::simulationStart()
{
    ui->graphicsView->setEnabled(false);
}

void Stage::simulationStop()
{
    ui->graphicsView->setEnabled(true);
}

void Stage::bodyChanged(const QBodyDef *qbody)
{
    updateFixtures(qbody);
}

void Stage::fixtureChanged(const QFixtureDef *qfixture)
{
    // we need to remove old fixture from stage and call updateFixtures
    if (qGraphicsItemsMap_.contains(qfixture))
    {
           scene_->removeItem(qGraphicsItemsMap_[qfixture]);
           delete qGraphicsItemsMap_[qfixture];
           // we also delete fixture from map, because if updateFixtures doesn't
           // find it, it will create new graphics which is what we want.:
           qGraphicsItemsMap_.remove(qfixture);
           updateFixtures(qfixture->getOwner());
    }
}

void Stage::setSelection(QRectF area)
{
    selectionArea_.setRect(area);
    selectionArea_.setVisible(true);
}

void Stage::setSelection(qreal x1, qreal y1, qreal width, qreal height)
{
    setSelection(QRectF(x1, y1, width, height));
}

void Stage::clearSelection()
{
    selectionArea_.setVisible(false);
}


void Stage::zoomIn()
{
    ui->graphicsView->scale(2, 2);
}

void Stage::zoomOut()
{
    ui->graphicsView->scale(0.5, 0.5);
}

void Stage::resetZoom()
{
    ui->graphicsView->setTransform(QTransform());
}

bool Stage::eventFilter(QObject *obj, QEvent *evt)
{
    if (obj != scene_) return false;

    switch (evt->type()) {
    case QEvent::GraphicsSceneMousePress:
    case QEvent::GraphicsSceneMouseRelease:
    case QEvent::GraphicsSceneMouseMove:
        emit mouseEvent(dynamic_cast<QGraphicsSceneMouseEvent*>(evt));
        break;

    case QEvent::KeyPress:
    case QEvent::KeyRelease:
        emit keyEvent(dynamic_cast<QKeyEvent*>(evt));
    default:
        break;
    }

    return false;
}

// help function in updateFixtures method
QGraphicsItem* createQGraphicsItemFromb2Shape(const b2Shape *shape)
{
    QGraphicsItem *graphicsItem = nullptr;

    switch (shape->GetType())
    {
    case b2Shape::e_polygon:
    {
        const b2PolygonShape *b2Poly = static_cast<const b2PolygonShape*>(shape);
        int i = b2Poly->GetVertexCount() - 1;

        QPolygonF qtPoly;

        for (; i >= 0 ; --i)
        {
            qtPoly << QPointF( b2Poly->GetVertex(i).x,
                               b2Poly->GetVertex(i).y );

        }

        graphicsItem = new QGraphicsPolygonItem(qtPoly);
    } break;

    case b2Shape::e_circle:
    {
        const b2CircleShape *b2Circle = static_cast<const b2CircleShape*>(shape);
        QGraphicsItem* elipse = new QGraphicsEllipseItem(b2Circle->m_p.x - b2Circle->m_radius,
                                                 b2Circle->m_p.y - b2Circle->m_radius,
                                                 b2Circle->m_radius * 2,
                                                 b2Circle->m_radius * 2);
        QGraphicsItem* radious = new QGraphicsLineItem(
                    b2Circle->m_p.x, b2Circle->m_p.y,
                    b2Circle->m_p.x + b2Circle->m_radius, b2Circle->m_p.y
        );

        radious->setParentItem(elipse);
        graphicsItem = elipse;
    } break;

    default:
        break;
    }

    return graphicsItem;
}

// resizes the item aabb so there will be no overlapping
QRectF getAABB(const QGraphicsItem* item)
{
    QRectF aabb(item->sceneBoundingRect());
    aabb.setWidth(aabb.width() + 2);
    aabb.setHeight(aabb.height() + 2);
    aabb.setLeft(aabb.left()-1);
    aabb.setTop(aabb.top()-1);
    return aabb;
}

void Stage::updateFixtures(const QBodyDef *qbody)
{
    static const qreal PI = 3.1415926535;

    foreach (const QFixtureDef *fixture, qbody->getFixtureList())
    {
        QGraphicsItem* graphics = nullptr;
        // if fixture doesn't have corespondig graphics item we need to create it
        // and add to the stage
        if (qGraphicsItemsMap_.contains(fixture) == false)
        {
            graphics = createQGraphicsItemFromb2Shape(fixture->getShape());
            qGraphicsItemsMap_[fixture] = graphics;
            scene_->addItem(graphics);
        }

        // now we can update posiotion and rotation
        // todo in future we should replace this with a transform matrix
        // because this is only will be working when just one fixture is attached
        // to the body
        if (graphics == nullptr) graphics = qGraphicsItemsMap_[fixture];
        // update position
        graphics->setPos(qbody->getPosition().x, qbody->getPosition().y);
        // update rotation
        graphics->setRotation(qbody->getAngle()*180/PI);

        // the last thing to update is the colors of the fixtures
        QAbstractGraphicsShapeItem *shape = dynamic_cast<QAbstractGraphicsShapeItem*>(graphics);
        if (shape)
        {
            BodyColor color = getBodyColor(qbody);
            shape->setPen(color.first);
            shape->setBrush(color.second);

            foreach (QGraphicsItem *item, graphics->childItems())
            {
                QGraphicsLineItem *line = dynamic_cast<QGraphicsLineItem*>(item);
                if (line != nullptr)
                    line->setPen(color.first);
            }

            // update aabb of selected items
            if (qbody->isSelected() && !aabb_.contains(qbody))
            {
                QGraphicsRectItem *aabb = new QGraphicsRectItem(getAABB(shape));
                aabb->setPen(QPen(QApplication::palette().midlight(), 1, Qt::DashLine));
                aabb->setZValue(-100);
                scene_->addItem(aabb);
                aabb_[qbody] = aabb;
            }
            else if(qbody->isSelected() && aabb_.contains(qbody))
            {
                aabb_[qbody]->setRect(getAABB(shape));
            }
            else if (!qbody->isSelected() && aabb_.contains(qbody))
            {
                scene_->removeItem(aabb_[qbody]);
                delete aabb_[qbody];
                aabb_.remove(qbody);
            }
        }
    }
}

Stage::BodyColor Stage::getBodyColor(const QBodyDef *qbody)
{
    QColor color = bodyColor_[qbody->getType()];
    QPen pen = color;
    color.setAlphaF(0.5);
    QBrush brush = color;

    if (qbody->isSelected())
        brush.setStyle(Qt::FDiagPattern);
    else
        brush.setStyle(Qt::SolidPattern);

    return BodyColor(pen, brush);
}
