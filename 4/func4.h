#ifndef FUNC4_H
#define FUNC4_H

#include "parameter_tof_json.h"
#include <QWidget>

namespace Ui {
class func4;
}

class func4 : public QWidget
{
    Q_OBJECT

public:
    explicit func4(QWidget *parent = nullptr);
    ~func4();

    void init();

private slots:
    void on_btn_create_released();

private:
    QString create_id_trans(int pair);
    void fill_table(int cnt_beam, int cnt_id_trans);

private:
    Ui::func4 *ui;
    TofJsonManger manger;
};

#endif // FUNC4_H
