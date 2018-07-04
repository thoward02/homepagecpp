#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <ctime>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //set window size

    //set up background
    ui->setupUi(this);
    title = new QLabel("T   I   M   E",this); //I cant figure out how to use letterSpacing()
    title->setGeometry(QRect(60, 60, 140, 31));
    title->setStyleSheet("QLabel {color: #0c3444;font: 16pt 'Kiona';}");

    //time
    time = new QLabel("",this);
    time->setGeometry(QRect(60, 80, 181, 81));
    time->setStyleSheet("QLabel {font: 40pt 'Kiona';color: #0b3241;}");
    //Day
    std::time_t t1 = std::time(0);
    std::tm* now1 = std::localtime(&t1);
    //weekday -- ctime spits out weekdays in a int, 0 = sunday, 6 = saturday
    std::string cday = std::to_string(now1->tm_wday);
    int intDay = std::stoi(cday);
    std::string weekday;
    switch(intDay){
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
    //compiled
    std::string today = weekday+"\n"+std::to_string((now1->tm_mon)+1)+"-"+ std::to_string(now1->tm_mday)+"-"+std::to_string((now1->tm_yday)+1834);
    date = new QLabel("",this);
    date->setGeometry(60,140,171,81);
    date-> setText(QString::fromStdString(today));
    date->setStyleSheet("QLabel {font: 20pt 'Kiona';color: #0b3241;}");
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




