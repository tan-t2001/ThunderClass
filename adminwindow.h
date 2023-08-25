#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include "adminprocess.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();
private slots:
    void on_AddButton_clicked();

    void on_DeleteButton_clicked();

    void on_EditButton_clicked();

private:
    Ui::AdminWindow *ui;
    AdminProcess* m_pProc;
    QTimer* m_pTimer;
    QLabel *label;
};

#endif // ADMINWINDOW_H
