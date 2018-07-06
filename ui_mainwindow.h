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
    QFrame *frame;
    QFrame *frame_2;
    QFrame *frame_3;

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
        titleFrame->setGeometry(QRect(0, 0, 1001, 50));
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
        timeBox->setGeometry(QRect(0, 50, 321, 700));
        timeBox->setStyleSheet(QLatin1String("QFrame#timeBox{\n"
"	background: qlineargradient(spread:pad, x1:0, y1:0, x2:0.5, y2:0.5, x3:1, y3:1, stop:0 rgba(25, 103, 134,1), stop:1 rgba(18, 78, 102, 0.5), stop:2 rgba(17, 70, 91,0));\n"
"	border: none;\n"
"\n"
"}"));
        timeBox->setFrameShape(QFrame::StyledPanel);
        timeBox->setFrameShadow(QFrame::Raised);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(0, 50, 321, 701));
        frame->setStyleSheet(QLatin1String("QFrame{\n"
"	background: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0.5, x3:1, y3:0, stop:0 rgba(90, 161, 205, 0.7), stop:1 rgba(45, 167, 151,0.2), stop:2 rgba(17, 70, 91,0));\n"
"	border: none;\n"
"\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(320, 50, 681, 701));
        frame_2->setStyleSheet(QLatin1String("QFrame{\n"
"	background: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0.5, x3:1, y3:0, stop:0 rgba(96, 63, 205, 0.7), stop:1 rgba(45, 167, 151,0.2), stop:2 rgba(17, 70, 91,0));\n"
"	border: none;\n"
"\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame_2);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(0, 0, 681, 701));
        frame_3->setStyleSheet(QLatin1String("QFrame{\n"
"	background: qlineargradient(spread:pad, x0:1, y1:0.4, x2:0.5, y2:0.7, x3:0.5, y3:1, stop:0 rgba(163, 233, 199, 0.5), stop:1 rgba(63, 204, 136,0.3), stop:2 rgba(17, 70, 91,0));\n"
"	border: none;\n"
"\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
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
