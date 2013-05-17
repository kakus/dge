#include "stage.h"
#include "ui_stage.h"
#include "qbodydef.h"
#include "qfixturedef.h"
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>

Stage::Stage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stage)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(ui->graphicsView);
    scene_->setBackgroundBrush(QBrush(QColor(32, 32, 32)));
    ui->graphicsView->setScene(scene_);

    scene_->installEventFilter(this);

    bodyColor_[b2BodyType::b2_staticBody] = QColor(0, 255, 0);
    bodyColor_[b2BodyType::b2_kinematicBody] = QColor(0, 0, 255);
    bodyColor_[b2BodyType::b2_dynamicBody] = QColor(255, 255, 160);
}

Stage::~Stage()
{
    delete ui;
}

void Stage::bodyAdded(const QBodyDef *qbody)
{
    updateFixtures(qbody);
    connect(qbody, &QBodyDef::bodyChanged,
            this, &Stage::bodyChanged,
            Qt::QueuedConnection);
}

void Stage::bodyRemoved(const QBodyDef *qbody)
{
    foreach (const QFixtureDef *fixture, *qbody->getFixtureList())
        scene_->removeItem(qGraphicsItemsMap_[fixture]);

    disconnect(qbody, &QBodyDef::bodyChanged, this, &Stage::bodyChanged);
}

void Stage::bodyChanged(const QBodyDef *qbody)
{
    updateFixtures(qbody);
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
        graphicsItem = new QGraphicsEllipseItem(b2Circle->m_p.x,
                                                 b2Circle->m_p.y,
                                                 b2Circle->m_radius,
                                                 b2Circle->m_radius);
    } break;

    default:
        break;
    }

    return graphicsItem;
}

void Stage::updateFixtures(const QBodyDef *qbody)
{
    static const qreal PI = 3.1415926535;

    foreach (const QFixtureDef *fixture, *qbody->getFixtureList())
    {
        QGraphicsItem* graphics = nullptr;
        // if fixture doesn't have corespondig graphics item we need to create it
        // and add to the stage
        if (qGraphicsItemsMap_.find(fixture) == qGraphicsItemsMap_.end())
        {
            QGraphicsItem* graphics = createQGraphicsItemFromb2Shape(fixture->getShape());
            qGraphicsItemsMap_[fixture] = graphics;
            scene_->addItem(graphics);
        }

        // now we can update posiotion and rotation
        if (graphics == nullptr) graphics = qGraphicsItemsMap_[fixture];
        // update position
        graphics->setPos(qbody->getPosition().x, qbody->getPosition().y);
        // update rotation
        graphics->setRotation(qbody->getAngle()*180/PI);

        // the last thing to update is the colors of the fixtures
        // we must check if body type was changed and if update color
        QAbstractGraphicsShapeItem *shape =
                dynamic_cast<QAbstractGraphicsShapeItem*>(graphics);

        if (shape->pen().color() != bodyColor_[qbody->getType()])
        {
            QColor brushColor = bodyColor_[qbody->getType()];
            brushColor.setAlphaF(0.5);

            shape->setPen(bodyColor_[qbody->getType()]);
            shape->setBrush(brushColor);
        }
    }
}
