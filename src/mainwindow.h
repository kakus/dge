#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "console.h"

namespace Ui {
class MainWindow;
}
class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    Console *console_;
    Controller *controller_;

    friend class Controller;
};

#endif // MAINWINDOW_H
