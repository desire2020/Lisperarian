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
			case 3 : AddBook(); break;
			case 4 : DelBook(); break;
			case 5 : BorBook(); break;
			case 6 : RetBook(); break; 
			case 7 : EditBook(); break;
			case 8 : DelUser(); break;
			case 9 : BanUser(); break;
			case 10 : ChangeNickName(); break;
			case 11 : ChangePassword(); break;
			default : break;
		}
		
	}
	Finalization();
}