#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
#include "studentprocess.h"

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();
    void closeEvent (QCloseEvent* e) override;
    void UpdateControlEnabled(bool IsInClass);

private slots:
    void on_btnEnterClass_clicked();
    void on_btnExitClass_clicked();
    void on_btnSend_clicked();
    void TimerEvent();
    //统计处于屏幕焦点时间
    void AttentionTime();
    //进入课堂信号
    void ClassEntered();
    //退出课堂信号
    void ClassExited();
    //收到文字消息信号
    void RecvChat(QString Msg);
    //收到屏幕共享消息信号
    void RecvScreen(QImage Img);
    //实时更新处于窗口焦点时间
    void ShowAttentionTime();
    //实时更新上课时间
    void ShowTime();
private:
    Ui::StudentWindow *ui;
    StudentProcess* m_pProc;
    QTimer* m_pTimer;
    QTimer* m_pAttentionTimer;
};

#endif // STUDENTWINDOW_H
