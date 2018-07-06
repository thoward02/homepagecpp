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
    //Set up the UI
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint); //TODO: Make window sizeable // dragable
     ui->setupUi(this);

    //Networking pre start
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));
    QUrl url = QStringLiteral("http://api.openweathermap.org/data/2.5/forecast?q=atlanta&APPID=d058fabdf4fd8dd173c64b06d5a9a610");
    networkManager.get(QNetworkRequest(url));

    //Build the weather labels
    atl = new QLabel("", this);
    atl->setGeometry(QRect(10, 225, 301, 31));
    atl->setText("Atlanta, Ga");
    atl->setStyleSheet("QLabel {font: 25px 'Kiona';color: #0b3241;}");

    atlW = new QLabel("", this);
    atlW->setGeometry(QRect(10, 230, 300, 400));
    atlW->setStyleSheet("QLabel {font: 15pt 'Kiona';color: #0b3241;}");
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
    std::string today = weekday+"\n"+std::to_string((now1->tm_mon)+1)+"-"+ std::to_string(now1->tm_mday)+"-"+std::to_string((now1->tm_yday)+1832);
    date = new QLabel("",this);
    date->setGeometry(20,110,171,81);
    date-> setText(QString::fromStdString(today));
    date->setStyleSheet("QLabel {font: 20pt 'Kiona';color: #0b3241;}");


    //Start the event loop for every 1 second
    timerId = startTimer(1000);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::handleNetworkData(QNetworkReply *networkReply){
    if (networkReply->error() == QNetworkReply::NoError) {
        std::vector<std::vector<QString>> weather;
        std::cout << "Success" << std::endl;
        //Output comes in as a Byte array, so we convert it to a string using the line below.
        QString response((QString)networkReply->readAll());
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray jsonArray = jsonObject["list"].toArray();

        foreach (const QJsonValue & value, jsonArray) {
            QJsonObject obj = value.toObject();
            QJsonArray obj1 = obj["weather"].toArray();
            QJsonObject temp = obj["main"].toObject();
            foreach (const QJsonValue & value1, obj1) {
                //okay this is really FUCKING annoying, for some hellish reason OWM thought it was a good idea todo this weather: [{data}]
                //THEY PUT JUST ONE OBJECT IN AN ARRAY, SO NOW I HAVE TO GO INTO THE ARRAY AND FIX IT.
                int tempConvert = temp["temp"].toDouble();

                tempConvert = tempConvert - 273.15;
                QString tempConverted = QString::number(tempConvert);
                QJsonObject weatherValue = value1.toObject();
                QString weatherValueDesc = weatherValue["description"].toString();
                QString dateTime = obj["dt_txt"].toString();
                std::vector<QString> data;
                data.push_back(weatherValueDesc); //the weather
                data.push_back(dateTime); //the date
                data.push_back(tempConverted); //temp in CDeg
                weather.push_back(data);

            }

        }
        int i = 0;
        QString weatherToday;
        QString temp;
        for(auto a:weather){
            QString weather = a[0];
            temp = a[2];
            std::string datetime = a[1].toUtf8().constData();
            datetime =(datetime.substr(11,datetime.length()-3));
            QString datetimeFormatted = QString::fromStdString(datetime);
            weatherToday = weatherToday + datetimeFormatted + " " + weather +"\n" + temp +"°C"+"\n";
            i++;
            if(i > 5){break;}
        }



        atlW->setText(weatherToday);

        qDebug() << "Done";

    }

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



