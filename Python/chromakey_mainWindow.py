import sys
import uuid

import cv2
import numpy as np
from matplotlib import pyplot as plt
# from PyQt5 import QtCore, QtGui, QtWidgets, QtMultimedia, uic

import PyQt5
from PyQt5 import QtCore, QtGui, QtWidgets, QtMultimedia, uic
from PyQt5.QtCore import Qt, QObject, QUrl, QRect, pyqtSlot, pyqtSignal, QThread, QMetaObject, Q_ARG, QPoint
from PyQt5.QtGui import QPainter, QImage
from PyQt5.QtWidgets import QWidget, QApplication, QMainWindow, QGridLayout, QToolBar, QAction
from PyQt5.QtMultimedia import QMediaPlayer, QMediaContent, QAbstractVideoBuffer, QVideoProbe, QVideoFrame, QVideoSurfaceFormat, QAbstractVideoSurface
from PyQt5.QtMultimediaWidgets import QVideoWidget



from chromakey_mainWindow_compilePy import Ui_MainWindow


# region FUNCTIONS
def imqt2cv(frame):
    incomingImage = frame
    width = incomingImage.width()
    height = incomingImage.height()
    
    if incomingImage.isGrayscale():
        incomingImage = incomingImage.convertToFormat(QImage.Format_Grayscale8)
        ptr = incomingImage.bits()
        ptr.setsize(incomingImage.byteCount())
        arr = np.array(ptr).reshape(height, width)  #  Copies the data
        # cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), arr)
    else:
        incomingImage = incomingImage.convertToFormat(QImage.Format_RGB32)
        ptr = incomingImage.bits()
        ptr.setsize(incomingImage.byteCount())
        arr = np.array(ptr).reshape(height, width, 4)  #  Copies the data
        arr =  cv2.cvtColor(arr, cv2.COLOR_BGR2RGB)
        # arr = arr[:,:,0:3]
        # print(arr.shape)
    return arr



def imcv2qt(img):
    cvImg = img

    # cvImg =  cv2.cvtColor(cvImg, cv2.COLOR_BGR2GRAY)

    if len(cvImg.shape) == 3:
        height, width, channel = cvImg.shape
    else:
        height, width = cvImg.shape
        channel = 1

    bytesPerLine = channel * width # step of cvmat

    if channel == 1:
        qImg = QImage(cvImg.data, width, height, bytesPerLine, QImage.Format_Indexed8).copy()
    elif channel == 3:
        # cvImg =  cv2.cvtColor(cvImg, cv2.COLOR_BGR2RGB) 
        qImg = QImage(cvImg.data, width, height, bytesPerLine, QImage.Format_RGB888).copy() # only with RGB
        # qImg = QImage(cvImg.data, width, height, bytesPerLine, QImage.Format_RGB888).rgbSwapped()
    return qImg

 


def processImageRGB(img, edit_params, colors): # RGB
        
    tol = edit_params[0]
    soft = edit_params[1]
    df = edit_params[2]

    # rgb = np.array(colors[0][0:3])
    hsv = np.array(colors[0][0:3])
    # hsv = np.array(colors[1][0:3])

    # plt.imshow(img)
    # plt.show()



    if soft > 0:
        step = np.round(np.mean(img.shape[0:2])/100)
        size = int(step + round(soft/5))
        if size % 2 == 0:
            size += 1
        # sigma = 0.3 * ((size − 1) * 0.5 − 1) + 0.8
        blur = cv2.GaussianBlur(img, (size, size), 0, 0)

        # blur2 = cv2.cvtColor(blur, cv2.COLOR_BGR2RGB)
        # cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), blur2) # cv2 uses BGR

    else:
        blur = img
    
    # img_hsv = cv2.cvtColor(blur, cv2.COLOR_RGB2HSV)
    img_hsv = cv2.cvtColor(blur, cv2.COLOR_BGR2RGB)
    # cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), img_hsv) # cv2 uses BGR
    

    
    lower_hsv = np.round(hsv * (1 - tol/100)) - 35
    upper_hsv = np.round(hsv * (1 + tol/100)) + 35

    lower_hsv[lower_hsv<0]  = 0

    # if upper_hsv[0] > 180:
    #     upper_hsv[0] = 180

    upper_hsv[upper_hsv>255] = 255

    # mask = cv2.inRange(img_hsv, (36, 25, 25), (70, 255,255))
    mask = cv2.inRange(img_hsv, lower_hsv, upper_hsv)
    mask = ~mask

    # plt.imshow(mask)
    # plt.show()

    # img2 = cv2.bitwise_and(img, mask)
    img2 = cv2.bitwise_and(img, img, mask=mask)

    img2_brg = cv2.cvtColor(img2, cv2.COLOR_BGR2RGB)
    cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), img2_brg) # cv2 uses BGR

    # plt.imshow(img2)
    # plt.show()
        
    return img2

