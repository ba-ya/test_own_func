#ifndef TESTUDPHEART_2_H
#define TESTUDPHEART_2_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class TestUdpHeart_2;
}

class TestUdpHeart_2 : public QWidget
{
    Q_OBJECT

public:
    explicit TestUdpHeart_2(QWidget *parent = nullptr);
    ~TestUdpHeart_2();

private slots:
    void read_msg();

    void on_btn_send_released();

private:
    Ui::TestUdpHeart_2 *ui;
    QUdpSocket socket;
    QUdpSocket socket_send;
    int cnt = 0;
};

#endif // TESTUDPHEART_2_H
