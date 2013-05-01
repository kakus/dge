#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMap>

class MainWindow;
class WorldModel;
class WorldView;

class Controller : public QObject
{
    Q_OBJECT
public:

signals:
    
public slots:
    void createNewProject();
    void rectangleTEST();

private:
    /*!
     * It can only be constructed by MainWindow class
     */
    explicit Controller(MainWindow *mainWindow);

    WorldModel* getActiveModel() const;

    MainWindow *mainWindow_;
    QMap<QObject*, WorldModel*> viewMap_;

    friend class MainWindow;
};

#endif // CONTROLLER_H
