#ifndef QUIZPROCESS_H
#define QUIZPROCESS_H
#include <QString>
#include <Server.h>
#include "teacherprocess.h"
using namespace std;

class QuizProcess:public TeacherProcess
{
public:
    //由当前的TeacherProcess创建本类
    QuizProcess(const TeacherProcess* pTeacherProc);

    //答题时间
    unsigned int m_pQuizTime;

    //是否处于答题环节
    const bool& IsInQuiz;

    //开始答题
    void StartQuiz();

    //结束答题
    void EndQuiz();

    //将题面与选项结合成题目
    void Combine(const QString& Question,const QString& OptA,const QString& OptB,const QString& OptC,const QString& OptD);

    //向全员发题
    bool SendQuizToAll(const string& QuestionAndOptions);

    //向随机一位同学发题
    bool SendQuizToOne(const string& QuestionAndOptions,unsigned int& ReiceiverNum);

    //由题面及选项组合成的题目
    string QuestionAndOptions;

    //QString转换为String
    string QstrToStr(const QString& Qstr) {
        QByteArray cdata = Qstr.toUtf8();
        return string(cdata);
    }

private:
    //是否处于答题环节
    bool m_pIsInQuiz;

    //创建本类的TeacherProcess指针
    TeacherProcess* m_pTeacherProc;
};

#endif // QUIZPROCESS_H
