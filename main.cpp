#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // 窗口背景颜色
    w.setAutoFillBackground(true);
    w.setPalette(QPalette(QColor(223,233,245)));

    // 窗口尺寸 分辨率 自适应


    w.show();
    return a.exec();
}
