#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>





MainWindow::~MainWindow(){
    delete ui;
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //Set up the UI
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint); //TODO: Make window sizeable // dragable
    ui->setupUi(this);
    QPushButton * extBut = new QPushButton("E X I T", this);
    extBut->setGeometry(QRect(0, 929, 321, 151));
    extBut->setStyleSheet("QPushButton{background-color: rgba(0,0,0,0);border: none;font: 30px 'Kiona';color:#439cc1;}QPushButton:hover {background-color: rgba(0,0,0,0);border: none;font: 30px 'Kiona';color: #11465B;}");
    connect(extBut, SIGNAL (clicked()),this, SLOT (closeFunct()));
    //Networking pre start
    connect(&weatherNetworkManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(handleWeatherData(QNetworkReply*)));
    QUrl url = QStringLiteral("http://api.openweathermap.org/data/2.5/forecast?q=30549&APPID=d058fabdf4fd8dd173c64b06d5a9a610");
    weatherNetworkManager.get(QNetworkRequest(url));
    //Build the weather labels
    int weatherPadding = 20;
    atl = new QLabel("", this);
    atl->setGeometry(QRect(weatherPadding, 220, 301, 31));
    atl->setText("Jefferson, Ga");
    atl->setStyleSheet("QLabel {font: 25px 'Kiona';color: #439cc1;}");

    atlW = new QLabel("", this);
    atlW->setGeometry(QRect(weatherPadding, 230, 300, 400));
    atlW->setStyleSheet("QLabel {font: 15pt 'Kiona';color: #439cc1;}");
    //time
    time = new QLabel("",this);
    time->setGeometry(QRect(weatherPadding + 10, 40, 181, 81));
    time->setStyleSheet("QLabel {font: 40pt 'Kiona';color: #439cc1;}");
    //Day
    std::time_t t1 = std::time(0);
    std::tm* now1 = std::localtime(&t1);
    //weekday -- ctime spits out weekdays in a int, 0 = sunday, 6 = saturday
    std::string cday = std::to_string(now1->tm_wday);
    int intDay = std::stoi(cday);
    std::string weekday = MainWindow::getDay(intDay);
    //std::cout <<  weekday;
    //compiled
    std::string today = weekday+"\n"+std::to_string((now1->tm_mon)+1)+"-"+ std::to_string(now1->tm_mday)+"-"+std::to_string((now1->tm_year)+1900);
    date = new QLabel("",this);
    date->setGeometry(weatherPadding + 10,100,171,81);
    date-> setText(QString::fromStdString(today));
    date->setStyleSheet("QLabel {font: 20pt 'Kiona';color: #439cc1;}");
    //Set up the right side animation
    topFrame = new QFrame(this);
    topFrame->setGeometry(320, 30, 1600, 1050);
    //topFrame->setStyleSheet("QFrame{background: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(25, 109, 141, 0.4), stop:0.2 rgba(63, 204, 136, .3), stop:1 rgba(17, 70, 91,.5));}");
    //Create the login box
    loginForeground = new QFrame(this);
    loginForeground->setGeometry(770,80,900,1000);
    loginForeground->setObjectName("loginForeground");
    loginForeground->setStyleSheet("QFrame#loginForeground{background-color: rgba(25, 109, 141, 0.1);border: none;}");
    //Adding the dark background
    QFrame * shaderFrame = new QFrame(loginForeground);
    shaderFrame->setGeometry(0, 19, 700, 900);
    shaderFrame->setStyleSheet("QFrame {background-color: rgba(17, 70, 91, 0.9);border: none;}");
    /**
     *  LOGIN SECTION
     *  -- Done using http(s) POST request to a node.js server --
     **/
    loginTitle = new QLabel(loginForeground);
    loginTitle->setText("L   O   G   I   N");
    loginTitle->setStyleSheet("QLabel{color: #439cc1;font: 25pt 'Kiona';}");
    loginTitle->setGeometry(235, 100, 230, 121);
    bool loggedIn = false;
    lerr = new QLabel(loginForeground); //For login err notifications
    lerr->setStyleSheet("QLabel{color:red;font:8pt 'Comfortaa';}");
    lerr->setGeometry(175,265, 191, 31);
    username = new QLabel(loginForeground);
    username->setText("USERNAME");
    username->setStyleSheet("QLabel{color: #439cc1;font: 15px 'Kiona';}");
    username->setGeometry(175,295, 350, 21);
    usernameEntry = new QLineEdit(loginForeground);
    usernameEntry->setStyleSheet("QLineEdit{background-color:#066185;border:none;font: 10pt 'Comfortaa';color: #439cc1;}");
    usernameEntry->setGeometry(175, 320, 350, 31);
    password = new QLabel(loginForeground);
    password->setText("PASSWORD");
    password->setStyleSheet("QLabel{color: #439cc1;font: 15px 'Kiona';}");
    password->setGeometry(175,380, 350, 21);
    passwordEntry = new QLineEdit(loginForeground);
    passwordEntry->setStyleSheet("QLineEdit{background-color:#066185;border:none;font: 10pt 'Comfortaa';color: #439cc1;}");
    passwordEntry->setEchoMode(QLineEdit::Password);
    passwordEntry->setGeometry(175, 405, 350, 31);
    //login button
    loginButton = new QPushButton("LOGIN",loginForeground);
    loginButton->setGeometry(175, 470, 350, 80);
    loginButton->setObjectName("loginButton");
    loginButton->setStyleSheet("QPushButton#loginButton{background-color: #11465B;border: none;font: 30px 'Kiona';color:#439cc1;}QPushButton#loginButton:hover {background-color: #196D8D;border: none;font: 30px 'Kiona';color: #11465B;}");
    connect(loginButton, SIGNAL (clicked()),this, SLOT (login()));

    //Start the timers
    clock = new QTimer(this);
    connect(clock, SIGNAL(timeout()), this, SLOT(clockFunct()));
    clock->start(1000);

}

