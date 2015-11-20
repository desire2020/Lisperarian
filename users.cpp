/* 
	文件users为根，其下有：
		usersRB ：用户借还书日志
		usersInf ：用户的信息（加密储存）
		usersOccupiedBooks ：用户当前所借的书（加密存储）
*/

#include "stdincs.hpp"

namespace Nusers 
{

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
		return 0;
	}
	
	int TUsers :: DeleteUserByUID(long long tgUID, long long UID) 
	{
		if (!CheckUID(tgUID)) return -1;
		Tuser &temp = UIDTree[tgUID];
		set<long long> :: iterator that;
		for (that = temp.occupiedBooks.begin(); that != temp.occupiedBooks.end(); ++that)
		{
			UIDandISBN now = make_pair<tgUID , *that>;
			TInnerUIDandISBN :: iterator its;
			its = UIDandISBNTree.find(now);
			if (its != UIDandISBNTree.end()) UIDandISBNTree.erase(its);
		}			//删除TInnerUIDandISBN中对应的元素
		TInnerStruct :: iterator it;
		it = UIDTree.find(tgUID);
		UIDTree.erase(it);
		remove(Nios :: SearchingFile("users\\usersRB\\" , Nios :: NumStr(tgUID) , ".log"));
		remove(Nios :: SearchingFile("users\\usersInf\\" , Nios :: NumStr(tgUID) , ".log"));
		remove(Nios :: SearchingFile("users\\usersOccupiedBooks\\" , Nios :: NumStr(tgUID) , ".log"));
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
		if (!CheckUID(UID)) return -1;
		UIDandISBN temp = make_pair(UID, tgISBN);
		TInnerUIDandISBN :: iterator it;
		it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) 
		{
			TTime preTime = PresentTime();
			UIDandISBNTree[temp] = preTime;
			Nios :: PrintUserSysRecordBorrow(UID , tgISBN , preTime);
			UIDTree[UID].occupiedBooks.insert(tgISBN);
			return 0;
		}
		else return -1;
	}
	
	int TUsers :: ReturnOneSpecificBook(long long tgISBN, long long UID) 
	{
		if (!CheckUID(UID)) return -1;
		UIDandISBN temp = make_pair(UID, tgISBN);
		TInnerUIDandISBN :: iterator it;
		it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) return -1;
		else
		{
			TTime preTime = PresentTime();
			UIDandISBNTree.erase(it);
			Nios :: PrintUserSysRecordReturn((UID , tgISBN , preTime);
			UIDTree[UID].occupiedBooks.erase(UIDTree[UID].occupiedBooks.find(tgISBN));
			return 0;
		}
	}
	
	int TUesrs :: SetUserAuthority(long long UID, long long newAuthority) 
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].authority = newAuthority;
		return 0;
	}
}