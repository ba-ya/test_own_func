#include "multi_signals_one_slot.h"
#include "ui_multi_signals_one_slot.h"

MultiSignalsOneSlot::MultiSignalsOneSlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiSignalsOneSlot)
{
    ui->setupUi(this);
    connect(this, &MultiSignalsOneSlot::trig_signal, this, &MultiSignalsOneSlot::do_something);
    Qt::ConnectionType connect_type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    connect(ui->btn_1, &Btn1::trig_signal, this, &MultiSignalsOneSlot::do_something);
    connect(ui->btn_1, &Btn1::trig_signal, this, &MultiSignalsOneSlot::do_something, connect_type);
    qDebug() << ui->btn_1->objectName() << this->objectName();
}

MultiSignalsOneSlot::~MultiSignalsOneSlot()
{
    delete ui;
}

void MultiSignalsOneSlot::on_btn_1_released()
{
    emit ui->btn_1->trig_signal(1);
}

void MultiSignalsOneSlot::on_btn_2_released()
{
    emit trig_signal(2);
}

void MultiSignalsOneSlot::do_something(int type)
{
    ui->info->append("--------------------");
    ui->info->append(QString("type: %1").arg(type));
    QString sender = "name:" + this->sender()->objectName();
    ui->info->append(sender);
}

void MultiSignalsOneSlot::on_btn_clear_released()
{
    ui->info->clear();
}

