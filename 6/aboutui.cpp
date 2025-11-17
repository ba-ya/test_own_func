#include "aboutui.h"
#include "ui_aboutui.h"

AboutUI::AboutUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutUI)
{
    ui->setupUi(this);
    init();
}

AboutUI::~AboutUI()
{
    delete ui;
}

void AboutUI::init()
{
    _1_triangle_btn();
    _2_radius();
    _3_hover_press_exit();
}

void AboutUI::_1_triangle_btn()
{
#if 1
    // setIcon, 正常比例
    ui->btn_1->setIcon(QIcon(":/img/triangle.png"));
#else
    // border-image, 图片拉伸了
    ui->btn_1->setStyleSheet("QPushButton{"
                             "image: url(:/img/triangle.png)"
                             "}");
#endif
    connect(ui->btn_1, &QPushButton::released, this, []() {
        // ...
        qDebug() << "btn_1 is released.";
    });
}

void AboutUI::_2_radius()
{
    ui->w_1->setStyleSheet("QWidget{"
                           "border-radius: 20px;"
                           "background-color: rgb(170, 255, 255); "
                           "}");
}

void AboutUI::_3_hover_press_exit()
{
    QString qss = "QPushButton{"
                  "background-color: rgb(170, 255, 255);"
                  "}"
                  "QPushButton::hover{"
                  "background-color: pink;"
                  "image:url(:/img/triangle.png);"
                  "}"
                  "QPushButton::pressed{"
                  "background-color: red;"
                  "image: none;"
                  "}";
    ui->btn_2->setStyleSheet(qss);
}
