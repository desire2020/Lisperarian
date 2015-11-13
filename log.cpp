//
//  log.cpp
//  
//
//  Created by 盛佩瑶 on 15/11/11.
//
//

#include <stdincs.hpp>
using namespace Nlog;

/***************************************
 This is a
 param level 1: DEBUG
             2: INFO
             3: WARN
             4: ERROR
 param logCtrol 0000 1: open 0: close
 ***************************************/

//日志信息读入
void Log_Read(int log_type, string id_1, string id_2);

//日志信息处理
void Log_Debug(const char *pszFmt, ...);

/*-------------------------------------*
 * 功能 : 将当前系统时间转换为 string 字符串*
 *-------------------------------------*
 * 函数 : TimeString
 * 返回 : 
 *-------------------------------------*/
void TimeString()
{
    time_t second;
    tm* local; //本地时间
    tm* gmt;   //格林威治时间
    char buf[128]= {0};
    
    second = time(NULL); //获取目前秒时间
    local = localtime(&second); //转为本地时间
    strftime(brf, 64, "%Y-%m-%d %H:%M:%S", local);
    cout << buf << endl;
    
    gmt = gmtime(&t);//转为格林威治时间
    strftime(buf, 64, "%Y-%m-%d %H:%M:%S", gmt);
    cout << buf << std;
}

