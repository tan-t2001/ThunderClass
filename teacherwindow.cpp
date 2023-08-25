#include "teacherwindow.h"
#include "ui_teacherwindow.h"
#include <QGuiApplication>
#include <QScreen>
#include <QSize>
#include <QMessageBox>
#include "quizwindow.h"
#include "user.h"

TeacherWindow::TeacherWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherWindow) {
    ui->setupUi(this);
    m_pProc = new TeacherProcess(this);

    //建立信号和槽的连接关系
    //一定要在m_pProc构造后才能建立
    //connect是建立联系，而非调用槽函数
    connect(m_pProc, SIGNAL(ClassBegined()), this, SLOT(ClassBegined()));
    connect(m_pProc, SIGNAL(ClassEnded()), this, SLOT(ClassEnded()));
    connect(m_pProc, SIGNAL(RecvStudentLogin(QString)), this, SLOT(RecvStudentLogin(QString)));
    connect(m_pProc, SIGNAL(RecvStudentLogout(QString)), this, SLOT(RecvStudentLogout(QString)));
    connect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

TeacherWindow::~TeacherWindow() {
    //先disconnected，再释放业务流程类
    disconnect(m_pProc, SIGNAL(ClassBegined()), this, SLOT(ClassBegined()));
    disconnect(m_pProc, SIGNAL(ClassEnded()), this, SLOT(ClassEnded()));
    disconnect(m_pProc, SIGNAL(RecvStudentLogin(QString)), this, SLOT(RecvStudentLogin(QString)));
    disconnect(m_pProc, SIGNAL(RecvStudentLogout(QString)), this, SLOT(RecvStudentLogout(QString)));
    disconnect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    delete m_pProc;
    delete ui;
}

void TeacherWindow::UpdateControlEnabled(bool IsInClass) {
    if (!IsInClass) {
        ui->cmbStudent->clear();
        ui->cmbChatList->clear();
        ui->edtChat->clear();
        ui->ckbScreenShare->setChecked(false);
        ui->ckbVoiceShare->setChecked(false);
        ui->btnQuiz->setEnabled(!IsInClass);
    }
    ui->btnBeginClass->setEnabled(!IsInClass);
    ui->btnEndClass->setEnabled(IsInClass);
    ui->btnSend->setEnabled(IsInClass);
    ui->btnQuiz->setEnabled(IsInClass);
    ui->ckbVoiceShare->setEnabled(IsInClass);
    ui->ckbScreenShare->setEnabled(IsInClass);
    ui->edtChat->setEnabled(IsInClass);
}

void TeacherWindow::showEvent(QShowEvent* e) {
    int iWidth = QGuiApplication::screens()[0]->size().width();
    this->move((iWidth - this->width()) / 2, 0);
    e->accept();
}

void TeacherWindow::closeEvent (QCloseEvent* e) {
    if (m_pProc->IsInClass) {
        e->ignore();
    }
}

void TeacherWindow::on_btnBeginClass_clicked() {
    if (m_pProc->BeginClass()) {
        ui->cmbStudent->clear();
        ui->cmbChatList->clear();
    }
}

void TeacherWindow::on_ckbScreenShare_clicked()
{
    if (ui->ckbScreenShare->isChecked()) {
        ui->ckbScreenShare->setChecked(m_pProc->StartScreenShare());
    }
    else {
        ui->ckbScreenShare->setChecked(m_pProc->StopScreenShare());
    }
}

void TeacherWindow::on_ckbVoiceShare_clicked()
{
    if (ui->ckbVoiceShare->isChecked()) {
        ui->ckbVoiceShare->setChecked(m_pProc->StartVoiceShare());
    }
    else {
        ui->ckbVoiceShare->setChecked(m_pProc->StopVoiceShare());
    }
}

void TeacherWindow::on_btnEndClass_clicked() {
    m_pProc->EndClass();
}

void TeacherWindow::on_btnSend_clicked() {
    if (m_pProc->SendStrChat(ui->edtChat->text())) {
        ui->edtChat->clear();
    }
}

void TeacherWindow::ClassBegined() {
    UpdateControlEnabled(true);
}

void TeacherWindow::ClassEnded() {
    UpdateControlEnabled(false);
}

void TeacherWindow::RecvStudentLogin(QString Name) {
    int idx = ui->cmbStudent->findText(Name);
    if (idx == -1) {
        ui->cmbStudent->insertItem(0, Name);
        idx = 0;
    }
    ui->cmbStudent->setCurrentIndex(idx);
}

void TeacherWindow::RecvStudentLogout(QString Name) {
    int idx = ui->cmbStudent->findText(Name);
    if (idx != -1) {
        ui->cmbStudent->removeItem(idx);
    }
}

void TeacherWindow::RecvChat(QString Msg) {
    ui->cmbChatList->insertItem(0, Msg);
    ui->cmbChatList->setCurrentIndex(0);
}

void TeacherWindow::on_btnQuiz_clicked()
{
    if (m_pProc->IsInClass) {
        QuizWindow* pQuizWindow;
        pQuizWindow = new QuizWindow(this);
        pQuizWindow->setWindowTitle("教师 "+QString::fromStdString(User::GetLoginedUser()->GetName())+" 编辑题目");
        pQuizWindow->exec();
        delete pQuizWindow;
        pQuizWindow = nullptr;
    }
    else {
        QMessageBox::information(NULL, "提示", "还未开课！");
    }
}
