#include "toolmanager.h"

ToolManager* ToolManager::instance_;

ToolManager::ToolManager() : activeTool_(nullptr)
{
}

ToolManager::~ToolManager()
{
    delete instance_;
}

ToolManager* ToolManager::getInstance()
{
    if(!ToolManager::instance_)
    {
        if(!instance_)
            instance_ = new ToolManager;
    }

    return instance_;
}

void ToolManager::createTools()
{
    QScriptValue tools = EngineProxy::getEngine()->globalObject().property("tools");

    for(QScriptValueIterator it(tools); it.hasNext();)
    {
        it.next();
        createTool(it.value(), it.name());
    }
}

void ToolManager::createTool(const QScriptValue& object, QString name)
{
    Tool* newTool;
    QScriptValue positionOnToolbar = object.property("positionOnToolbar");

    tools_.push_back(new Tool(name.remove(name.length()-3,3),this));
    newTool = tools_.back();

    newTool->setIcon(QIcon::fromTheme(object.property("icon").toString(),
                                      QIcon("tools/" + object.property("icon").toString())));
    newTool->setCheckable(object.property("checkable").toBool());
    newTool->setShortcut(QKeySequence::fromString(object.property("shortcut").toString()));

    if(positionOnToolbar.isNumber())
        newTool->setPosition(positionOnToolbar.toInt32());

    qScriptConnect(newTool,SIGNAL(mouseButtonPress(int,int)),
                   object,object.property("mouseButtonPress"));
    qScriptConnect(newTool,SIGNAL(mouseButtonRelease(int,int)),
                   object,object.property("mouseButtonRelease"));
    qScriptConnect(newTool,SIGNAL(mouseMove(int,int)),
                   object,object.property("mouseMove"));
    qScriptConnect(newTool, SIGNAL(triggered()),
                   object, object.property("buttonClicked"));
    qScriptConnect(newTool,SIGNAL(keyPress(int,int)),
                   object, object.property("keyboardManager").property("keyPress"));

    QObject::connect(newTool, SIGNAL(triggered()),
                     ToolManager::getInstance(),SLOT(setActiveTool()));


}

void ToolManager::redirectEvent(QGraphicsSceneMouseEvent *event)
{
    if(activeTool_ != nullptr)
    {
        switch(event->type())
        {
        case QGraphicsSceneMouseEvent::GraphicsSceneMousePress:
            emit activeTool_->mouseButtonPress(event->scenePos().x(),event->scenePos().y()); break;
        case QGraphicsSceneMouseEvent::GraphicsSceneMouseRelease:
            emit activeTool_->mouseButtonRelease(event->scenePos().x(), event->scenePos().y()); break;
        case QGraphicsSceneMouseEvent::GraphicsSceneMouseMove:
            emit activeTool_->mouseMove(event->scenePos().x(), event->scenePos().y()); break;
        default:    break;
        }
    }
}

void ToolManager::redirectEvent(QKeyEvent *event)
{
    if(activeTool_ != nullptr){
        switch(event->type())
        {
        case QKeyEvent::KeyPress:
            emit activeTool_->keyPress(event->key(), event->modifiers()); break;
        default: break;
        }
    }
}

void ToolManager::setActiveTool()
{
    Tool* newActiveTool = static_cast<Tool*>(QObject::sender());

    if( newActiveTool->isCheckable()){
        if(activeTool_ != nullptr)
            activeTool_->setChecked(false);

        activeTool_ = newActiveTool;
        activeTool_->setChecked(true);
    }
}

void ToolManager::createToolbar(QMainWindow *window){

    QToolBar* toolbar = window->addToolBar("Toolbar");
    toolbar->setIconSize(QSize(24,24));
    qSort(tools_.begin(),tools_.end(),isLessThen);

    foreach(Tool* x, tools_)
        toolbar->addAction(x);
}
