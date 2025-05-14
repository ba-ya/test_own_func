#include "func3.h"
#include "ui_func3.h"

#define CNT_DOCK 9

func3::func3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::func3)
{
    ui->setupUi(this);
    init();
}

func3::~func3()
{
    delete ui;
}

void func3::init()
{
    init_dock();
    init_action();
    ui->action_sudoku->trigger();
}

void func3::init_dock()
{
    // delete central widget
    QWidget* p = takeCentralWidget();
    if (p) {
        delete  p;
    }
    // enable nest
    setDockNestingEnabled(true);
    // store
    QList<QDockWidget *> ws = {ui->w_1, ui->w_2, ui->w_3, ui->w_4,
                               ui->w_5, ui->w_6, ui->w_7, ui->w_8, ui->w_9,
                               };
    for (auto w : ws) {
        docks.append(w);
    }
}

void func3::init_action()
{
    connect(ui->action_sudoku, &QAction::triggered, this, [this]() {
        layout_chain({docks[3], docks[4], docks[5]}, {2, 1, 2}, Qt::Horizontal);
        layout_chain({docks[0], docks[1], docks[2]}, {1, 1, 1}, Qt::Horizontal);
        layout_chain({docks[6], docks[7], docks[8]}, {1, 1, 1}, Qt::Horizontal);
        resizeDocks({docks[0], docks[3], docks[6]}, {1, 1, 1}, Qt::Vertical);
    });
    connect(ui->action_v, &QAction::triggered, this, [this]() {
        layout_chain(docks, QList<int>(9, 1), Qt::Horizontal);
    });
    connect(ui->action_h, &QAction::triggered, this, [this]() {
        layout_chain(docks, QList<int>(9, 1), Qt::Vertical);
    });
}

void func3::layout_chain(const QList<QDockWidget *> &dock, const QList<int> &size, Qt::Orientation orientation)
{
    // Starting location point
    addDockWidget(Qt::LeftDockWidgetArea, dock[0]);
    // show
    for (auto &w : dock) {
        w->show();
    }
    // add dock
    for (int i = 0; i < dock.size() - 1; i++) {
        splitDockWidget(dock[i], dock[i + 1], orientation);
    }
    // layout
    resizeDocks(dock, size, orientation);
}
