#include "jsmethods.h"

QScriptValue copyJSObject( const QScriptValue& obj)
{
    if( (obj.isObject() || obj.isArray()) && !obj.isFunction() )
    {
        QScriptValue copy = obj.isArray() ? obj.engine()->newArray() : obj.engine()->newObject();
        copy.setData( obj.data() );
        QScriptValueIterator it(obj);

        while(it.hasNext())
        {
            it.next();
            copy.setProperty( it.name(), copyJSObject(it.value()) );
        }

        return copy;
    }

    return obj;
}

QString getFileContent(QString fileName)
{
    QFile scriptFile(fileName);

    if(!scriptFile.open(QIODevice::ReadOnly))
        qDebug() << "Cannot open " << fileName << endl;

    QTextStream stream(&scriptFile);
    QString content = stream.readAll();
    scriptFile.close();

    return content;
}

