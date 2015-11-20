/***********************************************************
This header file defines a few varibles used in the project.
***********************************************************/
#ifndef DEF_GLOBALVAR
#define DEF_GLOBALVAR
#include "classes.hpp"
#include "constants.hpp"
static int keepPeriod;
extern ifstream fileSettings("settings.ini");
extern ofstream fileLogs;
extern Nlibrary :: TLibrary ELibrary;
extern Nusers :: TUsers EUsers;
#endif