void MainWindow::loadServerUi(){
    /**
     * This is where the server interface will be built
     **/
    loggedIn = true;
    delete loginForeground; //Is there a better way to clean up that interface?
    //Create the main backdrop
    QFrame * backDropFrame = new QFrame(this);
    backDropFrame->setObjectName("backdropFrame"); //This way we can only style the backdrop frame by using #
    backDropFrame->setGeometry(370,80,601,581);
    backDropFrame->setStyleSheet("QFrame#backDropFrame{background-color:red;}");


}

void MainWindow::displayLoginErr(std::string err){
    loginButton->setHidden(false);
    if(err=="usernameempty"){
            qDebug() << "Login Was empty ";
            usernameEntry->setStyleSheet("QLineEdit{background-color: #066185;border: 2px solid #722f37;font: 10pt 'Comfortaa';color: #439cc1;}");
            lerr->setText("Username field was left empty");


    }
    if(err=="passwordempty"){
        qDebug() << "Password was left empty";
        passwordEntry->setStyleSheet("QLineEdit{background-color: #066185;border: 2px solid #722f37;font: 10pt 'Comfortaa';color: #439cc1;}");
        lerr->setText("Password field was left empty");
    }
    if(err=="wrngpassword"){
        qDebug() << "Incorrect Password // username";
        lerr->setText("Incorrect password or username");
        usernameEntry->setStyleSheet("QLineEdit{background-color: #066185;border: 2px solid #722f37;font: 10pt 'Comfortaa';color: #439cc1;}");
        passwordEntry->setStyleSheet("QLineEdit{background-color: #066185;border: 2px solid #722f37;font: 10pt 'Comfortaa';color: #439cc1;}");
    }
    if(err=="noconn"){
        qDebug() << "No Connection to server";
        lerr->setText("Couldn't connect to the server");
    }
}

void MainWindow::keyPressEvent(QKeyEvent *enter){
    if(enter->key() == 16777220 || enter->key() == 16777221){
        if(!loggedIn){qDebug() << "x";login();}
    }
}
