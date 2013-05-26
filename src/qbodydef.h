#ifndef QBODYDEF_H
#define QBODYDEF_H


#include <QObject>
#include <QSharedPointer>
#include <QLinkedList>
#include <QScriptValue>
#include <Box2D/Box2D.h>
#include "qfixturedef.h"


/*!
 * \brief The QBodyDef class
 *        This class is a wrapper around box2d b2BodyDef class, so it can
 *        be used in qscript engine.
 */
class QBodyDef : public QObject
{
    Q_OBJECT

    //Q_PROPERTY(b2BodyType type READ getType WRITE setType )
    // replacment for b2BodyType so we dont need to translate this class to qobject
    Q_PROPERTY(bool static READ getStatic WRITE setStatic )
    Q_PROPERTY(bool dynamic READ getDynamic WRITE setDynamic )
    Q_PROPERTY(bool kinematic READ getKinematic WRITE setKinematic )

    //Q_PROPERTY(b2Vec2 position READ getPosition WRITE setPosition )
    // replacment for position so we dont need to import b2Vec2 to script engine
    Q_PROPERTY(qreal x READ getX WRITE setX)
    Q_PROPERTY(qreal y READ getY WRITE setY)

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

    // Custom property
    Q_PROPERTY(QObjectList fixtureList READ getQObjectFixtureList)
    Q_PROPERTY(bool isSelected READ isSelected WRITE setSelected)
    Q_PROPERTY(uint id READ getId)

public:

    /*!
     * \brief QBodyDef
     * \param id the id of the body, if none is given the it will be generated
     *        automaticaly
     * \param parent check out qt parent
     */
    explicit QBodyDef(uint id = 0, QObject *parent = 0);
    virtual ~QBodyDef();

    /*!
     * \brief Clone the fixture given and adds to the fixture list.
     */
    void createFixture(const QFixtureDef*);

    /*!
     * \brief getBodyDef
     * \return The body definition, so you can create this body in b2World.
     */
    const b2BodyDef* getBodyDef() const { return &bodyDef_; }

    /*!
     * \brief Save the current state of this b2BodyDef, you can restore it
     *        using restore().
     */
    void save();

    /*!
     * \brief Restore state of this b2BodyDef, to state when last save was
     *        called. If no save were called this method do nothig.
     */
    void restore();

    /*!
     * \brief clone this object and returning new one
     * \warning CLONE HAVE THE SAME ID !!!
     */
    QBodyDef* clone() const;

    const QLinkedList<QFixtureDef*>& getFixtureList() const;

    // auto generated code

    b2BodyType getType() const;
    void setType( b2BodyType value );

    bool getStatic() const;
    void setStatic( bool value );

    bool getDynamic() const;
    void setDynamic( bool value );

    bool getKinematic() const;
    void setKinematic( bool value );

    b2Vec2 getPosition() const;
    void setPosition( b2Vec2 value );

    qreal getX() const;
    void  setX(qreal value);

    qreal getY() const;
    void  setY(qreal value);

    float32 getAngle() const;
    void setAngle( float32 value );

    b2Vec2 getLinearVelocity() const;
    void setLinearVelocity( b2Vec2 value );

    float32 getAngularVelocity() const;
    void setAngularVelocity( float32 value );

    float32 getLinearDamping() const;
    void setLinearDamping( float32 value );

    float32 getAngularDamping() const;
    void setAngularDamping( float32 value );

    bool getAllowSleep() const;
    void setAllowSleep( bool value );

    bool getAwake() const;
    void setAwake( bool value );

    bool getFixedRotation() const;
    void setFixedRotation( bool value );

    bool getBullet() const;
    void setBullet( bool value );

    bool getActive() const;
    void setActive( bool value );

    void* getUserData() const;
    void setUserData( void* value );

    float32 getGravityScale() const;
    void setGravityScale( float32 value );

    // end auto generated code

    // custom properties
    QObjectList getQObjectFixtureList() { return qObjectFixtureList_; }

    bool isSelected() const;
    void setSelected(bool value);

    uint getId() const;


signals:
    void bodyChanged(const QBodyDef*);
    void fixtureChanged(const QFixtureDef*);

public slots:
    /*!
     * \brief   Create fixture form given definition. The fixture definition
     *          will be cloned.
     *
     * \example var f = new FixtureDef; f.setAsBox(10, 10);
     *          var b = world.createBody();
     *          b.createFixture(f);
     *
     * \param   fixtureDef which will be added to the body
     */
    void createFixture(const QScriptValue &fixtureDef);

private:

    b2BodyDef bodyDef_;
    QLinkedList<QFixtureDef*> fixtureList_;
    QObjectList qObjectFixtureList_;
    b2BodyDef saveState_;
    bool      wasSaved_;
    bool      isSelected_;

    const uint id_;
    // number of qbodydef created - 1
    static uint id_generator;

