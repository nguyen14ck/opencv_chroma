#include "Chroma2.h"

#include <QtCore>
#include <QtWidgets>
#include <QVideoWidget>

#include <QDebug>

#include<iostream> 
#include <sstream>  // for string streams 
#include <string>  // for string 
#include <math.h> 

//#include "includeLibraries.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;




Chroma2::Chroma2(QWidget *parent): QMainWindow(parent)
{
	ui.setupUi(this);

	#pragma region INIT_COLOR
	color_picking = false;
	color_picked = false;
	connect(ui.buttonPickScreen, &QAbstractButton::clicked, this, &Chroma2::color_onButtonPickScreenClicked);

	connect(this, &Chroma2::colorChanged, this, &Chroma2::color_updatePreview);


	#pragma endregion INIT_COLOR



	#pragma region INIT_VIDEO
	//self.video_mediaPlayer = QtMultimedia.QMediaPlayer(None, QtMultimedia.QMediaPlayer.VideoSurface)
	//self.video_mediaPlayer.setVideoOutput(self.video_displayWidget)
	//self.video_mediaPlayer.stateChanged.connect(self.mediaStateChanged)
	//self.video_mediaPlayer.positionChanged.connect(self.positionChanged)
	//self.video_mediaPlayer.durationChanged.connect(self.durationChanged)
	//self.video_mediaPlayer.error.connect(self.handleError)
	//self.video_probe = QVideoProbe()

	video_mediaPlayer = new QMediaPlayer(this, QMediaPlayer::VideoSurface);
	video_mediaPlayer ->setVideoOutput(ui.video_displayWidget);
	connect(ui.video_buttonOpen, &QAbstractButton::clicked, this, &Chroma2::video_openFile);
	ui.video_buttonPlay->setEnabled(false);
	ui.video_buttonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	connect(ui.video_buttonPlay, &QAbstractButton::clicked, this, &Chroma2::video_play);


	connect(video_mediaPlayer, &QMediaPlayer::stateChanged, this, &Chroma2::mediaStateChanged);
	connect(video_mediaPlayer, &QMediaPlayer::positionChanged, this, &Chroma2::positionChanged);
	connect(video_mediaPlayer, &QMediaPlayer::durationChanged, this, &Chroma2::durationChanged);
	connect(video_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &Chroma2::handleError);


	video_probe = new QVideoProbe(this);
	video_probe->setSource(video_mediaPlayer);
	connect(video_probe, SIGNAL(videoFrameProbed(QVideoFrame)), this, SLOT(frameChanged(QVideoFrame)));

	ui.video_outputFrame->setScaledContents(true);
	ui.video_outputFrame->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


	#pragma endregion INIT_VIDEO


	#pragma region INIT_FRAME
	//self.m_processor = FrameProcessor()
	//self.m_processorThread = QThread()
	//self.m_processor.moveToThread(self.m_processorThread)
	//self.m_processorThread.finished.connect(self.m_processor.deleteLater)
	//# self.video_probe.videoFrameProbed.connect(self.m_processor.processFrame2)
	//self.video_probe.videoFrameProbed.connect(self.frameChanged)
	//self.m_processor.imageReady.connect(self.show_and_write)
	//self.m_processorThread.start()

	//Worker* worker = new Worker;
	//worker->moveToThread(&workerThread);
	//connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
	//connect(this, &Controller::operate, worker, &Worker::doWork);
	//connect(worker, &Worker::resultReady, this, &Controller::handleResults);
	//workerThread.start();

	
	

	m_processor = new FrameProcessor();
	m_processor->moveToThread(&m_processorThread);
	connect(&m_processorThread, &QThread::finished, m_processor, &QObject::deleteLater);
	connect(m_processor, &FrameProcessor::imageReady, this, &Chroma2::show_and_write);
	m_processorThread.start();

	connect(video_probe, &QVideoProbe::videoFrameProbed, this, &Chroma2::frameChanged);

	m_processor2 = new FrameProcessor(); // for using methods (converting format) of this object (in main thread, not in worker thread)

	#pragma region INIT_FRAME


	#pragma region INIT_EDIT
	connect(ui.edit_hSliderTol, &QAbstractSlider::valueChanged, this, &Chroma2::edit_toleranceChanged);
	connect(ui.edit_hSliderSoft, &QAbstractSlider::valueChanged, this, &Chroma2::edit_softChanged);
	connect(ui.edit_hSliderDefringe, &QAbstractSlider::valueChanged, this, &Chroma2::edit_defringeChanged);
	connect(ui.edit_buttonSave, &QAbstractButton::clicked, this, &Chroma2::edit_buttonSaveClicked);

	#pragma endregion INIT_EDIT






}

