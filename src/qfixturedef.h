#ifndef QFIXTUREDEF_H
#define QFIXTUREDEF_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <QGraphicsItem>

class QFixtureDef : public QObject
{
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
    virtual ~QFixtureDef();

    const b2FixtureDef* getb2FixtureDef() const { return &fixtureDef_; }
    
    const b2Shape*  getShape() const { return fixtureDef_.shape; }
    //void setShape( const b2Shape*  value ) { fixtureDef_.shape = value; }
    // TODO: for now we handle only polygon and circle
    void setShape( const b2Shape*  value );

    // for now is unused property maybe in future ;)
    // void* getUserData() const { return fixtureDef_.userData; }
    // void setUserData( void* value ) { fixtureDef_.userData = value; }

    float32 getFriction() const { return fixtureDef_.friction; }
    void setFriction( float32 value ) { fixtureDef_.friction = value; emit fixtureChanged(this); }

    float32 getRestitution() const { return fixtureDef_.restitution; }
    void setRestitution( float32 value ) { fixtureDef_.restitution = value; emit fixtureChanged(this); }

    float32 getDensity() const { return fixtureDef_.density; }
    void setDensity( float32 value ) { fixtureDef_.density = value; emit fixtureChanged(this); }

    bool getIsSensor() const { return fixtureDef_.isSensor; }
    void setIsSensor( bool value ) { fixtureDef_.isSensor = value; emit fixtureChanged(this); }

    // b2Filter getFilter() const { return fixtureDef_.filter; }
    // void setFilter( b2Filter value ) { fixtureDef_.filter = value; }

signals:
    void fixtureChanged(const QFixtureDef*);

public slots:
    void setAsBox(qreal width, qreal height);
    void setAsCircle(qreal radious);

private:
    b2FixtureDef fixtureDef_;

    friend class QBodyDef;
};

#endif // QFIXTUREDEF_H
