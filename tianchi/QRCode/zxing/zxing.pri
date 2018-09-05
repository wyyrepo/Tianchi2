isEmpty($$ZXING_DIR)
{
    $$ZXING_DIR = $$PWD
}

INCLUDEPATH += $$ZXING_DIR

HEADERS += \
    $$ZXING_DIR/CameraImageWrapper.h \
    $$ZXING_DIR/zxing/ResultPointCallback.h \
    $$ZXING_DIR/zxing/ResultPoint.h \
    $$ZXING_DIR/zxing/Result.h \
    $$ZXING_DIR/zxing/ReaderException.h \
    $$ZXING_DIR/zxing/Reader.h \
    $$ZXING_DIR/zxing/NotFoundException.h \
    $$ZXING_DIR/zxing/MultiFormatReader.h \
    $$ZXING_DIR/zxing/LuminanceSource.h \
    $$ZXING_DIR/zxing/FormatException.h \
    $$ZXING_DIR/zxing/Exception.h \
    $$ZXING_DIR/zxing/DecodeHints.h \
    $$ZXING_DIR/zxing/BinaryBitmap.h \
    $$ZXING_DIR/zxing/Binarizer.h \
    $$ZXING_DIR/zxing/BarcodeFormat.h \
    $$ZXING_DIR/zxing/aztec/AztecReader.h \
    $$ZXING_DIR/zxing/aztec/AztecDetectorResult.h \
    $$ZXING_DIR/zxing/aztec/decoder/Decoder.h \
    $$ZXING_DIR/zxing/aztec/detector/Detector.h \
    $$ZXING_DIR/zxing/common/StringUtils.h \
    $$ZXING_DIR/zxing/common/Str.h \
    $$ZXING_DIR/zxing/common/Point.h \
    $$ZXING_DIR/zxing/common/PerspectiveTransform.h \
    $$ZXING_DIR/zxing/common/IllegalArgumentException.h \
    $$ZXING_DIR/zxing/common/HybridBinarizer.h \
    $$ZXING_DIR/zxing/common/GridSampler.h \
    $$ZXING_DIR/zxing/common/GreyscaleRotatedLuminanceSource.h \
    $$ZXING_DIR/zxing/common/GreyscaleLuminanceSource.h \
    $$ZXING_DIR/zxing/common/GlobalHistogramBinarizer.h \
    $$ZXING_DIR/zxing/common/EdgeDetector.h \
    $$ZXING_DIR/zxing/common/DetectorResult.h \
    $$ZXING_DIR/zxing/common/DecoderResult.h \
    $$ZXING_DIR/zxing/common/Counted.h \
    $$ZXING_DIR/zxing/common/CharacterSetECI.h \
    $$ZXING_DIR/zxing/common/BitSource.h \
    $$ZXING_DIR/zxing/common/BitMatrix.h \
    $$ZXING_DIR/zxing/common/BitArray.h \
    $$ZXING_DIR/zxing/common/Array.h \
    $$ZXING_DIR/zxing/common/detector/WhiteRectangleDetector.h \
    $$ZXING_DIR/zxing/common/detector/MonochromeRectangleDetector.h \
    $$ZXING_DIR/zxing/common/reedsolomon/ReedSolomonException.h \
    $$ZXING_DIR/zxing/common/reedsolomon/ReedSolomonDecoder.h \
    $$ZXING_DIR/zxing/common/reedsolomon/GenericGFPoly.h \
    $$ZXING_DIR/zxing/common/reedsolomon/GenericGF.h \
    $$ZXING_DIR/zxing/datamatrix/Version.h \
    $$ZXING_DIR/zxing/datamatrix/DataMatrixReader.h \
    $$ZXING_DIR/zxing/datamatrix/decoder/Decoder.h \
    $$ZXING_DIR/zxing/datamatrix/decoder/DecodedBitStreamParser.h \
    $$ZXING_DIR/zxing/datamatrix/decoder/DataBlock.h \
    $$ZXING_DIR/zxing/datamatrix/decoder/BitMatrixParser.h \
    $$ZXING_DIR/zxing/datamatrix/detector/MonochromeRectangleDetector.h \
    $$ZXING_DIR/zxing/datamatrix/detector/DetectorException.h \
    $$ZXING_DIR/zxing/datamatrix/detector/Detector.h \
    $$ZXING_DIR/zxing/datamatrix/detector/CornerPoint.h \
    $$ZXING_DIR/zxing/oned/UPCEReader.h \
    $$ZXING_DIR/zxing/oned/UPCEANReader.h \
    $$ZXING_DIR/zxing/oned/UPCAReader.h \
    $$ZXING_DIR/zxing/oned/OneDResultPoint.h \
    $$ZXING_DIR/zxing/oned/OneDReader.h \
    $$ZXING_DIR/zxing/oned/MultiFormatUPCEANReader.h \
    $$ZXING_DIR/zxing/oned/MultiFormatOneDReader.h \
    $$ZXING_DIR/zxing/oned/ITFReader.h \
    $$ZXING_DIR/zxing/oned/EAN13Reader.h \
    $$ZXING_DIR/zxing/oned/EAN8Reader.h \
    $$ZXING_DIR/zxing/oned/Code128Reader.h \
    $$ZXING_DIR/zxing/oned/Code39Reader.h \
    $$ZXING_DIR/zxing/qrcode/Version.h \
    $$ZXING_DIR/zxing/qrcode/QRCodeReader.h \
    $$ZXING_DIR/zxing/qrcode/FormatInformation.h \
    $$ZXING_DIR/zxing/qrcode/ErrorCorrectionLevel.h \
    $$ZXING_DIR/zxing/qrcode/decoder/Mode.h \
    $$ZXING_DIR/zxing/qrcode/decoder/Decoder.h \
    $$ZXING_DIR/zxing/qrcode/decoder/DecodedBitStreamParser.h \
    $$ZXING_DIR/zxing/qrcode/decoder/DataMask.h \
    $$ZXING_DIR/zxing/qrcode/decoder/DataBlock.h \
    $$ZXING_DIR/zxing/qrcode/decoder/BitMatrixParser.h \
    $$ZXING_DIR/zxing/qrcode/detector/QREdgeDetector.h \
    $$ZXING_DIR/zxing/qrcode/detector/FinderPatternInfo.h \
    $$ZXING_DIR/zxing/qrcode/detector/FinderPatternFinder.h \
    $$ZXING_DIR/zxing/qrcode/detector/FinderPattern.h \
    $$ZXING_DIR/zxing/qrcode/detector/Detector.h \
    $$ZXING_DIR/zxing/qrcode/detector/AlignmentPatternFinder.h \
    $$ZXING_DIR/zxing/qrcode/detector/AlignmentPattern.h \
    $$ZXING_DIR/zxing/multi/MultipleBarcodeReader.h \
    $$ZXING_DIR/zxing/multi/GenericMultipleBarcodeReader.h \
    $$ZXING_DIR/zxing/multi/ByQuadrantReader.h \
    $$ZXING_DIR/zxing/multi/qrcode/QRCodeMultiReader.h \
    $$ZXING_DIR/zxing/multi/qrcode/detector/MultiFinderPatternFinder.h \
    $$ZXING_DIR/zxing/multi/qrcode/detector/MultiDetector.h

