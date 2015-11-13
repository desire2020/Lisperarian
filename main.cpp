#include "stdincs.hpp"
Nusers :: TUser inOperation;
int Initialization()
{
	Nios :: InitUserSys();
	Nios :: InitBookSys();
	ios :: sync_with_stdio(false);
	
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
	int 
	if (inOp.
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
	RecordEvent
	return 0;
}
int Login()
{
	long long inputUserID;
	string inputPassword;
	inputUserID = Nios :: GetNum();
	inputPassword = Nios :: GetLine();
	if 
}
int Logout()
{
	
}
int main()
{
	int p;
	Initialization();
	while(true)
	{
		p = Nios :: GetRequest();
		if (CheckAuthority(p, inOperation))
		switch p
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
}