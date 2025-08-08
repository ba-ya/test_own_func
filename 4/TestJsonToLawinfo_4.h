#ifndef TESTJSONTOLAWINFO_4_H
#define TESTJSONTOLAWINFO_4_H

#include "parameter_tof_json.h"
#include <QWidget>

namespace Ui {
class TestJsonToLawinfo_4;
}

class TestJsonToLawinfo_4 : public QWidget
{
    Q_OBJECT

public:
    explicit TestJsonToLawinfo_4(QWidget *parent = nullptr);
    ~TestJsonToLawinfo_4();

    void init();

private slots:
    void on_btn_create_released();
    void load_file();

private:
    QString create_id_trans(int pair);
    void fill_table(int cnt_beam, int cnt_id_trans);

    void push_data(QByteArray data);

private:
    Ui::TestJsonToLawinfo_4 *ui;
    TofJsonManger manger;
};

#endif // TESTJSONTOLAWINFO_4_H
