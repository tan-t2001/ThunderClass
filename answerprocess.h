#ifndef ANSWERPROCESS_H
#define ANSWERPROCESS_H
#include "studentprocess.h"

class AnswerProcess
{
public:
    //由当前的StudentProcess创建本类
    AnswerProcess(const StudentProcess* pStudentProc);
    //是否处于答题环节
    const bool& IsInQuiz;

    //答题时间
    unsigned int m_pAnswerTime;

    //开始答题
    void StartAnswer();

    //结束答题
    void EndAnswer();

    //选择选项记录数组(初始化为全0）
    bool m_Options[5] = {0};

private:
    //是否处于答题环节
    bool m_pIsInQuiz;

    //创建本类的StudentProcess指针
    StudentProcess* m_pStudentProc;

};

#endif // ANSWERPROCESS_H
