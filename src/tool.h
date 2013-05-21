#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QIcon>
#include <QApplication>


class Tool : public QAction
{
    Q_OBJECT

public:

    explicit Tool(const QIcon & icon, const QString & text, QObject * parent) : QAction(icon, text, parent), position_(999) {}
    explicit Tool(const QString & text, QObject * parent) : QAction(text, parent),position_(999) {}
    int position(){ return position_; }
    void setPosition(int pos){ position_ = pos;  }
    ~Tool(){}


signals:

    void mouseButtonPress(int x, int y);
    void mouseButtonRelease(int x, int y);
    void mouseMove(int x, int y);


private:

    int position_;

    friend class ToolManager;

};

bool isLessThen(Tool* a, Tool* b);

#endif // TOOL_H
