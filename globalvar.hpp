/***********************************************************
This header file defines a few varibles used in the project.
***********************************************************/
#ifndef DEF_GLOBALVAR
#define DEF_GLOBALVAR
#include "classes.hpp"
#include "stdincs.hpp"
#include "constants.hpp"
extern int keepPeriod;
extern Nlibrary :: TLibrary ELibrary;
extern Nusers :: TUsers EUsers;
extern stack<Nlibrary :: TBook> ResultStack;
extern long long presentUID;
extern Nusers :: TInnerUIDandISBNTree UIDandISBNTree;
extern Nusers :: TUser inOperation;
extern MainWindow *www;
#endif
