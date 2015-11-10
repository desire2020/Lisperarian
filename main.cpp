#include "stdincs.hpp"
#include "constants.hpp"
#include "globalvar.hpp"
#include "classes.hpp"
int Initialization()
{
	
}
int Finalization()
{
	fileSettings.close();
	return 0;
}
int main()
{
	Initialization();
	while(true)
	{
		GetRequest();
		
	}
	Finalization();
}