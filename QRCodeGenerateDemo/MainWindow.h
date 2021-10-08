#pragma once
#include <QDir>
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

	const QString tmpSavePath = QDir::tempPath() + "/qr_export.png";

	QTimer inputDelayTimer{ this };
	QTimer renderDelayTimer{ this };
};

