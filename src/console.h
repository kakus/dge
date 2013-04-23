#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDockWidget>

namespace Ui {
class Console;
}

class Console : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit Console(QWidget *parent = 0);
    ~Console();
    
private:
    Ui::Console *ui;
};

#endif // CONSOLE_H
