/*****************************************************
This head file defines all the data stuctures that are
useful.
Namespace: NDatabase;

Headfile flag: DEF_DATABASE;

Constants:
int FLAG_USER = 0;
int FLAG_POWERUSER = 1;
int FLAG_ADMIN = 2;
void* nil = NULL; //easier to be compatible with C++11

Functions:
inline int CharHash(char p);
######################################################
It transforms a character into its hash value.
To simplify the problem, we only allow spaces, numbers
and small letters to form the index string of a book.
Any other characters will be treated as spaces.
While constructing the character tree, it's a must for
us to use such a hash function.

Appendix #1
Characters allowed and their hash values:

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
######################################################


*****************************************************/
#ifndef DEF_DATABASE
#define DEF_DATABASE 
#include <string>
#include <map>
#include <algorithm>

const int FLAG_USER = 0, FLAG_POWERUSER = 1, FLAG_ADMIN = 2;
const void* nil = NULL;
namespace NDatabase
{
	inline int CharHash(char p)
	{
		if((p <= '9') && (p >= '0'))
			return (p - '0');
		if((p >= 'a') && (p <= 'z'))
			return (p - 'a' + 10);
		return 36;
	}
	struct Tnode
	{
		string title;
		long long ISBN;
		string nickname;
		string author;
		string description;
		int avaliableNum;
		string lastTenBorrowers[10];
	}
	struct TCharTree
	{
		Tnode *details;
		TCharTree *succChar[37];
	} 
	class TLibrary
	{
		private:
			TCharTree *innerTree;
			TCharTree find(TCharTree *src, string indexStr)
			{
				if(src == nil) return nil;
				if(s == "") return (*src);
				return find((*src).succChar[CharHash(indexStr[0])],
							indexStr.erase(0, 1));
			};
		public:
			TLibrary()
			{
				innerTree = new (TCharTree);
				(*innerTree).details = nil;
				fillchar((*innerTree).succChar, 0, sizeof((*innerTree).succChar));
			};
			TCharTree searchIndex(string indexStr)
			{
				return find(innerTree, indexStr);
			}
			
	};
	
}
NDatabase :: Tnode GlobalTempProperty;
#endif
