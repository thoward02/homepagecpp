#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QFont>
#include <QtNetwork>
#include <QJsonDocument>
#include <vector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
   void handleNetworkData(QNetworkReply *networkReply);
private:
    //network
    QNetworkAccessManager networkManager;
    //UI

    Ui::MainWindow *ui;
    //Labels
    QLabel * time;
    QLabel * date;
    QLabel * title;
    QLabel * weatherTitle;
    QLabel * atl;
    QLabel * atlW;

    int timerId;
protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MAINWINDOW_H
