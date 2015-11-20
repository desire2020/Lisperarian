/* 
	权限：0 ：未注册用户  对应任务：0 ：0 ，1
		1 ：普通用户				1 ：2 ，3 ，4
		2 : 管理员					2 ：2 ，3 ，4 ，5 ，6 ，7
		3 ：馆长					3 ：2 ，3 ，4 ，5 ，6 ，7 ，8 ，9 ，
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
		TInnerStruct :: iterator it;
		it = UIDTree.find(tgUID);
		UIDTree.erase(it);
		return 0;
	}
	bool TUsers :: TestPassword(long long UID, TPassword passGiven)
	{
		if (passGiven != EncryptingWithMd5(UIDTree[UID].userPassword)) return false;
		return true;
	}
	TUser TUsers :: GetUser(long long UID) 
	{
        //if (!CheckUID(UID)) return NULL;
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
    int TUsers :: ChangePrivateInf(long long UID, PrivateInformation newPrivateInf)
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].privateInf = newPrivateInf;
		return 0;
	}
	int TUsers :: BorrowOneSpecificBook(long long tgISBN, long long UID) 
	{
		UIDandISBN temp = make_pair(UID, tgISBN);
        TInnerUIDISBNTree :: iterator it;
        it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) 
		{
            UIDandISBNTree[temp] = Nios :: PresentTime();
			if (!CheckUID(UID)) return -1;
			UIDTree[UID].occupiedBooks.insert(tgISBN);
			return 0;
		}
		else return -1;
	}
	int TUsers :: ReturnOneSpecificBook(long long tgISBN, long long UID) 
	{
		UIDandISBN temp = make_pair(UID, tgISBN);
        TInnerUIDISBNTree :: iterator it;
		it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) return -1;
		else 
		{
			if (!CheckUID(UID)) return -1;
			UIDTree[UID].occupiedBooks.erase(UIDTree[UID].occupiedBooks.find(tgISBN));
			return 0;
		}
	}
    int TUsers :: SetUserAuthority(long long UID, int newAuthority)
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].authority = newAuthority;
		return 0;
	}
}
