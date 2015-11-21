/* 
	文件users为根，其下有：
		usersRB ：用户借还书日志
		usersInf ：用户的信息（加密储存）
		usersOccupiedBooks ：用户当前所借的书（加密存储）
*/

#include "stdincs.hpp"
#include "classes.hpp"
#include "globalvar.hpp"
#include "constants.hpp"

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
        TUser &temp = UIDTree[tgUID];
		set<long long> :: iterator that;
		for (that = temp.occupiedBooks.begin(); that != temp.occupiedBooks.end(); ++that)
		{
            UIDandISBN now(tgUID , *that);
            TInnerUIDandISBNTree :: iterator its;
			its = UIDandISBNTree.find(now);
			if (its != UIDandISBNTree.end()) UIDandISBNTree.erase(its);
		}			//删除TInnerUIDandISBN中对应的元素
		TInnerStruct :: iterator it;
		it = UIDTree.find(tgUID);
		UIDTree.erase(it);
        remove(("users\\usersRB\\" + Nios :: NumStr(tgUID) + ".log").c_str());
        remove(("users\\usersInf\\" + Nios :: NumStr(tgUID) + ".log").c_str());
        remove(("users\\usersOccupiedBooks\\" + Nios :: NumStr(tgUID) + ".log").c_str());
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
		if (!CheckUID(UID)) return -1;
		UIDandISBN temp = make_pair(UID, tgISBN);
        TInnerUIDandISBNTree :: iterator it;
        it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) 
		{
            TTime preTime = Nios :: PresentTime();
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
        TInnerUIDandISBNTree :: iterator it;
		it = UIDandISBNTree.find(temp);
		if (it == UIDandISBNTree.end()) return -1;
		else
		{
            TTime preTime = Nios :: PresentTime();
            Nios :: PrintUserSysRecordReturn(UID , tgISBN , preTime);
			UIDandISBNTree.erase(it);
			UIDTree[UID].occupiedBooks.erase(UIDTree[UID].occupiedBooks.find(tgISBN));
			return 0;
		}
	}
	
    int TUsers :: SetUserAuthority(long long UID, long long newAuthority)
	{
		if (!CheckUID(UID)) return -1;
		UIDTree[UID].authority = newAuthority;
		return 0;
	}
	
	bool KeepingTimedOut(long long UID)
	{
		if (!CheckUID(UID)) return -1;
		TUser &temp = GetUser(UID);
		set<long long> :: iterator it;
		for (it = temp.occupiedBooks.begin(); it != temp.occupiedBooks.end(); ++it)
		{
			long long ISBN = *it;
			UIDandISBN wht = make_pair(UID , ISBN);
			TInnerUIDandISBNTree :: iterator its;
			its = UIDandISBNTree.find(now);
			if (its != UIDandISBNTree.end()) 
			{
				TTime preTime = (*its).second;
				TTime nowTime = Nios :: PresentTime();
				if (preTime.year + 1 < nowTime.year) return true;
				if (preTime.year + 1 == nowTime.year && nowTime.yday + 365 - preTime.yday > keepPeriod) return true;
				if (preTime.year == nowTime.year && nowTime.yday - preTime.yday > keepPeriod) return true;
			}
		}
		return true;
	}
}
