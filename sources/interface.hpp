#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include "stdincs.hpp"
#include "classes.hpp"
#include "constants.hpp"
#include "globalvar.hpp"

extern queue<long long> queueNum;
extern queue<string> queueStr;
int Initialization();
int Finalization();
bool CheckAuthority(int Event, const Nusers :: TUser &inOp);
int SignIn();
int Login();
int Logout();
int BorBook();
int RetBook();
int ChangeNickName();
int ChangePassword();
int AddBook();
int EditBook();
int DelBook();
int DelUser();
int ChangeUserAuthority();
int SearchBookByKeyword();
int procFunc(int p);

#endif // INTERFACE_HPP

