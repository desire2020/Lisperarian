/***********************************************************
This header file defines a few varibles used in the project.
***********************************************************/
#ifndef DEF_GLOBALVAR
#define DEF_GLOBALVAR
static int keepPeriod;
ifstream fileSettings("settings.ini");
ofstream fileLogs("syslog.log", ios :: app | ios :: out);
Nlibrary :: TLibrary ELibrary;
Nusers :: TUsers EUsers;
#endif