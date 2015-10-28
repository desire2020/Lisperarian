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
	};
	typedef map<long long, TBook> TInnerStruct;
	class TLibrary
	{
	private:
		TInnerStruct ISBNTree;
		TPlan aboutOneWeek;
	public:
		
		int AddBook(Tbook inPendingBook);
		int DeleteBookByISBN(long long targetBook);
		int BorrowOneSpecificBook(long long ISBN, long long UserID);
	};
}
namespace Nusers
{
	
}
#endif