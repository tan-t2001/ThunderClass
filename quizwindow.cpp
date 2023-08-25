#include "quizwindow.h"
#include "ui_quizwindow.h"
#include <QTimer>
#include "user.h"

QuizWindow::QuizWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuizWindow)
{
    ui->setupUi(this);
    m_pQuizTimer = new QTimer();
    m_pQuizTimer->setInterval(1000);
    connect(m_pQuizTimer, SIGNAL(timeout()), this, SLOT(QuizTime()));
    m_pQuizTimer->start();
}

QuizWindow::~QuizWindow()
{
    m_pQuizTimer->stop();
    disconnect(m_pQuizTimer, SIGNAL(timeout()), this, SLOT(QuizTime()));
    delete m_pQuizTimer;
    m_pQuizTimer = nullptr;
    delete m_pQuizProc;
    m_pQuizProc = nullptr;
    delete ui;
}

void QuizWindow::QuizTime() {
    //处于答题环节时计时
    if (m_pQuizProc->IsInQuiz) {
        m_pQuizProc->m_pQuizTime += 1000;
    }
}

void QuizWindow::ShowQuizTime() {
    ui->Timelabel->setText(QString::number(m_pQuizProc->m_pQuizTime/1000));
}

void QuizWindow::on_QuizAllButton_clicked()
{
    m_pQuizProc->Combine(ui->QuestionEdit->toPlainText(),ui->AOption->text(),ui->BOption->text(),ui->COption->text(),ui->DOption->text());
    m_pQuizProc->StartQuiz();
    m_pQuizProc->SendQuizToAll(m_pQuizProc->QuestionAndOptions);
}

void QuizWindow::on_QuizOneButton_clicked()
{
    srand((int)time(0));
    unsigned int LuckyNum = rand()%m_pQuizProc->pServer->ConnectionNum();
    m_pQuizProc->StartQuiz();
    m_pQuizProc->SendQuizToOne(m_pQuizProc->QuestionAndOptions,LuckyNum);
}

void QuizWindow::on_QuizEndButton_clicked()
{
    m_pQuizProc->EndQuiz();
}
