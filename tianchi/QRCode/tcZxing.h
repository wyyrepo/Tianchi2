/// ********************************************************************************************************************
/// @copyright Tianchi C++ source library for Qt5 (天池共享源码库)\n
/// 天池共享源码库开发组(www.qtcn.org)\n
/// @license 授权协议：请阅读天池共享源码库附带的授权协议(LICENSE.LGPLv2.1)\n
/// ********************************************************************************************************************
/// @file tcZxing.h
/// @brief 解析二维码
/// @version 1.0
/// @date 2014.12.30
/// @author 圣域天子(Jonix@qtcn.org)
///
/// ====================================================================================================================

#pragma once
#ifndef TIANCHI_TCZXING_H
#define TIANCHI_TCZXING_H

#ifndef TIANCHI_API
    #define TIANCHI_API
#endif

#include <QObject>
#include <QImage>

class TIANCHI_API TcZXing : public QObject
{
    Q_OBJECT
    Q_ENUMS(DecoderFormat)
public:
    enum DecoderFormat {
                    DecoderFormat_None = 0,
                    DecoderFormat_QR_CODE = 1,
                    DecoderFormat_DATA_MATRIX = 2,
                    DecoderFormat_UPC_E = 4,
                    DecoderFormat_UPC_A = 8,
                    DecoderFormat_EAN_8 = 16,
                    DecoderFormat_EAN_13 = 32,
                    DecoderFormat_CODE_128 = 64,
                    DecoderFormat_CODE_39 = 128,
                    DecoderFormat_ITF = 256,
                    DecoderFormat_Aztec = 512
            } ;
    typedef unsigned int DecoderFormatType;

public:
    TcZXing(QObject *parent = NULL);
    void setDecoder(DecoderFormatType hint);

public slots:
    QString decodeImage(QImage image);
    QString decodeImageQML(const QUrl &imageUrl);
    QString decodeSubImageQML(const QUrl &imageUrl,
                              const double offsetX = 0 , const double offsetY = 0,
                              const double width = 0, const double height = 0);
signals:
    void decodingStarted();
    void decodingFinished(bool succeeded);
    void tagFound(QString tag);

private:
    void* decoder;
    DecoderFormatType supportedFormats;
};

#endif // TIANCHI_TCZXING_H