Chroma2::~Chroma2()
{
	m_processorThread.quit();
	m_processorThread.wait();
}



#pragma region COLOR


void Chroma2::color_onButtonPickScreenClicked()
{
	color_picking = true;
	Chroma2::grabKeyboard();
	Chroma2::grabMouse(Qt::CrossCursor);

}

void Chroma2::mouseMoveEvent(QMouseEvent* ev)
{
	//// That's where the magic happens
	//QTransform t;
	//t.scale(1, -1);
	//t.translate(0, -height() + 1);
	//QPoint pos = ev->pos() * t;
	//setText(QStringLiteral("%1, %2").arg(pos.x()).arg(pos.y()));

	if (color_picking)
	{
		Chroma2::color_pickColor(ev->globalPos());
		return;
	}
}

void Chroma2::mouseReleaseEvent(QMouseEvent* ev)
{
	if (color_picking)
	{
		color_picking = false;
		Chroma2::releaseKeyboard();
		Chroma2::releaseMouse();
		Chroma2::color_pickColor(ev->globalPos());
		color_picked = true;
		return;
	}
}


void Chroma2::color_pickColor(QPoint pos)
{
	int winid = QApplication::desktop()->winId();
	QScreen* screen = QGuiApplication::primaryScreen();
	QPixmap pixmap = screen->grabWindow(winid, pos.x(), pos.y(), 1, 1);

	//QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(), pos.x(), pos.y(), 1, 1);
	//QRgb pixelValue = pixmap.toImage().pixel(0, 0);

	QImage img = pixmap.toImage();
	QColor color = QColor::QColor(img.pixel(0, 0));

	//int r, g, b, a;
	//color.getRgb(&r, &g, &b, &a);
	//QString srgb = QStringLiteral("RGB = (%1,%2,%3)").arg(QString::number(r), QString::number(g), QString::number(b));
	//QString srgb;
	//QTextStream(&srgb) << "RGB: (" << r << ", " << g << "," << b << ")";

	//int rgba[4];
	color.getRgb(&rgba[0], &rgba[1], &rgba[2], &rgba[3]);
	QString srgb = QStringLiteral("RGB = (%1,%2,%3)").arg(QString::number(rgba[0]), QString::number(rgba[1]), QString::number(rgba[2]));
	//QString srgb;
	//QTextStream(&srgb) << "RGB: (" << rgba[0] << ", " << rgba[1] << "," << rgba[2] << ")";



	ui.textColorCode->setText(srgb);

	emit colorChanged(color);

}

void Chroma2::color_updatePreview(QColor color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, color_invertColor(color));
	ui.textColorCode->setPalette(palette);

}
QColor Chroma2::color_invertColor(QColor color)
{
	int r, g, b, alpha;
	color.getRgb(&r, &g, &b, &alpha);
	int invertedRed = 255 - r;
	int invertedGreen = 255 - g;
	int invertedBlue = 255 - b;
	QColor invertedColor = QColor::fromRgb(invertedRed, invertedGreen, invertedBlue, alpha);
	return invertedColor;
}


#pragma endregion COLOR










#pragma region VIDEO


void Chroma2::video_openFile()
{
	QFileDialog fileDialog(this);

	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setWindowTitle(tr("Open Movie"));

	QStringList supportedMimeTypes = video_mediaPlayer->supportedMimeTypes();

	if (!supportedMimeTypes.isEmpty())
		fileDialog.setMimeTypeFilters(supportedMimeTypes);

	//fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));

	if (fileDialog.exec() == QDialog::Accepted)
	{
		//qDebug() << fileDialog.selectedUrls().constFirst() << "Hello";

		inputFileName = fileDialog.selectedUrls().constFirst().toString();
		
		video_setUrl(fileDialog.selectedUrls().constFirst());
		
	}
		
}

