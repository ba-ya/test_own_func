#ifndef FUNC3_H
#define FUNC3_H

#include <QMainWindow>

namespace Ui {
class func3;
}

class func3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit func3(QWidget *parent = nullptr);
    ~func3();

private:
    void init();
    void init_dock();
    void init_action();

    void layout_chain(const QList<QDockWidget*> &dock,
                      const QList<int> &size,
                      Qt::Orientation orientation);
private:
    Ui::func3 *ui;
    QList<QDockWidget*> docks;
};

#endif // FUNC3_H
