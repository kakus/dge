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


void Engine::evaluate(const QString &code)
{
    QScriptValue result = engine_.evaluate(code);
    emit evaluateResult(result);
}

void Engine::testTools(const QString& fileName, const QString& functionName) const
{
    QScriptValue function;

    function = engine_.globalObject().property("tools").property(fileName).property(functionName);

    if(!function.isFunction())
        qDebug() << functionName << " is unknown for " << fileName << " script" << endl;
    else
        qDebug() << function.call().toString()<< endl;

}