void Chroma2::video_setUrl(const QUrl& url)
{
	//m_errorLabel->setText(QString());
	setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
	video_mediaPlayer->setMedia(url);
	ui.video_buttonPlay->setEnabled(true);
}

void Chroma2::video_play()
{
	switch (video_mediaPlayer->state()) 
	{
		case QMediaPlayer::PlayingState:
			video_mediaPlayer->pause();
			ui.video_buttonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			ui.video_buttonPlay->setText("Play");
			break;

		default:
			video_mediaPlayer->play();
			ui.video_buttonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
			ui.video_buttonPlay->setText("Pause");
			break;
	}
}



void Chroma2::mediaStateChanged(QMediaPlayer::State state)
{
	switch (state) {
	case QMediaPlayer::PlayingState:
		ui.video_buttonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		break;
	default:
		ui.video_buttonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
		break;
	}
}

void Chroma2::positionChanged(qint64 position)
{
	ui.video_hSlider->setValue(position);
	ui.video_labelCurrent->setText(video_hhmmss_2(position));
	
}

void Chroma2::durationChanged(qint64 duration)
{
	ui.video_hSlider->setRange(0, duration);
	ui.video_labelTotal->setText(video_hhmmss_2(duration));
}

void Chroma2::setPosition(int position)
{
	ui.video_hSlider->setValue(position);
}

void Chroma2::handleError()
{
	ui.video_buttonPlay->setEnabled(false);

	const QString errorString = video_mediaPlayer->errorString();
	QString message = "Error: ";
	if (errorString.isEmpty())
		message += " #" + QString::number(int(video_mediaPlayer->error()));
	else
		message += errorString;

	ui.video_labelStatus->setText(message);
}




QString Chroma2::video_hhmmss()
{
	//	# s = 1000
//	# m = 60000
//	# h = 360000
//	h, r = divmod(ms, 36000)
//	m, r = divmod(r, 60000)
//	s, _ = divmod(r, 1000)
//	return ("%d:%02d:%02d" % (h, m, s)) if h else ("%d:%02d" % (m, s))

	QString timeStringTemplate;
	timeStringTemplate = QString("hh:mm:ss");

	return timeStringTemplate;
}

QString Chroma2::video_hhmmss_2(qint64 timeMS)
{
	double time_in_sec = timeMS / 1000.0;

	int totalNumberOfSeconds = timeMS / 1000.0; 
	int seconds = totalNumberOfSeconds % 60;
	int minutes = (totalNumberOfSeconds / 60) % 60;
	int hours = (totalNumberOfSeconds / 60 / 60);

	QTime  totalTime = QTime(hours, minutes, seconds, (seconds*1000)%1000);

	QString timeStringTemplate;
	if (seconds > 3600)
	{
		timeStringTemplate = QString("hh:mm:ss");
	}
	else
	{
		timeStringTemplate = QString("mm:ss");
	}

	QString timeString = totalTime.toString(timeStringTemplate);

	//QString timeString = QString("%1:%2:%3")
	//	.arg(hours, 2, 10, QChar('0'))
	//	.arg(minutes, 2, 10, QChar('0'))
	//	.arg(seconds, 2, 10, QChar('0'));

	return timeString;
}





void Chroma2::frameChanged(QVideoFrame frame)
{
	//QImage img;
	//img = qframe2qimage(frame);
	//QPixmap pix = QPixmap::fromImage(img);
	//ui.video_outputFrame->setPixmap(pix);

	//QMetaObject.invokeMethod(self.m_processor, 'processFrame', Qt.QueuedConnection, Q_ARG(QVideoFrame, frame), Q_ARG(list, self.edit_params), Q_ARG(list, self.colors))

	//QString retVal;
	//QMetaObject::invokeMethod(obj, "compute", Qt::DirectConnection,
	//	Q_RETURN_ARG(QString, retVal),
	//	Q_ARG(QString, "sqrt"),
	//	Q_ARG(int, 42),
	//	Q_ARG(double, 9.7));

	Chroma2::video_currentFrame = frame;
	if (color_picked)
	{
        // FOR WORKER THREAD
		QMetaObject::invokeMethod(m_processor, "processFrame", Qt::DirectConnection, Q_ARG(QVideoFrame, frame), Q_ARG(int[3], edit_params), Q_ARG(int[4], rgba));

		// FOR MAIN THREAD, DEBUGGING
		//QImage img = qframe2qimage(frame);
		//QImage resIm = m_processor2->processImage(img, edit_params, rgba);
		//show_and_write(resIm);
	}
	else
	{
		QImage img = qframe2qimage(frame);
		show_and_write(img);
	}
	




	
}