def processImageHSV(img, edit_params, colors): # HSV
        
    tol = edit_params[0]
    soft = edit_params[1]
    df = edit_params[2]

    rgb = np.array(colors[0][0:3])
    hsv = np.array(colors[1][0:3])

    # plt.imshow(img)
    # plt.show()

    hsv[0] = hsv[0]/2
    # hsv[1] = hsv[1] - 50
    # hsv[2] = hsv[2] - 50

    if soft > 0:
        step = np.round(np.mean(img.shape[0:2])/100)
        size = int(step + round(soft/5))
        if size % 2 == 0:
            size += 1
        # sigma = 0.3 * ((size − 1) * 0.5 − 1) + 0.8
        blur = cv2.GaussianBlur(img, (size, size), 0, 0)

    else:
        blur = img

    
    img_hsv = cv2.cvtColor(blur, cv2.COLOR_RGB2HSV)
    # img_bgr = cv2.cvtColor(blur, cv2.COLOR_BGR2RGB)
    # cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), img_bgr) # cv2 uses BGR
    
    lower_hsv = np.round(hsv * (1 - tol/100)) - 35
    upper_hsv = np.round(hsv * (1 + tol/100)) + 35

    lower_hsv[0] += 30
    lower_hsv[1] -= 45
    lower_hsv[2] -= 30

    upper_hsv[0] -= 30
    upper_hsv[1] += 45
    upper_hsv[2] += 30

    lower_hsv[lower_hsv<0]  = 0

    if upper_hsv[0] > 180:
        upper_hsv[0] = 180

    upper_hsv[upper_hsv>255] = 255

    # mask = cv2.inRange(img_hsv, (36, 25, 25), (70, 255,255))
    mask = cv2.inRange(img_hsv, lower_hsv, upper_hsv)
    mask = ~mask

    # plt.imshow(mask)
    # plt.show()

    # img2 = cv2.bitwise_and(img, mask)
    img2 = cv2.bitwise_and(img, img, mask=mask)

    img3 = img2
    # img3 = defringe(img2, df)

    # img3_brg = cv2.cvtColor(img2, cv2.COLOR_BGR2RGB)
    # cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), img3_brg) # cv2 uses BGR

    # plt.imshow(img3)
    # plt.show()
        
    return img3

