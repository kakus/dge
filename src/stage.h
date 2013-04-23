#ifndef STAGE_H
#define STAGE_H

#include <QWidget>

namespace Ui {
class Stage;
}

class Stage : public QWidget
{
    Q_OBJECT
    
public:
    explicit Stage(QWidget *parent = 0);
    ~Stage();
    
private:
    Ui::Stage *ui;
};

#endif // STAGE_H
