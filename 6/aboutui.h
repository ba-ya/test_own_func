#ifndef ABOUTUI_H
#define ABOUTUI_H

#include <QWidget>

namespace Ui {
class AboutUI;
}

class AboutUI : public QWidget
{
    Q_OBJECT

public:
    explicit AboutUI(QWidget *parent = nullptr);
    ~AboutUI();

private:
    void init();
    void _1_triangle_btn();
    void _2_radius();
    void _3_hover_press_exit();

private:
    Ui::AboutUI *ui;
};

#endif // ABOUTUI_H
