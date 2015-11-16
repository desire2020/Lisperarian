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
#include "stdincs.h"
#include <ctime>
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <fstream>
namespace Nlog
{
    int Event;
    char buf[128]= {0};
    
    /*-------------------------------------*
     * 函数 : TimeString()
     * 功能 : 将当前系统时间转换为字符串,并输出
     *-------------------------------------*/
    
    void TimeString()
    {
        time_t second;
        tm* local; //本地时间
        
        second = time(NULL); //获取目前秒时间
        local = localtime(&second); //转为本地时间
        strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
        fout << buf << "    ";
    }
    
    /*-------------------------------------*
     * 函数 : RecordEvent(int Event, long long ID1<< long long ID2
     * 功能 : 日志信息接受、处理、输出
     *-------------------------------------*/
    
    void RecordEvent(int Event, long long ID1, long long ID2)
    {
        fout.open("syslog.log");
        TimeString();
        switch (Event) {
            case 0:
                fout<<"UserID : "<< ID1<<"    "<<"Registration Completed";
                break;
            case 1:
                fout<<"UserID : "<< ID1<< "    "<< "Login Completed";
                break;
            case 2:
                fout<<"UserID : "<< ID1<< "    "<< "Logout Completed";
                break;
            case 3:
                fout<<"ISBN : "<< ID1<< "    is borrowed by   "<<"UserID : "<< ID2;
                break;
            case 4:
                fout<<"ISBN : "<< ID1<< "    is returned by   "<<"UserID : "<< ID2;
                break;
            case 5:
                if (ID1 != ID2)
                    fout<<"UserID : "<< ID1<< "    Nickname is changed by   "<<"UserID : "<< ID2;
                else
                    fout<<"UserID : "<< ID1<< "    Nickname is changed by   "<<"AdminID : "<< ID2;
                break;
            case 6:
                if (ID1 != ID2)
                    fout<<"UserID : "<< ID1<< "    Passward is changed by   "<<"UserID : "<< ID2;
                else
                    fout<<"UserID : "<< ID1<< "    Passward is changed by   "<<"AdminID : "<< ID2;
                break;
            case 7:
                fout<<"ISBN : "<< ID1<< "    is added by   "<<"AdminID : "<< ID2;
                break;
            case 8:
                fout<<"ISBN : "<< ID1<< "    is deleted by   "<<"AdminID : "<< ID2;
                break;
            case 9:
                fout<<"ISBN : "<< ID1<< "    is set by   "<<"AdminID : "<< ID2;
                break;
            case 10:
                fout<<"UserID : "<< ID1<< "    is deleted by   "<<"AdminID : "<< ID2;
                break;
            case 11:
                fout<<"UserID : "<< ID1<< "    UserMode is changed by   "<<"AdminID : "<< ID2;
                break;
                
        }
        fout<<"\n";
        fout.close();
    }
}

