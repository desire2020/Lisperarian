/*****************************************************
This file implements all the data stuctures that are
useful while constructing a virtual library.
Namespace: Nlibrary;

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
		}
		else
		{
			(*it).avaliableNum += inPendingBook.avaliableNum;
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
				fo.open(("\\books\\" + NumStr(tgISBN) + ".log").c_str(), ios :: app | ios :: out);
				fo << Nios :: SysDateStr() << " " << NumStr(userID) << endl;
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
		return 0;
	}
};
	
}