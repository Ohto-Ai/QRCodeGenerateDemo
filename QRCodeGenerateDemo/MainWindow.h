#pragma once
#include <QMainWindow>
#include <QTimer>
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
protected:
	void doUpdateQrCode();

	void mousePressEvent(QMouseEvent* event) override;
private:
	QImage renderedImage;
	QREncoder encoder;
	Ui::MainWindow ui;

	QTimer inputDelayTimer{ this };
};

