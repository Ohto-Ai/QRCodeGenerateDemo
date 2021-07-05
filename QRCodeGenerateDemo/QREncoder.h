#pragma once

#include <QREncode.h>
#include <QBitArray>
#include <QPainter>

class QREncoder
{
public:
    enum ErrorCorrectionLevel {
        LevelL = 0, ///< lowest
        LevelM,
        LevelQ,
        LevelH      ///< highest
    };

    enum EncodeMode {
        ModeNul = -1,   ///< Terminator (NUL character). Internal use only
        ModeNum = 0,    ///< Numeric mode
        ModeAn,         ///< Alphabet-numeric mode
        Mode8,          ///< 8-bit data mode
        ModeKanji,      ///< Kanji (shift-jis) mode
        ModeStructure,  ///< Internal use only
        ModeEci,        ///< ECI mode
        ModeFnc1first,  ///< FNC1, first position
        ModeFnc1second, ///< FNC1, second position
    };
public:
	
    QImage toImage(int codeImageWidth = 400, int borderWidth = -1, QColor foreColor = Qt::black, QColor backgroundColor = Qt::white)
    {
        if (qrData.isEmpty())
            return QImage();

    	
        double scale = (double)codeImageWidth / qrWidth;
        if (borderWidth < 0)
            borderWidth = scale * 2;
        else
            borderWidth *= scale;
    	
        QImage qrImage = QImage(codeImageWidth + borderWidth * 2, codeImageWidth + borderWidth * 2, QImage::Format_ARGB32);
        QPainter painter(&qrImage);
        painter.setBrush(backgroundColor);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, qrImage.width(), qrImage.height());
        painter.setBrush(foreColor);

        for (int i = 0; i < qrWidth; ++i)
        {
            for (int j = 0; j < qrWidth; ++j)
            {
                if (qrData[i * qrWidth + j])
                {
                    painter.drawRect(QRectF(borderWidth + j * scale, borderWidth + i * scale, scale, scale));
                }
            }
        }

        return qrImage;
    }

    static QREncoder encode(QString string, ErrorCorrectionLevel ecLevel = LevelQ, bool useMicroQR = false
        , int version = 0, EncodeMode hint = Mode8, bool caseSensitive = true)
    {
        QRcode* qrCode;
    	if(useMicroQR )
            qrCode= QRcode_encodeStringMQR(string.toUtf8(), version
            , static_cast<QRecLevel>(ecLevel), static_cast<QRencodeMode>(hint), caseSensitive);
        else
            qrCode = QRcode_encodeString(string.toUtf8(), version
                , static_cast<QRecLevel>(ecLevel), static_cast<QRencodeMode>(hint), caseSensitive);
        if (qrCode == nullptr)
            return QREncoder();
        QREncoder code;
        code.qrWidth = qrCode->width;
        code.qrVersion = qrCode->version;
        code.qrData = QBitArray(code.qrWidth * code.qrWidth);

        auto qrCodeWidth = qrCode->width > 0 ? qrCode->width : 1;
        for (int i = 0; i < qrCodeWidth; ++i)
        {
            for (int j = 0; j < qrCodeWidth; ++j)
            {
                code.qrData.setBit(i * qrCodeWidth + j, qrCode->data[i * qrCodeWidth + j] & 1);
            }
        }

        QRcode_free(qrCode);

        return code;
    }

    QBitArray data()const
    {
        return qrData;
    }
    int width() const
    {
        return qrWidth;
    }
    int version() const
    {
        return qrVersion;
    }


private:
    int qrWidth{ 0 };
    int qrVersion{ 0 };
    QBitArray qrData{};
};
