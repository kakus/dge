#include "loader.h"

Loader::Loader()
{

}


/*!
 * \brief Loader::loadScripts
 *  Load scripts from "scripts" and "tools" directories
*/
void Loader::loadScripts()
{
    loadToolsScripts();
    loadOtherScripts();
}

/*!
 * \brief Loader::loadOtherScripts
 *  Load scripts from "scripts" directory -> add them to Engine global object
 */
void Loader::loadOtherScripts()
{
    QDir fromWhichDir ("scripts");
    QString scriptContent;
    QScriptValue result;

    QFileInfoList scriptsList = findScripts( fromWhichDir );

    foreach ( QFileInfo x, scriptsList){

        // qDebug() << "Other: File" << x.filePath() << endl;

        scriptContent = getFileContent(x.absoluteFilePath());
        result = Engine::getInstance()->engine_.evaluate(scriptContent);

        if(result.isError())
            qDebug() << "Error in "<< x.fileName() << " script." << x.fileName() << endl;
    }

}

/*!
 * \brief Loader::loadToolsScripts
 *  Load scripts describing tools from "tools" directory
 *  Add them to Engine global object
 *  Access to tools in global object -> tools.fileName
 */
void Loader::loadToolsScripts()
{
    QDir fromWhichDir ("tools");
    QScriptValue result, tools;
    QString scriptContent;
    QScriptEngine& engine = Engine::getInstance()->engine_;

    QFileInfoList scriptsList = findScripts( fromWhichDir );

    tools = engine.newObject();

    foreach (QFileInfo x, scriptsList)
    {
        //qDebug() << "Tools: File" << x.filePath() << endl;

        scriptContent = getFileContent(x.absoluteFilePath());
        result = engine.evaluate(scriptContent);

        tools.setProperty(x.fileName(), copyJSObject(engine.globalObject()));

        if(result.isError())
            qDebug() << "Error in "<< x.fileName() << " script." << x.fileName() << endl;
    }

    engine.globalObject().setProperty("tools",tools);

}

/*!
 * \brief findScripts
 * \param directory
 * \return list of all scripts in directory directory (and all of its subdirectories)
 */
QFileInfoList findScripts(const QDir& directory)
{
    QStringList nameFilter("*.js");
    QFileInfoList filesList, directoriesList;

    directoriesList = directory.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot );

    foreach( QFileInfo x, directoriesList )
        filesList << findScripts( QDir( x.absoluteFilePath() ) );

    filesList << directory.entryInfoList( nameFilter );

    return filesList;

}
