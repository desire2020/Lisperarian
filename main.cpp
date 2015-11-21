/****************************************
这里是主程序，负责将已经实现的各模块有机
组合起来。
两种不同的错误返回值的说明：
-1 ：系统错误，可能是由于指定了不合法或不
存在的操作对象
-2 ：操作流程中错误，这可能是由于密码有错
或两次密码输入不一致等等
****************************************/
#include "stdincs.hpp"
#include "classes.hpp"
#include "constants.hpp"
#include "interface.hpp"
MainWindow *www;

int main(int argc, char *argv[])
{
    int p;
    Initialization();
    QApplication a(argc, argv);
    MainWindow w;
    www = &w;
    w.show();
	p = a.exec();
    Finalization();
	return p;
}
