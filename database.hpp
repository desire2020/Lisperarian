#ifndef DEF_DATABASE
#define DEF_DATABASE 
#include <string>
#include <map>
#include <algorithm>


namespace NDatabase
{
	struct Tnode
	{
		string Title;
		
	}
	typedef map<string,Tnode> TCharTree;
	class TLibrary
	{
		private:
			TCharTree innerTree;
	    public:
			TCharTree find(char *s);
			
	};
}
#endif