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

    /*!
     * \brief Open file by given file name, if file name is not specified
     *        then promp will be opened so user can choose a file
     * \return Path to opened file
     */
    QString openFile(QString filename = "");

    /*!
     * \brief Save content to to file given by file name, if file name is not
     *        specified then prompt will be opened so user can choose desitination.
     * \return Path to saved file
     */
    QString saveFile(const QString &content, QString filename = "");
    
private:
    Ui::MainWindow *ui;
    Console *console_;
    Controller *controller_;

    friend class Controller;
};

#endif // MAINWINDOW_H
