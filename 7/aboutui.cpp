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
    // triangle btn
    // setIcon, 正常比例
    ui->btn_1->setIcon(QIcon(":/img/triangle.png"));
    // border-image, 图片拉伸了
    // ui->btn_1->setStyleSheet("QPushButton{"
    //                          "border-image: url(:/img/triangle.png)"
    //                          "}");
    connect(ui->btn_1, &QPushButton::released, this, []() {
        // ...
        qDebug() << "btn_1 is released.";
    });

    // radius
    ui->w_1->setStyleSheet("QWidget{"
                           "border-radius: 20px;"
                           "background-color: rgb(170, 255, 255); "
                           "}");
}
