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

private:
    Ui::TestUdpHeart_2 *ui;
    QUdpSocket socket;
};

#endif // TESTUDPHEART_2_H
