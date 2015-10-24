#ifndef DEF_DATABASE
#define DEF_DATABASE 
#include <string>
namespace NDatabase
{
	
	class TLibrary
	{
		private:
			TCharTree innerTree;
	    public:
			Tnode find(char *s);
			
	};
}
#endif