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
}
int Login()
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