

#include "MainWindow.h"

#include <QApplication>
#include <QIcon>


int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    qApp->setWindowIcon(QIcon(":/icon/QRCode"));

    MainWindow w;
    w.show();
	
    return a.exec();
}