QImage Chroma2::qframe2qimage(QVideoFrame frame)
{
	QImage img;

	//QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
	frame.map(QAbstractVideoBuffer::ReadOnly);

	QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());

	// BUT the frame.pixelFormat() is QVideoFrame::Format_Jpeg, and this is mapped to QImage::Format_Invalid by
	// QVideoFrame::imageFormatFromPixelFormat

	if (imageFormat != QImage::Format_Invalid)
	{
		img = QImage(frame.bits(),
			frame.width(),
			frame.height(),
			//frame.bytesPerLine(),
			imageFormat);
	}
	else
	{
		// e.g. JPEG
		int nbytes = frame.mappedBytes();
		img = QImage::fromData(frame.bits(), nbytes);
	}
	frame.unmap();

	/*QTransform myTransform;
	myTransform.rotate(180);
	img = img.transformed(myTransform);*/

	img = img.mirrored(false, true);

	//bool bSave = img.save("test.png");

	return img;
}


void Chroma2::show_and_write(QImage qImage)
{
	//Mat imcv = m_processor2->QImageToMat(qImage);

	QPixmap pix = QPixmap::fromImage(qImage);
	ui.video_outputFrame->setPixmap(pix);

	//bool bSave = qImage.save("test.png");
}

#pragma endregion VIDEO










#pragma region EDIT


void Chroma2::edit_toleranceChanged()
{
	edit_params[0] = ui.edit_hSliderTol->value();
	QString sTol;
	QTextStream(&sTol) << edit_params[0] << "%";
	ui.edit_labelTolValue->setText(sTol);
	Chroma2::edit_updatePauseFrame();
}

void Chroma2::edit_softChanged()
{
	edit_params[1] = ui.edit_hSliderSoft->value();
	QString sSof;
	QTextStream(&sSof) << edit_params[1] << "%";
	ui.edit_labelSoftValue->setText(sSof);
	Chroma2::edit_updatePauseFrame();

}

void Chroma2::edit_defringeChanged()
{
	edit_params[2] = ui.edit_hSliderDefringe->value();
	QString sDefringe;
	QTextStream(&sDefringe) << edit_params[2] << "%";
	ui.edit_labelDefringeValue->setText(sDefringe);
	Chroma2::edit_updatePauseFrame();

}

void Chroma2::edit_updatePauseFrame()
{

	if (video_mediaPlayer->state() == QMediaPlayer::PausedState)
	{
		QImage img = m_processor2->editFrame(Chroma2::video_currentFrame, Chroma2::edit_params, Chroma2::rgba);
		show_and_write(img);
	}


}

void Chroma2::edit_buttonSaveClicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Video File"), "", tr("Video File (*.mp4)"));

	if (fileName.isEmpty())
		return;
	else 
	{

		Chroma2::edit_apply(fileName);
	}

}

