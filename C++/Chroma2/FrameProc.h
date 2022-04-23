#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chroma2.h"

#include <QMediaPlayer>
#include <QWidget>
#include <QVideoFrame>

#include <iostream>
//#include "includeLibraries.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
class QUrl;
QT_END_NAMESPACE




class FrameProcessor : public QObject
{
	Q_OBJECT

public:
	//FrameProcessor();
	//~FrameProcessor();
	QImage editFrame(QVideoFrame frame, int edit_params[3], int colors[4]);
	QImage processImage(QImage imqt, int edit_params[3], int colors[4]);

	QImage qframe2qimage(QVideoFrame frame);
	Mat QImageToMat(QImage image);
	QImage MatToQImage(const cv::Mat& mat);


signals:
	void imageReady(QImage);

public slots:
	void processFrame(QVideoFrame frame, int edit_params[3], int colors[4]);

};
