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
        return preTime;
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
	
	string NumStr(long long userID)
	{
		string p = "";
		while (userID > 0) {
			p = char(userID % 10 + '0') + p;
			userID /= 10;
		}
		return p;
	}
	
	char *SearchingFile(string s1 , long long userID , string s3) 
	{
		string s2 = NumStr(userID);
		string ss = s1 + s2 + s3;
		char str[30];
		int len = ss.length();
		for (int i = 0; i < len; ++i) str[i] = ss[i]; str[len] = '\0';
		return str;
	}
	
	int PrintTheFileOfInf(Tuser temp)
	{
		ofstream theFile(SearchingFile("usersInf\\" , NumStr(temp.userUID) , ".log"));
			theFile << SysInfEncry(Number(temp.userID)) << endl;
			theFile << SysInfEncry(temp.userNickname) << endl;
			theFile << SysInfEncry(temp.userPassword) << endl;
			theFile << SysInfEncry(temp.authority) << endl;
			theFile << SysInfEncry(temp.privateInf.realName) << endl;
			theFile << SysInfEncry(temp.privateInf.telephoneNumber) << endl;
			theFile << SysInfEncry(temp.privateInf.identificationNumber) << endl;
		theFile.close();
		return 0;
	}
	
	int PrintTheFileOfOccupiedBooks(TUser temp) 
	{
		ofstream theFile(SearchingFile("usersOccupiedBooks\\" , NumStr(temp.userUID) , ".log"));
			set<long long> :: iterator it;
			for (it = temp.occupiedBooks.begin(); it != temp.occupiedBooks.end(); ++it)
			{
				theFile << *it << endl;
			}
		theFile.close();
		return 0;
	}
	
	int CypInit()
	{
		
	}
	
	int RefreshUserSys(const Nusers :: TUsers &inProgressLib)
	{
		TInnerStruct :: iterator it;
		for (it = inProgressLib.UIDTree.begin(); it != inProgressLib.UIDTree.end(); ++it) 
		{
			PrintTheFileOfInf(*it);
			PrintTheFileOfOccupiedBooks(*it);
		}
		return 0;
	}
	
	int InitUserSys(TUsers &inProgressLib)
	{
		
	}
}

#endif