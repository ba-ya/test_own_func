#include "headers.h"
#include <QApplication>

#define test4

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef test4
    // sdk, 解析json格式的tof,并设置到lawinfo里面
    func4 w;
    w.show();
#endif

#ifdef test00
    /// func4, console
    /// 左边"项目"-"运行"-勾选"在终端中运行"
    QTextStream input(stdin);
    QString line;

    qDebug() << "Please enter commands like: t:";
    qDebug() << "Type 'exit' or 'q' to quit.";
    while (true) {
        line = input.readLine();  // 读取一行输入

        if (line.trimmed() == "exit" || line.trimmed() == "q") {
            break;  // 如果用户输入 'exit'，退出程序
        }

    }
#endif

#ifdef test3
    /// func 3, dock_widget, only mainwindow can use
    func3 w;
    w.show();
#endif

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
