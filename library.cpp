/*****************************************************
This file implements all the data stuctures that are
useful while constructing a virtual library.
Namespace: Nlibrary;

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
#include "stdincs.hpp"
namespace Nlibrary
{
	string NumStr(long long tgNum)
	{
		static string p = "";
		long long PS = tgNum;
		for (int i = 0; i < ISBNLEN; i++)
		{
			p = char(PS % 10 + '0') + p;
		}
		return p;
	}
	int TLibrary :: AddBook(Tbook inPendingBook, long long userID)
	{
		ofstream fo;
		TInnerStruct :: iterator it;
		it = ISBNTree.find(inPendingBook.ISBN);
		if (it == ISBNTree.end())
		{
			ISBNTree[inPendingBook.ISBN] = inPendingBook;
			fo.open(("\\books\\" + NumStr(inPendingBook.ISBN) + ".log").c_str(), ios :: app | ios :: out);
			fo << SysInfEncry(Nios :: SysDateStr() + ": User " + NumStr(userID) + "add the book.") << endl;
			fo.close();
		else
		{
			inPendingBook.avaliableNum += (*it).avaliableNum;
			fo.open(("\\books\\" + NumStr(inPendingBook.ISBN) + ".log").c_str(), ios :: app | ios :: out);
			fo << SysInfEncry(Nios :: SysDateStr() + ": User " + NumStr(userID) + "add the book.") << endl;
			fo.close();
			(*it) = inPendingBook;
		}
			return 0;
	}
	int TLibrary :: DeleteBookByISBN(long long tgISBN, long long userID)
	{
		TInnerStruct :: iterator it;
		it = ISBNTree.find(tgISBN);
		if (it == ISBNTree.end())
			return -1;
		else
		{
				ISBNTree.erase(it);
				
		}
	}
	int TLibrary :: BorrowOneSpecificBook(long long tgISBN, long long userID)
	{
		TInnerStruct :: iterator it;
		it = ISBNTree.find(tgISBN);
		if (it == ISBNTree.end())
			return -1;
		else
		{
			if ((*it).avaliableNum == 0) return -1;
			if ((*it).occupyingUsers.find(userID) == (*it).occupyingUsers.end())
			{
				(*it).avaliableNum--;
				(*it).occupyingUsers.insert(userID);
			}
		}
	}

	int TLibrary :: ReturnOneSpecificBook(long long tgISBN, long long userID)
	{
		TInnerStruct :: iterator it;
		it = ISBNTree.find(tgISBN);
		if (it != ISBNTree.end())
		{
			if ((*it).occupyingUsers.find(userID) != (*it).occupyingUsers.end())
			{
				(*it).avaliableNum++;
				(*it).occupyingUsers.erase((*it).occupyingUsers.find(userID));
			}
		}
		else return -2;
	}
	
	int TLibrary :: EditBookProperty(long long tgISBN, long long userID, const TBook &newBook)
	{
		TInnerStruct :: iterator it;
		it = ISBNTree.find(tgISBN);
		if (tgISBN != newBook.ISBN)
		{
			return -1;
		}
		else
		{
			if (it == ISBNTree.end())
			{
				return -1;
			}
			else
			{
				 it -> title = newBook.title;
				 it -> indexname = newBook.indexname;
				 it -> author = newBook.author;
				 it -> description = newBook.description;
				 it -> lowerBoundOfAuthority = newBook.lowerBoundOfAuthority;
				
			}
		}
	}
};
	
}
