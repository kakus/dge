#include "controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stage.h"
#include "worldmodel.h"
#include "engine.h"

Controller *Controller::instance_ = nullptr;

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    mainWindow_(mainWindow)
{
    instance_ = this;

    loadScripts();
    createTools();
    initEngine();
}

void Controller::initEngine()
{
    // Add console to script engine, so user can write on console
    QScriptValue console = Engine::getInstance()->newQObject(mainWindow_->console_);
    Engine::getInstance()->globalObject().setProperty("console", console);

    // Add QFixtureDef constructor
    QScriptValue ctor = Engine::getInstance()->newFunction(&Controller::qFixtureDefConstructor);
    QScriptValue qMeta = Engine::getInstance()->
            newQMetaObject(&QObject::staticMetaObject, ctor);
    Engine::getInstance()->globalObject().setProperty("FixtureDef", qMeta);

    // Add QBodyDef constructor
    ctor = Engine::getInstance()->newFunction(&Controller::qBodyDefConstructor);
    qMeta = Engine::getInstance()->
            newQMetaObject(&QObject::staticMetaObject, ctor);
    Engine::getInstance()->globalObject().setProperty("BodyDef", qMeta);

    // Add active world to the engine
    Engine::getInstance()->globalObject()
            .setProperty("world",
                         Engine::getInstance()->newFunction(&Controller::getActiveModel),
                         QScriptValue::PropertyGetter);

    // Connect console to the script engine
    connect(mainWindow_->console_, SIGNAL(command(QString)),
            Engine::getInstance(), SLOT(evaluate(QString)));

    connect(Engine::getInstance(), SIGNAL(evaluateResult(QString)),
            mainWindow_->console_,  SLOT(write(QString)));
}

void Controller::loadScripts()
{
    loader_.loadScripts();
}

void Controller::createTools()
{
    ToolManager::getInstance()->createTools();
    ToolManager::getInstance()->createToolbar(mainWindow_);
}

void Controller::createNewProject()
{
    Stage *stage = new Stage(mainWindow_->ui->tabWidget);
    mainWindow_->ui->tabWidget->addTab(stage, "new project");

    WorldModel *model = new WorldModel(this);
    stage->connectToModel(stage, model);

    viewMap_.insert(stage, model);

    // redirects mouse events from new stage
    connect(stage, SIGNAL(mouseEvent(QGraphicsSceneMouseEvent*)),
            ToolManager::getInstance(),  SLOT(redirectEvent(QGraphicsSceneMouseEvent*)));
    connect(stage, SIGNAL(keyEvent(QKeyEvent*)),
            ToolManager::getInstance(), SLOT(redirectEvent(QKeyEvent*)));

    mainWindow_->ui->tabWidget->setCurrentWidget(stage);
}

WorldModel* Controller::getActiveModel() const
{
    return viewMap_.value(mainWindow_->ui->tabWidget->currentWidget());
}

Stage* Controller::getActiveStage() const
{
    return dynamic_cast<Stage*>(mainWindow_->ui->tabWidget->currentWidget());
}

// -------- static mehtods --------

QScriptValue Controller::getActiveModel(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(context);

    if (instance_->getActiveModel() == nullptr)
        return QScriptValue("Err: There are no active models/projects");

    QScriptValue model = engine->newQObject(instance_->getActiveModel());
    // add method for creating bodies
    model.setProperty("createBody", engine->newFunction(&Controller::createBody));
    // add method for getting bodies at given point
    model.setProperty("bodyAt", engine->newFunction(&Controller::getBodyUnderPoint));
    model.setProperty("bodiesAt", engine->newFunction(&Controller::getBodiesInArea));
    model.setProperty("stage", engine->newQObject(instance_->getActiveStage()));
    return model;
}

