#ifndef TESTDOCKWIDGET_3_H
#define TESTDOCKWIDGET_3_H

#include <QMainWindow>

namespace Ui {
class TestDockWidget_3;
}

class TestDockWidget_3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestDockWidget_3(QWidget *parent = nullptr);
    ~TestDockWidget_3();

private:
    void init();
    void init_dock();
    void init_action();

    void layout_chain(const QList<QDockWidget*> &dock,
                      const QList<int> &size,
                      Qt::Orientation orientation);
    void layout_nest(const QList<QDockWidget*> dock);

    void remove_docks(const QList<QDockWidget*> dock);

private:
    Ui::TestDockWidget_3 *ui;
    QList<QDockWidget*> docks;
};

#endif // TESTDOCKWIDGET_3_H
