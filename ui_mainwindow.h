/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *titleFrame;
    QLabel *title;
    QFrame *timeBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 750);
        MainWindow->setStyleSheet(QLatin1String("QWidget#centralWidget{\n"
"	background-color: #196D8D;\n"
"\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        titleFrame = new QFrame(centralWidget);
        titleFrame->setObjectName(QStringLiteral("titleFrame"));
        titleFrame->setGeometry(QRect(0, 0, 1001, 51));
        titleFrame->setStyleSheet(QLatin1String("QFrame#titleFrame {\n"
"	background-color: #11465B;\n"
"	border: none;\n"
"}"));
        titleFrame->setFrameShape(QFrame::StyledPanel);
        titleFrame->setFrameShadow(QFrame::Raised);
        title = new QLabel(titleFrame);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(10, 10, 241, 31));
        title->setStyleSheet(QLatin1String("QLabel{\n"
"font: 14pt \"Kiona\";\n"
"color: #196D8D;\n"
"}"));
        timeBox = new QFrame(centralWidget);
        timeBox->setObjectName(QStringLiteral("timeBox"));
        timeBox->setGeometry(QRect(40, 90, 281, 151));
        timeBox->setStyleSheet(QLatin1String("QFrame#timeBox{\n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.5, y2:0.5, x3:1, y3:1, stop:0 rgba(25, 103, 134,1), stop:1 rgba(18, 78, 102, 0.5), stop:2 rgba(17, 70, 91,0));\n"
"	border: none;\n"
"\n"
"}"));
        timeBox->setFrameShape(QFrame::StyledPanel);
        timeBox->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        title->setText(QApplication::translate("MainWindow", "Thoward02/TimeKeeper", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
