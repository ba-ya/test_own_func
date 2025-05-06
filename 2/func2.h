#ifndef FUNC2_H
#define FUNC2_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class func2;
}

class func2 : public QWidget
{
    Q_OBJECT

public:
    explicit func2(QWidget *parent = nullptr);
    ~func2();

private slots:
    // void on_input_valueChanged(int arg1);
    void read_msg();

private:
    int data_to_int(QByteArray data);

private:
    Ui::func2 *ui;
    QUdpSocket socket;
};

#endif // FUNC2_H