def processImage(img, edit_params, colors): # YCrCb

    # Input params
    tol = edit_params[0]
    soft = edit_params[1]
    df = edit_params[2]

    # rgb = np.array(colors[0][0:3])
    # hsv = np.array(colors[1][0:3])
    rgb = np.zeros([1,1,3]).astype(np.uint8)
    rgb[0,0,:] = colors[0][0:3]
    ycc = cv2.cvtColor(rgb, cv2.COLOR_RGB2YCrCb)
    # ycc2 = rgb2ycbcr(rgb)




    # Gaussian
    if soft > 0:
        step = np.round(np.mean(img.shape[0:2])/100)
        size = int(step + round(soft/5))
        if size % 2 == 0:
            size += 1
        # sigma = 0.3 * ((size − 1) * 0.5 − 1) + 0.8
        blur = cv2.GaussianBlur(img, (size, size), 0, 0)
    else:
        blur = img


    

    # Convert from RGB to YCrCb
    im_ycc = cv2.cvtColor(img, cv2.COLOR_RGB2YCrCb)
    im_yccf = im_ycc.astype(np.float64)
    


    # Setting the distances
    dr = im_yccf[:,:,1] - ycc[0,0,1]
    db = im_yccf[:,:,2] - ycc[0,0,2]
    # # dist = np.sqrt(dr**2 + db**2)
    dist = dr**2 + db**2
    # # dist = np.square(dr) + np.square(db)
    # # dist = np.abs(dr) + np.abs(db)


    tolb = 15.0*(1+ 5*tol/100)
    tola = tolb - 2 + 4*(1 + 5*df/100)

    if tola > tolb:
        tolb = tola

    tola = tola**2
    tolb = tolb**2




    # Filter the distances
    # region1 = dist < tola
    region2 = (dist >= tola) & (dist < tolb)
    region3 = dist > tolb

    mask = np.zeros(img.shape[0:2]).astype(np.uint8)
    # mask[region2] = (dist[region2] - tola) / (tola - tolb)
    mask[region2] = 1
    mask[region3] = 1



    # Apply mask
    mask2 = 1 - mask
    img2 = cv2.bitwise_and(img, img, mask=mask)

    # %%
    bgFileName = 'tapety.tja.pl-175327.jpg' # should be read 1 time from the upper class
    bg= cv2.imread(bgFileName)
    bg = cv2.cvtColor(bg, cv2.COLOR_BGR2RGB)
    bg = cv2.resize(bg, (img.shape[1], img.shape[0]), interpolation = cv2.INTER_AREA)
    # plt.imshow(bg)
    # plt.show()

    # %%
    img3 = cv2.bitwise_and(bg, bg, mask=mask2)
    # plt.imshow(img3)
    # plt.show()

    # %%
    # img4 = np.array(img2.data) + np.array(img3.data)
    img4 = img2 + img3
    # plt.imshow(img4)
    # plt.show()

    # print('Done!')

    # return img2
    return img4




def rgb2ycbcr(img, only_y=False):
    '''same as matlab rgb2ycbcr
    only_y: only return Y channel
    Input:
        uint8, [0, 255]
        float, [0, 1]
    '''
    in_img_type = img.dtype
    img.astype(np.float64)
    if in_img_type != np.uint8:
        img *= 255.
    # convert
    if only_y:
        rlt = np.dot(img, [65.481, 128.553, 24.966]) / 255.0 + 16.0
    else:
        rlt = np.matmul(img, [[65.481, -37.797, 112.0], [128.553, -74.203, -93.786],
                                [24.966, 112.0, -18.214]]) / 255.0 + [16, 128, 128]
    if in_img_type == np.uint8:
        rlt = rlt.round()
    else:
        rlt /= 255.
    return rlt.astype(in_img_type)

