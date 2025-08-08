#ifndef TESTAPERTURECHECK_1_H
#define TESTAPERTURECHECK_1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class TestApertureCheck_1;
}
QT_END_NAMESPACE

class TestApertureCheck_1 : public QMainWindow
{
    Q_OBJECT

public:
    TestApertureCheck_1(QWidget *parent = nullptr);
    ~TestApertureCheck_1();

private slots:
    void on_board_type_currentTextChanged(const QString &board_type);
    void on_ap_valueChanged(int apeture);

private:
    void check_apeture(const QString &board_type, int apeture);

private:
    Ui::TestApertureCheck_1 *ui;
};
#endif // TESTAPERTURECHECK_1_H
