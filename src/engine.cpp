#include "engine.h"

EngineProxy* EngineProxy::pInstance_;

EngineProxy::EngineProxy()
    : engine_(this)
{
}

EngineProxy::~EngineProxy()
{
    delete pInstance_;
}

EngineProxy* EngineProxy::getInstace()
{
    if(!EngineProxy::pInstance_)
    {
        if(!pInstance_)
            pInstance_ = new EngineProxy;
    }

    return pInstance_;
}

QScriptEngine* EngineProxy::getEngine()
{
    return &getInstace()->engine_;
}

void EngineProxy::evaluate(const QString &code)
{
    QScriptValue result = getEngine()->evaluate(code);
    emit evaluateResult(result.toString());
}

