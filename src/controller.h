#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMap>
#include "loader.h"
#include "toolmanager.h"
#include <QThread>

class MainWindow;
class WorldModel;
class WorldView;
class QScriptContext;
class QScriptValue;
class QScriptEngine;
class Stage;
class QBodyDef;

class Controller : public QObject
{
    Q_OBJECT
public:

signals:
    
public slots:
    void createNewProject();

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
    void createTools();

    WorldModel* getActiveModel() const;
    Stage*      getActiveStage() const;

    /*!
     * return model that is currently being displayed/focused
     */
    static QScriptValue getActiveModel(QScriptContext *context, QScriptEngine *engine);

    /*!
     * create new body in model
     */
    static QScriptValue createBody(QScriptContext *context, QScriptEngine *engine);

    /*!
     * get body under cursor
     */
    static QScriptValue getBodyUnderPoint(QScriptContext *context, QScriptEngine *engine);

    /*!
     * get bodies in given area
     */
    static QScriptValue getBodiesInArea(QScriptContext *context, QScriptEngine *engine);

    /*!
     * QFixtureDef constructor
     */
    static QScriptValue qFixtureDefConstructor(QScriptContext *context, QScriptEngine *engine);

    /// QBodyDef constructor
    static QScriptValue qBodyDefConstructor(QScriptContext *context, QScriptEngine *engine);

    /*!
     * \see MainWindow::saveFile
     */
    static QScriptValue saveFile(QScriptContext *context, QScriptEngine *engine);

    /*!
     * \see MainWindow::openFile
     */
    static QScriptValue openFile(QScriptContext *context, QScriptEngine *engine);

    /*!
     * \return array of current worlds
     */
    static QScriptValue getWorlds(QScriptContext *context, QScriptEngine *engine);

    MainWindow *mainWindow_;
    QMap<QObject*, WorldModel*> viewMap_;
    QMap<const QBodyDef*, QScriptValue> engineQBodyMap_;
    QList<WorldModel*> worlds_;
    Loader loader_;

    static Controller *instance_;
    friend class MainWindow;
};

#endif // CONTROLLER_H
