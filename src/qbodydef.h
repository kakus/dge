#ifndef QBODYDEF_H
#define QBODYDEF_H

#include <Box2D/Box2D.h>
#include <QObject>
#include <QSharedPointer>
#include <QLinkedList>
#include <QScriptValue>
#include "qfixturedef.h"


class QBodyDef : public QObject
{

    Q_OBJECT

    // TODO
    //Q_PROPERTY(b2BodyType type READ getType WRITE setType )
    // TODO
    //Q_PROPERTY(b2Vec2 position READ getPosition WRITE setPosition )
    Q_PROPERTY(qreal angle READ getAngle WRITE setAngle )
    // TODO
    //Q_PROPERTY(b2Vec2 linearVelocity READ getLinearVelocity WRITE setLinearVelocity )
    Q_PROPERTY(qreal angularVelocity READ getAngularVelocity WRITE setAngularVelocity )
    Q_PROPERTY(qreal linearDamping READ getLinearDamping WRITE setLinearDamping )
    Q_PROPERTY(qreal angularDamping READ getAngularDamping WRITE setAngularDamping )
    Q_PROPERTY(bool allowSleep READ getAllowSleep WRITE setAllowSleep )
    Q_PROPERTY(bool awake READ getAwake WRITE setAwake )
    Q_PROPERTY(bool fixedRotation READ getFixedRotation WRITE setFixedRotation )
    Q_PROPERTY(bool bullet READ getBullet WRITE setBullet )
    Q_PROPERTY(bool active READ getActive WRITE setActive )
    // currently not avaliable through script engine
    //Q_PROPERTY(void* userData READ getUserData WRITE setUserData )
    Q_PROPERTY(qreal gravityScale READ getGravityScale WRITE setGravityScale )

public:
    typedef QSharedPointer<const QFixtureDef> SpQFixtureDef;

    explicit QBodyDef(QObject *parent = 0);

    void addFixtureDef(const QFixtureDef* );
    const QLinkedList<SpQFixtureDef>* getFixtureList() const;

    // auto generated code
    b2BodyType getType() const { return bodyDef_.type; }
    void setType( b2BodyType value ) { bodyDef_.type = value; }

    b2Vec2 getPosition() const { return bodyDef_.position; }
    void setPosition( b2Vec2 value ) { bodyDef_.position = value; }

    qreal getAngle() const { return bodyDef_.angle; }
    void setAngle( qreal value ) { bodyDef_.angle = value; }

    b2Vec2 getLinearVelocity() const { return bodyDef_.linearVelocity; }
    void setLinearVelocity( b2Vec2 value ) { bodyDef_.linearVelocity = value; }

    qreal getAngularVelocity() const { return bodyDef_.angularVelocity; }
    void setAngularVelocity( qreal value ) { bodyDef_.angularVelocity = value; }

    qreal getLinearDamping() const { return bodyDef_.linearDamping; }
    void setLinearDamping( qreal value ) { bodyDef_.linearDamping = value; }

    qreal getAngularDamping() const { return bodyDef_.angularDamping; }
    void setAngularDamping( qreal value ) { bodyDef_.angularDamping = value; }

    bool getAllowSleep() const { return bodyDef_.allowSleep; }
    void setAllowSleep( bool value ) { bodyDef_.allowSleep = value; }

    bool getAwake() const { return bodyDef_.awake; }
    void setAwake( bool value ) { bodyDef_.awake = value; }

    bool getFixedRotation() const { return bodyDef_.fixedRotation; }
    void setFixedRotation( bool value ) { bodyDef_.fixedRotation = value; }

    bool getBullet() const { return bodyDef_.bullet; }
    void setBullet( bool value ) { bodyDef_.bullet = value; }

    bool getActive() const { return bodyDef_.active; }
    void setActive( bool value ) { bodyDef_.active = value; }

    void* getUserData() const { return bodyDef_.userData; }
    void setUserData( void* value ) { bodyDef_.userData = value; }

    qreal getGravityScale() const { return bodyDef_.gravityScale; }
    void setGravityScale( qreal value ) { bodyDef_.gravityScale = value; }
    // end auto generated code

signals:
    
public slots:
    void addFixtureDef(const QFixtureDef&);
    void addFixtureDef(const QScriptValue&);

private:
    b2BodyDef bodyDef_;
    QLinkedList<SpQFixtureDef> fixtureList_;
};

#endif // QBODYDEF_H
