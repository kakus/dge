// singleton class to keep javasript interpreter
// thread safe

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <mutex>
#include <QScriptEngine>
#include <QPushButton>
#include <QDebug>

//#include "loader.h"

/*!
 * \brief The Engine class
 *  Singleton class wrapping javascript interpreter
 *  Friend class Loader add preloaded tools to engine's global object before app start
 */

class Engine : public QObject
{
    Q_OBJECT

public:
    ~Engine();

    static Engine* getInstance();

    QScriptValue globalObject() const;
    QScriptValue newQObject(QObject*);
    QScriptValue newFunction(QScriptEngine::FunctionSignature fun, int length = 0);
    QScriptValue newQMetaObject(const QMetaObject * meta,
                                   const QScriptValue ctor = QScriptValue());

public slots:
    void evaluate(const QString& code);

signals:
    void evaluateResult(const QString& value);

private:

    Engine();
    Engine(const Engine&);

    static Engine* pInstance_;
    static std::mutex mutex_;

    QScriptEngine engine_;

    friend class Loader;
};

#endif // ENGINE_H
