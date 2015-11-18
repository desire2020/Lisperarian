/*****************************************************
This header file implements the input/output system of
the library management system.
Namespace: Nios;

Headfile flag: DEF_IOSYSTEM;
*****************************************************/
#ifndef DEF_IOSYSTEM
#define DEF_IOSYSTEM

namespace Nios{
    
    /*-------------------------------------*
     * 函数 : SysDateStr()
     * 功能 : 将当前系统时间转换为字符串
     *-------------------------------------*/
    
    string SysDateStr()
    {
        char buf[128]= {0};
        static string time_str;
        time_t second;
        tm* local; //本地时间
        
        second = time(NULL); //获取目前秒时间
        local = localtime(&second); //转为本地时间
        strftime(buf, 64, "%Y-%m-%d %H:%M:%S", local);
        time_str = buf;
        return time_str;
    }

    
}

#endif