void Chroma2::edit_apply(QString fileName)
{
	VideoCapture vcap(Chroma2::inputFileName.toUtf8().constData());
	//VideoCapture vcap(fileName.toUtf8().constData());

	if(!vcap.isOpened()){
    cout << "Error opening video stream or file" << endl;
}

	int frame_width;
	int frame_height;
	int fps;
	if (vcap.isOpened())
	{
		fps = (int) vcap.get(cv::CAP_PROP_FPS);

		frame_width = (int)vcap.get(3);
		frame_height = (int) vcap.get(4);

		//int frame_width = vcap->get(cv::CAP_PROP_FRAME_WIDTH);
		//int frame_height = vcap->get(cv::CAP_PROP_FRAME_HEIGHT);
	}
	else
	{
		qDebug() << "Error opening video stream or file" << endl;
	}

	

	// Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file. 
	//VideoWriter outvideo(fileName.toUtf8().constData(), VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(frame_width, frame_height)); //avi # NOT WORKING
	//VideoWriter outvideo(fileName.toUtf8().constData(), VideoWriter::fourcc('X', 'V', 'I', 'D'), 10, Size(frame_width, frame_height)); //mp4

	//VideoWriter outvideo(fileName.toUtf8().constData(), cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Size(frame_width, frame_height)); //avi
	VideoWriter outvideo(fileName.toUtf8().constData(), cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, Size(frame_width, frame_height)); //mp4


	int count = 0;
	bool success = true;

	// Read until video is completed
	while (vcap.isOpened()) 
	{

		Mat frame;

		// Capture frame-by-frame
		vcap >> frame;

		// If the frame is empty, break immediately
		if (frame.empty())
			break;

		QImage qFrameIn = m_processor2->MatToQImage(frame);
		QImage qFrameOut = m_processor2->editFrame(qFrameIn, Chroma2::edit_params, Chroma2::rgba);
		Mat frameOut = m_processor2->QImageToMat(qFrameOut);

		Mat frameFlip;
		cv::flip(frameOut, frameFlip, 0);

		outvideo.write(frameFlip);

		// Write the frame into the file 'outputChaplin.mp4'
		//imshow("Frame", frame);

		// Wait for 25 ms before moving on to the next frame
		// This will slow down the video 
		//waitKey(25);
	}

	// When everything done, release the video capture and write object
	vcap.release();
	outvideo.release();

	


}

void Chroma2::MatInfo(Mat inputMat)
{
	int inttype = inputMat.type();

	string r, a;
	uchar depth = inttype & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (inttype >> CV_CN_SHIFT);
	switch (depth) {
	case CV_8U:  r = "8U";   a = "Mat.at<uchar>(y,x)"; break;
	case CV_8S:  r = "8S";   a = "Mat.at<schar>(y,x)"; break;
	case CV_16U: r = "16U";  a = "Mat.at<ushort>(y,x)"; break;
	case CV_16S: r = "16S";  a = "Mat.at<short>(y,x)"; break;
	case CV_32S: r = "32S";  a = "Mat.at<int>(y,x)"; break;
	case CV_32F: r = "32F";  a = "Mat.at<float>(y,x)"; break;
	case CV_64F: r = "64F";  a = "Mat.at<double>(y,x)"; break;
	default:     r = "User"; a = "Mat.at<UKNOWN>(y,x)"; break;
	}
	r += "C";
	r += (chans + '0');
	//cout << "Mat is of type " << r << " and should be accessed with " << a << endl;

	//string ty = type2str(M.type());
	/*printf("Matrix: %s %dx%d ", r, inputMat.cols, inputMat.rows);
	cout << " and should be accessed with " << a << endl;*/

	qDebug() << "Matrix: " << QString::fromStdString(r) << " Size: " << inputMat.cols << "," << inputMat.rows;
	qDebug() << " and should be accessed with " << QString::fromStdString(a) << endl;
}

#pragma endregion EDIT


#pragma region FRAME_PROCESSOR

//FrameProcessor::FrameProcessor()
//{
//
//}
//
//FrameProcessor::~FrameProcessor()
//{
//
//}

void FrameProcessor::processFrame(QVideoFrame frame, int edit_params[3], int colors[4])
{
	QImage imqt = editFrame(frame, edit_params, colors);
	emit imageReady(imqt);
}

QImage FrameProcessor::editFrame(QVideoFrame frame, int edit_params[3], int colors[4])
{
	QImage imqt = qframe2qimage(frame);
	QImage imProc = processImage(imqt, edit_params, colors);
	
	return imProc;
}

