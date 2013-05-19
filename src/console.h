#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDockWidget>
#include <QLinkedList>

namespace Ui {
class Console;
}

class Console : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit Console(QWidget *parent = 0);
    ~Console();

    /*!
     * \brief if true then commands that was issued form command
     *        line will be rewritten in the console window
     * \param value true or false
     */
    void setEchoEnable(bool value);

public slots:
    /*!
     * \brief Write message on the console
     * \param msg Message that will be displayed
     */
    void write(const QString& msg);

signals:
    /*!
     * \brief This signal is emited when user press enter, and
     *        the command length is greater than 0.
     * \param msg Message that user entered
     */
    void command(const QString &msg);

private slots:
    void returnPressed(void);

protected:
    void keyPressEvent(QKeyEvent *);
    
private:
    Ui::Console *ui;
    bool echo_;
    QLinkedList<const QString> commandHistory_;
    QLinkedList<const QString>::iterator historyIt_;
};

#endif // CONSOLE_H
