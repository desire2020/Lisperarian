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
    int log_type;
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
        printf("%s%s", buf, "    ");
    }
    
    /*-------------------------------------*
     * 函数 : Log_Record(int log_type, char[] id1, char[]id2)
     * 功能 : 日志信息接受、处理、输出
     *-------------------------------------*/
    
    void Log_Record(int log_type, char id1[], char id2[])
    {
        TimeString();
        switch (log_type) {
            case 0:
                printf("%s%s%s%s","UserID : ", id1, "    ", "Registration Completed");
                break;
            case 1:
                printf("%s%s%s%s","UserID : ", id1, "    ", "Login Completed");
                break;
            case 2:
                printf("%s%s%s%s","UserID : ", id1, "    ", "Logout Completed");
                break;
            case 3:
                printf("%s%s%s%s%s","ISBN : ", id1, "    is borrowed by   ","UserID : ", id2);
                break;
            case 4:
                printf("%s%s%s%s%s","ISBN : ", id1, "    is returned by   ","UserID : ", id2);
                break;
            case 5:
                if (!strcmp(id1,id2))
                    printf("%s%s%s%s%s","UserID : ", id1, "    Nickname is changed by   ","UserID : ", id2);
                else
                    printf("%s%s%s%s%s","UserID : ", id1, "    Nickname is changed by   ","AdminID : ", id2);
                break;
            case 6:
                if (!strcmp(id1,id2))
                    printf("%s%s%s%s%s","UserID : ", id1, "    Passward is changed by   ","UserID : ", id2);
                else
                    printf("%s%s%s%s%s","UserID : ", id1, "    Passward is changed by   ","AdminID : ", id2);
                break;
            case 7:
                printf("%s%s%s%s%s","ISBN : ", id1, "    is added by   ","AdminID : ", id2);
                break;
            case 8:
                printf("%s%s%s%s%s","ISBN : ", id1, "    is deleted by   ","AdminID : ", id2);
                break;
            case 9:
                printf("%s%s%s%s%s","ISBN : ", id1, "    is set by   ","AdminID : ", id2);
                break;
            case 10:
                printf("%s%s%s%s%s","UserID : ", id1, "    is deleted by   ","AdminID : ", id2);
                break;
            case 11:
                printf("%s%s%s%s%s","UserID : ", id1, "    UserMode is changed by   ","AdminID : ", id2);
                break;
                
        }
        printf("\n");
    }
}

