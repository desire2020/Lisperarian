/****************************************
这里是主程序，负责将已经实现的各模块有机
组合起来。
两种不同的错误返回值的说明：
-1 ：系统错误，可能是由于指定了不合法或不
存在的操作对象
-2 ：操作流程中错误，这可能是由于密码有错
或两次密码输入不一致等等
****************************************/
#include "stdincs.hpp"
Nusers :: TUser inOperation;
int Initialization()
{
	TUser defaultAdmin;
	defaultAdmin.userNickname = "admin";
	defaultAdmin.authority = 3;
	defaultAdmin.userPassword = "admin";
	defaultAdmin.userID = Nusers :: INITOFSUM;
	defaultAdmin.occupiedBooks.clear();
	defaultAdmin.privateInf.realName = "";
	defaultAdmin.privateInf.telephoneNumber = 0;
	defaultAdmin.privateInf.identificationNumber = "";
	ios :: sync_with_stdio(false);
	Nios :: InitUserSys(EUsers);
	Nios :: InitBookSys(ELibrary);
	if (Nusers :: presentUID == Nusers :: INITOFSUM)
	{
		EUsers.AddUser(defaultAdmin, 0);
	}
	return 0;
}
int Finalization()
{
	Nios :: RefreshUserSys();
	Nios :: RefreshBookSys();
	fileSettings.close();
	return 0;
}
bool CheckAuthority(int Event, const Nusers :: TUser &inOp)
{
	int presentAuthority = inOp.authority;
	Event = abs(Event);
	switch(presentAuthority)
	{
		case 0 : {if (Event <= 1) return true; else return false; break; }
		case 1 : {if ((Event >= 2) && (Event <= 6)) return true; else return false; break; }
		case 2 : {if ((Event >= 2) && (Event <= 9)) return true; else return false; break; }
		case 3 : {if ((Event >= 2) && (Event <= 11)) return true; else return false; break; }
		default : {return (Event == 2); break;}
	}
	return false;
}
int SignIn()
{
	Nusers :: TUser inPending;
	inPending.userNickname = Nios :: GetLine();
	inPending.userPassword = Nios :: GetLine();
	inPending.occupiedBooks.clear();
	inPending.privateInf.realName = Nios :: GetLine();
	do
	{
		inPending.privateInf.telephoneNumber = Nios :: GetNum();
	}
	while(inPending.privateInf.telephoneNumber == -1);
	inPending.privateInf.identificationNumber = Nios :: GetLine();
	EUsers.AddUser(inPending, 0);
	RecordEvent(0, Nusers :: presentUID - 1, Nusers :: presentUID - 1);
	return 0;
}
int Login()
{
	long long inputUserID;
	Nusers :: TPassword inputPassword;
	inputUserID = Nios :: GetNum();
	inputPassword = Nios :: GetLine();
	if (EUsers.CheckUID(inputUserID))
	{
		if (EUsers.TestPassword(inputUserID, inputPassword))
		{
			inOperation = EUsers.GetUser(inputUserID);
			Nios :: Welcome(inOperation.userNickname);
			RecordEvent(1, Nusers :: inputUserID, Nusers :: inputUserID);
		}
		else
			return -2;
	}
	else
		return -1;
	return 0;
}
int Logout()
{
	inOperation.userNickname = "";
	inOperation.userID = 0;
	inOperation.userPassword = "";
	inOperation.occupiedBooks.clear();
	inOperation.authority = 0;
	inOperation.privateInf.realName = "";
	inOperation.privateInf.telephoneNumber = 0;
	inOperation.identificationNumber = "";
	RecordEvent(2, Nusers :: inputUserID, Nusers :: inputUserID);
	return 0;
}
int BorBook()
{
	long long target = Nios :: GetNum();
	int state;
	state = ELibrary.BorrowOneSpecificBook(target, inOperation.userID);
	if (state != 0) return -1;
	else
	{
		state = EUsers.BorrowOneSpecificBook(target, inOperation.userID);
		if (state == 0)
		{
			RecordEvent(3, target, inOperation.userID);
			return 0;
		}
		else 
			return -1;
	}
}
int RetBook()
{
	long long target = Nios :: GetNum();
	int state;
	state = ELibrary.ReturnOneSpecificBook(target, inOperation.userID);
	if (state != 0) return -1;
	else
	{
		state = EUsers.ReturnOneSpecificBook(target, inOperation.userID);
		if (state == 0)
		{
			RecordEvent(4, target, inOperation.userID);
			return 0;
		}
		else
			return -1;
	}
}
int ChangeNickName()
{
	string inputNewNickname;
	long long targetUID;
	targetUID = Nios :: GetNum();
	if (!(EUsers.CheckUID(targetUID))) return -1;
	if (((inOperation.authority == 1) && (inOperation.userID == UID)) || (inOperation.authority >= 2))
	{
		inputNewNickname = Nios :: GetLine();
		EUsers.ChangeUserNickname(targetUID, inputNewNickname);
		RecordEvent(5, targetUID, inOperation.userID);
		return 0;
	}
	return -1;
}
int ChangePassword()
{
	TPassword inputNewPassword, inputNewPassword2;
	long long targetUID;
	targetUID = Nios :: GetNum();
	if (!(EUsers.CheckUID(targetUID))) return -1;
	if (((inOperation.authority == 1) && (inOperation.userID == UID)) || (inOperation.authority >= 2))
	{
		inputNewPassword = Nios :: GetLine();
		inputNewPassword2 = Nios :: GetLine();
		if (inputNewPassword == inputNewPassword2)
		{	
			EUsers.ChangePassword(targetUID, inputNewPassword);
			RecordEvent(6, targetUID, inOperation.userID);
			return 0;
		}
		else
			return -2;
	}
	return -1;
}
int AddBook()
{
	TBook inputNewBook;
	inputNewBook.title = Nios :: GetLine();
	inputNewBook.ISBN = Nios :: GetNum();
	inputNewBook.author = Nios :: GetLine();
	inputNewBook.description = Nios :: GetLine();
	inputNewBook.avaliableNum = int(Nios :: GetNum());
	inputNewBook.lowerBoundOfAuthority = int(Nios :: GetNum());
	inputNewBook.occupyingUsers.clear();
	ELibrary.AddBook(inputNewBook, inOperation.userID);
	RecordEvent(7, inputNewBook.ISBN, inOperation.userID);
	return 0;
}
int EditBook()
{
	long long targetISBN;
	TBook inputNewBook;
	targetISBN = Nios :: GetLine();
	inputNewBook.title = Nios :: GetLine();
	inputNewBook.author = Nios :: GetLine();
	inputNewBook.description = Nios :: GetLine();
	inputNewBook.lowerBoundOfAuthority = int(Nios :: GetNum());
	ELibrary.AddBook(inputNewBook, inOperation.userID);
	RecordEvent(8, inputNewBook.ISBN, inOperation.userID);
	return 0;
}
int DelUser()
{
	long long targetUID;
	targetUID = Nios :: GetNum();
	return (EUsers.DeleteUserByUID(targetUID));
}
int ChangeUserAuthority()
{
	long long workingMode;
	long long targetUID;
	TUser targetUser;
	targetUID = Nios :: GetNum();
	if (!(EUsers.CheckUID(targetUID))) return -1;
	targetUser = EUsers.GetUser(targetUID);
	workingMode = Nios :: GetNum();
	switch(workingMode)
	{
		case MODE_BAN : EUsers.SetUserAuthority(targetUID, -targetUser.authority); break;
		case MODE_UPGRADE : EUsers.SetUserAuthority(targetUID, 2); break;
		case MODE_DEGRADE : EUsers.SetUserAuthority(targetUID, 1); break;
		case MODE_ASSITANT : EUsers.SetUserAuthority(targetUID, 3); break;
		default : break;
	}
	return 0;
}
int SearchBookByKeyword()
{
	string KeyWord1, KeyWord2, KeyWord3;
	KeyWord1 = Nios :: GetLine();
	KeyWord2 = Nios :: GetLine();
	KeyWord3 = Nios :: GetLine();
	ELibrary.SearchBook(KeyWord1, KeyWord2, KeyWord3);
	Nios :: ShowBookRequired();
	return 0;
}
int main()
{
	int p;
	int message;
	Initialization();
	while(true)
	{
		p = Nios :: GetRequest();
		if (CheckAuthority(p, inOperation))
		switch(p)
		{
			case 0 : message = SignIn(); break;
			case 1 : message = Login(); break;
			case 2 : message = Logout(); break;
			case -3 : message = SearchBookByKeyword();break;
			case 3 : message = BorBook(); break;
			case 4 : message = RetBook(); break; 
			case 5 : message = ChangeNickName(); break;
			case 6 : message = ChangePassword(); break;
			case 7 : message = AddBook(); break;
			case 8 : message = DelBook(); break;
			case 9 : message = EditBook(); break;
			case 10 : message = DelUser(); break;
			case 11 : message = ChangeUserAuthority(); break;
			default : break;
		}
		switch(message)
		{
			case -1 : Nios :: ErrorInvalidTarget(); break;
			case -2 : Nios :: ErrorIncorrectOperation(); break;
			default : break;
		}
	}
	Finalization();
	return 0;
}