QImage FrameProcessor::processImage(QImage imqt, int edit_params[3], int colors[4])
{
	// Input params
	Mat imcv = QImageToMat(imqt);
	int nRows = imcv.rows;
	int nCols = imcv.cols;


	int tol = edit_params[0];
	int soft = edit_params[1];
	int df = edit_params[2];

	double tolb = 15.0 * (1 + 5 * tol / 100);
	double tola = tolb - 2 + 4 * (1 + 5 * df / 100);

	if (tola > tolb)
	{
		tolb = tola;
	}
		

	tola = tola * tola;
	tolb = tolb * tolb;


	//Mat rgb = Mat::zeros(Size(1, 3), CV_8UC1);

	//cv::Size imgSize(640, 480);
	//cv::Mat image = cv::Mat(imgSize, CV_8UC3, cv::Scalar(1, 1, 1));
	//for (int row = 0; row < image.rows; ++row)
	//{
	//	const uchar* ptr = image.ptr(row);
	//	for (int col = 0; col < image.cols; col++)
	//	{
	//		const uchar* uc_pixel = ptr;
	//		int a = uc_pixel[0];
	//		int b = uc_pixel[1];
	//		int c = uc_pixel[2];
	//		sum += a + b + c;
	//		ptr += 3;
	//	}
	//}


	cv::Mat colorRgb = cv::Mat(Size(1, 1), CV_8UC3, cv::Scalar(colors[0], colors[1], colors[2]));
	Mat colorYcc = cv::Mat(Size(1, 1), CV_8UC3);
	cv::cvtColor(colorRgb, colorYcc, cv::COLOR_RGB2YCrCb);

	int ycolor, cr, cb;
	const uchar* ptrColor = colorYcc.ptr(0);
	const uchar* pixelColor = ptrColor;
	ycolor = pixelColor[0];
	cr = pixelColor[1];
	cb = pixelColor[2];

	//# Gaussian
	//	if soft > 0:
	//step = np.round(np.mean(img.shape[0:2]) / 100)
	//	size = int(step + round(soft / 5))
	//	if size % 2 == 0 :
	//		size += 1
	//		# sigma = 0.3 * ((size − 1) * 0.5 − 1) + 0.8
	//		blur = cv2.GaussianBlur(img, (size, size), 0, 0)
	//	else:
	//blur = img

	Mat imGauss;
	if (soft > 0)
	{
		int step = (nRows + nCols) % 100;
		int ssize = step + (soft % 5);
		double sigma;

		if ((ssize % 2) == 0)
		{
			ssize += 1;
		}
		//sigma = 0.3 * ((size - 1) * 0.5 - 1) + 0.8;
		cv::GaussianBlur(imcv, imGauss, Size(ssize, ssize), 0, 0);
	}
	else
	{
		imGauss = imcv;
	}
		




	//# Convert image from RGB to YCrCb
	Mat imYcc = cv::Mat(imcv.size(), CV_8UC3);
	cv::cvtColor(imGauss, imYcc, cv::COLOR_RGB2YCrCb);

	Mat distMap = cv::Mat(Size(nCols, nRows), CV_32FC1);
	Mat mask = cv::Mat(Size(nCols, nRows), CV_8UC1);

	Mat imBackground = cv::Mat(imcv.size(), CV_8UC3, cv::Scalar(0, 0, 0));

	Mat imRessult = cv::Mat(imcv.size(), CV_8UC3, cv::Scalar(0, 0, 0));

	//double distanceMap[][][];

	uchar* rgbPr;
	uchar* rgbPc;
	uchar* yccPr;
	uchar* yccPc;

	uchar* distPr;
	uchar* distPc;
	uchar* maskPr;
	uchar* maskPc;

	uchar* bgPr;
	uchar* bgPc;

	uchar* resPr;
	uchar* resPc;

	for (int i = 0; i < nRows; ++i)
	{
		rgbPr = imcv.ptr(i);
		yccPr = imYcc.ptr(i);

		distPr = distMap.ptr(i);
		maskPr = mask.ptr(i);

		bgPr = imBackground.ptr(i);
		resPr = imRessult.ptr(i);

		for (int j = 0; j < nCols; ++j)
		{
			rgbPc = rgbPr;
			yccPc = yccPr;
			distPc = distPr;
			maskPc = maskPr;
			bgPc = bgPr;
			resPc = resPr;

			int ypix = yccPc[0];
			int crpix = yccPc[1];
			int cbpix = yccPc[2];

			int dcr = crpix - cr;
			int dcb = cbpix - cb;
			int distance = dcr * dcr + dcb * dcb;
			distPc[0] = distance;

			//int temp0 = rgbPc[0];
			//int temp1 = rgbPc[1];
			//int temp2 = rgbPc[2];

			if (distance < tola)
			{
				maskPc[0] = 255;



				resPc[0] = bgPc[0];
				resPc[1] = bgPc[1];
				resPc[2] = bgPc[2];
				//resPc[0] = temp0;
				//resPc[1] = temp1;
				//resPc[2] = temp2;




			}
			else
			{
				maskPc[0] = 0;

				resPc[0] = rgbPc[0];
				resPc[1] = rgbPc[1];
				resPc[2] = rgbPc[2];


			}

			rgbPr += 3;
			yccPr += 3;

			distPr += 1;
			maskPr += 1;

			bgPr += 3;
			resPr += 3;



		}
	}



	//img3 = cv2.bitwise_and(bg, bg, mask = mask2)
	//img4 = img2 + img3


	QImage imProc = MatToQImage(imRessult);

	//bool bSave1 = imqt.save("test1.png");
	//bool bSave2 = imProc.save("test2.png");

	//Mat imRessult2 = QImageToMat(imProc);


	


	return imProc;
}

