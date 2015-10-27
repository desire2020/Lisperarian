/*****************************************************
This header file defines all the data stuctures that are
useful while constructing a virtual library.
Namespace: Nlibrary;

Headfile flag: DEF_LIBRARY;

Appendix #1
To simplify the problem, we only allow spaces, numbers
and small letters to form the index string of a book.
Any other characters will be treated as spaces.

Appendix #2
Characters allowed in a indexname and their hash values:

Character	Hashvalue
'0'			0		
'1'			1		
'2'			2		
'3'			3		
'4'			4		
'5'			5		
'6'			6		
'7'			7		
'8'			8		
'9'			9		
'a'			10	
'b'			11	
'c'			12	
'd'			13	
'e'			14	
'f'			15	
'g'			16	
'h'			17	
'i'			18	
'j'			19	
'k'			20	
'l'			21	
'm'			22	
'n'			23	
'o'			24
'p'			25	
'q'			26	
'r'			27	
's'			28	
't'			29	
'u'			30	
'v'			31	
'w'			32	
'x'			33	
'y'			34	
'z'			35	
' '			36	

*****************************************************/
#ifndef DEF_LIBRARY
#define DEF_LIBRARY 
#include <string>
#include <utility>
#include <cstring>
#include <map>
#include <list>
#include <algorithm>
5
namespace Nlibrary
{
	struct Tnode
	{
		string title;//Allow Chinese here
		long long ISBN;
		string indexname;
		string author;
		string description;
		int avaliableNum;
		int lowerBoundOfAuthority;
		Tnode()
		{
		}
		Tnode(string inputTitle,
			  long long inputISBN,
			  string inputIndexname,
			  string inputAuthor,
			  string inputDescription,
			  int inputLBOAuthority)
		{
			title = inputTitle;
			ISBN = inputISBN;
			indexname = inputIndexname;
			author = inputAuthor;
			description = inputDescription;
			lowerBoundOfAuthority = inputLBOAuthority;
			while(!listOfAllBorrowersID.empty()) listOfAllBorrowersID.pop();
		}
		Tnode(string inputTitle,
			  long long inputISBN,
			  string inputIndexname,
			  string inputAuthor,
			  string inputDescription)
		{
			title = inputTitle;
			ISBN = inputISBN;
			indexname = inputIndexname;
			author = inputAuthor;
			description = inputDescription;
			lowerBoundOfAuthority = FLAG_USER;
			while(!listOfAllBorrowersID.empty()) listOfAllBorrowersID.pop();
		}
		~Tnode()
		{
			while(!listOfAllBorrowersID.empty()) listOfAllBorrowersID.pop();
		}
	}
	typedef map<long long, Tnode> TInnerStruct;
	typedef list<>
	class TLibrary
	{
	private:
		TInnerStruct ISBNTree;
		TPlan aboutOneWeek;
	public:
		
		int AddBook(Tnode inPendingBook)
		{
			TInnerStruct :: iterator it;
			it = ISBNTree.find(inPendingBook.ISBN);
			if (it == ISBNTree.end())
				ISBNTree[inPendingBook.ISBN] = inPendingBook;
			else
			{
				inPendingBook.avaliableNum += (*it).avaliableNum;
				(*it) = inPendingBook;
			}
			return 0;
		}
		int DeleteBookByISBN(long long targetBook)
		{
			TInnerStruct :: iterator it;
			it = ISBNTree.find(targetBook);
			if (it == ISBNTree.end())
				return -1;
			else
			{
				ISBNTree.erase(it);
			}
		}
		int BorrowOneSpecificBook(long long ISBN, long long UserID)
		{
			TInnerStruct :: iterator it;
			it = ISBNTree.find(targetBook);
			if (it == ISBNTree.end())
				return -1;
			else
			{
				if ((*it).avaliableNum == 0) return -1;
				else
				{
					(*it).avaliableNum--;
					(*it).listOfAllBorrowersID.p
				}
			}
		}
	};
	
}
#endif
