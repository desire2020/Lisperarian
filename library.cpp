/*****************************************************
This file implements all the data stuctures that are
useful while constructing a virtual library.
Namespace: Nlibrary;

*****************************************************/
#include "stdincs.hpp"
namespace Nlibrary
{
	string TLibrary :: NumStr(long long tgNum)
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
				return 0;
		}
	}
	int TLibrary :: BorrowOneSpecificBook(long long tgISBN, long long userID)
	{
		TInnerStruct :: iterator it;
		TUser currentUser;
		currentUser = EUsers.GetUser(userID);
		it = ISBNTree.find(tgISBN);
		if (it == ISBNTree.end())
			return -2;
		else
		if (currentUser.authority < it -> authority)
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
				 it -> author = newBook.author;
				 it -> description = newBook.description;
				 it -> lowerBoundOfAuthority = newBook.lowerBoundOfAuthority;
			}
		}
		return 0;
	}
	int TLibrary :: SearchBook(const string &KeyWord1, const string &KeyWord2, const string &KeyWord3)
	{
		string information;
		while (!ResultStack.empty()) ResultStack.pop();
		TInnerStruct :: iterator it;
		for (it = ISBNTree.begin(); it != ISBNTree.end; it++)
		{
			information = it -> title + it -> author + it -> description;
			if ((information.find(KeyWord1) != string :: npos) && (information.find(KeyWord2) != string :: npos) && (information.find(KeyWord3) != string :: npos))
			{
				ResultStack.push(*it);
			}
		}
		return 0;
	}
};
	
}