def defringe(img, df):

    lowPassWindowWidth = 15; 
    highPassWindowWidth = 3; 

    lowFilter = round(lowPassWindowWidth * (1 + df/20))
    highFilter = round(highPassWindowWidth * (1 + df/100))

    if lowFilter % 2 == 0:
        lowFilter += 1

    if highFilter % 2 == 0:
        highFilter += 1

    imLow = cv2.medianBlur(img, lowFilter)
    imLow_brg = cv2.cvtColor(imLow, cv2.COLOR_BGR2RGB)
    cv2.imwrite('frames/captured_images/L_{}.jpg'.format(str(uuid.uuid4())), imLow_brg) # cv2 uses BGR

    imHigh = img - cv2.medianBlur(img, highFilter)
    imHigh_brg = cv2.cvtColor(imHigh, cv2.COLOR_BGR2RGB)
    cv2.imwrite('frames/captured_images/M_{}.jpg'.format(str(uuid.uuid4())), imHigh_brg) # cv2 uses BGR

    imFinal = img + imLow - imHigh
    img2_brg = cv2.cvtColor(imFinal, cv2.COLOR_BGR2RGB)
    cv2.imwrite('frames/captured_images/N_{}.jpg'.format(str(uuid.uuid4())), img2_brg) # cv2 uses BGR


    fz = 31
    imMed = cv2.medianBlur(img, fz)
    fz2 = 201
    imGa = cv2.GaussianBlur(imMed, (fz2, fz2), 0, 0)
    meanGa = np.mean(imGa)
    newGa = imMed + imGa - int(meanGa)
    img2_brg = cv2.cvtColor(newGa, cv2.COLOR_BGR2RGB)
    cv2.imwrite('frames/captured_images/O_{}.jpg'.format(str(uuid.uuid4())), img2_brg) # cv2 uses BGR

    return imFinal


def editFrame(frame, edit_params, colors):
    if frame.map(QAbstractVideoBuffer.ReadOnly):
        pixelFormat = frame.pixelFormat()
        imageFormat = QVideoFrame.imageFormatFromPixelFormat(pixelFormat)
        if imageFormat != QImage.Format_Invalid:
            # Process RGB data
            image = QImage(frame.bits(), frame.width(), frame.height(), imageFormat)
            image2 = image.mirrored(False, True)
            
            imcv = imqt2cv(image2)

            if (colors != []):
                improc = processImage(imcv, edit_params, colors)
                imqt = imcv2qt(improc)
            else:
                improc = imcv
                imqt = image2


    return imqt, improc












# originalGrayImage = im2double(imread('whitehouse.tif')); 
# subplot(2,2,1);
# imshow(originalGrayImage); 
# title('Original Grayscale Image', 'FontSize', fontSize);
# set(gcf, 'Position', get(0,'Screensize')); % Enlarge figure to full screen.

# lowPassWindowWidth = 21; 
# highPassWindowWidth = 7; 
#
# Idm = medfilt2(originalGrayImage, [lowPassWindowWidth lowPassWindowWidth]); 
# subplot(2,2,2);
# imshow(Idm); 
# title('Lowpass Image', 'FontSize', fontSize);

# Ide = originalGrayImage - medfilt2(originalGrayImage, [highPassWindowWidth highPassWindowWidth]); 
# subplot(2,2,3);
# imshow(Ide); 
# title('Highpass Image', 'FontSize', fontSize);

# finalFilteredGrayImage = Idm + Ide; 
# subplot(2,2,4);
# imshow(finalFilteredGrayImage);
# caption = sprintf('Final Filtered Image =\nLow Pass Image + High Pass Image');
# title(caption, 'FontSize', fontSize);     

# endregion FUNCTIONS



