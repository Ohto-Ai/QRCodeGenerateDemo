#pragma once
#include <QMainWindow>
#include "ui_MainWindow.h"
#include "QREncoder.h"

class MainWindow :
    public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget*parent = nullptr);

	void updateQRCode();
	void renderQRCode();
private:
	QImage renderedImage;
	QREncoder encoder;
	Ui::MainWindow ui;
};

