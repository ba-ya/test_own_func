#include "TestApertureCheck_1.h"
#include "./ui_TestApertureCheck_1.h"

TestApertureCheck_1::TestApertureCheck_1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestApertureCheck_1)
{
    ui->setupUi(this);
    setWindowTitle("TestApertureCheck_1");
}

TestApertureCheck_1::~TestApertureCheck_1 ()
{
    delete ui;
}

void TestApertureCheck_1::on_board_type_currentTextChanged(const QString &board_type)
{
    check_apeture(board_type, ui->ap->value());
}

void TestApertureCheck_1 ::on_ap_valueChanged(int apeture)
{
    check_apeture(ui->board_type->currentText(), apeture);
}

void TestApertureCheck_1 ::check_apeture(const QString &board_type, int apeture)
{
    int board_ap = board_type.mid(0, 2).toInt();
    bool is_valid = apeture <= board_ap;
    ui->flag->setChecked(is_valid);
    qDebug() << "board_apeture:" << board_ap << "apeture:" << apeture << "valid:" << is_valid;
    return;
}

