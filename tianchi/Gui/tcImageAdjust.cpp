#include "tcImageAdjust.h"
#include <QtGlobal>

bool TcImageAdjust::soften(QImage& image) // 柔化
{
    bool ret = false;
    if ( ! image.isNull() )
    {
        for( int i = 1; i < image.width() -1; i++ )
        {
            for( int j = 1; j < image.height() -1; j++ )
            {
                int r=0, g=0, b=0;
                for( int m = 0; m < 9; m++ )
                {
                    int s = 0;
                    int p = 0;
                    switch(m)
                    {
                    case 0: s = i -1; p = j -1; break;
                    case 1: s = i   ; p = j -1; break;
                    case 2: s = i +1; p = j -1; break;
                    case 3: s = i +1; p = j   ; break;
                    case 4: s = i +1; p = j +1; break;
                    case 5: s = i   ; p = j +1; break;
                    case 6: s = i -1; p = j +1; break;
                    case 7: s = i -1; p = j   ; break;
                    case 8: s = i   ; p = j   ; break;
                    }
                    QRgb color = image.pixel(s, p);
                    r += qRed(color);
                    g += qGreen(color);
                    b += qBlue(color);
                }
                r = qMin(255.0, qMax(0.0, r / 9.0));
                g = qMin(255.0, qMax(0.0, g / 9.0));
                b = qMin(255.0, qMax(0.0, b / 9.0));

                image.setPixel(i, j, qRgb(r, g, b));
            }
        }
        ret = true;
    }
    return ret;
}

bool TcImageAdjust::sharpen(QImage& image) // 锐化
{
    bool ret = false;
    if ( ! image.isNull() )
    {
        int width = image.width();
        int height = image.height();
        int threshold = 80;
        QImage sharpen(width, height, QImage::Format_ARGB32);
        for(int i = 0; i < width; i++)
        {
            for(int j= 0; j < height; j++)
            {
                if ( image.valid(i, j) && image.valid(i+1, j) && image.valid(i, j+1))
                {
                    QRgb rgb00 = image.pixel(i, j);
                    QRgb rgb01 = image.pixel(i, j+1);
                    QRgb rgb10 = image.pixel(i+1, j);
                    int r = qRed(rgb00);
                    int g = qGreen(rgb00);
                    int b = qBlue(rgb00);
                    int gradientR = abs(r - qRed(rgb01)) + abs(r - qRed(rgb10));
                    int gradientG = abs(g - qGreen(rgb01)) + abs(g - qGreen(rgb10));
                    int gradientB = abs(b - qBlue(rgb01)) + abs(b - qBlue(rgb10));

                    if ( gradientR > threshold )
                    {
                        r = qMin(gradientR + 100, 255);
                    }
                    if ( gradientG > threshold )
                    {
                        g = qMin( gradientG + 100, 255);
                    }
                    if ( gradientB > threshold )
                    {
                        b = qMin( gradientB + 100, 255);
                    }
                    sharpen.setPixel(i, j, qRgb(r, g, b));
                }
            }
        }
        image = sharpen;
        ret = true;
    }
    return ret;
}

bool TcImageAdjust::grayscale(QImage& image) // 灰度
{
    bool ret = false;
    if ( ! image.isNull() )
    {
        for(int i = 0; i < image.width(); i++)
        {
            for(int j= 0; j < image.height(); j++)
            {
                QRgb color = image.pixel(i, j);
                int  gray  = qGray(color);
                image.setPixel(i, j, qRgba(gray, gray, gray, qAlpha(color)));
            }
        }
        ret = true;
    }
    return ret;
}

bool TcImageAdjust::blackwhite(QImage& image) //黑白
{
    bool ret = false;
    if ( ! image.isNull() )
    {
        for( int i=0; i<image.width(); i++ )
        {
            for( int j=0; j<image.height(); j++ )
            {
                QRgb color = image.pixel(i, j);
                QRgb avg = (qRed(color) + qGreen(color) + qBlue(color))/3;
                image.setPixel(i, j, avg >= 128 ? Qt::white : Qt::black);
            }
        }
        ret = true;
    }
    return ret;
}

bool TcImageAdjust::negative(QImage& image) // 底片
{
    bool ret = false;
    if ( ! image.isNull() )
    {
        for( int i=0; i<image.width(); i++ )
        {
            for(int j=0; j<image.height(); j++)
            {
                QRgb color = image.pixel(i, j);
                QRgb negative = qRgba(255 - qRed(color), 255 - qGreen(color), 255 - qBlue(color), qAlpha(color));
                image.setPixel(i, j, negative);
            }
        }
        ret = true;
    }
    return ret;
}

bool TcImageAdjust::relief(QImage& image) //浮雕
{
    bool ret = false;
    if ( ! image.isNull() )
    {
        QRgb preColor = 0;
        for( int i=0; i<image.width(); i++ )
        {
            for( int j=0; j<image.height(); j++ )
            {
                QRgb color = image.pixel(i, j);
                int r = qRed(color)   - qRed(preColor)   + 128;
                int g = qGreen(color) - qGreen(preColor) + 128;
                int b = qBlue(color)  - qBlue(preColor)  + 128;
                int a = qAlpha(color);
                int gray = qGray(r, g, b);
                QRgb newColor = qRgba(gray, gray, gray, a);
                image.setPixel(i, j, newColor);
                preColor = newColor;
            }
        }
        ret = true;
    }
    return ret;
}
