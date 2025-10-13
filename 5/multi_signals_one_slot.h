#ifndef MULTI_SIGNALS_ONE_SLOT_H
#define MULTI_SIGNALS_ONE_SLOT_H

#include <QPushButton>
#include <QWidget>

namespace Ui {
class MultiSignalsOneSlot;
}

class Btn1 : public QPushButton
{
    Q_OBJECT
public:
    explicit Btn1(QWidget *parent = nullptr) : QPushButton(parent) {}
    ~Btn1() {};
signals:
    void trig_signal(int type);
};

class MultiSignalsOneSlot : public QWidget
{
    Q_OBJECT

public:
    explicit MultiSignalsOneSlot(QWidget *parent = nullptr);
    ~MultiSignalsOneSlot();

signals:
    void trig_signal(int type);

private slots:
    void on_btn_1_released();
    void on_btn_2_released();
    void do_something(int type);

    void on_btn_clear_released();

private:
    Ui::MultiSignalsOneSlot *ui;
};

#endif // MULTI_SIGNALS_ONE_SLOT_H
