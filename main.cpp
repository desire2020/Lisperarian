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
	Nios :: InitUserSys();
	Nios :: InitBookSys();
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
			RecordEvent(1, Nusers :: inputUserID, Nusers :: inputUserID);
		}
		else
			return -1;
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
			return -1;
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
	long long targetISBN;
	targetISBN = Nios :: GetNum();
	
}
int main()
{
	int p;
	Initialization();
	while(true)
	{
		p = Nios :: GetRequest();
		if (CheckAuthority(p, inOperation))
		switch(p)
		{
			case 0 : SignIn(); break;
			case 1 : Login(); break;
			case 2 : Logout(); break;
			case 3 : BorBook(); break;
			case 4 : RetBook(); break; 
			case 5 : ChangeNickName(); break;
			case 6 : ChangePassword(); break;
			case 7 : AddBook(); break;
			case 8 : DelBook(); break;
			case 9 : EditBook(); break;
			case 10 : DelUser(); break;
			case 11 : ChangeUserAuthority(); break;
			default : break;
		}
		
	}
	Finalization();
	return 0;
}