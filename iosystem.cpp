/*****************************************************
This file implements the input/output system of
the library management system.
Namespace: Nios;

*****************************************************/
#ifndef DEF_IOSYSTEM
#define DEF_IOSYSTEM

namespace Nios
{
    
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
        time_str = buf;
        return time_str;
	}
	
	string SysInfEncry(const string &originStr)
	{
		string encriedStr = originStr;
		int lengthOfStr = originStr.length();
		for (int i = 0; i < lengthOfStr; ++i) encriedStr[i] = encriedStr[i] ^ constOfKey;
		return encriedStr;
	}
	
	string SysInfDecry(const string &encriedStr)
	{
		string originStr = encriedStr;
		int lengthOfStr = encriedStr.length();
		for (int i = 0; i < lengthOfStr; ++i) originStr[i] = originStr[i] ^ constOfKey;
		return originStr;
	}
	
	int CypInit()
	{
		
	}
	
	int RefreshUserSys(const Nusers :: TUsers &inProgressLib)
	{
		
	}
	
	int InitUserSys(TUsers &inProgressLib)
	{
		
	}
}

#endif