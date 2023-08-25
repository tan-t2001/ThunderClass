#ifndef QUIZRESULTWINDOW_H
#define QUIZRESULTWINDOW_H

#include <QDialog>

namespace Ui {
class QuizResultWindow;
}

class QuizResultWindow : public QDialog
{
    Q_OBJECT

public:
    explicit QuizResultWindow(QWidget *parent = nullptr);
    ~QuizResultWindow();

private:
    Ui::QuizResultWindow *ui;
};

#endif // QUIZRESULTWINDOW_H
