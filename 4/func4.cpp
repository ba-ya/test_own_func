#include "func4.h"
#include "ui_func4.h"
#include "parameter_tof_json.h"
#include <random>

func4::func4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::func4)
{
    ui->setupUi(this);
    init();
}

func4::~func4()
{
    delete ui;
}

void func4::init()
{
    ui->table->setColumnCount(2);
    ui->table->setHorizontalHeaderLabels({"beam id", "values"});
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->spinBox_cnt_beam->setValue(4);
    ui->spinBox_cnt_id_trans->setValue(5);
    fill_table(ui->spinBox_cnt_beam->value(), ui->spinBox_cnt_id_trans->value());
    connect(ui->spinBox_cnt_beam, &QSpinBox::valueChanged, this, [this](int cnt_beam) {
        auto cnt_id_trans = ui->spinBox_cnt_id_trans->value();
        fill_table(cnt_beam, cnt_id_trans);
    });
    connect(ui->spinBox_cnt_id_trans, &QSpinBox::valueChanged, this, [this](int cnt_id_trans) {
        auto cnt_beam = ui->spinBox_cnt_beam->value();
        fill_table(cnt_beam, cnt_id_trans);
    });
}

void func4::on_btn_create_released()
{
    QJsonObject root;
    auto cnt_group = 1;
    for (int i = 0; i < cnt_group; ++i) {
        auto cnt_beam = ui->table->rowCount();;
        QJsonObject group_obj;
        for (int j = 0; j < cnt_beam; ++j) {
            QJsonObject beam_obj;
            auto parts = ui->table->item(j, 1)->text().split(";");
            auto cnt_id_trans = parts.size() - 1;
            for (int k = 0; k < cnt_id_trans; k++) {
                auto id_trans = parts[k].split(":");
                auto k_id = id_trans.first();
                auto k_value = id_trans.last().toInt();
                beam_obj[QString("id trans %1").arg(k_id)] = k_value;
            }
            group_obj[QString("beam %1").arg(j)] = beam_obj;
        }
        root[QString("group %1").arg(i)] = group_obj;
    }
    QJsonDocument doc(root);
    auto bytes = doc.toJson();
    auto data_0 = bytes.mid(0, bytes.size() / 2);
    auto data_1 = bytes.mid(bytes.size() / 2, bytes.size() / 2);
    manger.push_data(11, data_1);
    manger.push_data(10, data_0);
    manger.completed();
}

QString func4::create_id_trans(int pair)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);
    QString info;
    for (int i = 0; i < pair; i++) {
        info += QString("%1:%2;").arg(i).arg(dist(gen));
    }
    return info;
}

void func4::fill_table(int cnt_beam, int cnt_id_trans)
{
    ui->table->setRowCount(cnt_beam);
    for (int i = 0; i < ui->table->rowCount(); ++i) {
        ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        auto info = create_id_trans(cnt_id_trans);
        ui->table->setItem(i, 1, new QTableWidgetItem(info));
    }
}
