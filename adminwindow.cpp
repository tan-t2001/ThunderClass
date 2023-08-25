#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "admin.h"
#include <QMessageBox>
#include "User.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    m_pProc = new AdminProcess();
    m_pTimer = new QTimer();
    m_pTimer->setInterval(100);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    m_pTimer->start();
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    this->setWindowTitle("管理员模式");
}

AdminWindow::~AdminWindow()
{
    m_pTimer->stop();
    delete m_pTimer;
    m_pTimer = nullptr;
    delete m_pProc;
    m_pProc = nullptr;
    delete ui;
}

void AdminWindow::on_AddButton_clicked()
{
    Admin* p = dynamic_cast<Admin*>(const_cast<User*>(User::GetUser("Admin")));
    string AddName = ui->AddName->text().toStdString();
    string AddPassword = ui->AddPassword->text().toStdString();
    string AddType = ui->AddType->text().toStdString();
    if (p->AddUser(AddName,AddPassword,AddType)) {
        QMessageBox::information(NULL, "提示", "新增成功！");
    }
    else {
        QMessageBox::information(NULL, "提示", "新增失败！");
    }
}

void AdminWindow::on_DeleteButton_clicked()
{
    Admin* p = dynamic_cast<Admin*>(const_cast<User*>(User::GetUser("Admin")));
    string DeleteName = ui->DeleteName->text().toStdString();
    if (p->DeleteUser(DeleteName)) {
        QMessageBox::information(NULL, "提示", "删除成功！");
    }
    else {
        QMessageBox::information(NULL, "提示", "删除失败！");
    }
}

void AdminWindow::on_EditButton_clicked()
{
    Admin* p = dynamic_cast<Admin*>(const_cast<User*>(User::GetUser("Admin")));
    string EditedName = ui->EditedName->text().toStdString();
    string EditName = ui->EditName->text().toStdString();
    string EditPassword = ui->EditPassword->text().toStdString();
    string EditType = ui->EditType->text().toStdString();
    if (p->EditUser(EditedName,EditName,EditPassword,EditType)) {
        QMessageBox::information(NULL, "提示", "修改成功！");

    }
    else {
        QMessageBox::information(NULL, "提示", "修改失败！");
    }
}
