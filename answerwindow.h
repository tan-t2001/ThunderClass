#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

#include <QDialog>
#include "answerprocess.h"
#include <QTimer>
#include <QString>

namespace Ui {
class AnswerWindow;
}

class AnswerWindow : public QDialog
{
    Q_OBJECT

public:
    //利用题目生成答题界面
    explicit AnswerWindow(QWidget *parent = nullptr,const QString& Quiz = "");
    ~AnswerWindow();

    //统计答题时间
    void AnswerTime();

    //展示答题时间
    void ShowAnswerTime();

private slots:
    void on_pushButton_clicked();

    void on_AcheckBox_clicked();

    void on_BcheckBox_clicked();

    void on_CcheckBox_clicked();

    void on_DcheckBox_clicked();

private:
    Ui::AnswerWindow *ui;
    AnswerProcess* m_pAnswerProc;
    QTimer* AnswerTimer;
};

#endif // ANSWERWINDOW_H
