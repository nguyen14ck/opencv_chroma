/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtMultimediaWidgets"


QT_BEGIN_NAMESPACE

class Ui_Chroma2Class
{
public:
	QWidget* centralwidget;
	QWidget* horizontalLayoutWidget;
	QHBoxLayout* color_horizontalLayout;
	QLineEdit* textColorCode;
	QPushButton* buttonPickScreen;
	QPushButton* buttonColorPalette;
	QWidget* verticalLayoutWidget;
	QVBoxLayout* video_mainVBoxLayout;
	QLabel* video_labelInput;
	QVideoWidget* video_displayWidget;
	QHBoxLayout* video_toolHBoxLayout;
	QPushButton* video_buttonOpen;
	QPushButton* video_buttonPlay;
	QLabel* video_labelCurrent;
	QSlider* video_hSlider;
	QLabel* video_labelTotal;
	QLabel* video_labelStatus;
	QWidget* gridLayoutWidget;
	QGridLayout* edit_gridLayout;
	QLabel* edit_labelTolValue;
	QLabel* edit_labelTol;
	QSlider* edit_hSliderDefringe;
	QLabel* edit_labelDefringe;
	QSlider* edit_hSliderTol;
	QLabel* edit_labelSoftValue;
	QLabel* edit_labelSoft;
	QSlider* edit_hSliderSoft;
	QLabel* edit_labelDefringeValue;
	QPushButton* edit_buttonSave;
	QWidget* verticalLayoutWidget_2;
	QVBoxLayout* video_outputLayout;
	QLabel* video_labelOutput;
	QLabel* video_outputFrame;
	QMenuBar* menubar;
	QStatusBar* statusbar;

	void setupUi(QMainWindow* MainWindow)
	{
		if (MainWindow->objectName().isEmpty())
			MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
		MainWindow->resize(1042, 533);
		centralwidget = new QWidget(MainWindow);
		centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
		horizontalLayoutWidget = new QWidget(centralwidget);
		horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
		horizontalLayoutWidget->setGeometry(QRect(590, 240, 431, 51));
		color_horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
		color_horizontalLayout->setObjectName(QString::fromUtf8("color_horizontalLayout"));
		color_horizontalLayout->setContentsMargins(0, 0, 0, 0);
		textColorCode = new QLineEdit(horizontalLayoutWidget);
		textColorCode->setObjectName(QString::fromUtf8("textColorCode"));
		textColorCode->setReadOnly(true);

		color_horizontalLayout->addWidget(textColorCode);

		buttonPickScreen = new QPushButton(horizontalLayoutWidget);
		buttonPickScreen->setObjectName(QString::fromUtf8("buttonPickScreen"));

		color_horizontalLayout->addWidget(buttonPickScreen);

		buttonColorPalette = new QPushButton(horizontalLayoutWidget);
		buttonColorPalette->setObjectName(QString::fromUtf8("buttonColorPalette"));

		color_horizontalLayout->addWidget(buttonColorPalette);

		verticalLayoutWidget = new QWidget(centralwidget);
		verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
		verticalLayoutWidget->setGeometry(QRect(20, 10, 561, 461));
		video_mainVBoxLayout = new QVBoxLayout(verticalLayoutWidget);
		video_mainVBoxLayout->setObjectName(QString::fromUtf8("video_mainVBoxLayout"));
		video_mainVBoxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
		video_mainVBoxLayout->setContentsMargins(0, 0, 0, 0);
		video_labelInput = new QLabel(verticalLayoutWidget);
		video_labelInput->setObjectName(QString::fromUtf8("video_labelInput"));
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(video_labelInput->sizePolicy().hasHeightForWidth());
		video_labelInput->setSizePolicy(sizePolicy);

		video_mainVBoxLayout->addWidget(video_labelInput);

		video_displayWidget = new QVideoWidget(verticalLayoutWidget);
		video_displayWidget->setObjectName(QString::fromUtf8("video_displayWidget"));

		video_mainVBoxLayout->addWidget(video_displayWidget);

		video_toolHBoxLayout = new QHBoxLayout();
		video_toolHBoxLayout->setObjectName(QString::fromUtf8("video_toolHBoxLayout"));
		video_toolHBoxLayout->setSizeConstraint(QLayout::SetMinimumSize);
		video_buttonOpen = new QPushButton(verticalLayoutWidget);
		video_buttonOpen->setObjectName(QString::fromUtf8("video_buttonOpen"));

		video_toolHBoxLayout->addWidget(video_buttonOpen);

		video_buttonPlay = new QPushButton(verticalLayoutWidget);
		video_buttonPlay->setObjectName(QString::fromUtf8("video_buttonPlay"));
		video_buttonPlay->setEnabled(true);

		video_toolHBoxLayout->addWidget(video_buttonPlay);

		video_labelCurrent = new QLabel(verticalLayoutWidget);
		video_labelCurrent->setObjectName(QString::fromUtf8("video_labelCurrent"));
		sizePolicy.setHeightForWidth(video_labelCurrent->sizePolicy().hasHeightForWidth());
		video_labelCurrent->setSizePolicy(sizePolicy);

		video_toolHBoxLayout->addWidget(video_labelCurrent);

		video_hSlider = new QSlider(verticalLayoutWidget);
		video_hSlider->setObjectName(QString::fromUtf8("video_hSlider"));
		video_hSlider->setOrientation(Qt::Horizontal);

		video_toolHBoxLayout->addWidget(video_hSlider);

		video_labelTotal = new QLabel(verticalLayoutWidget);
		video_labelTotal->setObjectName(QString::fromUtf8("video_labelTotal"));
		sizePolicy.setHeightForWidth(video_labelTotal->sizePolicy().hasHeightForWidth());
		video_labelTotal->setSizePolicy(sizePolicy);

		video_toolHBoxLayout->addWidget(video_labelTotal);


		video_mainVBoxLayout->addLayout(video_toolHBoxLayout);

		video_labelStatus = new QLabel(verticalLayoutWidget);
		video_labelStatus->setObjectName(QString::fromUtf8("video_labelStatus"));
		sizePolicy.setHeightForWidth(video_labelStatus->sizePolicy().hasHeightForWidth());
		video_labelStatus->setSizePolicy(sizePolicy);

		video_mainVBoxLayout->addWidget(video_labelStatus);

		gridLayoutWidget = new QWidget(centralwidget);
		gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
		gridLayoutWidget->setGeometry(QRect(590, 300, 431, 171));
		edit_gridLayout = new QGridLayout(gridLayoutWidget);
		edit_gridLayout->setObjectName(QString::fromUtf8("edit_gridLayout"));
		edit_gridLayout->setContentsMargins(0, 0, 0, 0);
		edit_labelTolValue = new QLabel(gridLayoutWidget);
		edit_labelTolValue->setObjectName(QString::fromUtf8("edit_labelTolValue"));
		QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Minimum);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(edit_labelTolValue->sizePolicy().hasHeightForWidth());
		edit_labelTolValue->setSizePolicy(sizePolicy1);

