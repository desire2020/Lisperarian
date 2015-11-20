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
		int avaliableNum;
		int lowerBoundOfAuthority;
		set<long long> occupyingUsers;
	};
    extern stack<TBook> ResultStack;
    typedef map<long long, TBook> TInnerStruct;
	class TLibrary
	{
	private:
		TInnerStruct ISBNTree;
	public:
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
    const long long INITOFSUM = 1e5;
    extern long long presentUID;
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
		int year, month, day;
    };
    typedef map<UIDandISBN, TTime> TInnerUIDISBNTree;
    extern TInnerUIDISBNTree UIDandISBNTree;
	struct TUser
	{
		string userNickname;
		long long userID;
		TPassword userPassword;
		set<long long> occupiedBooks;
		int authority;//it's minus when the user is banned
		PrivateInformation privateInf;
    };
	typedef map<long long, TUser> TInnerStruct;
	class TUsers
	{
	private:
		TInnerStruct UIDTree;
	public:
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
		int SetUserAuthority(long long UID, int newAuthority);
    };
}
namespace Nios
{
	string SysDateStr();//yyyy mm dd
    typedef Nusers :: TTime TTime;
    TTime PresentTime();
	string SysInfEncry(const string &originStr);
	string SysInfDecry(const string &encriedStr);
	int GetRequest();
	string GetLine();
	long long GetNum();
	int CypInit();
	int RefreshUserSys(const Nusers :: TUsers &inProgressLib);
    int InitUserSys(Nusers :: TUsers &inProgressLib);
	int RefreshBookSys(const Nlibrary :: TLibrary &inProgressLib);
    int InitBookSys(Nlibrary :: TLibrary &inProgressLib);
	int Welcome(const string &nickname);
	int ErrorInvalidTarget();
	int ErrorIncorrectOperation();
    int ShowBookRequired();
}
#endif
