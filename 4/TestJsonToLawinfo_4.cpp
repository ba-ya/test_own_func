#include "TestJsonToLawinfo_4.h"
#include "ui_TestJsonToLawinfo_4.h"
#include "parameter_tof_json.h"
#include <QFileDialog>
#include <QJsonArray>
#include <random>

TestJsonToLawinfo_4::TestJsonToLawinfo_4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestJsonToLawinfo_4)
{
    ui->setupUi(this);
    setWindowTitle("TestJsonToLawinfo_4");
    init();
}

TestJsonToLawinfo_4::~TestJsonToLawinfo_4()
{
    delete ui;
}

void TestJsonToLawinfo_4::init()
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

    // load
    auto act = new QAction();
    act->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
    ui->lineEdit_load->addAction(act, QLineEdit::TrailingPosition);
    connect(act, &QAction::triggered, this, &TestJsonToLawinfo_4::load_file);

    // init
    ui->spinBox_cnt_beam->setValue(12);
    ui->spinBox_cnt_id_trans->setValue(3);
}

void TestJsonToLawinfo_4::on_btn_create_released()
{
    QJsonObject root;
    auto cnt_group = 1;
    for (int i = 0; i < cnt_group; ++i) {
        auto cnt_beam = ui->table->rowCount();;
        QJsonObject group_obj;
        for (int j = 0; j < cnt_beam; ++j) {
            QJsonArray beam_array;
            auto parts = ui->table->item(j, 1)->text().split(";");
            auto cnt_id_trans = parts.size() - 1;
            for (int k = 0; k < cnt_id_trans; k++) {
                auto k_value = parts[k].toInt();
                QJsonObject id_trans_obj;
                id_trans_obj[QString("id_trans %1").arg(k)] = k_value;
                beam_array.push_back(id_trans_obj);
            }
            group_obj[QString("beam %1").arg(j)] = beam_array;
        }
        root[QString("group %1").arg(i)] = group_obj;
    }
    QJsonDocument doc(root);
    auto bytes = doc.toJson();
    push_data(bytes);
}

void TestJsonToLawinfo_4::load_file()
{
    auto file_path = QFileDialog::getOpenFileName(this, tr("Files"), QDir::currentPath(), "*.*");
    if (file_path.isEmpty()) {
        return;
    }
    ui->lineEdit_load->setText(file_path);
    auto data = manger.load_from_file(file_path);
    push_data(data);
}

QString TestJsonToLawinfo_4::create_id_trans(int pair)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 99);
    QString info;
    for (int i = 0; i < pair; i++) {
        info += QString("%1;").arg(dist(gen));
    }
    return info;
}

void TestJsonToLawinfo_4::fill_table(int cnt_beam, int cnt_id_trans)
{
    ui->table->setRowCount(cnt_beam);
    for (int i = 0; i < ui->table->rowCount(); ++i) {
        ui->table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        auto info = create_id_trans(cnt_id_trans);
        ui->table->setItem(i, 1, new QTableWidgetItem(info));
    }
}

void TestJsonToLawinfo_4::push_data(QByteArray data)
{
    auto data_0 = data.mid(0, data.size() / 2);
    auto data_1 = data.mid(data.size() / 2, data.size() / 2);
    manger.push_data(11, data_1);
    manger.push_data(10, data_0);
    manger.completed();
}
