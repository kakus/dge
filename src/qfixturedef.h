#ifndef QFIXTUREDEF_H
#define QFIXTUREDEF_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QGraphicsItem>
#include <QSharedPointer>

class QFixtureDef : public QObject
{
    typedef QSharedPointer<QGraphicsItem> SpQGraphicsItem;

    Q_OBJECT

    // TODO high priority
    //Q_PROPERTY(const b2Shape*  shape READ getShape WRITE setShape )
    //Q_PROPERTY(void* userData READ getUserData WRITE setUserData )
    Q_PROPERTY(qreal friction READ getFriction WRITE setFriction )
    Q_PROPERTY(qreal restitution READ getRestitution WRITE setRestitution )
    Q_PROPERTY(qreal density READ getDensity WRITE setDensity )
    Q_PROPERTY(bool isSensor READ getIsSensor WRITE setIsSensor )
    // TODO: for now too low priority
    //Q_PROPERTY(b2Filter filter READ getFilter WRITE setFilter )

public:
    explicit QFixtureDef(QObject *parent = 0);

    QGraphicsItem* getGraphicsItem() const {
        return graphicsItem_.data();
    }
    
    const b2Shape*  getShape() const { return fixtureDef_.shape; }
    //void setShape( const b2Shape*  value ) { fixtureDef_.shape = value; }
    // TODO: for now we handle only polygon and circle
    void setShape( const b2Shape*  value );

    // for now is unused property maybe in future ;)
    // void* getUserData() const { return fixtureDef_.userData; }
    // void setUserData( void* value ) { fixtureDef_.userData = value; }

    qreal getFriction() const { return fixtureDef_.friction; }
    void setFriction( qreal value ) { fixtureDef_.friction = value; }

    qreal getRestitution() const { return fixtureDef_.restitution; }
    void setRestitution( qreal value ) { fixtureDef_.restitution = value; }

    qreal getDensity() const { return fixtureDef_.density; }
    void setDensity( qreal value ) { fixtureDef_.density = value; }

    bool getIsSensor() const { return fixtureDef_.isSensor; }
    void setIsSensor( bool value ) { fixtureDef_.isSensor = value; }

    // b2Filter getFilter() const { return fixtureDef_.filter; }
    // void setFilter( b2Filter value ) { fixtureDef_.filter = value; }

public slots:

private:
    b2FixtureDef fixtureDef_;
    SpQGraphicsItem graphicsItem_;

    friend class QBodyDef;
};

#endif // QFIXTUREDEF_H
