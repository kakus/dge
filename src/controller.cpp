#include "controller.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stage.h"
#include "worldmodel.h"
#include "engine.h"

template<class T>
QScriptValue scriptConstructor(QScriptContext *context, QScriptEngine *engine)
{
    QObject *parent = context->argument(0).toQObject();
    T *object = new T(parent);
    return engine->newQObject(object, QScriptEngine::ScriptOwnership);
}

Controller *Controller::instance_ = nullptr;

Controller::Controller(MainWindow *mainWindow) :
    QObject(mainWindow),
    mainWindow_(mainWindow)
{
    instance_ = this;

    initEngine();

    // Connect console to the script engine
    connect(mainWindow->console_, SIGNAL(command(QString)),
            Engine::getInstance(), SLOT(evaluate(QString)));

    connect(Engine::getInstance(), SIGNAL(evaluateResult(QString)),
            mainWindow->console_,  SLOT(write(QString)));
}

void Controller::initEngine()
{
    // Add console to script engine, so user can write on console
    QScriptValue console = Engine::getInstance()->getNewQObject(mainWindow_->console_);
    Engine::getInstance()->getGlobalObject().setProperty("console", console);

    // Add QBodyDef constructor
    QScriptValue ctor = Engine::getInstance()->getNewFunction(scriptConstructor<QBodyDef>);
    QScriptValue qBodyMeta = Engine::getInstance()->
            getNewQMetaObject(&QObject::staticMetaObject, ctor);
    Engine::getInstance()->getGlobalObject().setProperty("BodyDef", qBodyMeta);

    // Add QFixtureDef constructor
    ctor = Engine::getInstance()->getNewFunction(scriptConstructor<QFixtureDef>);
    QScriptValue qFixtureMeta = Engine::getInstance()->
            getNewQMetaObject(&QObject::staticMetaObject, ctor);
    Engine::getInstance()->getGlobalObject().setProperty("FixtureDef", qFixtureMeta);

    // Add active world to the engine
    Engine::getInstance()->getGlobalObject()
            .setProperty("world",
                         Engine::getInstance()->getNewFunction(&Controller::getActiveModel),
                         QScriptValue::PropertyGetter);
}

void Controller::createNewProject()
{
    Stage *stage = new Stage(mainWindow_->ui->tabWidget);
    mainWindow_->ui->tabWidget->addTab(stage, "new project");

    WorldModel *model = new WorldModel(this);
    stage->connectToModel(stage, model);

    viewMap_.insert(stage, model);
}

void Controller::rectangleTEST()
{
    QBodyDef *body = new QBodyDef;
    QFixtureDef *fix = new QFixtureDef;

    b2PolygonShape shape;
    shape.SetAsBox(20, 20);
    fix->setShape(&shape);

    body->addFixtureDef(fix);

    WorldModel* model = getActiveModel();
    if (model)
        model->addBody(body);
}

WorldModel* Controller::getActiveModel() const
{
    return viewMap_.value(mainWindow_->ui->tabWidget->currentWidget());
}

QScriptValue Controller::getActiveModel(QScriptContext *context, QScriptEngine *engine)
{
    return engine->newQObject(instance_->getActiveModel());
}
