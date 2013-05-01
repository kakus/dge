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
public:
    static Engine* getInstance();
    void testTools(const QString& fileName, const QString& functionName) const;
    ~Engine();

public slots:
    void evaluate(const QString& code);

signals:
    void evaluateResult(const QScriptValue& code);

private:

    Q_OBJECT

    QScriptEngine engine_;

    static Engine* pInstance_;
    static std::mutex mutex_;

    Engine();
    Engine(const Engine&);

    //friend class Loader;
};

#endif // ENGINE_H
