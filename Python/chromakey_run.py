import sys
from PyQt5 import QtCore, QtGui, QtWidgets, uic


from chromakey_mainWindow import MainWindow
# from chromakey_mainWindow_compilePy import Ui_MainWindow


if __name__ == '__main__':

    # create application
    app = QtWidgets.QApplication(sys.argv)
    app.setApplicationName('My PyQt5 QtGui Project')

    # create widget
    mainWindow = MainWindow()
    mainWindow.setWindowTitle('Chroma Keying')
    mainWindow.show()

    # connection
    # QtCore.QObject.connect(app, SIGNAL('lastWindowClosed()'), app, SLOT('quit()'))

    # execute application
    sys.exit(app.exec_())



