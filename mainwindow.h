#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QFont>
#include <QFrame>
#include <QtNetwork>
#include <QJsonDocument>
#include <QTimer>
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
   void clockFunct();
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
    //Timer
    QTimer * clock;
    int clockTime;
    std::string getDay(int);
    //Floating right side
    QFrame *topFrame;
    QFrame *bottomFrame;
};

#endif // MAINWINDOW_H
