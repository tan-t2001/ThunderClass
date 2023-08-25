#include "loginprocess.h"

LoginProcess::LoginProcess()
{
    User::LoadFromFile("UserInformation.txt");
}

LoginResult LoginProcess::Login(const QString& UserName, const QString& Password) {
    const User* pCurrentUser = User::GetUser(QStrToStr(UserName), QStrToStr(Password));
    if (pCurrentUser == nullptr) {
        return LR_NOUSER;
    }
    if (pCurrentUser->Type == "Admin") {
        return LR_ADMIN;
    }
    else if (pCurrentUser->Type == "Teacher") {
        return LR_TEACHER;
    }
    else {
        return LR_STUDENT;
    }
}

