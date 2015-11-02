/***********************************************************
This header file declares classes used in the project.
It can also be used as a plan or catalog of the project.
***********************************************************/
#ifndef DEF_CLASSES
#define DEF_CLASSES
namespace Nios
{
	
}
namespace Nlibrary
{
	struct TBook
	{
		string title;//Allow Chinese here
		long long ISBN;
		string indexname;
		string author;
		string description;
		int avaliableNum;
		int lowerBoundOfAuthority;
		set<long long> occupyingUsers;
	};
	typedef map<long long, TBook> TInnerStruct;
	class TLibrary
	{
	private:
		TInnerStruct ISBNTree;
	public:
		int AddBook(TBook inPendingBook, long long userID);
		int DeleteBookByISBN(long long tgISBN, long long userID);
		int BorrowOneSpecificBook(long long tgISBN, long long userID);
		int ReturnOneSpecificBook(long long tgISBN, long long userID);
		int SetLowerBoundOfAuthority(long long tgISBN, long long userID, int authority);
	};
}
namespace Nusers
{
	typedef string TPassword;
	struct TInformation
	{
	}
	struct TUser
	{
		string userName;
		long long userID;
		TPassword userPassword;
		set<long long> occupiedBooks;
		int authority;
		TInformation privateInf;
	}
	typedef map<long long, TUser> TInnerStruct;
	class TUsers
	{
	private:
		TInnerStruct UIDTree;
	public:
		int AddUser(TUser inPendingUser, long long userID);
		int DeleteUserByUID(long long tgUID, long long userID);
		bool TestPassword(long long UID, TPassword passGiven);
		TUsers GetUser(long long userID);
		int ChangePassword(long long UID, TPassword newPassword);
		int ChangeUserName(long long UID, string newName);
		int ChangePrivateInf(long long UID, TInformation newInf);
		int BorrowOneSpecificBook(long long tgISBN, long long userID);
		int ReturnOneSpecificBook(long long tgISBN, long long userID);
	}
	
}
#endif