#include "quizresult.h"
#include "ui_quizresult.h"

QuizResult::QuizResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuizResult)
{
    ui->setupUi(this);
}

QuizResult::~QuizResult()
{
    delete ui;
}
