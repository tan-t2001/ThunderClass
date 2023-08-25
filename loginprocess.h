#ifndef LOGINPROCESS_H
#define LOGINPROCESS_H
#include <vector>
#include <string>
#include <QString>
#include "user.h"
using namespace std;

enum LoginResult {LR_NOUSER, LR_ADMIN, LR_TEACHER, LR_STUDENT};

class LoginProcess
{
public:
    LoginProcess();
    LoginResult Login(const QString& UserName, const QString& Password);
    string QStrToStr(const QString& Qstr) {
        QByteArray cdata = Qstr.toUtf8();
        return string(cdata);
    }
private:
};

#endif // LOGINPROCESS_H
