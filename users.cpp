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
	int TUsers :: AddUser(TUser inPendingUser , long long UID) 
	{
		TUser &temp = inPendingUser;
		temp.userPassword = encryptingWithMd5(temp.userPassword);
		UIDTree[++presentUID] = inPendingUser;
		return 0;
	}
	int TUsers :: DeleteUserByUID(long long tgUID, long long UID) 
	{
		TInnerStruct :: iterator it;
		it = UIDTree.find(tgUID);
		if (it == UIDTree.end()) 
		{
			
			return -1;
		}
		else 
		{
			
			UIDTree.erase(it);
		}
		return 0;
	}
	bool TUsers :: TestPassword(long long UID, TPassword passGiven)
	{
		if (!strcmp(passGiven , encryptingWithMd5(UIDTree[UID].userPassword))) return false;
		return true;
	}
	TUser TUsers :: GetUser(long long UID) 
	{
		return UIDTree[UID];
	}
	int TUsers :: ChangePassword(long long UID, TPassword newPassword) 
	{
		TInnerStruct :: iterator it;
		it = UIDTree.find(UID);
		if (it == UIDTree.end()) return -1;
		else (*it).userPassword = encryptingWitMd5(newPassword);
		return 0;
	}
	int ChangeUserNickname(long long UID, string newName) 
	{
		
	}
}