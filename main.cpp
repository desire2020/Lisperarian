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
	Nios :: PrintString("欢迎使用Lisperarian图书管理系统");
	Nios :: PrintString("您将作为普通用户进行注册，如需申请管理员账号请联系馆长。");
	Nios :: 
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