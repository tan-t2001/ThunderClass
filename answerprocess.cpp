#include "answerprocess.h"

AnswerProcess::AnswerProcess(const StudentProcess* pStudentProc):IsInQuiz(m_pIsInQuiz)
{
    //初始化内部状态
    m_pIsInQuiz = 0;
    StudentProcess* m_pStudentProc = const_cast<StudentProcess*>(pStudentProc);
}

void AnswerProcess::StartAnswer() {
    m_pIsInQuiz = 1;
}

void AnswerProcess::EndAnswer() {
    m_pIsInQuiz = 0;
}