class FrameProcessor(QObject):
    imageReady = pyqtSignal(QImage, np.ndarray)

    @pyqtSlot(QVideoFrame)
    def processFrame2(self, frame):
        if frame.map(QAbstractVideoBuffer.ReadOnly):
            pixelFormat = frame.pixelFormat()
            imageFormat = QVideoFrame.imageFormatFromPixelFormat(pixelFormat)
            if imageFormat != QImage.Format_Invalid:
                # Process RGB data
                image = QImage(frame.bits(), frame.width(), frame.height(), imageFormat)
                image2 = image.mirrored(False, True)

                imcv = imqt2cv(image2)
                imqt = imcv2qt(imcv)

        # self.imageReady.emit(image2)
        self.imageReady.emit(imqt)

    @pyqtSlot(QVideoFrame, list, list)
    def processFrame1(self, frame, edit_params, colors):
        if frame.map(QAbstractVideoBuffer.ReadOnly):
            pixelFormat = frame.pixelFormat()
            imageFormat = QVideoFrame.imageFormatFromPixelFormat(pixelFormat)
            if imageFormat != QImage.Format_Invalid:
                # Process RGB data
                image = QImage(frame.bits(), frame.width(), frame.height(), imageFormat)
                image2 = image.mirrored(False, True)

                if (colors != []):
                    imcv = imqt2cv(image2)
                    improc = processImage(imcv, edit_params, colors)
                    # plt.imshow(improc)
                    # plt.show()
                    imqt = imcv2qt(improc)
                else:
                    imqt = image2

                # imqt.save('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())))

                # self.imageReady.emit(image2)
                self.imageReady.emit(imqt)

    @pyqtSlot(QVideoFrame, list, list)
    def processFrame(self, frame, edit_params, colors):
        imqt, improc = editFrame(frame, edit_params, colors)
        self.imageReady.emit(imqt, improc)
        


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):

    colorChanged = QtCore.pyqtSignal('QColor')

    def __init__(self, parent=None):
        # super().__init__(parent)
        QtWidgets.QMainWindow.__init__(self, parent)
        Ui_MainWindow.__init__(self)
        self.setupUi(self)

        # region INIT COLOR
        self.color_picking = False

        self.colorChanged.connect(self.color_updatePreview)

        self.buttonPickScreen.clicked.connect(self.color_onButtonPickScreenClicked)

        self.color_rgba = []
        self.color_hsva = []
        self.colors = []
        # endregion INIT COLOR

        # region INIT VIDEO
        self.fileName = ''

        p = QtGui.QPalette()
        # p.setColor(QtGui.QPalette.Window, QtCore.Qt.black)
        p.setColor(QtGui.QPalette.Background, QtGui.QColor('black'))
        self.video_displayWidget.setAutoFillBackground(True)
        self.video_displayWidget.setPalette(p)

        self.video_mediaPlayer = QtMultimedia.QMediaPlayer(None, QtMultimedia.QMediaPlayer.VideoSurface)
        self.video_mediaPlayer.setVideoOutput(self.video_displayWidget)
        self.video_mediaPlayer.stateChanged.connect(self.mediaStateChanged)
        self.video_mediaPlayer.positionChanged.connect(self.positionChanged)
        self.video_mediaPlayer.durationChanged.connect(self.durationChanged)
        self.video_mediaPlayer.error.connect(self.handleError)


        self.video_probe = QVideoProbe()
        # self.video_probe.videoFrameProbed.connect(self.frameChanged)
        # self.video_probe.setSource(self.video_mediaPlayer))

        self.video_currentFrame = None

        self.m_processor = FrameProcessor()
        self.m_processorThread = QThread()
        self.m_processor.moveToThread(self.m_processorThread)
        self.m_processorThread.finished.connect(self.m_processor.deleteLater)
        # self.video_probe.videoFrameProbed.connect(self.m_processor.processFrame2)
        self.video_probe.videoFrameProbed.connect(self.frameChanged)
        self.m_processor.imageReady.connect(self.show_and_write)
        self.m_processorThread.start()

        self.video_probe.setSource(self.video_mediaPlayer)


        self.video_outputFrame.setScaledContents(True) # to set display size to QLabel's size, if not display will expand to image'size
        self.video_outputFrame.setSizePolicy(QtWidgets.QSizePolicy.Ignored, QtWidgets.QSizePolicy.Ignored)

        self.video_buttonOpen.clicked.connect(self.video_openFile)

        self.video_buttonPlay.setEnabled(False)
        self.video_buttonPlay.setIcon(self.style().standardIcon(QtWidgets.QStyle.SP_MediaPlay))
        self.video_buttonPlay.clicked.connect(self.video_play)

        self.video_hSlider.setRange(0, 0)
        self.video_hSlider.sliderMoved.connect(self.setPosition)

        self.check_image = True

        # endregion INIT VIDEO

        # region INIT EDIT
        self.edit_hSliderTol.valueChanged.connect(self.toleranceChanged)
        self.edit_hSliderSoft.valueChanged.connect(self.softChanged)
        self.edit_hSliderDefringe.valueChanged.connect(self.defringeChanged)

        self.edit_params = [0, 0, 0]

        self.edit_buttonSave.clicked.connect(self.edit_buttonSaveClicked)

        # endregion INIT EDIT



    def __del__ ( self ):
        self.ui = None
    

