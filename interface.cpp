#include "stdincs.hpp"
#include "classes.hpp"
#include "constants.hpp"

int keepPeriod;
Nlibrary :: TLibrary ELibrary;
Nusers :: TUsers EUsers;
stack<Nlibrary :: TBook> ResultStack;
long long presentUID;
Nusers :: TInnerUIDandISBNTree UIDandISBNTree;
Nusers :: TUser inOperation;
queue<long long> queueNum;
queue<string> queueStr;
int workingModeGer;


int Initialization()
{
    Nusers :: TUser defaultAdmin;
    defaultAdmin.userNickname = "admin";
    defaultAdmin.authority = 3;
    defaultAdmin.userPassword = "admin";
    defaultAdmin.userID = Nusers :: INITOFSUM;
    defaultAdmin.occupiedBooks.clear();
    defaultAdmin.privateInf.realName = "";
    defaultAdmin.privateInf.telephoneNumber = 0;
    defaultAdmin.privateInf.identificationNumber = "";
    ios :: sync_with_stdio(false);
    Nios :: InitUserSys(EUsers);
    Nios :: InitBookSys(ELibrary);
    Nios :: InitUIDandISBNTree(UIDandISBNTree);
    if (presentUID == Nusers :: INITOFSUM)
    {
        EUsers.AddUser(defaultAdmin, 0);
    }
    return 0;
}
int Finalization()
{
    Nios :: RefreshUserSys(EUsers);
    Nios :: RefreshBookSys(ELibrary);
    Nios :: RefreshUIDandISBNTree(UIDandISBNTree);
    return 0;
}
bool CheckAuthority(int Event, const Nusers :: TUser &inOp)
{
    int presentAuthority = inOp.authority;
    Event = abs(Event);
    switch(presentAuthority)
    {
        case 0 : {if (Event <= 1) return true; else return false; break; }
        case 1 : {if ((Event >= 2) && (Event <= 6)) return true; else return false; break; }
        case 2 : {if ((Event >= 2) && (Event <= 9)) return true; else return false; break; }
        case 3 : {if ((Event >= 2) && (Event <= 11)) return true; else return false; break; }
        default : {return (Event == 2); break;}
    }
    return false;
}
int SignIn()
{
    Nusers :: TUser inPending;
    inPending.userNickname = Nios :: GetLine();
    inPending.userPassword = Nios :: GetLine();
    inPending.authority = 1;
    inPending.occupiedBooks.clear();
    inPending.privateInf.realName = Nios :: GetLine();
    inPending.privateInf.telephoneNumber = Nios :: GetNum();
    inPending.privateInf.identificationNumber = Nios :: GetLine();
    EUsers.AddUser(inPending, 0);
    Nlog :: RecordEvent(0, presentUID - 1, presentUID - 1);
    return 0;
}
int Login()
{
    long long inputUserID;
    Nusers :: TPassword inputPassword;
    inputUserID = Nios :: GetNum();
    inputPassword = Nios :: GetLine();
    if (EUsers.CheckUID(inputUserID))
    {
        if (EUsers.TestPassword(inputUserID, inputPassword))
        {
            inOperation = EUsers.GetUser(inputUserID);
            Nios :: Welcome(inOperation.userNickname);
            Nlog :: RecordEvent(1, inputUserID, inputUserID);
        }
        else
            return -2;
    }
    else
        return -1;
    return 0;
}
int Logout()
{
    Nlog :: RecordEvent(2, inOperation.userID, inOperation.userID);
    inOperation.userNickname = "";
    inOperation.userID = 0;
    inOperation.userPassword = "";
    inOperation.occupiedBooks.clear();
    inOperation.authority = 0;
    inOperation.privateInf.realName = "";
    inOperation.privateInf.telephoneNumber = 0;
    inOperation.privateInf.identificationNumber = "";
    Finalization();
    return 0;
}
int BorBook()
{
    long long target = Nios :: GetNum();
    int state;
    state = ELibrary.BorrowOneSpecificBook(target, inOperation.userID);
    if (state != 0) return -1;
    else
    {
        state = EUsers.BorrowOneSpecificBook(target, inOperation.userID);
        if (state == 0)
        {
            Nlog :: RecordEvent(3, target, inOperation.userID);
            return 0;
        }
        else
            return -1;
    }
}
int RetBook()
{
    long long target = Nios :: GetNum();
    int state;
    state = ELibrary.ReturnOneSpecificBook(target, inOperation.userID);
    if (state != 0) return -1;
    else
    {
        state = EUsers.ReturnOneSpecificBook(target, inOperation.userID);
        if (state == 0)
        {
            Nlog :: RecordEvent(4, target, inOperation.userID);
            return 0;
        }
        else
            return -1;
    }
}
int ChangeNickName()
{
    string inputNewNickname;
    long long targetUID;
    targetUID = Nios :: GetNum();
    if (!(EUsers.CheckUID(targetUID))) return -1;
    if (((inOperation.authority == 1) && (inOperation.userID == targetUID)) || (inOperation.authority >= 2))
    {
        inputNewNickname = Nios :: GetLine();
        EUsers.ChangeUserNickname(targetUID, inputNewNickname);
        Nlog :: RecordEvent(5, targetUID, inOperation.userID);
        return 0;
    }
    return -1;
}
int ChangePassword()
{
    Nusers :: TPassword inputNewPassword, inputNewPassword2;
    long long targetUID;
    targetUID = Nios :: GetNum();
    if (!(EUsers.CheckUID(targetUID))) return -1;
    if (((inOperation.authority == 1) && (inOperation.userID == targetUID)) || (inOperation.authority >= 2))
    {
        inputNewPassword = Nios :: GetLine();
        inputNewPassword2 = Nios :: GetLine();
        if (inputNewPassword == inputNewPassword2)
        {
            EUsers.ChangePassword(targetUID, inputNewPassword);
            if (inOperation.userID == targetUID)
                inOperation = EUsers.GetUser(targetUID);
            Nlog :: RecordEvent(6, targetUID, inOperation.userID);
            return 0;
        }
        else
            return -2;
    }
    return -1;
}
int AddBook()
{
    Nlibrary :: TBook inputNewBook;
    inputNewBook.title = Nios :: GetLine();
    inputNewBook.ISBN = Nios :: GetNum();
    inputNewBook.author = Nios :: GetLine();
    inputNewBook.description = Nios :: GetLine();
    inputNewBook.avaliableNum = int(Nios :: GetNum());
    inputNewBook.lowerBoundOfAuthority = int(Nios :: GetNum());
    inputNewBook.occupyingUsers.clear();
    ELibrary.AddBook(inputNewBook, inOperation.userID);
    Nlog :: RecordEvent(7, inputNewBook.ISBN, inOperation.userID);
    return 0;
}
int EditBook()
{
    long long targetISBN;
    Nlibrary :: TBook inputNewBook;
    targetISBN = Nios :: GetNum();
    inputNewBook.title = Nios :: GetLine();
    inputNewBook.author = Nios :: GetLine();
    inputNewBook.ISBN = targetISBN;
    inputNewBook.description = Nios :: GetLine();
    inputNewBook.lowerBoundOfAuthority = int(Nios :: GetNum());
    if (ELibrary.EditBookProperty(targetISBN, inOperation.userID, inputNewBook) == 0)
        Nlog :: RecordEvent(8, targetISBN, inOperation.userID);
    return 0;
}
int DelBook()
{
    long long targetISBN;
    targetISBN = Nios :: GetNum();
    ELibrary.DeleteBookByISBN(targetISBN, inOperation.userID);
    Nlog :: RecordEvent(9, targetISBN, inOperation.userID);
    return 0;
}
int DelUser()
{
    long long targetUID;
    targetUID = Nios :: GetNum();
    return (EUsers.DeleteUserByUID(targetUID, inOperation.userID));
}
int ChangeUserAuthority()
{
    long long workingMode;
    long long targetUID;
    Nusers :: TUser targetUser;
    targetUID = Nios :: GetNum();
    if (!(EUsers.CheckUID(targetUID))) return -1;
    targetUser = EUsers.GetUser(targetUID);
    workingMode = Nios :: GetNum();
    switch(workingMode)
    {
        case MODE_BAN : EUsers.SetUserAuthority(targetUID, -targetUser.authority); break;
        case MODE_UPGRADE : EUsers.SetUserAuthority(targetUID, 2); break;
        case MODE_DEGRADE : EUsers.SetUserAuthority(targetUID, 1); break;
        case MODE_ASSITANT : EUsers.SetUserAuthority(targetUID, 3); break;
        default : break;
    }
    return 0;
}
int SearchBookByKeyword()
{
    string KeyWord1, KeyWord2, KeyWord3;
    KeyWord1 = Nios :: GetLine();
    KeyWord2 = Nios :: GetLine();
    KeyWord3 = Nios :: GetLine();
    ELibrary.SearchBook(KeyWord1, KeyWord2, KeyWord3);
    Nios :: ShowBookRequired();
    return 0;
}
int procFunc(int p)
{
    int message;
    if (CheckAuthority(p, inOperation))
    switch(p)
    {
        case 0 : message = SignIn(); break;
        case 1 : message = Login(); break;
        case -2 : message = Finalization(); break;
        case 2 : message = Logout(); break;
        case -3 : message = SearchBookByKeyword();break;
        case 3 : message = BorBook(); break;
        case 4 : message = RetBook(); break;
        case 5 : message = ChangeNickName(); break;
        case 6 : message = ChangePassword(); break;
        case 7 : message = AddBook(); break;
        case 8 : message = DelBook(); break;
        case 9 : message = EditBook(); break;
        case 10 : message = DelUser(); break;
        case 11 : message = ChangeUserAuthority(); break;
        default : break;
    }
    return message;
}
