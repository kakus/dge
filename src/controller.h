#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMap>
#include "loader.h"

class MainWindow;
class WorldModel;
class WorldView;
class QScriptContext;
class QScriptValue;
class QScriptEngine;

class Controller : public QObject
{
    Q_OBJECT
public:

signals:
    
public slots:
    void createNewProject();
    void runWorldSimultion();

private:
    /*!
     * It can only be constructed by MainWindow class
     */
    explicit Controller(MainWindow *mainWindow);
    /*!
     * \brief Setup engine with all object that are needed to work.
     *  For example: QBodyDef constructor, Console.
     */
    void initEngine();
    void loadScripts();

    WorldModel* getActiveModel() const;
    /*!
     * this method is exported to the script engine
     */
    static QScriptValue getActiveModel(QScriptContext *context, QScriptEngine *engine);

    MainWindow *mainWindow_;
    QMap<QObject*, WorldModel*> viewMap_;
    Loader loader_;

    static Controller *instance_;
    friend class MainWindow;
};

#endif // CONTROLLER_H
