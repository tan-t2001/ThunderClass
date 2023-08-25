#include "quizresultwindow.h"
#include "ui_quizresultwindow.h"

QuizResultWindow::QuizResultWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuizResultWindow)
{
    ui->setupUi(this);
}

QuizResultWindow::~QuizResultWindow()
{
    delete ui;
}
