#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <QFont>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel * time;
    QLabel * date;
    QLabel * title;
    int timerId;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H