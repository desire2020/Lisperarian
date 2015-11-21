/*****************************************************
This file implements the input/output system of
the library management system.
Namespace: Nios;

*****************************************************/
#ifndef DEF_IOSYSTEM
#define DEF_IOSYSTEM
#define currentDir string("D:\\")
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
		preTime.yday = local -> tm_yday;
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
    long long StrNum(string str)
	{
		long long num = 0;
		int lengthOfStr = str.length();
		for (int i = 0; i < lengthOfStr; ++i) num = num * (long long)10 + str[i] - '0';
		return num;
	}
	
    int PrintTheFileOfInf(TUser temp)
	{
        ofstream theFile((currentDir + "users\\usersInf\\" + NumStr(temp.userID) + ".log").c_str());
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
        ofstream theFile((currentDir + "users\\usersOccupiedBooks\\" + NumStr(temp.userID) + ".log").c_str());
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
	
    int ScanTheUIDInf(long long userID, Nusers :: TUsers &inProgressLib)
	{
        ifstream theFile((currentDir + "users\\usersInf\\" + NumStr(userID) + ".log").c_str());
		{
			if (!theFile) return -1;
			string str;
            getline(theFile, str); inProgressLib.UIDTree[userID].userID = StrNum(SysInfDecry(str));
            getline(theFile, str); inProgressLib.UIDTree[userID].userNickname = SysInfDecry(str);
            getline(theFile, str); inProgressLib.UIDTree[userID].userPassword = SysInfDecry(str);
            getline(theFile, str); inProgressLib.UIDTree[userID].authority = StrNum(SysInfDecry(str));
            getline(theFile, str); inProgressLib.UIDTree[userID].privateInf.realName = SysInfDecry(str);
            getline(theFile, str); inProgressLib.UIDTree[userID].privateInf.telephoneNumber = StrNum(SysInfDecry(str));
            getline(theFile, str); inProgressLib.UIDTree[userID].privateInf.identificationNumber = SysInfDecry(str);
		}
		theFile.close();
		return 0;
	}
	
    int ScanTheUIDOccupiedBooks(long long userID, Nusers :: TUsers &inProgressLib)
	{
        ifstream theFile((currentDir + "users\\usersOccupiedBooks\\" + NumStr(userID) + ".log").c_str());
		{
			if (!theFile) return -1;
			long long tgISBN;
            while (theFile >> tgISBN)
			{
                inProgressLib.UIDTree[userID].occupiedBooks.insert(tgISBN);
			}
		}
		theFile.close();
		return 0;
	}
	
	int PrintUserSysRecordBorrow(long long userID, long long ISBN, Nusers :: TTime preTime)
	{
        ofstream theFile((currentDir + "users\\usersRB\\" + NumStr(userID) + ".log").c_str(), ios :: app);
            theFile << "用户ID：" << userID << "  借书" << endl;
            theFile << "    书籍ISBN：" << ISBN;
			theFile << "    日期：" << preTime.year << "." << preTime.month << "." << preTime.day << endl;
		theFile.close();
		return 0;
	}
	
	int PrintUserSysRecordReturn(long long userID, long long ISBN, Nusers :: TTime preTime)
	{
        ofstream theFile((currentDir + "users\\usersRB\\" + NumStr(userID) + ".log").c_str(), ios :: app);
		{
            theFile << "用户ID：" << userID << "  还书" << endl;
            theFile << "    书籍ISBN：" << ISBN;
			theFile << "    日期：" << preTime.year << "." << preTime.month << "." << preTime.day << endl;
		}
		theFile.close();
		return 0;
	}
	
    int RefreshUserSys(Nusers :: TUsers &inProgressLib)
	{
        ofstream theFile((currentDir + "users\\globalvar.ini").c_str());
		{
            theFile << presentUID << endl;
		}
        theFile.close();
        Nusers :: TInnerStruct :: iterator it;
		for (it = inProgressLib.UIDTree.begin(); it != inProgressLib.UIDTree.end(); ++it) 
		{
            PrintTheFileOfInf(it -> second);
            PrintTheFileOfOccupiedBooks(it -> second);
        }


		return 0;
	}
	
    int InitUserSys(Nusers :: TUsers &inProgressLib)
	{
        fstream theFile((currentDir + "users\\globalvar.ini").c_str(), ios :: in);
		if (!theFile)
		{
            theFile.open((currentDir + "users\\globalvar.ini").c_str(), ios :: out);
            presentUID = Nusers :: INITOFSUM;
            theFile << presentUID << endl;
			theFile.close();
			return 0;
		}
		else
		{
            theFile >> presentUID;
		}
		theFile.close();
        inProgressLib.UIDTree.clear();
        for (long long i = Nusers :: INITOFSUM; i <= presentUID; ++i)
		{
            ifstream it((currentDir + "users\\usersInf\\" + NumStr(i) + ".log").c_str());
			{
				if (!it) continue;
			}
			it.close();
            ScanTheUIDInf(i, inProgressLib);
            ScanTheUIDOccupiedBooks(i, inProgressLib);
		}
        return 0;
	}
    int InitBookSys(Nlibrary :: TLibrary &inProgressLib)
    {
        fstream theFile((currentDir + "library\\Book.db").c_str(), ios :: in);
		if (!theFile)
		{
            theFile.open((currentDir + "library\\Book.db").c_str(), ios :: out);
			theFile.close();
			return 0;
		}
		Nlibrary :: TBook inProgressBook;
		while(!theFile.eof())
		{
			long long ll;
			getline(theFile, inProgressBook.title);
            if (theFile.eof())
                return 0;
			theFile >> inProgressBook.ISBN;
			getline(theFile, inProgressBook.author);
			getline(theFile, inProgressBook.description);
            theFile >> inProgressBook.avaliableNum;
            theFile >> inProgressBook.lowerBoundOfAuthority;
			do
			{
				theFile >> ll;
				if (ll != -1)
				{
					inProgressBook.occupyingUsers.insert(ll);
				}
			}
			while (ll != -1);
            inProgressLib.AddBook(inProgressBook, Nusers :: INITOFSUM);
		}
		theFile.close();
		return 0;
    }
	int PrintOneSpecificBook(fstream &fout, Nlibrary :: TBook &targetBook)
	{
		fout << targetBook.title << endl;
		fout << targetBook.ISBN << endl;
		fout << targetBook.author << endl;
		fout << targetBook.description << endl;
		fout << targetBook.avaliableNum << endl;
		fout << targetBook.lowerBoundOfAuthority << endl;
		set<long long> :: iterator it;
		for (it = targetBook.occupyingUsers.begin(); it != targetBook.occupyingUsers.end(); it++)
		{
			fout << *it << endl;
		}
		fout << -1 << endl;
        return 0;
	}
	int RefreshBookSys(Nlibrary :: TLibrary &inProgressLib)
	{
        fstream theFile((currentDir + "library\\Book.db").c_str(), ios :: out);
		Nlibrary :: TInnerStruct :: iterator it;
		for (it = inProgressLib.ISBNTree.begin(); it != inProgressLib.ISBNTree.end(); it++)
		{
            PrintOneSpecificBook(theFile, it -> second);
		}
		theFile.close();
		return 0;
	}
	long long GetNum()
	{
        long long GottenInt = queueNum.front();
        queueNum.pop();
		return GottenInt;
	}
	string GetLine()
	{
        string GottenStr = queueStr.front();
        queueStr.pop();
		return GottenStr;
	}	
	int ShowBookRequired()
	{
		return 0;
	}
    void ErrorInvalidTarget(MainWindow &w)
	{
        QMessageBox :: warning(&w, "警告", "操作对象错误!!!", QMessageBox::Yes);
	}
    void ErrorIncorrectOperation(MainWindow &w)
	{

	}
	int Welcome(const string &nickname)
	{
		return 0;
	}
}
#endif
