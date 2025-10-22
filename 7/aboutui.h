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

private:
    Ui::AboutUI *ui;
};

#endif // ABOUTUI_H
