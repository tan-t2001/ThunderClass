#include "quizprocess.h"
#include "Message.h"
#include "Server.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>

QuizProcess::QuizProcess(const TeacherProcess* pTeacherProc):IsInQuiz(m_pIsInQuiz)
{
    //初始化内部状态
    m_pQuizTime = 0;
    m_pIsInQuiz = false;
    TeacherProcess* m_pTeacherProc = const_cast<TeacherProcess*>(pTeacherProc);
}

void QuizProcess::StartQuiz() {
    m_pIsInQuiz = true;

}

void QuizProcess::EndQuiz() {
    m_pIsInQuiz = false;
}

void QuizProcess::Combine(const QString& Question,const QString& OptA,const QString& OptB,const QString& OptC,const QString& OptD) {
    string QuestionAndOptions = QstrToStr(Question)
            + '\n'
            + '\n'
            + "(A)  "
            + QstrToStr(OptA)
            + '\n'//Debug标注：加上此'\n'开始QuestionAndOptions变为乱码
            + "(B)  "
            + QstrToStr(OptB)
            + '\n'
            + "(C)  "
            + QstrToStr(OptC)
            + '\n'
            + "(D)  "
            + QstrToStr(OptD);
}

bool QuizProcess::SendQuizToAll(const string& QuestionAndOptions) {
    if (!m_pIsInQuiz) {
        return m_pIsInQuiz;
    }
    Message QueAndOpt(MSG_STRING, (unsigned char*)QuestionAndOptions.c_str(), QuestionAndOptions.length());
    m_pTeacherProc->pServer->SendToAll(QueAndOpt);
    qDebug() << "TP: send to all quiz:" << QString::fromStdString(QuestionAndOptions);
    return m_pIsInQuiz;
}

bool QuizProcess::SendQuizToOne(const string& QuestionAndOptions,unsigned int& ReceiverNum) {
    if (!m_pIsInQuiz) {
        return m_pIsInQuiz;
    }
    Message QueAndOpt(MSG_STRING, (unsigned char*)QuestionAndOptions.c_str(), QuestionAndOptions.length());
    m_pTeacherProc->pServer->SendTo(ReceiverNum,QueAndOpt);
    qDebug() << "TP: send to all quiz:" << QString::fromStdString(QuestionAndOptions);
    return m_pIsInQuiz;
}
