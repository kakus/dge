#include "toolmanager.h"

ToolManager* ToolManager::instance_;
std::mutex ToolManager::mutex_;

ToolManager::ToolManager()
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
        mutex_.lock();
        if(!instance_)
            instance_ = new ToolManager;
        mutex_.unlock();
    }

    return instance_;
}

void ToolManager::createTools()
{
    QScriptValue tools = Engine::getInstance()->getGlobalObject().property("tools");

    for(QScriptValueIterator it(tools); it.hasNext();)
    {
        it.next();
        createTool(it.value(), it.name());
    }

}

void ToolManager::createTool(const QScriptValue& object, QString name)
{
    Tool* newTool;

    tools_.push_back(new Tool(name.remove(name.length()-3,3),this));
    newTool = tools_.back();

    qScriptConnect(newTool,SIGNAL(mouseButtonPress(int,int)),
                   object,object.property("mouseButtonPress"));
    qScriptConnect(newTool,SIGNAL(mouseButtonRelease(int,int)),
                   object,object.property("mouseButtonRelease"));
    qScriptConnect(newTool,SIGNAL(mouseMove(int,int)),
                   object,object.property("mouseMove"));

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

void ToolManager::setActiveTool()
{
    activeTool_ = static_cast<Tool*>(QObject::sender());
    qDebug() << activeTool_->text() << "changed" << endl;
}

void ToolManager::createToolbar(QMainWindow *window){

    QToolBar* toolbar = window->addToolBar("Toolbar");

    foreach(Tool* x, tools_)
        toolbar->addAction(x);

}