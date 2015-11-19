/* 
	权限：0 ：未注册用户  对应任务：0 ：0 ，1
		1 ：普通用户				1 ：2 ，3 ，4
		2 : 管理员					2 ：2 ，3 ，4 ，5 ，6 ，7
		3 ：馆长					3 ：2 ，3 ，4 ，5 ，6 ，7 ，8 ，9 ，
*/

#include "stdincs.hpp"

namespace Nusers 
{
	char str[30];
	
	string NumStr(long long userID)
	{
		string p = "";
		while (userID > 0) {
			p = char(userID % 10 + '0') + p;
			userID /= 10;
		}
		return p;
	}
	
	char *SearchingFile(string s1 , long long userID , string s3) {
		string s2 = NumStr(userID);
		string ss = s1 + s2 + s3;
		int len = ss.length();
		for (int i = 0; i < len; ++i) str[i] = ss[i]; str[len] = '\0';
		return str;
	}

	bool TUsers :: CheckUID(long long UID) 
	{
		TInnerStruct :: iterator it;
		it = UIDTree.find(UID);
		if (it == UIDTree.end()) return false;
		return true;
	}
	
	int TUsers :: AddUser(TUser inPendingUser , long long UID) 
	{
		TUser &temp = inPendingUser;
		temp.userPassword = EncryptingWithMd5(temp.userPassword);
		UIDTree[++presentUID] = inPendingUser;
		ofstream theFile(SearchingFile("usersRB\\" , presentUID , ".log"));
		theFile.close();
		ofstream theFile(SearchingFile("usersInf\\" , presentUID , ".log"));
			theFile << EncryptingWithXor(temp.presentUID) << endl;
			theFile << EncryptingWithXor(temp.userNickname) << endl;
			theFile << EncryptingWithXor(temp.userPassword) << endl;
			theFile << EncryptingWithXor(temp.authority) << endl;
			theFile << EncryptingWithXor(temp.privateInf.realName) << endl;
			theFile << EncryptingWithXor(temp.privateInf.telephoneNumber) << endl;
			theFile << EncryptingWithXor(temp.privateInf.identificationNumber) << endl;
		theFile.close();
		return 0;
	}
	
	int TUsers :: DeleteUserByUID(long long tgUID, long long UID) 
	{
		if (!CheckUID(tgUID)) return -1;
		TInnerStruct :: iterator it;
		it = UIDTree.find(tgUID);
		UIDTree.erase(it);
		remove(SearchingFile("usersRB\\" , tgUID , ".log"));
		return 0;
	}
	
	bool TUsers :: TestPassword(long long UID, TPassword passGiven)
	{
		if (!CheckUID(UID)) return false;
		if (passGiven != EncryptingWithMd5(UIDTree[UID].userPassword)) return false;
		return true;
	}
	
	TUser TUsers :: GetUser(long long UID) 
	{
		if (!CheckUID(UID)) return NULL;
		return UIDTree[UID];
	}
	
	int TUsers :: ChangePassword(long long UID, TPassword newPassword) 
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].userPassword = EncryptingWithMd5(newPassword);
		return 0;
	}
	
	int TUsers :: ChangeUserNickname(long long UID, string newNickname) 
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].userNickname = newNickname;
		return 0;
	}
	
	int TUesrs :: ChangePrivateInf(long long UID, PrivateInformation newPrivateInf) 
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].privateInf = newPrivateInf;
		return 0;
	}
	
	int TUsers :: BorrowOneSpecificBook(long long tgISBN, long long UID) 
	{
		UIDandISBN temp = make_pair(UID, tgISBN);
		TInnerUIDandISBN :: iterator it;
		it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) 
		{
			UIDandISBNTree[temp] = PresentTime();
			if (!CheckUID(UID)) return -1;
			UIDTree[UID].occupiedBooks.insert(tgISBN);
			return 0;
		}
		else return -1;
	}
	
	int TUsers :: ReturnOneSpecificBook(long long tgISBN, long long UID) 
	{
		UIDandISBN temp = make_pair(UID, tgISBN);
		TInnerUIDandISBN :: iterator it;
		it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) return -1;
		else 
		{
			if (!CheckUID(UID)) return -1;
			UIDTree[UID].occupiedBooks.erase(UIDTree[UID].occupiedBooks.find(tgISBN));
			return 0;
		}
	}
	
	int TUesrs :: SetUserAuthority(long long UID, int newAuthority) 
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].authority = newAuthority;
		return 0;
	}
}