		edit_gridLayout->addWidget(edit_labelTolValue, 0, 2, 1, 1);

		edit_labelTol = new QLabel(gridLayoutWidget);
		edit_labelTol->setObjectName(QString::fromUtf8("edit_labelTol"));

		edit_gridLayout->addWidget(edit_labelTol, 0, 0, 1, 1);

		edit_hSliderDefringe = new QSlider(gridLayoutWidget);
		edit_hSliderDefringe->setObjectName(QString::fromUtf8("edit_hSliderDefringe"));
		edit_hSliderDefringe->setMaximum(100);
		edit_hSliderDefringe->setOrientation(Qt::Horizontal);

		edit_gridLayout->addWidget(edit_hSliderDefringe, 2, 1, 1, 1);

		edit_labelDefringe = new QLabel(gridLayoutWidget);
		edit_labelDefringe->setObjectName(QString::fromUtf8("edit_labelDefringe"));

		edit_gridLayout->addWidget(edit_labelDefringe, 2, 0, 1, 1);

		edit_hSliderTol = new QSlider(gridLayoutWidget);
		edit_hSliderTol->setObjectName(QString::fromUtf8("edit_hSliderTol"));
		edit_hSliderTol->setMaximum(100);
		edit_hSliderTol->setOrientation(Qt::Horizontal);

		edit_gridLayout->addWidget(edit_hSliderTol, 0, 1, 1, 1);

		edit_labelSoftValue = new QLabel(gridLayoutWidget);
		edit_labelSoftValue->setObjectName(QString::fromUtf8("edit_labelSoftValue"));
		sizePolicy1.setHeightForWidth(edit_labelSoftValue->sizePolicy().hasHeightForWidth());
		edit_labelSoftValue->setSizePolicy(sizePolicy1);

		edit_gridLayout->addWidget(edit_labelSoftValue, 1, 2, 1, 1);

		edit_labelSoft = new QLabel(gridLayoutWidget);
		edit_labelSoft->setObjectName(QString::fromUtf8("edit_labelSoft"));

		edit_gridLayout->addWidget(edit_labelSoft, 1, 0, 1, 1);