# region COLOR

    def color_onButtonPickScreenClicked(self, event):
        self.color_picking = True
        self.grabKeyboard() # inherit from QtWidgets.QWidget, also from QtWidgets.QMainWindow
        self.grabMouse(QtCore.Qt.CrossCursor)

    def mouseMoveEvent(self, event):
        if self.color_picking:
            self.color_pickColor(event.globalPos())
            return
        return QtWidgets.QWidget.mouseMoveEvent(self, event)

    def mouseReleaseEvent(self, event):
        if self.color_picking:
            self.color_picking = False
            self.releaseKeyboard()
            self.releaseMouse()
            self.color_pickColor(event.globalPos())
            return
        return QtWidgets.QWidget.mouseReleaseEvent(self, event)
    
    def color_pickColor(self, pos):
        desktop = QtWidgets.QApplication.desktop().winId()
        screen = QtWidgets.QApplication.primaryScreen()
        pixmap = screen.grabWindow(desktop, pos.x(), pos.y(), 1, 1)
        img = pixmap.toImage()
        color = QtGui.QColor(img.pixel(0,0))

        self.color_rgba = color.getRgb()
        self.color_hsva = color.getHsv()
        self.colors = [self.color_rgba, self.color_hsva]

        # self.textColorCode.setText(color.name())
        self.textColorCode.setText('HSV = ' + str(self.color_hsva[0:3]))
        self.colorChanged.emit(color)

		# if isinstance(self.spinColEdit,QColorSpinEdit):
		# 	self.spinColEdit.setColor(col)
		# else:
		# 	self.spinColEdit.setCurrentColor(col)
		# self.setColor(col)


    # def color_toggleHsv(self, checked):
	# 	if checked:
	# 		self.spinColEdit.show()
	# 		really_here = self.mapToGlobal(self.rect().bottomRight())
	# 		bottom_margin = self.layout().contentsMargins().bottom()
	# 		bottom_corner= really_here.x()-self.spinColEdit.width()
	# 		pop_here = really_here.y()-bottom_margin
	# 		#print(bottom_corner, pop_here, self.height(), really_here.y(), bottom_margin)
	# 		self.spinColEdit.move(bottom_corner, pop_here)
	# 		self.previewPanel.setText("▼")
	# 	else:
	# 		#print("e")
	# 		self.spinColEdit.hide()
	# 		self.previewPanel.setText("▶")
    
    def color_updatePreview(self, color):
        # px=QtGui.QPixmap(128,128)
        # px.fill(color)
		# self.previewPanel.setIcon(QtGui.QIcon(px))

        # self.textColorCode.setStyleSheet("QLineEdit {background: %s}" % color.name())
        # self.textColorCode.setStyleSheet("QLineEdit {background: %s}" % self.color_invertColor(color).name())

        palette= QtGui.QPalette()
        palette.setColor(QtGui.QPalette.Base, color)
        palette.setColor(QtGui.QPalette.Text, self.color_invertColor(color))
        self.textColorCode.setPalette(palette)


    def color_invertColor(self, color):
        r, g, b, alpha = color.getRgb()
        # print(color.getRgb())
        invertedRed = 255 - r
        invertedGreen = 255 - g
        invertedBlue = 255 - b
        invertedColor = QtGui.QColor.fromRgb(invertedRed, invertedGreen, invertedBlue, alpha)
        # print(invertedColor.getRgb())
        return invertedColor

