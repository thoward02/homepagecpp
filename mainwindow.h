#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QtNetwork>
#include <QUrl>
#include <QKeyEvent>
#include <QJsonDocument>
#include <QTimer>
#include <vector>
#include <ctime>
#include <algorithm>
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
   void handleWeatherData(QNetworkReply *networkReply){
        if (networkReply->error() == QNetworkReply::NoError) {
            std::vector<std::vector<QString>> weather;

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


        }
        else{
            atlW->setText("");
            atl->setText("Null--No Connection");
        }
    }
   void closeFunct(){
       qDebug() << "close";
       MainWindow::close();
   }
   void login(){
       loginButton->setHidden(true);
       //Reset theBox borders
       lerr->setText(""); //Reset the err text
       passwordEntry->setStyleSheet("QLineEdit{background-color:#066185;border:none;font: 10pt 'Comfortaa';color: #439cc1;}");
       usernameEntry->setStyleSheet("QLineEdit{background-color:#066185;border:none;font: 10pt 'Comfortaa';color: #439cc1;}");
       qDebug() << "Login Called\n";
       bool loginCont = false; //Okay so I could put the rest of my code in that last else statement, but that would just look messy. If you know CPP and this is not the way todo it pls tell me <3
       std::string usernameD = usernameEntry->text().toStdString();
       std::transform(usernameD.begin(), usernameD.end(), usernameD.begin(), ::tolower); //Convert the username to all lowercase C:
       std::string passwordD = passwordEntry->text().toStdString();
       //Check and make sure username and password fields have content
       if(usernameD.size() < 1){
           MainWindow::displayLoginErr(0);
       }else{
           if(passwordD.size() < 1){
               MainWindow::displayLoginErr(1);
           }else{
               loginCont = true;
           }
       }
       if(loginCont==true){
           //Check server for username and pass
           QNetworkAccessManager *manager = new QNetworkAccessManager(this); //Ima just init it here instead of the header.
           QUrl url = QStringLiteral("http://127.0.0.1/api/login");
           QUrlQuery params;
           params.addQueryItem("username", QString::fromStdString(usernameD));
           params.addQueryItem("password", QString::fromStdString(passwordD));
           QNetworkRequest request(url);
           request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
           connect(manager, SIGNAL(finished(QNetworkReply*)),
                   this, SLOT(loginRequest(QNetworkReply*)));
           manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
       }
       //delete loginForeground; //This is how we get rid of the login foreground, is there a way to just remove it from screen and save it in memory maybe?
   }
   void loginRequest(QNetworkReply *networkReply){
       if (networkReply->error() == QNetworkReply::NoError) {
           QString response((QString)networkReply->readAll());
           QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
           QJsonObject jsonObject = jsonResponse.object();
           QJsonObject successMessage = jsonObject.value("response").toObject();
           if(successMessage["0"]=="Success"){
               QString token = successMessage["token"].toString();
               MainWindow::loadServerUi();
           }else{
               MainWindow::displayLoginErr(2);
           }

       }else{
           //No connection found -- return err
           MainWindow::displayLoginErr(4);
       }
   }
   void clockFunct(){
       //Time
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

private:
    //network
    QNetworkAccessManager weatherNetworkManager;
    //UI
    Ui::MainWindow *ui;
    //Labels
    QLabel * time;
    QLabel * date;
    QLabel * title;
    QLabel * weatherTitle;
    QLabel * atl;
    QLabel * atlW;
    QLabel * loginTitle;
    QLabel * username;
    QLabel * password;
    QLabel * lerr;
    //Timer
    QTimer * clock;
    bool loggedIn;
    QLineEdit * usernameEntry;
    QLineEdit * passwordEntry;
    QPushButton * loginButton;
    void keyPressEvent(QKeyEvent *enter); //For hitting enter to login ~ need to del this event on login.
    void displayLoginErr(int);
    void loadServerUi();
    std::string getDay(int day) {
    const std::string dayName[7] = {"Sunday", "Monday", "Tuesday", "Wedensday", "Thursday", "Friday", "Saturday"};
        if(day >= 0 && day <= 7){
            return dayName[day];
        }
        return "null";
    }
    QFrame *topFrame;
    QFrame *loginForeground;
    QString token; //This is for network requests
};
#endif // MAINWINDOW_H
