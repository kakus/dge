#include "loader.h"

Loader::Loader()
{

}

void Loader::loadScripts()
{

    loadOtherScripts();
    loadToolsScripts();
}

void Loader::loadOtherScripts()
{
    QDir fromWhichDir ("scripts");
    QString scriptContent;
    QScriptValue result;

    QFileInfoList scriptsList = findScripts( fromWhichDir );

    foreach ( QFileInfo x, scriptsList)
    {
        scriptContent = getFileContent(x.absoluteFilePath());
        result = Engine::getInstance()->engine_.evaluate(scriptContent);

        if(result.isError())
            qDebug() << "Error in "<< x.fileName() << " script." << x.fileName() << endl;
    }

}

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
        scriptContent = getFileContent(x.absoluteFilePath());
        result = engine.evaluate(scriptContent);

        tools.setProperty(x.fileName(), result);

        // check if file has correct javascript content
        if(result.isError())
            qDebug() << "Error in "<< x.fileName() << " script." << x.fileName() << endl;
    }

    engine.globalObject().setProperty("tools",tools);

}

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