QScriptValue Controller::createBody(QScriptContext *context, QScriptEngine *engine)
{
    if (instance_->getActiveModel() == nullptr)
    {
        engine->evaluate("console.write('Err: There are no active models/projects')");
        return QScriptValue(QScriptValue::UndefinedValue);
    }

    QBodyDef* qbody =  nullptr;
    // if no argument is given, we create body with no fixtures
    if (context->argument(0).isUndefined())
        qbody = instance_->getActiveModel()->createBody();


    // argument could be qfixtredef or qbodydef
    QObject *arg = context->argument(0).toQObject();
    // first we try qfixture, it should be more common cause
    QFixtureDef *qfixture = dynamic_cast<QFixtureDef*>(arg);

    if (qfixture != nullptr)
        // argument was a type of qfixturedef
        qbody = instance_->getActiveModel()->createBody(qfixture);
    else
        // else maybe we have a qbodydef as a argument.
    {
        QBodyDef *qbodyToClone = dynamic_cast<QBodyDef*>(arg);
        // if yes then we can clone it
        if (qbodyToClone != nullptr)
            qbody = instance_->getActiveModel()->createBody(qbodyToClone);
    }

    if (qbody != nullptr)
    {
        // add to the map, so when we want return this body to the script
        // engine we don't need to create new qobject
        instance_->engineQBodyMap_[qbody] = engine->newQObject(qbody);
        return instance_->engineQBodyMap_[qbody];
    }
    else
        // we didn't create qbody so there were errors
    {
        engine->evaluate("console.write('Err: world.createBody type of argument isn't QFixtureDef')");
        return QScriptValue(QScriptValue::UndefinedValue);
    }
}

QScriptValue Controller::getBodyUnderPoint(QScriptContext *context, QScriptEngine *engine)
{
    const Stage* stage = instance_->getActiveStage();
    if (stage == nullptr)
    {
        engine->evaluate("console.write('Err: There are no active models/projects')");
        return QScriptValue(QScriptValue::UndefinedValue);
    }

    qreal x = context->argument(0).toNumber();
    qreal y = context->argument(1).toNumber();

    const QBodyDef* qbody = stage->bodyAt(x, y);

    if (qbody != nullptr)
        return instance_->engineQBodyMap_[qbody];
    else
        return QScriptValue(QScriptValue::UndefinedValue);
}

QScriptValue Controller::getBodiesInArea(QScriptContext *context, QScriptEngine *engine)
{
    const Stage* stage = instance_->getActiveStage();
    if (stage == nullptr) return QScriptValue(QScriptValue::UndefinedValue);

    qreal x1 = context->argument(0).toNumber(),
          y1 = context->argument(1).toNumber(),
          x2 = context->argument(2).toNumber(),
          y2 = context->argument(3).toNumber();

    QObjectList bodies;
    foreach (const QBodyDef* qbody, stage->getBodiesAt(QRectF(x1, y1, x2, y2)))
        bodies.push_back(instance_->engineQBodyMap_[qbody].toQObject());

    return qScriptValueFromSequence(engine, bodies);
}

QScriptValue Controller::qFixtureDefConstructor(QScriptContext *context, QScriptEngine *engine)
{
    QFixtureDef *qfixture = new QFixtureDef();

    if (!context->argument(0).isUndefined())
    {
        QFixtureDef *prototype = dynamic_cast<QFixtureDef*>(context->argument(0).toQObject());
        if (prototype != nullptr)
        {
            qfixture->fixtureDef_ = prototype->fixtureDef_;
            qfixture->setShape(prototype->getShape());
        }
    }

    return engine->newQObject(qfixture, QScriptEngine::ScriptOwnership);
}

QScriptValue Controller::qBodyDefConstructor(QScriptContext *context, QScriptEngine *engine)
{
    QBodyDef* prototype = dynamic_cast<QBodyDef*>(context->argument(0).toQObject());
    QBodyDef* qbody = nullptr;

    if (prototype != nullptr)
        qbody = prototype->clone();
    else
        qbody = new QBodyDef;

    return engine->newQObject(qbody, QScriptEngine::ScriptOwnership);
}
