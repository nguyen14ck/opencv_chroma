#include "Chroma2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	//QCoreApplication::addLibraryPath("C:\\Qt\\Qt5.14.0\\5.14.0\\msvc2017_64\\bin");
	//QCoreApplication::addLibraryPath("C:\\Qt\\Qt5.14.0\\5.14.0\\msvc2017_64\\plugins\\platforms");

	QApplication a(argc, argv);
	Chroma2 w;
	w.show();
	return a.exec();
}
