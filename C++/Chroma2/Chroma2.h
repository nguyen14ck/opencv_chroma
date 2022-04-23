#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chroma2.h"
#include "FrameProc.h"

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

class Chroma2 : public QMainWindow
{
Q_OBJECT
	QThread m_processorThread;

public:
	bool color_picking;
	bool color_picked;
	int edit_params[3] = { 0, 0, 0 };
	int rgba[4] = { 0, 0, 0, 0 };
	FrameProcessor *m_processor;
	FrameProcessor* m_processor2; // for using methods (converting format) of this object (in main thread, not in worker thread)

	QVideoFrame video_currentFrame;
	QString inputFileName;

private:
	Ui::Chroma2Class ui;

	QMediaPlayer* video_mediaPlayer;
	//QAbstractButton* m_playButton;
	//QSlider* m_positionSlider;
	//QLabel* m_errorLabel;

	QVideoProbe* video_probe;

	
	


public:
	Chroma2(QWidget *parent = Q_NULLPTR);
	~Chroma2();
	void video_setUrl(const QUrl& url);
	void MatInfo(Mat inputMat);
	
	

private:
	void color_pickColor(QPoint pos);
	void color_updatePreview(QColor color);
	QColor color_invertColor(QColor color);


	QString Chroma2::video_hhmmss();
	QString Chroma2::video_hhmmss_2(qint64 timeMS);

	QImage qframe2qimage(QVideoFrame frame);
	void show_and_write(QImage qImage);


	void edit_updatePauseFrame();
	void edit_apply(QString fileName);

	

signals:
	void colorChanged(QColor);


	

public slots:
	void color_onButtonPickScreenClicked();

	void video_openFile();
	void video_play();

	void edit_toleranceChanged();
	void edit_softChanged();
	void edit_defringeChanged();
	void edit_buttonSaveClicked();


private slots:
	void mediaStateChanged(QMediaPlayer::State state);
	void positionChanged(qint64 position);
	void durationChanged(qint64 duration);
	void setPosition(int position);
	void handleError();

	void frameChanged(QVideoFrame frame);

	

protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

//virtual void mousePressEvent(QMouseEvent* event);
//virtual void mouseMoveEvent(QMouseEvent* event);
//virtual void mouseReleaseEvent(QMouseEvent* event);


};


//class FrameProcessor: public QObject
//{
//Q_OBJECT
//
//public:
//	//FrameProcessor();
//	//~FrameProcessor();
//	QImage editFrame(QVideoFrame frame, int edit_params[3], int colors[4]);
//	Mat processImage(QVideoFrame frame, int edit_params[3], int colors[4]);
//
//	Mat QImageToMat(QImage image);
//	QImage MatToQImage(const cv::Mat& mat);
//
//
//signals:
//	void imageReady(QImage);
//
//public slots:
//	void processFrame(QVideoFrame frame, int edit_params[3], int colors[4]);
//
//};
