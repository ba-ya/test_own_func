#ifndef FUNC1_H
#define FUNC1_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_board_type_currentTextChanged(const QString &board_type);
    void on_ap_valueChanged(int apeture);

private:
    void check_apeture(const QString &board_type, int apeture);

private:
    Ui::MainWindow *ui;
};
#endif // FUNC1_H
