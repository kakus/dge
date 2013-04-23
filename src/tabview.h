#ifndef TABVIEW_H
#define TABVIEW_H

#include <QTabWidget>

namespace Ui {
class TabView;
}

class TabView : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit TabView(QWidget *parent = 0);
    ~TabView();
    
private:
    Ui::TabView *ui;
};

#endif // TABVIEW_H
