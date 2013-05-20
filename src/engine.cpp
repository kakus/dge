#include "engine.h"

Engine* Engine::pInstance_;
std::mutex Engine::mutex_;

Engine::Engine()
{
}

Engine::~Engine()
{
    delete pInstance_;
}

Engine* Engine::getInstance()
{
    if(!Engine::pInstance_)
    {
        mutex_.lock();
        if(!pInstance_)
            pInstance_ = new Engine;
        mutex_.unlock();
    }

    return pInstance_;
}

QScriptValue Engine::getGlobalObject() const
{
    mutex_.lock();
        QScriptValue v = engine_.globalObject();
    mutex_.unlock();
    return v;
}

QScriptValue Engine::getNewQObject(QObject* object)
{
    mutex_.lock();
        QScriptValue v =  engine_.newQObject(object);
    mutex_.unlock();
    return v;
}

QScriptValue Engine::newFunction(QScriptEngine::FunctionSignature fun, int length)
{
    mutex_.lock();
        QScriptValue v =  engine_.newFunction(fun, length);
    mutex_.unlock();
    return v;
}

QScriptValue Engine::newQMetaObject(const QMetaObject *meta, const QScriptValue ctor)
{
    mutex_.lock();
        QScriptValue v =  engine_.newQMetaObject(meta, ctor);
    mutex_.unlock();
    return v;
}

void Engine::evaluate(const QString &code)
{
    QScriptValue result = engine_.evaluate(code);
    emit evaluateResult(result.toString());
}

