#ifndef JSMETHODS_H
#define JSMETHODS_H

#include <QScriptValueIterator>
#include <QScriptEngine>
#include <QDebug>
#include <QString>
#include <QList>
#include <QFile>
#include <QDir>

/*!
 * \brief copyJSObject
 * \param obj
 * \return deep copy of obj
 */
QScriptValue copyJSObject(const QScriptValue& obj);

/*!
 * \brief getFileContent
 * \param fileName
 * \return file's content
 */
QString getFileContent(QString fileName);

#endif// JSMETHODS_H
