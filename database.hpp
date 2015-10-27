/*****************************************************
This head file defines all the data stuctures that are
useful.
Namespace: NDatabase;

Headfile flag: DEF_DATABASE;

Constants:
int FLAG_USER = 0;
int FLAG_POWERUSER = 1;
int FLAG_ADMIN = 2;
#define nil NULL; //easier to be compatible with C++11

Functions:

*****************************************************/
#ifndef DEF_DATABASE
#define DEF_DATABASE 
#include <string>
#include <cstring>
#include <map>
#include <algorithm>

const int FLAG_USER = 0, FLAG_POWERUSER = 1, FLAG_ADMIN = 2;
namespace NDatabase
{

	struct Tnode
	{
		string title;
		long long ISBN;
		string nickname;
		string author;
		string description;
		int avaliableNum;
	}

	class TLibrary
	{
		private:
			map<long long, Tnode> ISBNTree;
		public:
			TLibrary 
	};
	
}
#endif
