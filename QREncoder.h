#pragma once

#include <qrencode.h>
#include <vector>
#include <string>

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
    void print(std::string foreground = "█", std::string background = "  ")
    {
        for (int i = 0; i < qrWidth; ++i)
        {
            for (int j = 0; j < qrWidth; ++j)
            {
                printf("%s", qrData[i * qrWidth + j] ? foreground.c_str(): background.c_str());
            }
            printf("\n");
        }
    }

    static QREncoder encode(std::string string, ErrorCorrectionLevel ecLevel = LevelQ, bool useMicroQR = false
        , int version = 0, EncodeMode hint = Mode8, bool caseSensitive = true)
    {
        QRcode* qrCode;
    	if(useMicroQR )
            qrCode= QRcode_encodeStringMQR(string.c_str(), version
            , static_cast<QRecLevel>(ecLevel), static_cast<QRencodeMode>(hint), caseSensitive);
        else
            qrCode = QRcode_encodeString(string.c_str(), version
                , static_cast<QRecLevel>(ecLevel), static_cast<QRencodeMode>(hint), caseSensitive);
        if (qrCode == nullptr)
            return QREncoder();
        QREncoder code;
        code.qrWidth = qrCode->width;
        code.qrVersion = qrCode->version;
        code.qrData = std::vector<bool>(code.qrWidth * code.qrWidth, false);

        auto qrCodeWidth = qrCode->width > 0 ? qrCode->width : 1;
        for (int i = 0; i < qrCodeWidth; ++i)
        {
            for (int j = 0; j < qrCodeWidth; ++j)
            {
                code.qrData[i * qrCodeWidth + j]= qrCode->data[i * qrCodeWidth + j] & 1;
            }
        }

        QRcode_free(qrCode);

        return code;
    }

    std::vector<bool> data()const
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
    std::vector<bool> qrData{};
};
