#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include <QShowEvent>
#include <QTimer>
#include "teacherprocess.h"

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = nullptr);
    ~TeacherWindow();

private slots:
    void closeEvent (QCloseEvent* e) override;
    void showEvent(QShowEvent* e) override;

    void on_btnBeginClass_clicked();

    void on_ckbScreenShare_clicked();

    void on_ckbVoiceShare_clicked();

    void on_btnEndClass_clicked();

    void on_btnSend_clicked();

    void ClassBegined();

    void ClassEnded();

    void RecvStudentLogin(QString Name);

    void RecvStudentLogout(QString Name);

    void RecvChat(QString Msg);

    void on_btnQuiz_clicked();

private:
    Ui::TeacherWindow *ui;
    TeacherProcess* m_pProc;
    QTimer* m_pTimer;
    void UpdateControlEnabled(bool IsInClass);
};

#endif // TEACHERWINDOW_H
