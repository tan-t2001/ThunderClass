#include "answerwindow.h"
#include "ui_answerwindow.h"

/*************************************************************************
【函数名称】AnswerWindow::AnswerWindow
【函数功能】构造函数，用Quiz文本构造答题界面
【参数】无
【返回值】构造函数不可有返回值
【开发者及日期】谭跳 2020-6-19
*************************************************************************/
AnswerWindow::AnswerWindow(QWidget *parent,const QString& Quiz) :
    QDialog(parent),
    ui(new Ui::AnswerWindow)
{
    ui->setupUi(this);
    //将获得的题目文本在题目文本框打印出来
    //答题业务流程类一经创建，便进入答题环节
    m_pAnswerProc->StartAnswer();
}

AnswerWindow::~AnswerWindow()
{
    delete ui;
}

/*************************************************************************
【函数名称】AnswerWindow::AnswerTime
【函数功能】当处于答题环节时以秒为单位计时
【参数】无
【返回值】无
【开发者及日期】谭跳 2020-6-19
*************************************************************************/
void AnswerWindow::AnswerTime() {
    //处于答题环节时计时
    if (m_pAnswerProc->IsInQuiz) {
        m_pAnswerProc->m_pAnswerTime += 1000;
    }
}

/*************************************************************************
【函数名称】AnswerWindow::ShowAnswerTime
【函数功能】在答题界面上显示已用答题时间
【参数】无
【返回值】无
【开发者及日期】谭跳 2020-6-19
*************************************************************************/
void AnswerWindow::ShowAnswerTime() {
    ui->Timelabel->setText(QString::number(m_pAnswerProc->m_pAnswerTime/1000));
}

/*************************************************************************
【函数名称】AnswerWindow::on_pushButton_clicked
【函数功能】信号沟槽，点击答题界面上的“结束答题”按钮后结束答题并将选项消息发送给教师
【参数】无
【返回值】无
【开发者及日期】谭跳 2020-6-19
*************************************************************************/
void AnswerWindow::on_pushButton_clicked()
{
    m_pAnswerProc->EndAnswer();
}

/*************************************************************************
【函数名称】AnswerWindow::on_pushButton_clicked
【函数功能】信号沟槽，若勾选A选项则，将数组m_Options的第一个元素赋值为1，否则赋值为0
【参数】无
【返回值】无
【开发者及日期】谭跳 2020-6-19
*************************************************************************/
void AnswerWindow::on_AcheckBox_clicked()
{
    if (ui->AcheckBox->isChecked()) {
        m_pAnswerProc->m_Options[0] = 1;
    }
    else {
        m_pAnswerProc->m_Options[0] = 0;
    }
}

void AnswerWindow::on_BcheckBox_clicked()
{
    if (ui->BcheckBox->isChecked()) {
        m_pAnswerProc->m_Options[1] = 1;
    }
    else {
        m_pAnswerProc->m_Options[1] = 0;
    }
}

void AnswerWindow::on_CcheckBox_clicked()
{
    if (ui->CcheckBox->isChecked()) {
        m_pAnswerProc->m_Options[2] = 1;
    }
    else {
        m_pAnswerProc->m_Options[2] = 0;
    }
}

void AnswerWindow::on_DcheckBox_clicked()
{
    if (ui->DcheckBox->isChecked()) {
        m_pAnswerProc->m_Options[3] = 1;
    }
    else {
        m_pAnswerProc->m_Options[3] = 0;
    }
}
