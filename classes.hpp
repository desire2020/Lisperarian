/***********************************************************
This header file declares classes used in the project.
It can also be used as a plan or catalog of the project.
***********************************************************/
#ifndef DEF_CLASSES
#define DEF_CLASSES
#include "stdincs.hpp"
namespace Nlog
{
	int RecordEvent(const int Event, long long ID1, long long ID2);
}
namespace Nlibrary
{
	struct TBook
	{
        string title;
		long long ISBN;
		string author;
		string description;
		long long avaliableNum;
		long long lowerBoundOfAuthority;
		set<long long> occupyingUsers;
	};
    typedef map<long long, TBook> TInnerStruct;
	class TLibrary
	{
    public:
		TInnerStruct ISBNTree;
		string NumStr(long long tgNum);
        int AddBook(const TBook &inPendingBook, long long userID);
		int DeleteBookByISBN(long long tgISBN, long long userID);
		int BorrowOneSpecificBook(long long tgISBN, long long userID);
		int ReturnOneSpecificBook(long long tgISBN, long long userID);
		int EditBookProperty(long long tgISBN, long long userID, const TBook &newBook);
        int SearchBook(const string &KeyWord1, const string &KeyWord2, const string &KeyWord3);
		
	};
}
namespace Nusers
{
	typedef string TPassword;
	TPassword EncryptingWithMd5(TPassword userPassword);
	struct PrivateInformation
	{
		string realName;
		long long telephoneNumber;
		string identificationNumber;
    };
	typedef pair<long long, long long> UIDandISBN;
	struct TTime 
	{
		long long year, month, day;
		long long yday;
    };
	typedef map<UIDandISBN , TTime> TInnerUIDandISBNTree;

	struct TUser
	{
		string userNickname;
		long long userID;
		TPassword userPassword;
		set<long long> occupiedBooks;
		long long authority;//it's minus when the user is banned
		PrivateInformation privateInf;
    };
	typedef map<long long, TUser> TInnerStruct;
	class TUsers
	{
    public:
		TInnerStruct UIDTree;
		int AddUser(TUser inPendingUser, long long UID);
		int DeleteUserByUID(long long tgUID, long long UID);
		bool TestPassword(long long UID, TPassword passGiven);
		TUser GetUser(long long UID);
        bool CheckUID(long long UID);
		int ChangePassword(long long UID, TPassword newPassword);
		int ChangeUserNickname(long long UID, string newNickname);
		int ChangePrivateInf(long long UID, PrivateInformation newPrivateInf);
		int BorrowOneSpecificBook(long long tgISBN, long long UID);
		int ReturnOneSpecificBook(long long tgISBN, long long UID);
		int SetUserAuthority(long long UID, long long newAuthority);
		bool KeepingTimedOut(long long UID);
    };

}
namespace Nios
{
	string SysDateStr();//yyyy mm dd
    typedef Nusers :: TTime TTime;
    typedef Nusers :: TUser TUser;
    TTime PresentTime();
	string SysInfEncry(const string &originStr);
	string SysInfDecry(const string &encriedStr);
	int GetRequest();
    string NumStr(long long userID);
    long long StrNum(string str);
	string GetLine();
	long long GetNum();
	int CypInit();
    int RefreshUserSys(Nusers :: TUsers &inProgressLib);
    int InitUserSys(Nusers :: TUsers &inProgressLib);
    int RefreshBookSys(Nlibrary :: TLibrary &inProgressLib);
    int PrintUserSysRecordBorrow(long long userID , long long ISBN , Nusers :: TTime preTime);
    int PrintUserSysRecordReturn(long long userID , long long ISBN , Nusers :: TTime preTime);
    int InitBookSys(Nlibrary :: TLibrary &inProgressLib);
	int Welcome(const string &nickname);
    void ErrorInvalidTarget(MainWindow &w);
    void ErrorIncorrectOperation(MainWindow &w);
    int ShowBookRequired();
}
#endif
