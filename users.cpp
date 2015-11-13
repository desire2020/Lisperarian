/* 
	权限：0 ：未注册用户  对应任务：0 ：0 ，1
		1 ：普通用户				1 ：2 ，3 ，4
		2 : 管理员					2 ：2 ，3 ，4 ，5 ，6 ，7
		3 ：馆长					3 ：2 ，3 ，4 ，5 ，6 ，7 ，8 ，9 ，
*/

#include "stdincs.hpp"

namespace Nusers 
{
	TPassword encryptingWithMd5(TPassword userPassword) 
	{
		
	}
	bool TUsers :: checkUID(long long UID) 
	{
		TInnerStruct :: iterator it;
		it = UIDTree.find(UID);
		if (it == UIDTree.end()) return false;
		return true;
	}
	int TUsers :: AddUser(TUser inPendingUser , long long UID) 
	{
		TUser &temp = inPendingUser;
		temp.userPassword = encryptingWithMd5(temp.userPassword);
		UIDTree[++presentUID] = inPendingUser;
		return 0;
	}
	int TUsers :: DeleteUserByUID(long long tgUID, long long UID) 
	{
		if (!checkUID(tgUID)) return -1;
		TInnerStruct :: iterator it;
		it = UIDTree.find(tgUID);
		UIDTree.erase(it);
		return 0;
	}
	bool TUsers :: TestPassword(long long UID, TPassword passGiven)
	{
		if (!strcmp(passGiven , encryptingWithMd5(UIDTree[UID].userPassword))) return false;
		return true;
	}
	TUser TUsers :: GetUser(long long UID) 
	{
		if (!checkUID(UID)) return -1;
		return UIDTree[UID];
	}
	int TUsers :: ChangePassword(long long UID, TPassword newPassword) 
	{
		if (!checkUID(UID)) return -1;
		UIDTree[UID].userPassword = encryptingWitMd5(newPassword);
		return 0;
	}
	int TUsers :: ChangeUserNickname(long long UID, string newName) 
	{
		TUser &temp = UIDTree[UID];
		temp.userNickname = newName;
		return 0;
	}
	int TUesrs :: ChangePrivateInf(long long UID, PrivateInformation newInf) 
	{
		TUser &temp = UIDTree[UID];
		temp.privateInf = newInf;
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
			GetUser(UID).occupiedBooks.insert(tgISBN);
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
			GetUser(UID).occupiedBooks.erase(GetUser(UID).occupiedBooks.find(tgISBN));
			return 0;
		}
	}
	int TUesrs :: SetUserAuthority(long long UID, int newAuthority) 
	{
		if (!checkUID(UID)) return -1;
		GetUser(UID).authority = newAuthority;
		return 0;
	}
}