    friend class WorldModel;
};


inline b2BodyType QBodyDef::getType() const {
    return bodyDef_.type;
}
inline void QBodyDef::setType( b2BodyType value ) {
    bodyDef_.type = value;
    emit bodyChanged(this);
}

inline bool QBodyDef::getStatic() const {
    return bodyDef_.type == b2BodyType::b2_staticBody;
}
inline void QBodyDef::setStatic( bool value ) {
    if (value)
        setType(b2BodyType::b2_staticBody);
}

inline bool QBodyDef::getDynamic() const {
    return bodyDef_.type == b2BodyType::b2_dynamicBody;
}
inline void QBodyDef::setDynamic( bool value ) {
    if (value)
        setType(b2BodyType::b2_dynamicBody);
}

inline bool QBodyDef::getKinematic() const {
    return bodyDef_.type == b2BodyType::b2_kinematicBody;
}
inline void QBodyDef::setKinematic( bool value ) {
    if (value)
        setType(b2BodyType::b2_kinematicBody);
}

inline qreal QBodyDef::getX() const {
    return bodyDef_.position.x;
}
inline void  QBodyDef::setX(qreal value) {
    bodyDef_.position.x = value;
    emit bodyChanged(this);
}

inline qreal QBodyDef::getY() const {
    return bodyDef_.position.y;
}
inline void  QBodyDef::setY(qreal value) {
    bodyDef_.position.y = value;
    emit bodyChanged(this);
}

inline b2Vec2 QBodyDef::getPosition() const {
    return bodyDef_.position;
}
inline void QBodyDef::setPosition( b2Vec2 value ) {
    bodyDef_.position = value;
    emit bodyChanged(this);
}

inline float32 QBodyDef::getAngle() const {
    return bodyDef_.angle;
}
inline void QBodyDef::setAngle( float32 value ) {
    bodyDef_.angle = value;
    emit bodyChanged(this);
}

inline b2Vec2 QBodyDef::getLinearVelocity() const {
    return bodyDef_.linearVelocity;
}
inline void QBodyDef::setLinearVelocity( b2Vec2 value ) {
    bodyDef_.linearVelocity = value;
    emit bodyChanged(this);
}

inline float32 QBodyDef::getAngularVelocity() const {
    return bodyDef_.angularVelocity;
}
inline void QBodyDef::setAngularVelocity( float32 value ) {
    bodyDef_.angularVelocity = value;
    emit bodyChanged(this);
}

inline float32 QBodyDef::getLinearDamping() const {
    return bodyDef_.linearDamping;
}
inline void QBodyDef::setLinearDamping( float32 value ) {
    bodyDef_.linearDamping = value;
    emit bodyChanged(this);
}

inline float32 QBodyDef::getAngularDamping() const {
    return bodyDef_.angularDamping;
}
inline void QBodyDef::setAngularDamping( float32 value ) {
    bodyDef_.angularDamping = value;
    emit bodyChanged(this);
}

inline bool QBodyDef::getAllowSleep() const {
    return bodyDef_.allowSleep;
}
inline void QBodyDef::setAllowSleep( bool value ) {
    bodyDef_.allowSleep = value;
    emit bodyChanged(this);
}

inline bool QBodyDef::getAwake() const {
    return bodyDef_.awake;
}
inline void QBodyDef::setAwake( bool value ) {
    bodyDef_.awake = value;
    emit bodyChanged(this);
}

inline bool QBodyDef::getFixedRotation() const {
    return bodyDef_.fixedRotation;
}
inline void QBodyDef::setFixedRotation( bool value ) {
    bodyDef_.fixedRotation = value;
    emit bodyChanged(this);
}

inline bool QBodyDef::getBullet() const {
    return bodyDef_.bullet;
}
inline void QBodyDef::setBullet( bool value ) {
    bodyDef_.bullet = value;
    emit bodyChanged(this);
}

inline bool QBodyDef::getActive() const {
    return bodyDef_.active;
}
inline void QBodyDef::setActive( bool value ) {
    bodyDef_.active = value;
    emit bodyChanged(this);
}

inline void* QBodyDef::getUserData() const {
    return bodyDef_.userData;
}
inline void QBodyDef::setUserData( void* value ) {
    bodyDef_.userData = value;
    emit bodyChanged(this);
}

inline float32 QBodyDef::getGravityScale() const {
    return bodyDef_.gravityScale;
}
inline void QBodyDef::setGravityScale( float32 value ) {
    bodyDef_.gravityScale = value;
    emit bodyChanged(this);
}

// custom properties

inline bool QBodyDef::isSelected() const {
    return isSelected_;
}
inline void QBodyDef::setSelected(bool value) {
    if (value != isSelected_)
    {
        isSelected_ = value;
        emit bodyChanged(this);
    }
}

inline uint QBodyDef::getId() const
{
    return id_;
}

#endif // QBODYDEF_H
