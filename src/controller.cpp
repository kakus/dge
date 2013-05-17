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
    return engine->newQObject(object, QScriptEngine::QtOwnership);
}

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
    QScriptValue console = Engine::getInstance()->getNewQObject(mainWindow_->console_);
    Engine::getInstance()->getGlobalObject().setProperty("console", console);

    // Add QBodyDef constructor
    // QScriptValue ctor = Engine::getInstance()->getNewFunction(scriptConstructor<QBodyDef>);
    // QScriptValue qBodyMeta = Engine::getInstance()->
    //         getNewQMetaObject(&QObject::staticMetaObject, ctor);
    // Engine::getInstance()->getGlobalObject().setProperty("BodyDef", qBodyMeta);

    // Add QFixtureDef constructor
    QScriptValue ctor = Engine::getInstance()->getNewFunction(scriptConstructor<QFixtureDef>);
    QScriptValue qFixtureMeta = Engine::getInstance()->
            getNewQMetaObject(&QObject::staticMetaObject, ctor);
    Engine::getInstance()->getGlobalObject().setProperty("FixtureDef", qFixtureMeta);

    // Add active world to the engine
    Engine::getInstance()->getGlobalObject()
            .setProperty("world",
                         Engine::getInstance()->getNewFunction(&Controller::getActiveModel),
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
}

void Controller::runWorldSimultion()
{
    if (getActiveModel() != nullptr)
        getActiveModel()->run();
}

WorldModel* Controller::getActiveModel() const
{
    return viewMap_.value(mainWindow_->ui->tabWidget->currentWidget());
}

QScriptValue Controller::getActiveModel(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(context);

    if (instance_->getActiveModel() == nullptr)
        return QScriptValue("Err: There are no active models/projects");

    QScriptValue model = engine->newQObject(instance_->getActiveModel());
    // add method for creating bodies
    model.setProperty("createBody", engine->newFunction(&Controller::createBody));
    return model;
}

QScriptValue Controller::createBody(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argument(0).isUndefined())
        return QScriptValue('Err: world.createBody take 1 argument ( QFixtureDef )');

    QObject *arg = context->argument(0).toQObject();
    QFixtureDef *fix = static_cast<QFixtureDef*>(arg);

    if (fix == nullptr)
        return QScriptValue("Err: world.createBody type of argument isn't QFixtureDef");

    if (instance_->getActiveModel() != nullptr)
        return engine->newQObject(instance_->getActiveModel()->createBody(fix));
    else
        return QScriptValue("Err: There are no active models/projects");
}

void Controller::createTools(){
    ToolManager::getInstance()->createTools();
    ToolManager::getInstance()->createToolbar(mainWindow_);

}
