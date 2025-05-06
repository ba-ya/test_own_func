#include "func1.h"
#include "./ui_func1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_board_type_currentTextChanged(const QString &board_type)
{
    check_apeture(board_type, ui->ap->value());
}

void MainWindow::on_ap_valueChanged(int apeture)
{
    check_apeture(ui->board_type->currentText(), apeture);
}

void MainWindow::check_apeture(const QString &board_type, int apeture)
{
    int board_ap = board_type.left(2).toInt();
    bool is_valid = apeture <= board_ap;
    ui->flag->setChecked(is_valid);
    qDebug() << "board_apeture:" << board_ap << "apeture:" << apeture << "valid:" << is_valid;
    return;
}

