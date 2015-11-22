/*****************************
 调用说明：
 RecordEvent(int Event, long long ID1; long long ID2)
/*****************************
 日志记录类型：
 0:新用户注册。
 1:老用户登录。
 2:用户登出。
 3:借阅书籍。
 4:归还书籍。
 5:修改用户昵称。
 6:修改用户密码。
 7:添加书籍。
 8:删除书籍。
 9:设定图书属性。
 10:删除用户。
 11:改变用户状态。
 *********************************/
#include "stdincs.hpp"
#include "globalvar.hpp"
#include "constants.hpp"
#include "classes.hpp"
#define currentDir string("")
namespace Nlog
{
    
    /*-------------------------------------*
     * 函数 : RecordEvent(int Event, long long ID1<< long long ID2
     * 功能 : 日志信息接受、处理、输出
     *-------------------------------------*/
    ofstream fileLogs;
    int RecordEvent(int Event, long long ID1, long long ID2)
    {
        fileLogs.open((currentDir + "syslog.log").c_str(), ios :: app | ios :: out);
        fileLogs<<Nios::SysDateStr()<<"    ";
        switch (Event) {
            case 0:
                fileLogs<<"UserID : "<< ID1<<"    "<<"Registration Completed";
                break;
            case 1:
                fileLogs<<"UserID : "<< ID1<< "    "<< "Login Completed";
                break;
            case 2:
                fileLogs<<"UserID : "<< ID1<< "    "<< "Logout Completed";
                break;
            case 3:
                fileLogs<<"ISBN : "<< ID1<< "    is borrowed by   "<<"UserID : "<< ID2;
                break;
            case 4:
                fileLogs<<"ISBN : "<< ID1<< "    is returned by   "<<"UserID : "<< ID2;
                break;
            case 5:
                if (ID1 != ID2)
                    fileLogs<<"UserID : "<< ID1<< "    Nickname is changed by   "<<"UserID : "<< ID2;
                else
                    fileLogs<<"UserID : "<< ID1<< "    Nickname is changed by   "<<"AdminID : "<< ID2;
                break;
            case 6:
                if (ID1 != ID2)
                    fileLogs<<"UserID : "<< ID1<< "    Passward is changed by   "<<"UserID : "<< ID2;
                else
                    fileLogs<<"UserID : "<< ID1<< "    Passward is changed by   "<<"AdminID : "<< ID2;
                break;
            case 7:
                fileLogs<<"ISBN : "<< ID1<< "    is added by   "<<"AdminID : "<< ID2;
                break;
            case 8:
                fileLogs<<"ISBN : "<< ID1<< "    is deleted by   "<<"AdminID : "<< ID2;
                break;
            case 9:
                fileLogs<<"ISBN : "<< ID1<< "    is edited by   "<<"AdminID : "<< ID2;
                break;
            case 10:
                fileLogs<<"UserID : "<< ID1<< "    is deleted by   "<<"AdminID : "<< ID2;
                break;
            case 11:
                fileLogs<<"UserID : "<< ID1<< "    UserMode is changed by   "<<"AdminID : "<< ID2;
                break;
                
        }
        fileLogs<<"\n";
        fileLogs.close();
    }
}

