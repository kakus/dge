#ifndef JSMETHODS_H
#define JSMETHODS_H

#include <QScriptValueIterator>
#include <QScriptEngine>
#include <QDebug>
#include <QString>
#include <QList>
#include <QFile>
#include <QDir>

QScriptValue copyJSObject(const QScriptValue& obj);
QString getFileContent(QString fileName);

#endif// JSMETHODS_H
