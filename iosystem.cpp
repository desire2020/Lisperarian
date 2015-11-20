/*****************************************************
This file implements the input/output system of
the library management system.
Namespace: Nios;

*****************************************************/
#ifndef DEF_IOSYSTEM
#define DEF_IOSYSTEM
#include "stdincs.hpp"
#include "classes.hpp"
#include "constants.hpp"
#include "globalvar.hpp"
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

    TTime PresentTime()
	{
		time_t second;
        tm* local; //本地时间
		static Nusers :: TTime preTime;
        
        second = time(NULL); //获取目前秒时间
        local = localtime(&second); //转为本地时间
        
		preTime.year = local -> tm_year + 1900;
        preTime.month = local -> tm_mon + 1;
		preTime.day = local -> tm_mday;
        return preTime;
	}
	
	string SysInfEncry(const string &originStr)
	{
		string encriedStr = originStr;
		int lengthOfStr = originStr.length();
        for (int i = 0; i < lengthOfStr; ++i) encriedStr[i] = encriedStr[i] ^ easyKey;
		return encriedStr;
	}
	
	string SysInfDecry(const string &encriedStr)
	{
		string originStr = encriedStr;
		int lengthOfStr = encriedStr.length();
        for (int i = 0; i < lengthOfStr; ++i) originStr[i] = originStr[i] ^ easyKey;
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
	long long StrNum(string &str)
	{
		long long num = 0;
		int lengthOfStr = str.length();
		for (int i = 0; i < lengthOfStr; ++i) num = num * (long long)10 + str[i] - '0';
		return num;
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
	
    int PrintTheFileOfInf(TUser temp)
	{
        ofstream theFile(SearchingFile("users\\usersInf\\", temp.userID, ".log"));
        {
            theFile << SysInfEncry(NumStr(temp.userID)) << endl;
            theFile << SysInfEncry(temp.userNickname) << endl;
			theFile << SysInfEncry(temp.userPassword) << endl;
			theFile << SysInfEncry(NumStr(temp.authority)) << endl;
			theFile << SysInfEncry(temp.privateInf.realName) << endl;
			theFile << SysInfEncry(NumStr(temp.privateInf.telephoneNumber)) << endl;
			theFile << SysInfEncry(temp.privateInf.identificationNumber) << endl;
        }
        theFile.close();
		return 0;
	}
	
	int PrintTheFileOfOccupiedBooks(TUser temp) 
	{
        ofstream theFile(SearchingFile("users\\usersOccupiedBooks\\" , temp.userID , ".log"));
		{
			set<long long> :: iterator it;
			for (it = temp.occupiedBooks.begin(); it != temp.occupiedBooks.end(); ++it)
			{
				theFile << *it << endl;
			}
		}
		theFile.close();
		return 0;
	}
	
	int ScanTheUIDInf(long long userID , Nusers :: TUser &temp)
	{
        ifstream theFile(SearchingFile("users\\usersInf\\" , userID , ".log"));
		{
			if (!theFile) return -1;
			string str;
			theFile >> str; temp.userID = StrNum(SysInfDecry(str));
			theFile >> str; temp.userNickname = SysInfDecry(str);
			theFile >> str; temp.userPassword = SysInfDecry(str);
			theFile >> str; temp.authority = StrNum(SysInfDecry(str));
			theFile >> str; temp.privateInf.realName = SysInfDecry(str);
			theFile >> str; temp.privateInf.telephoneNumber = StrNum(SysInfDecry(str));
			theFile >> str; temp.privateInf.identificationNumber = SysInfDecry(str);
		}
		theFile.close();
		return 0;
	}
	
	int ScanTheUIDOccupiedBooks(long long userID , Nusers :: TUser &temp)
	{
		ifstream theFile(SearchingFile("users\\usersOccupiedBooks\\" , userID , ".log"));
		{
			if (!theFile) return -1;
			long long tgISBN;
			while (cin >> tgISBN)
			{
				temp.occupiedBooks.insert(tgISBN);
			}
		}
		theFile.close();
		return 0;
	}
	
	int PrintUserSysRecordBorrow(long long userID , long long ISBN , Nusers :: TTime preTime)
	{
        ofstream theFile(SearchingFile("users\\usersRB\\" , userID , ".log") , ios :: app);
			theFlie << "用户ID：" << userID << "  借书" << endl;
			theFile << "    书籍ISBN：" << ISNM;
			theFile << "    日期：" << preTime.year << "." << preTime.month << "." << preTime.day << endl;
		theFile.close();
		return 0;
	}
	
	int PrintUserSysRecordReturn(long long userID , long long ISBN , Nusers :: TTime preTime)
	{
		ofstream theFile(SearchingFile("users\\usersRB\\" , NumStr(userUID) , ".log") , ios :: app);
		{
			theFlie << "用户ID：" << userID << "  还书" << endl;
			theFile << "    书籍ISBN：" << ISNM;
			theFile << "    日期：" << preTime.year << "." << preTime.month << "." << preTime.day << endl;
		}
		theFile.close();
		return 0;
	}
	
	int RefreshUserSys(const Nusers :: TUsers &inProgressLib)
	{
		ofstream theFile("users\\globalvar.log");
		{
			theFile << Nusers :: presentUID << endl;
		}
		theFile.close();
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
		ifstream theFile("users\\globalvar.log");
		{
			theFile >> Nusers :: presentUID;
		}
		theFile.close();
		inProgressLib.clear();
		for (long long i = Nusers :: INITOFSUM; i <= Nusers :: presentUID; ++i)
		{
			ifstream it(SearchingFile("users\\usersInf\\" , i , ".log"));
			{
				if (!it) continue;
			}
			it.close();
			inProgressLib.UIDTree.insert(i);
			ScanTheUIDInf(i , inProgressLib.UIDTree[i]);
			ScanTheUIDOccupiedBooks(i , inProgressLib.UIDTree[i]);
		}
	}
}

#endif
