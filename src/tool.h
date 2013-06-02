#ifndef TOOL_H
#define TOOL_H

#include <QAction>
#include <QIcon>
#include <QApplication>

/*!
 * \brief The Tool class
 */
class Tool : public QAction
{
    Q_OBJECT

public:

    explicit Tool(const QIcon & icon, const QString & text, QObject * parent) : QAction(icon, text, parent), position_(999), onFileMenu(false) {}
    explicit Tool(const QString & text, QObject * parent) : QAction(text, parent),position_(999), onFileMenu(false) {}
    int position(){ return position_; }
    void setPosition(int pos){ position_ = pos;  }
    ~Tool(){}


signals:

    void mouseButtonPress(int x, int y);
    void mouseButtonRelease(int x, int y);
    void mouseMove(int x, int y);
    void keyPress(int code, int modifier);

private:

    int position_;
    bool onFileMenu;

    friend class ToolManager;
};

/*!
 * \brief compare tools position_ (on toolbar)
 */
bool isLessThen(Tool* a, Tool* b);

#endif // TOOL_H