		edit_hSliderSoft = new QSlider(gridLayoutWidget);
		edit_hSliderSoft->setObjectName(QString::fromUtf8("edit_hSliderSoft"));
		edit_hSliderSoft->setMaximum(100);
		edit_hSliderSoft->setOrientation(Qt::Horizontal);

		edit_gridLayout->addWidget(edit_hSliderSoft, 1, 1, 1, 1);

		edit_labelDefringeValue = new QLabel(gridLayoutWidget);
		edit_labelDefringeValue->setObjectName(QString::fromUtf8("edit_labelDefringeValue"));
		sizePolicy1.setHeightForWidth(edit_labelDefringeValue->sizePolicy().hasHeightForWidth());
		edit_labelDefringeValue->setSizePolicy(sizePolicy1);

		edit_gridLayout->addWidget(edit_labelDefringeValue, 2, 2, 1, 1);

		edit_buttonSave = new QPushButton(gridLayoutWidget);
		edit_buttonSave->setObjectName(QString::fromUtf8("edit_buttonSave"));
		QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy2.setHorizontalStretch(0);
		sizePolicy2.setVerticalStretch(0);
		sizePolicy2.setHeightForWidth(edit_buttonSave->sizePolicy().hasHeightForWidth());
		edit_buttonSave->setSizePolicy(sizePolicy2);

		edit_gridLayout->addWidget(edit_buttonSave, 3, 1, 1, 1);

		verticalLayoutWidget_2 = new QWidget(centralwidget);
		verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
		verticalLayoutWidget_2->setGeometry(QRect(590, 10, 351, 221));
		video_outputLayout = new QVBoxLayout(verticalLayoutWidget_2);
		video_outputLayout->setObjectName(QString::fromUtf8("video_outputLayout"));
		video_outputLayout->setContentsMargins(0, 0, 0, 0);
		video_labelOutput = new QLabel(verticalLayoutWidget_2);
		video_labelOutput->setObjectName(QString::fromUtf8("video_labelOutput"));
		sizePolicy.setHeightForWidth(video_labelOutput->sizePolicy().hasHeightForWidth());
		video_labelOutput->setSizePolicy(sizePolicy);

		video_outputLayout->addWidget(video_labelOutput);

		video_outputFrame = new QLabel(verticalLayoutWidget_2);
		video_outputFrame->setObjectName(QString::fromUtf8("video_outputFrame"));

		video_outputLayout->addWidget(video_outputFrame);

		MainWindow->setCentralWidget(centralwidget);
		menubar = new QMenuBar(MainWindow);
		menubar->setObjectName(QString::fromUtf8("menubar"));
		menubar->setGeometry(QRect(0, 0, 1042, 30));
		MainWindow->setMenuBar(menubar);
		statusbar = new QStatusBar(MainWindow);
		statusbar->setObjectName(QString::fromUtf8("statusbar"));
		MainWindow->setStatusBar(statusbar);

		retranslateUi(MainWindow);

		QMetaObject::connectSlotsByName(MainWindow);
	} // setupUi

	void retranslateUi(QMainWindow* MainWindow)
	{
		MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
		buttonPickScreen->setText(QCoreApplication::translate("MainWindow", "Pick Color", nullptr));
		buttonColorPalette->setText(QCoreApplication::translate("MainWindow", "Color Palette", nullptr));
		video_labelInput->setText(QCoreApplication::translate("MainWindow", "Input Video", nullptr));
		video_buttonOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
		video_buttonPlay->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
		video_labelCurrent->setText(QCoreApplication::translate("MainWindow", "0:00", nullptr));
		video_labelTotal->setText(QString());
		video_labelStatus->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
		edit_labelTolValue->setText(QCoreApplication::translate("MainWindow", "    0 %", nullptr));
		edit_labelTol->setText(QCoreApplication::translate("MainWindow", "Tolerance", nullptr));
		edit_labelDefringe->setText(QCoreApplication::translate("MainWindow", "Defringe", nullptr));
		edit_labelSoftValue->setText(QCoreApplication::translate("MainWindow", "    0 %", nullptr));
		edit_labelSoft->setText(QCoreApplication::translate("MainWindow", "Softness", nullptr));
		edit_labelDefringeValue->setText(QCoreApplication::translate("MainWindow", "    0 %", nullptr));
		edit_buttonSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
		video_labelOutput->setText(QCoreApplication::translate("MainWindow", "Output Video", nullptr));
		video_outputFrame->setText(QString());
	} // retranslateUi

};

namespace Ui {
	class Chroma2Class : public Ui_Chroma2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
