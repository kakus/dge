#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <QObject>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include <QMainWindow>
#include <QToolBar>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QtAlgorithms>
#include <QList>
#include <mutex>
#include "tool.h"
#include "engine.h"

class ToolManager : public QObject
{
    Q_OBJECT

public:

    ~ToolManager();

    static ToolManager* getInstance();

    /*!
     * \brief createTools from loaded tools scripts
     */
    void createTools();

    /*!
     * \brief createToolbar with all loaded tools and dock it on "window"
     * \param window
     */
    void createToolbar(QMainWindow *window);

public slots:

    /*!
     * \brief redirectEvent to activeTool_
     */
    void redirectEvent(QGraphicsSceneMouseEvent *event);
    void redirectEvent(QKeyEvent *event);
    void setActiveTool();

signals:
    void keyEvent(int code, int modifier);

private:

    ToolManager();

    static ToolManager* instance_;

    void createTool(const QScriptValue&,  QString);

    QList<Tool*> tools_;
    Tool* activeTool_;

};

#endif // TOOLMANAGER_H
