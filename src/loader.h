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

    /*!
     * \brief load all scripts from directories "scripts" and "tools"
     */
    void loadScripts();
    /*!
     * \brief load scripts with tools from "tools" directory
     * access to tools in engine's global object -> tools["fileName"]
     * example tool available in "tools" directory in "ex_tool.js"
     */
    void loadToolsScripts();
    /*!
     * \brief load scripts from "scripts" directory
     * add everything to engine's global object
     * to prevent overriding objects in your scripts consider using namespaces
     */
    void loadOtherScripts();

};

/*!
 * \brief find all *.js files in directory "directory" ( and its subdirectories )
 * \param directory
 * \return
 */
QFileInfoList findScripts(const QDir& directory);

#endif // LOADER_H
