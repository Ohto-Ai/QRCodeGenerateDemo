#include "MainWindow.h"
#include <QMenu>
#include <QClipboard>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
		
	ui.qrType->clear();
	ui.qrType->addItem("QR Code", false);
	ui.qrType->addItem("Micro QR Code", true);
	
	ui.qrLevel->clear();
	ui.qrLevel->addItem("L(7%)", QREncoder::ErrorCorrectionLevel::LevelL);
	ui.qrLevel->addItem("M(15%)", QREncoder::ErrorCorrectionLevel::LevelM);
	ui.qrLevel->addItem("Q(25%)", QREncoder::ErrorCorrectionLevel::LevelQ);
	ui.qrLevel->addItem("H(30%)", QREncoder::ErrorCorrectionLevel::LevelH);

	connect(ui.text, &QPlainTextEdit::textChanged, this, &MainWindow::updateQRCode);
	connect(ui.qrLevel, &QComboBox::currentIndexChanged, this, &MainWindow::updateQRCode);
	connect(ui.qrType, &QComboBox::currentIndexChanged, this, &MainWindow::updateQRCode);

	connect(ui.sizeSpin, &QSpinBox::valueChanged, this, &MainWindow::renderQRCode);
	connect(ui.sizeSlider, &QSlider::rangeChanged, [=](int min, int max)
		{
			ui.sizeSpin->setMinimum(min);
			ui.sizeSpin->setMaximum(max);
		});

	connect(ui.qrCode, &QLabel::customContextMenuRequested, [=]
		{
			QMenu menu;
			menu.addAction("&Copy", [=]
				{
					qApp->clipboard()->setImage(renderedImage);
				});

			menu.exec(QCursor::pos());
		});

	connect(ui.borderSlider, &QSlider::valueChanged, [=]
		{
			if (ui.borderSlider->value() < 0)
				ui.borderDisplay->setText("Default");
			else
				ui.borderDisplay->setText(QString("%1x").arg(ui.borderSlider->value()));
			renderQRCode();
		});
	
	updateQRCode();
}

void MainWindow::updateQRCode()
{
	auto data = ui.text->toPlainText();
	if (data.isEmpty())
		data = ui.text->placeholderText();
	encoder = QREncoder::encode(data
		, ui.qrLevel->currentData().value<QREncoder::ErrorCorrectionLevel>()
		, ui.qrType->currentData().toBool());
	if (encoder.width() > 50)
	{
		if (encoder.width() > ui.sizeSpin->minimum())
		{
			ui.sizeSlider->setMinimum(encoder.width());
		}
	}
	else if(ui.sizeSpin->minimum()>50)
	{
		ui.sizeSlider->setMinimum(50);
	}
	
	renderQRCode();
}

void MainWindow::renderQRCode()
{
	renderedImage = encoder.toImage(ui.sizeSpin->value(), ui.borderSlider->value());
	ui.qrCode->setPixmap(QPixmap::fromImage(renderedImage).scaled(ui.qrCode->width(), ui.qrCode->height(), Qt::KeepAspectRatio));
}
