#ifndef QUIZRESULT_H
#define QUIZRESULT_H

#include <QDialog>

namespace Ui {
class QuizResult;
}

class QuizResult : public QDialog
{
    Q_OBJECT

public:
    explicit QuizResult(QWidget *parent = nullptr);
    ~QuizResult();

private:
    Ui::QuizResult *ui;
};

#endif // QUIZRESULT_H
