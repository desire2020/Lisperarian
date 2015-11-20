/*****************************************************
This file implements the input/output system of
the library management system.
Namespace: Nios;

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
        strftime(buf, 64, "%Y %m %d", local);
        time_str = buf;
        return time_str;
    }

	Nusers :: TTime PresentTime()
	{
		time_t second;
        tm* local; //本地时间
		static Nusers :: TTime preTime;
        
        second = time(NULL); //获取目前秒时间
        local = localtime(&second); //转为本地时间
        
		preTime.year = local -> tm_year + 1900;
		preTime.month = local -> tm_month + 1;
		preTime.day = local -> tm_mday;
        
        return preTime;
	}
    
	string SysInfEncry(const string &originStr)
	{
		static string encriedStr = originStr;
		for (int i = 0; i < encriedStr.length(); i++)
		{
			encriedStr[i] ^= easyKey;
		}
		return encriedStr;
	}
	
	string SysInfDecry(const string &encriedStr)
	{
		static string originStr = encriedStr;
		for (int i = 0; i < originStr.length(); i++)
		{
			originStr[i] ^= easyKey;
		}
		return originStr;	
	}
	
	
}

#endif
