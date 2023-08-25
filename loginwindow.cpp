#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QImage>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    QMessageBox msgBox;
    TeacherWindow* pTeacherWindow;
    StudentWindow* pStudentWindow;
    AdminWindow* pAdminWindow;
    LoginResult res = Proc.Login(ui->edtName->text(), ui->edtPassword->text());
    switch (res) {
    case LR_NOUSER :
        msgBox.setText("登录失败");
        msgBox.exec();
        break;
    case LR_ADMIN :
        this->setWindowOpacity(0.0);
        pAdminWindow = new AdminWindow(this);
        pAdminWindow->exec();
        this->setWindowOpacity(1.0);
        delete pAdminWindow;
        pAdminWindow = nullptr;
        break;
    case LR_TEACHER :
        this->setWindowOpacity(0.0);
        pTeacherWindow = new TeacherWindow(this);
        pTeacherWindow->setWindowTitle("教师 " + QString(User::GetLoginedUser()->GetName().c_str()));
        pTeacherWindow->exec();
        this->setWindowOpacity(1.0);
        delete pTeacherWindow;
        pTeacherWindow = nullptr;
        break;
    default:
        this->setWindowOpacity(0.0);
        pStudentWindow = new StudentWindow(this);
        pStudentWindow->exec();
        this->setWindowOpacity(1.0);
        delete pStudentWindow;
        pStudentWindow = nullptr;
    }
}

void LoginWindow::on_btnExit_clicked()
{
    this->close();
}
