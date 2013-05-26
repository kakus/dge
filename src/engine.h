// singleton class to keep javasript interpreter
// thread safe

#ifndef ENGINE_H
#define ENGINE_H

#include <QScriptEngine>
#include <QPushButton>
#include <QDebug>
#include <QMutex>
#include <iostream>
#include <mutex>

/*!
 * \brief The Engine class
 *  Singleton class wrapping javascript interpreter
 *  Friend class Loader add preloaded tools to engine's global object before app start
 */

class EngineProxy : public QObject
{
    Q_OBJECT

public:
    ~EngineProxy();

    static EngineProxy* getInstace();
    static QScriptEngine* getEngine();

public slots:
    void evaluate(const QString& code);

signals:
    void evaluateResult(const QString& value);

private:

    EngineProxy();
    EngineProxy(const EngineProxy&);

    static EngineProxy* pInstance_;

    QScriptEngine engine_;
    friend class Loader;
};

#endif // ENGINE_H
