#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QIcon>
#include <QApplication>


class Tool : public QAction
{
    Q_OBJECT

public:

    explicit Tool(const QIcon & icon, const QString & text, QObject * parent) : QAction(icon, text, parent) {}
    explicit Tool(const QString & text, QObject * parent) : QAction(text, parent) {}
    ~Tool(){}

signals:

    void mouseButtonPress(int x, int y);
    void mouseButtonRelease(int x, int y);
    void mouseMove(int x, int y);

    friend class ToolManager;
};

#endif // TOOL_H
