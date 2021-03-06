#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Button_Result_released();

    void on_pushButton_Restday_released();

    void on_pushButton_1_released();

    void on_pushButton_3_released();

    void on_pushButton_6_released();

    void on_pushButton_12_released();

    void on_pushButton_finalresult_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
