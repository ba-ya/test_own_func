#include "func1.h"
#include "func2.h"

#include <QApplication>

#define test2

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef test2
    /// func 2, 端口设置30003,接收QbyteArray,转成int,再显示到textBrower
    func2 w;
    w.show();
#endif

#ifdef test1
    // func 1, 提取硬件板前两位信息,与设置孔径进行比较,看是否合格
    MainWindow w;
    w.show();
#endif

    return a.exec();
}
