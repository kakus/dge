#ifndef QFIXTUREDEF_H
#define QFIXTUREDEF_H

#include <QObject>
#include <QVariant>
#include <Box2D/Box2D.h>

class QBodyDef;

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

    /*!
     * \brief getOwner
     * \return return qbodydef which this fixture is attached to.
     */
    const QBodyDef* getOwner() const { return owner_; }

    /// function that can be accesed from qscript
    /// and are well defined in script api doc.
    Q_INVOKABLE int getShapeType() const;
    Q_INVOKABLE QVariantList getShapeData() const;
    
    const b2Shape*  getShape() const;
    // TODO: for now we handle only polygon and circle
    void setShape( const b2Shape*  value );

    void* getUserData() const;
    void setUserData( void* value );

    float32 getFriction() const;
    void setFriction( float32 value );

    float32 getRestitution() const;
    void setRestitution( float32 value );

    float32 getDensity() const;
    void setDensity( float32 value );

    bool getIsSensor() const;
    void setIsSensor( bool value );

    // TODO b2Filter
    // b2Filter getFilter() const;
    // void setFilter( b2Filter value );


signals:
    void fixtureChanged(const QFixtureDef*);

public slots:
    void setAsBox(qreal width, qreal height);
    void setAsCircle(qreal radious);
    void setAsPolygon(const QVariantList &vertex);

private:
    b2FixtureDef fixtureDef_;
    const QBodyDef *owner_;

    friend class QBodyDef;
    // for building b2World
    friend class WorldModel;
    // for copy constructor
    friend class Controller;
};

inline const b2Shape*  QFixtureDef::getShape() const {
    return fixtureDef_.shape;
}
// set shape in cpp file

inline void* QFixtureDef::getUserData() const {
    return fixtureDef_.userData;
}
inline void QFixtureDef::setUserData( void* value ) {
    fixtureDef_.userData = value;
    emit fixtureChanged(this);
}

inline float32 QFixtureDef::getFriction() const {
    return fixtureDef_.friction;
}
inline void QFixtureDef::setFriction( float32 value ) {
    fixtureDef_.friction = value;
    emit fixtureChanged(this);
}

inline float32 QFixtureDef::getRestitution() const {
    return fixtureDef_.restitution;
}
inline void QFixtureDef::setRestitution( float32 value ) {
    fixtureDef_.restitution = value;
    emit fixtureChanged(this);
}

inline float32 QFixtureDef::getDensity() const {
    return fixtureDef_.density;
}
inline void QFixtureDef::setDensity( float32 value ) {
    fixtureDef_.density = value;
    emit fixtureChanged(this);
}

inline bool QFixtureDef::getIsSensor() const {
    return fixtureDef_.isSensor;
}
inline void QFixtureDef::setIsSensor( bool value ) {
    fixtureDef_.isSensor = value;
    emit fixtureChanged(this);
}

// inline b2Filter QFixtureDef::getFilter() const {
//     return fixtureDef_.filter;
// }
// inline void QFixtureDef::setFilter( b2Filter value ) {
//     fixtureDef_.filter = value;
//     emit fixtureChanged(this);
// }


#endif // QFIXTUREDEF_H