# endregion COLOR





# region VIDEO
    def video_openFile(self):
        # self.fileName, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open Movie", QtCore.QDir.homePath())
        self.fileName, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open Movie")
        if self.fileName != '':
            self.video_mediaPlayer.setMedia(QtMultimedia.QMediaContent(QtCore.QUrl.fromLocalFile(self.fileName)))
            self.video_buttonPlay.setEnabled(True)


    def video_play(self):
        if self.video_mediaPlayer.state() == QtMultimedia.QMediaPlayer.PlayingState:
            self.video_mediaPlayer.pause()
        else:
            self.video_mediaPlayer.play()

            # keys = self.video_mediaPlayer.availableMetaData() # ['Duration', 'PixelAspectRatio', 'Resolution', 'VideoBitRate', 'VideoCodec', 'VideoFrameRate']
            # fps = self.video_mediaPlayer.metaData(keys[5]) # 29.97
            fps = self.video_mediaPlayer.metaData('VideoFrameRate')
            if fps > 20:
                self.video_mediaPlayer.setPlaybackRate(0.75)

    def mediaStateChanged(self, state):
        if self.video_mediaPlayer.state() == QtMultimedia.QMediaPlayer.PlayingState:
            self.video_buttonPlay.setIcon(self.style().standardIcon(QtWidgets.QStyle.SP_MediaPause))
            self.video_buttonPlay.setText("Pause")
        else:
            self.video_buttonPlay.setIcon(self.style().standardIcon(QtWidgets.QStyle.SP_MediaPlay))
            self.video_buttonPlay.setText("Play")

    def positionChanged(self, position):
        self.video_hSlider.setValue(position)
        self.video_labelCurrent.setText(self.video_hhmmss_2(position))

    def durationChanged(self, duration):
        self.video_hSlider.setRange(0, duration)
        # self.video_hSlider.setMaximum(duration)
        if duration >= 0:
            self.video_labelTotal.setText(self.video_hhmmss_2(duration))
    
    # def update_duration(self, duration):
    #     self.timeSlider.setMaximum(duration)
    #     if duration >= 0:
    #         self.totalTimeLabel.setText(hhmmss(duration))

    def setPosition(self, position):
        self.video_mediaPlayer.setPosition(position)

    def handleError(self):
        self.video_buttonPlay.setEnabled(False)
        self.video_labelStatus.setText("Error: " + self.video_mediaPlayer.errorString())

    def video_hhmmss(self, ms):
        # s = 1000
        # m = 60000
        # h = 360000
        h, r = divmod(ms, 36000)
        m, r = divmod(r, 60000)
        s, _ = divmod(r, 1000)
        return ("%d:%02d:%02d" % (h,m,s)) if h else ("%d:%02d" % (m,s))

    def video_hhmmss_2(self, timeMs):
        time_in_sec = timeMs/1000.0
        totalTime = QtCore.QTime((time_in_sec/3600)%60, (time_in_sec/60)%60, time_in_sec%60, (time_in_sec*1000)%1000)
        format = 'hh:mm:ss' if time_in_sec > 3600 else 'mm:ss'
        timeString = totalTime.toString(format)
        return timeString

    
    def frameChanged(self, frame):
        self.video_currentFrame = frame
        QMetaObject.invokeMethod(self.m_processor, 'processFrame', Qt.QueuedConnection, Q_ARG(QVideoFrame, frame), Q_ARG(list, self.edit_params), Q_ARG(list, self.colors))

    def show_and_write(self, qImage, imcv):
        # imcv = self.imqt2cv(qImage)
        # imqt = self.imcv2qt(imcv)
        # pix = QtGui.QPixmap.fromImage(imqt)

        # qImage.save('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())))

        pix = QtGui.QPixmap.fromImage(qImage)
        self.video_outputFrame.setPixmap(pix)
        
        # imcv2 = cv2.cvtColor(imcv, cv2.COLOR_RGB2BGR)
        # cv2.imwrite('frames/captured_images/hello_{}.jpg'.format(str(uuid.uuid4())), imcv2) # cv2 uses BGR, should write in thread

    def write_video(self, cvImage):
        pass
        


