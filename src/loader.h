#ifndef LOADER_H
#define LOADER_H

#include <QScriptEngine>
#include <QDebug>
#include <QString>
#include <QFile>
#include "engine.h"
#include "jsmethods.h"

class Loader : public QObject
{

public:

    Loader();

    void loadScripts();
    void loadToolsScripts();
    void loadOtherScripts();

};

QFileInfoList findScripts(const QDir& directory);

#endif // LOADER_H
