#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <ctime>
std::string getDay(int day){
    std::string weekday;
    switch(day){
    case 0: weekday  = "Sunday";
        break;
    case 1: weekday = "Monday";
        break;
    case 2: weekday = "Tuesday";
        break;
    case 3: weekday= "Wednesday";
        break;
    case 4: weekday = "Thursday";
        break;
    case 5: weekday = "Friday";
        break;
    case 6: weekday = "Saturday";
        break;
    default:
        weekday = "null";
        break;
    }
    return weekday;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //set window size

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //set up background
    ui->setupUi(this);
    weatherTitle = new QLabel("", this);
    weatherTitle->setGeometry(QRect(10, 250, 301, 41));
    weatherTitle->setStyleSheet("QLabel {color: #0c3444;font: 20pt 'Kiona';font-style:bold;}");
    weatherTitle->setText("W E A T H E R");

    exampleCity = new QLabel("", this);
    exampleCity->setGeometry(QRect(10, 325, 301, 31));
    exampleCity->setText("Atlanta, Ga");
    exampleCity->setStyleSheet("QLabel {font: 25px 'Kiona';color: #0b3241;}");

    exampleWeather = new QLabel("", this);
    exampleWeather->setGeometry(QRect(10, 365, 241, 20));
    exampleWeather->setText("Slightly cloudy");
    exampleWeather->setStyleSheet("QLabel {font: 10pt 'Kiona';color: #0b3241;}");

    exampleCity1 = new QLabel("", this);
    exampleCity1->setGeometry(QRect(10, 420, 301, 31));
    exampleCity1->setText("Austin, Tx");
    exampleCity1->setStyleSheet("QLabel {font: 25px 'Kiona';color: #0b3241;}");

    exampleWeather1 = new QLabel("", this);
    exampleWeather1->setGeometry(QRect(10, 460, 241, 20));
    exampleWeather1->setText("Heavy fog, light rain");
    exampleWeather1->setStyleSheet("QLabel {font: 10pt 'Kiona';color: #0b3241;}");

    //time
    time = new QLabel("",this);
    time->setGeometry(QRect(20, 50, 181, 81));
    time->setStyleSheet("QLabel {font: 40pt 'Kiona';color: #0b3241;}");
    //Day
    std::time_t t1 = std::time(0);
    std::tm* now1 = std::localtime(&t1);
    //weekday -- ctime spits out weekdays in a int, 0 = sunday, 6 = saturday
    std::string cday = std::to_string(now1->tm_wday);
    int intDay = std::stoi(cday);
    std::string weekday = getDay(intDay);
    //compiled
    std::string today = weekday+"\n"+std::to_string((now1->tm_mon)+1)+"-"+ std::to_string(now1->tm_mday)+"-"+std::to_string((now1->tm_yday)+1834);
    date = new QLabel("",this);
    date->setGeometry(20,110,171,81);
    date-> setText(QString::fromStdString(today));
    date->setStyleSheet("QLabel {font: 20pt 'Kiona';color: #0b3241;}");

    //Weather
    //One box is 120 px tall

    //Start the event loop for every 1 second
    timerId = startTimer(1000);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    time_t h = (now->tm_hour);
    time_t m = (now->tm_min);
    std::string hour = std::to_string(h);
    if(hour.length() == 1){
        hour = "0"+hour;
    }
    std::string min = std::to_string(m);
    if(min.length() == 1){
        min = "0"+min;
    }
    std::string timenow = hour +":"+ min;
    time->setText(QString::fromStdString(timenow));

}