# endregion VIDEO





# region EDIT
    def toleranceChanged(self):
        self.edit_params[0] = self.edit_hSliderTol.value()
        self.edit_labelTolValue.setText(str(self.edit_params[0]) + ' %')
        self.edit_updatePauseFrame()
        
    def softChanged(self):
        self.edit_params[1]  = self.edit_hSliderSoft.value()
        self.edit_labelSoftValue.setText(str(self.edit_params[1]) + ' %')
        if self.video_mediaPlayer.state() == QtMultimedia.QMediaPlayer.PlayingState:
            self.video_buttonPlay.click()
        self.edit_updatePauseFrame()

    def defringeChanged(self):
        self.edit_params[2] = self.edit_hSliderDefringe.value()
        self.edit_labelDefringeValue.setText(str(self.edit_params[2]) + ' %')
        # if self.video_mediaPlayer.state() == QtMultimedia.QMediaPlayer.PlayingState:
        #     self.video_buttonPlay.click()
        self.edit_updatePauseFrame()

    def edit_updatePauseFrame(self):
        if self.video_mediaPlayer.state() == QtMultimedia.QMediaPlayer.PausedState:
            imqt, imcv = editFrame(self.video_currentFrame, self.edit_params, self.colors)
            self.show_and_write(imqt, imcv)

    def edit_buttonSaveClicked(self):
        # Open Save Dialog
        saveName, _ = QtWidgets.QFileDialog.getSaveFileName(self, "Save file", ".", ".mp4")
        # saveName = QtWidgets.QFileDialog.getSaveFileName(parent=self, caption='Select output file', dir='.', filter='Kicad PCB Files (*.kicad_pcb)')
        if saveName != '':
            self.apply(saveName)

    def apply(self, saveName):
        vcap = cv2.VideoCapture(self.fileName)

        # Find OpenCV version
        (major_ver, minor_ver, subminor_ver) = (cv2.__version__).split('.')
     
        if int(major_ver)  < 3 :
            fps = vcap.get(cv2.cv.CV_CAP_PROP_FPS)
            # print("Frames per second using video.get(cv2.cv.CV_CAP_PROP_FPS): {0}".format(fps))
        else :
            fps = vcap.get(cv2.CAP_PROP_FPS)
            # print("Frames per second using video.get(cv2.CAP_PROP_FPS) : {0}".format(fps))


        frame_width = int(vcap.get(3))
        frame_height = int(vcap.get(4))

        # frame_width = int(vcap.get(cv2.CAP_PROP_FRAME_WIDTH))
        # frame_height =int(vcap.get(cv2.CAP_PROP_FRAME_HEIGHT))

        # Define the codec and create VideoWriter object.
        # outavi = cv2.VideoWriter(saveName, cv2.VideoWriter_fourcc('M','J','P','G'), round(fps), (frame_width,frame_height))
        outmp4 = cv2.VideoWriter(saveName, cv2.VideoWriter_fourcc(*'XVID'), round(fps), (frame_width, frame_height))

        count = 0
        success = True

        success, imcv = vcap.read()
        
        

        while success:
            imcv = cv2.cvtColor(imcv, cv2.COLOR_BGR2RGB)
            improc = processImage(imcv, self.edit_params, self.colors)
            improc = cv2.cvtColor(improc, cv2.COLOR_RGB2BGR)
            
            # outavi.write(improc)
            outmp4.write(improc)

            success, imcv = vcap.read()

        # Release everything if job is finished
        vcap.release()
        # outavi.release()
        outmp4.release()




# endregion EDIT

        