SOURCES += \
    $$ZXING_DIR/CameraImageWrapper.cpp \
    $$ZXING_DIR/zxing/ResultPointCallback.cpp \
    $$ZXING_DIR/zxing/ResultPoint.cpp \
    $$ZXING_DIR/zxing/Result.cpp \
    $$ZXING_DIR/zxing/ReaderException.cpp \
    $$ZXING_DIR/zxing/Reader.cpp \
    $$ZXING_DIR/zxing/NotFoundException.cpp \
    $$ZXING_DIR/zxing/MultiFormatReader.cpp \
    $$ZXING_DIR/zxing/LuminanceSource.cpp \
    $$ZXING_DIR/zxing/FormatException.cpp \
    $$ZXING_DIR/zxing/Exception.cpp \
    $$ZXING_DIR/zxing/DecodeHints.cpp \
    $$ZXING_DIR/zxing/BinaryBitmap.cpp \
    $$ZXING_DIR/zxing/Binarizer.cpp \
    $$ZXING_DIR/zxing/BarcodeFormat.cpp \
    $$ZXING_DIR/zxing/aztec/AztecReader.cpp \
    $$ZXING_DIR/zxing/aztec/AztecDetectorResult.cpp \
    $$ZXING_DIR/zxing/common/StringUtils.cpp \
    $$ZXING_DIR/zxing/common/Str.cpp \
    $$ZXING_DIR/zxing/common/PerspectiveTransform.cpp \
    $$ZXING_DIR/zxing/common/IllegalArgumentException.cpp \
    $$ZXING_DIR/zxing/common/HybridBinarizer.cpp \
    $$ZXING_DIR/zxing/common/GridSampler.cpp \
    $$ZXING_DIR/zxing/common/GreyscaleRotatedLuminanceSource.cpp \
    $$ZXING_DIR/zxing/common/GreyscaleLuminanceSource.cpp \
    $$ZXING_DIR/zxing/common/GlobalHistogramBinarizer.cpp \
    $$ZXING_DIR/zxing/common/EdgeDetector.cpp \
    $$ZXING_DIR/zxing/common/DetectorResult.cpp \
    $$ZXING_DIR/zxing/common/DecoderResult.cpp \
    $$ZXING_DIR/zxing/common/Counted.cpp \
    $$ZXING_DIR/zxing/common/CharacterSetECI.cpp \
    $$ZXING_DIR/zxing/common/BitSource.cpp \
    $$ZXING_DIR/zxing/common/BitMatrix.cpp \
    $$ZXING_DIR/zxing/common/BitArray.cpp \
    $$ZXING_DIR/zxing/common/Array.cpp \
    $$ZXING_DIR/zxing/common/detector/WhiteRectangleDetector.cpp \
    $$ZXING_DIR/zxing/common/detector/MonochromeRectangleDetector.cpp \
    $$ZXING_DIR/zxing/common/reedsolomon/ReedSolomonException.cpp \
    $$ZXING_DIR/zxing/common/reedsolomon/ReedSolomonDecoder.cpp \
    $$ZXING_DIR/zxing/common/reedsolomon/GenericGFPoly.cpp \
    $$ZXING_DIR/zxing/common/reedsolomon/GenericGF.cpp \
    $$ZXING_DIR/zxing/datamatrix/DataMatrixReader.cpp \
    $$ZXING_DIR/zxing/oned/UPCEReader.cpp \
    $$ZXING_DIR/zxing/oned/UPCEANReader.cpp \
    $$ZXING_DIR/zxing/oned/UPCAReader.cpp \
    $$ZXING_DIR/zxing/oned/OneDResultPoint.cpp \
    $$ZXING_DIR/zxing/oned/OneDReader.cpp \
    $$ZXING_DIR/zxing/oned/MultiFormatUPCEANReader.cpp \
    $$ZXING_DIR/zxing/oned/MultiFormatOneDReader.cpp \
    $$ZXING_DIR/zxing/oned/ITFReader.cpp \
    $$ZXING_DIR/zxing/oned/EAN13Reader.cpp \
    $$ZXING_DIR/zxing/oned/EAN8Reader.cpp \
    $$ZXING_DIR/zxing/oned/Code128Reader.cpp \
    $$ZXING_DIR/zxing/oned/Code39Reader.cpp \
    $$ZXING_DIR/zxing/qrcode/QRCodeReader.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QREdgeDetector.cpp \
    $$ZXING_DIR/zxing/multi/MultipleBarcodeReader.cpp \
    $$ZXING_DIR/zxing/multi/GenericMultipleBarcodeReader.cpp \
    $$ZXING_DIR/zxing/multi/ByQuadrantReader.cpp \
    $$ZXING_DIR/zxing/multi/qrcode/QRCodeMultiReader.cpp \
    $$ZXING_DIR/zxing/multi/qrcode/detector/MultiFinderPatternFinder.cpp \
    $$ZXING_DIR/zxing/multi/qrcode/detector/MultiDetector.cpp \
    $$ZXING_DIR/zxing/aztec/decoder/AztecDecoder.cpp \
    $$ZXING_DIR/zxing/aztec/detector/AztecDetector.cpp \
    $$ZXING_DIR/zxing/datamatrix/DataMatrixVersion.cpp \
    $$ZXING_DIR/zxing/datamatrix/decoder/DataMatrixDecoder.cpp \
    $$ZXING_DIR/zxing/datamatrix/decoder/DataMatrixBitMatrixParser.cpp \
    $$ZXING_DIR/zxing/datamatrix/decoder/DataMatrixDataBlock.cpp \
    $$ZXING_DIR/zxing/datamatrix/decoder/DataMatrixDecodedBitStreamParser.cpp \
    $$ZXING_DIR/zxing/datamatrix/detector/DataMatrixCornerPoint.cpp \
    $$ZXING_DIR/zxing/datamatrix/detector/DataMatrixDetector.cpp \
    $$ZXING_DIR/zxing/datamatrix/detector/DataMatrixDetectorException.cpp \
    $$ZXING_DIR/zxing/datamatrix/detector/DataMatrixMonochromeRectangleDetector.cpp \
    $$ZXING_DIR/zxing/qrcode/decoder/QRBitMatrixParser.cpp \
    $$ZXING_DIR/zxing/qrcode/decoder/QRDataBlock.cpp \
    $$ZXING_DIR/zxing/qrcode/decoder/QRDataMask.cpp \
    $$ZXING_DIR/zxing/qrcode/decoder/QRDecodedBitStreamParser.cpp \
    $$ZXING_DIR/zxing/qrcode/decoder/QRDecoder.cpp \
    $$ZXING_DIR/zxing/qrcode/decoder/QRMode.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QRAlignmentPattern.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QRAlignmentPatternFinder.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QRDetector.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QRFinderPattern.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QRFinderPatternFinder.cpp \
    $$ZXING_DIR/zxing/qrcode/detector/QRFinderPatternInfo.cpp \
    $$ZXING_DIR/zxing/qrcode/QRVersion.cpp \
    $$ZXING_DIR/zxing/qrcode/QRFormatInformation.cpp \
    $$ZXING_DIR/zxing/qrcode/QRErrorCorrectionLevel.cpp


win32:{

    LIBS += -liconv
}
unix:{
    macx:{

    }else{

    }
}
