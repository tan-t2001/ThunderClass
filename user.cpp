#include "user.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"

unsigned int User::m_uUserCount = 0;
const unsigned int& User::UserCount = User::m_uUserCount;
vector<User*> User::m_UserList;
User* User::m_LoginedUser = nullptr;

User::User(const string& Name, const string& Password, const string& Type):Type(m_sType) {
    m_sName = Name;
    m_sPassword = Password;
    m_sType = Type;
    m_uUserCount++;
}

User::User(ifstream& inFile):Type(m_sType) {
    getline(inFile, m_sName);
    getline(inFile, m_sPassword);
    getline(inFile, m_sType);
    m_uUserCount++;
}


User::~User() {
    m_uUserCount--;
}

User::User(const User& anUser):Type(m_sType) {
    m_sName = anUser.m_sName;
    m_sPassword = anUser.m_sPassword;
    m_sType = anUser.m_sType;
}

User& User::operator=(const User& anUser) {
    if (this != &anUser) {
        m_sName = anUser.m_sName;
        m_sPassword = anUser.m_sPassword;
        m_sType = anUser.m_sType;
    }
    return *this;
}

Message User::ToMessage() const {
    unsigned int NameLen = m_sName.length();
    unsigned int PasswordLen = m_sPassword.length();
    unsigned char* Buffer = new unsigned char[NameLen + PasswordLen + 2 * sizeof (NameLen)];
    memcpy(Buffer, (char*)&NameLen, sizeof(NameLen));
    memcpy(Buffer + sizeof(NameLen), m_sName.c_str(), NameLen);
    memcpy(Buffer + sizeof(NameLen) + NameLen, (char*)&PasswordLen, sizeof(PasswordLen));
    memcpy(Buffer + 2 * sizeof(NameLen) + NameLen, m_sPassword.c_str(), PasswordLen);
    Message ret(MSG_ID_PSW, Buffer, NameLen + PasswordLen + 2 * sizeof (NameLen));
    delete [] Buffer;
    return ret;
}

void User::SaveToFileStream(ofstream& OutFile) const {
    OutFile << m_sName << endl;
    OutFile << m_sPassword << endl;
    OutFile << m_sType << endl;
}

string User::GetName() const{
    return m_sName;
}

bool User::TestPassword(const string& Password) const {
    if (Password == m_sPassword) {
        return true;
    }
    else {
        return false;
    }
}

bool User::AddUser(const string& Name, const string& Password, const string& Type) {
    Admin* p = nullptr;
    p = dynamic_cast<Admin*>(this);
    if (p != nullptr) {
        for (unsigned int i = 0; i < m_UserList.size(); i++) {
            if (m_UserList[i]->m_sName == Name) {
                return false;
            }
        }
        if (Type == "Admin") {
            for (unsigned int i = 0; i < m_UserList.size(); i++) {
                if (m_UserList[i]->Type == "Admin") {
                    return false;
                }
            }
            m_UserList.push_back(new Admin());
            SaveToFile("UserInformation.txt");
            return true;
        }
        else if (Type == "Teacher") {
            m_UserList.push_back(new Teacher(Name, Password));
            SaveToFile("UserInformation.txt");
            return true;
        }
        else {
            m_UserList.push_back((User*) new Student(Name, Password));
            SaveToFile("UserInformation.txt");
            return true;
        }
    }
    else {
        return false;
    }
}

/*
【函数名称】User::DeleteUser
【函数功能】按用户名从基类User的静态对象vector<User*> UserList中删除一个用户对象
【参数】用户名
【返回值】true表示删除成功，false表示删除失败
*/
bool User::DeleteUser(const string &Name) {
    Admin* p = nullptr;
    p = dynamic_cast<Admin*>(this);
    if (p != nullptr) {
        if (Name == "Admin") {
            return false;
        }
        for (unsigned int i = 0; i < m_UserList.size(); i++) {
            if (m_UserList[i]->m_sName == Name) {
                m_UserList.erase(m_UserList.begin()+i);
                SaveToFile("UserInformation.txt");
                return true;
            }
        }
    }
    else {
        return false;
    }
}

bool User::EditUser(const string &OldName,const string& Name, const string& Password, const string& Type) {
    return DeleteUser(OldName) && AddUser(Name,Password,Type);
}

//2020-05-19 范静涛增加了未找到文件则自动创建只包含Admin用户的功能
//2020-05-23 范静涛修改了重复调用此函数导致用户数翻倍的问题，感谢李浦豪同学发现此问题
void User::LoadFromFile(const string& FileName) {
    ifstream inFile(FileName.c_str());
    if (inFile.fail()) {
        ofstream OutFile(FileName.c_str(), ios::out | ios::app);
        OutFile << 1 << endl << "Admin" << endl << "Admin" << endl << "Admin" << endl;
        OutFile.close();
    }
    inFile.close();
    inFile.open(FileName.c_str());

    //2020-05-23 新增开始
    for (int i = m_UserList.size() - 1; i >= 0; i--) {
        User* pUser = m_UserList[i];
        delete pUser;
    }
    //2020-05-23 新增结束
    m_UserList.clear();
    unsigned int UserCount;
    inFile >> UserCount;
    inFile.get();
    for (unsigned int i = 0; i < UserCount; i++) {
        string Name;
        string Password;
        string Type;
        getline(inFile, Name);
        getline(inFile, Password);
        getline(inFile, Type);
        if (Type == "Admin") {
            m_UserList.push_back(new Admin());
        }
        else if (Type == "Teacher") {
            m_UserList.push_back(new Teacher(Name, Password));
        }
        else {
            m_UserList.push_back((User*)new Student(Name, Password));
        }
    }
    inFile.close();
}

void User::SaveToFile(const string& FileName) {
    ofstream OutFile(FileName.c_str());
    OutFile << m_UserList.size() << endl;
    for (unsigned int i = 0; i < m_UserList.size(); i++) {
        m_UserList[i]->SaveToFileStream(OutFile);
    }
}

const User* User::GetUser(const string& Name, const string& Password) {
    const User* Current = nullptr;
    for (unsigned int i = 0; i < m_UserList.size(); i++) {
        if (m_UserList[i]->GetName() == Name && m_UserList[i]->TestPassword(Password)) {
            Current = m_UserList[i];
            m_LoginedUser = m_UserList[i];
            break;
        }
    }
    return Current;
}

const User* User::GetUser(const string& Name) {
    const User* Current = nullptr;
    for (unsigned int i = 0; i < m_UserList.size(); i++) {
        if (m_UserList[i]->GetName() == Name) {
            Current = m_UserList[i];
            break;
        }
    }
    return Current;
}

User* User::GetLoginedUser() {
    return m_LoginedUser;
}

void User::OfflineAllStudents() {
    Student* pStudent;
    for (unsigned int i = 0; i < m_UserList.size(); i++) {
        if (m_UserList[i]->Type == "Student") {
            pStudent = dynamic_cast<Student*>(m_UserList[i]);
            pStudent->Offline();
        }
    }
}
