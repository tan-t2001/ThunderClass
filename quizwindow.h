#ifndef QUIZWINDOW_H
#define QUIZWINDOW_H

#include <QDialog>
#include "quizprocess.h"
namespace Ui {
class QuizWindow;
}

class QuizWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QuizWindow(QWidget *parent = nullptr);
    ~QuizWindow();

    //更新答题时间（单位：秒）
    void QuizTime();

    //显示答题时间
    void ShowQuizTime();

private slots:
    void on_QuizAllButton_clicked();

    void on_QuizOneButton_clicked();

    void on_QuizEndButton_clicked();

private:
    Ui::QuizWindow *ui;
    QTimer* m_pQuizTimer;
    QuizProcess* m_pQuizProc;
};

#endif // QUIZWINDOW_H
