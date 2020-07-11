#include "addressbook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 实例化 QApplication 对象 app
    //。QApplication 负责管理多种应用范围的资源（如默认 字体和光标），以及运行事件循环。
    //因此，在每个使用 Qt 的 GUI 应用程序中 都会有一个 QApplication 对象。
    QApplication app(argc, argv);

    AddressBook *addressBook = new AddressBook;
    addressBook->show();


    //show()该 widget 只有在应用程序事件循环开始时 才会显示。
    //我们通过调用应用程序的 exec() 函数开始事件循环
    return app.exec();
}
