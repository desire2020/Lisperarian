/***********************************************************
This header file defines a few constants used in the project
Constants:
int FLAG_USER = 0, FLAG_POWERUSER = 1, FLAG_ADMIN = 2
These constants describe the authority of three different t-
ypes of users.
***********************************************************/
#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

#define nil NULL
const int ISBNLEN = 13;
const int FLAG_GUEST = 0, FLAG_USER = 1, FLAG_POWERUSER = 2, FLAG_ADMIN = 3; 
const int MODE_BAN = 0, MODE_DEGRADE = 3, MODE_UPGRADE = 1, MODE_ASSITANT = 2;
const char easyKey = 0;
namespace Nusers
{
    const long long INITOFSUM = 1e5;
}
#endif
