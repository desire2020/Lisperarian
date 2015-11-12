#include "stdincs.hpp"
TUser inOperation;
int Initialization()
{
	Nios :: InitUserSys();
	Nios :: InitBookSys();
	
}
int Finalization()
{
	Nios :: RefreshUserSys();
	Nios :: RefreshBookSys();
	fileSettings.close();
	return 0;
}
int main()
{
	int p;
	Initialization();
	while(true)
	{
		p = Nios :: GetRequest();
		
	}
	Finalization();
}