cv::Mat FrameProcessor::QImageToMat(QImage image)
{
	cv::Mat mat;
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		break;
	case QImage::Format_Grayscale8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

//QImage FrameProcessor::MatToQImage(const cv::Mat& mat)
//{
//	cv::Mat rgbMat;
//	if (mat.channels() == 1) {
//		return QImage((uchar*)mat.data, mat.cols, mat.rows, (int)mat.step, QImage::Format_Indexed8).copy();
//	}
//	else if (mat.channels() == 3) {
//		//cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
//		return QImage((uchar*)rgbMat.data, mat.cols, mat.rows, (int)mat.step, QImage::Format_RGB888).copy();
//	}
//	return QImage();
//}

QImage FrameProcessor::MatToQImage(const cv::Mat& mat)
{
	int channels = mat.channels();
	int rows = mat.rows; // height
	int cols = mat.cols; // width
	int bytesperline = cols * channels;

	//qDebug() << mat.size;

	

	if (channels == 1) 
	{
		return QImage((uchar*)mat.data, mat.cols, mat.rows, bytesperline, QImage::Format_Indexed8).copy();
	}
	else if (channels == 3) 
	{
		//cv::Mat rgbMat;
		//cv::cvtColor(mat, rgbMat, cv::COLOR_BGR2RGB);
		//return QImage((uchar*)rgbMat.data, mat.cols, mat.rows, bytesperline, QImage::Format_RGB888).copy();

		return QImage((uchar*)mat.data, mat.cols, mat.rows, bytesperline, QImage::Format_RGB888).copy();
	}
	return QImage();
}




QImage FrameProcessor::qframe2qimage(QVideoFrame frame)
{
	QImage img;

	//QVideoFrame frame(buffer);  // make a copy we can call map (non-const) on
	frame.map(QAbstractVideoBuffer::ReadOnly);

	QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());

	// BUT the frame.pixelFormat() is QVideoFrame::Format_Jpeg, and this is mapped to QImage::Format_Invalid by
	// QVideoFrame::imageFormatFromPixelFormat

	if (imageFormat != QImage::Format_Invalid)
	{
		img = QImage(frame.bits(),
			frame.width(),
			frame.height(),
			//frame.bytesPerLine(),
			imageFormat);
	}
	else
	{
		// e.g. JPEG
		int nbytes = frame.mappedBytes();
		img = QImage::fromData(frame.bits(), nbytes);
	}
	frame.unmap();

	/*QTransform myTransform;
	myTransform.rotate(180);
	img = img.transformed(myTransform);*/

	img = img.mirrored(false, true);

	//bool bSave = img.save("test.png");

	return img;
}

#pragma endregion FRAME_PROCESSOR