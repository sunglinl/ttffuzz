//
//  jpg.cpp
//  AFL
//
//  Created by System Administrator on 2021/5/12.
//
/*
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "file_accessor.h"
typedef unsigned int DC_UINT32;
typedef int DC_SINT32;
typedef float DC_FLOAT32;

enum tagID : WORD {
    M_SOF0 = (WORD) 0xFFC0,
    M_SOF1,
    M_SOF2,
    M_SOF3,
    M_DHT,
    M_SOF5,
    M_SOF6,
    M_SOF7,
    M_JPG,
    M_SOF9,
    M_SOF10,
    M_SOF11,
    M_DAC = (WORD) 0xffcc,
    M_SOF13,
    M_SOF14,
    M_SOF15,
    M_RST0 = (WORD) 0xffd0,
    M_RST1,
    M_RST2,
    M_RST3,
    M_RST4,
    M_RST5,
    M_RST6,
    M_RST7,
    M_SOI = (WORD) 0xFFD8,
    M_EOI,
    M_SOS,
    M_DQT,
    M_DNL,
    M_DRI,
    M_DHP,
    M_EXP,
    M_APP0 = (WORD) 0xFFE0,
    M_APP1,
    M_APP2,
    M_APP3,
    M_APP4,
    M_APP5,
    M_APP6,
    M_APP7,
    M_APP8,
    M_APP9,
    M_APP10,
    M_APP11,
    M_APP12,
    M_APP13,
    M_APP14,
    M_APP15,
    M_JPG0 = (WORD) 0xfff0,
    M_JPG1,
    M_JPG2,
    M_JPG3,
    M_JPG4,
    M_JPG5,
    M_JPG6,
    M_JPGLS,
    M_JPG8,
    M_JPG9,
    M_JPG10,
    M_JPG11,
    M_JPG12,
    M_JPG13,
    M_JPG14,
    M_JPG15,
    M_COMM = (WORD) 0xFFFE,
};
std::vector<WORD> tagID_values = { M_SOF0, M_SOF1, M_SOF2, M_SOF3, M_DHT, M_SOF5, M_SOF6, M_SOF7, M_JPG, M_SOF9, M_SOF10, M_SOF11, M_DAC, M_SOF13, M_SOF14, M_SOF15, M_RST0, M_RST1, M_RST2, M_RST3, M_RST4, M_RST5, M_RST6, M_RST7, M_SOI, M_EOI, M_SOS, M_DQT, M_DNL, M_DRI, M_DHP, M_EXP, M_APP0, M_APP1, M_APP2, M_APP3, M_APP4, M_APP5, M_APP6, M_APP7, M_APP8, M_APP9, M_APP10, M_APP11, M_APP12, M_APP13, M_APP14, M_APP15, M_JPG0, M_JPG1, M_JPG2, M_JPG3, M_JPG4, M_JPG5, M_JPG6, M_JPGLS, M_JPG8, M_JPG9, M_JPG10, M_JPG11, M_JPG12, M_JPG13, M_JPG14, M_JPG15, M_COMM };

typedef enum tagID M_ID;
std::vector<WORD> M_ID_values = { M_SOF0, M_SOF1, M_SOF2, M_SOF3, M_DHT, M_SOF5, M_SOF6, M_SOF7, M_JPG, M_SOF9, M_SOF10, M_SOF11, M_DAC, M_SOF13, M_SOF14, M_SOF15, M_RST0, M_RST1, M_RST2, M_RST3, M_RST4, M_RST5, M_RST6, M_RST7, M_SOI, M_EOI, M_SOS, M_DQT, M_DNL, M_DRI, M_DHP, M_EXP, M_APP0, M_APP1, M_APP2, M_APP3, M_APP4, M_APP5, M_APP6, M_APP7, M_APP8, M_APP9, M_APP10, M_APP11, M_APP12, M_APP13, M_APP14, M_APP15, M_JPG0, M_JPG1, M_JPG2, M_JPG3, M_JPG4, M_JPG5, M_JPG6, M_JPGLS, M_JPG8, M_JPG9, M_JPG10, M_JPG11, M_JPG12, M_JPG13, M_JPG14, M_JPG15, M_COMM };

enum tagExifTag : WORD {
    InteropIndex = (WORD) 0x0001,
    InteropVersion = (WORD) 0x0002,
    SubfileType = (WORD) 0x00fe,
    OldSubfileType = (WORD) 0x00ff,
    ImageWidth = (WORD) 0x0100,
    ImageHeight = (WORD) 0x0101,
    BitsPerSample = (WORD) 0x0102,
    Compression = (WORD) 0x0103,
    PhotometricInterpretation = (WORD) 0x0106,
    Thresholding = (WORD) 0x0107,
    CellWidth = (WORD) 0x0108,
    CellLength = (WORD) 0x0109,
    FillOrder = (WORD) 0x010a,
    DocumentName = (WORD) 0x010d,
    ImageDescription = (WORD) 0x010e,
    Make = (WORD) 0x010f,
    Model = (WORD) 0x0110,
    StripOffsets = (WORD) 0x0111,
    Orientation = (WORD) 0x0112,
    SamplesPerPixel = (WORD) 0x0115,
    RowsPerStrip = (WORD) 0x0116,
    StripByteCounts = (WORD) 0x0117,
    MinSampleValue = (WORD) 0x0118,
    MaxSampleValue = (WORD) 0x0119,
    XResolution = (WORD) 0x011a,
    YResolution = (WORD) 0x011b,
    PlanarConfiguration = (WORD) 0x011c,
    PageName = (WORD) 0x011d,
    XPosition = (WORD) 0x011e,
    YPosition = (WORD) 0x011f,
    FreeOffsets = (WORD) 0x0120,
    FreeByteCounts = (WORD) 0x0121,
    GrayResponseUnit = (WORD) 0x0122,
    GrayResponseCurve = (WORD) 0x0123,
    T4Options = (WORD) 0x0124,
    T6Options = (WORD) 0x0125,
    ResolutionUnit = (WORD) 0x0128,
    PageNumber = (WORD) 0x0129,
    ColorResponseUnit = (WORD) 0x012c,
    TransferFunction = (WORD) 0x012d,
    Software = (WORD) 0x0131,
    ModifyDate = (WORD) 0x0132,
    Artist = (WORD) 0x013b,
    HostComputer = (WORD) 0x013c,
    Predictor = (WORD) 0x013d,
    WhitePoint = (WORD) 0x013e,
    PrimaryChromaticities = (WORD) 0x013f,
    ColorMap = (WORD) 0x0140,
    HalftoneHints = (WORD) 0x0141,
    TileWidth = (WORD) 0x0142,
    TileLength = (WORD) 0x0143,
    TileOffsets = (WORD) 0x0144,
    TileByteCounts = (WORD) 0x0145,
    BadFaxLines = (WORD) 0x0146,
    CleanFaxData = (WORD) 0x0147,
    ConsecutiveBadFaxLines = (WORD) 0x0148,
    SubIFD = (WORD) 0x014a,
    InkSet = (WORD) 0x014c,
    InkNames = (WORD) 0x014d,
    NumberofInks = (WORD) 0x014e,
    DotRange = (WORD) 0x0150,
    TargetPrinter = (WORD) 0x0151,
    ExtraSamples = (WORD) 0x0152,
    SampleFormat = (WORD) 0x0153,
    SMinSampleValue = (WORD) 0x0154,
    SMaxSampleValue = (WORD) 0x0155,
    TransferRange = (WORD) 0x0156,
    ClipPath = (WORD) 0x0157,
    XClipPathUnits = (WORD) 0x0158,
    YClipPathUnits = (WORD) 0x0159,
    Indexed = (WORD) 0x015a,
    JPEGTables = (WORD) 0x015b,
    OPIProxy = (WORD) 0x015f,
    GlobalParametersIFD = (WORD) 0x0190,
    ProfileType = (WORD) 0x0191,
    FaxProfile = (WORD) 0x0192,
    CodingMethods = (WORD) 0x0193,
    VersionYear = (WORD) 0x0194,
    ModeNumber = (WORD) 0x0195,
    Decode = (WORD) 0x01b1,
    DefaultImageColor = (WORD) 0x01b2,
    JPEGProc = (WORD) 0x0200,
    ThumbnailOffset = (WORD) 0x0201,
    ThumbnailLength = (WORD) 0x0202,
    JPEGRestartInterval = (WORD) 0x0203,
    JPEGLosslessPredictors = (WORD) 0x0205,
    JPEGPointTransforms = (WORD) 0x0206,
    JPEGQTables = (WORD) 0x0207,
    JPEGDCTables = (WORD) 0x0208,
    JPEGACTables = (WORD) 0x0209,
    YCbCrCoefficients = (WORD) 0x0211,
    YCbCrSubSampling = (WORD) 0x0212,
    YCbCrPositioning = (WORD) 0x0213,
    ReferenceBlackWhite = (WORD) 0x0214,
    StripRowCounts = (WORD) 0x022f,
    ApplicationNotes = (WORD) 0x02bc,
    RelatedImageFileFormat = (WORD) 0x1000,
    RelatedImageWidth = (WORD) 0x1001,
    RelatedImageLength = (WORD) 0x1002,
    ImageID = (WORD) 0x800d,
    WangAnnotation = (WORD) 0x80a4,
    Matteing = (WORD) 0x80e3,
    DataType = (WORD) 0x80e4,
    ImageDepth = (WORD) 0x80e5,
    TileDepth = (WORD) 0x80e6,
    Model2 = (WORD) 0x827d,
    CFARepeatPatternDim = (WORD) 0x828d,
    CFAPattern2 = (WORD) 0x828e,
    BatteryLevel = (WORD) 0x828f,
    Copyright = (WORD) 0x8298,
    ExposureTime = (WORD) 0x829a,
    FNumber = (WORD) 0x829d,
    PixelScale = (WORD) 0x830e,
    IPTC_NAA = (WORD) 0x83bb,
    IntergraphPacketData = (WORD) 0x8474,
    IntergraphFlagRegisters = (WORD) 0x847f,
    IntergraphMatrix = (WORD) 0x8480,
    ModelTiePoint = (WORD) 0x8482,
    Site = (WORD) 0x84e0,
    ColorSequence = (WORD) 0x84e1,
    IT8Header = (WORD) 0x84e2,
    RasterPadding = (WORD) 0x84e3,
    BitsPerRunLength = (WORD) 0x84e4,
    BitsPerExtendedRunLength = (WORD) 0x84e5,
    ColorTable = (WORD) 0x84e6,
    ImageColorIndicator = (WORD) 0x84e7,
    BackgroundColorIndicator = (WORD) 0x84e8,
    ImageColorValue = (WORD) 0x84e9,
    BackgroundColorValue = (WORD) 0x84ea,
    PixelIntensityRange = (WORD) 0x84eb,
    TransparencyIndicator = (WORD) 0x84ec,
    ColorCharacterization = (WORD) 0x84ed,
    HCUsage = (WORD) 0x84ee,
    IPTC_NAA2 = (WORD) 0x8568,
    ModelTransform = (WORD) 0x85d8,
    PhotoshopSettings = (WORD) 0x8649,
    ExifOffset = (WORD) 0x8769,
    ICC_Profile = (WORD) 0x8773,
    ImageLayer = (WORD) 0x87ac,
    GeoTiffDirectory = (WORD) 0x87af,
    GeoTiffDoubleParams = (WORD) 0x87b0,
    GeoTiffAsciiParams = (WORD) 0x87b1,
    ExposureProgram = (WORD) 0x8822,
    SpectralSensitivity = (WORD) 0x8824,
    GPSInfo = (WORD) 0x8825,
    ISO = (WORD) 0x8827,
    OptoElectricConvFactor = (WORD) 0x8828,
    Interlace = (WORD) 0x8829,
    TimeZoneOffset = (WORD) 0x882a,
    SelfTimerMode = (WORD) 0x882b,
    FaxRecvParams = (WORD) 0x885c,
    FaxSubAddress = (WORD) 0x885d,
    FaxRecvTime = (WORD) 0x885e,
    ExifVersion = (WORD) 0x9000,
    DateTimeOriginal = (WORD) 0x9003,
    CreateDate = (WORD) 0x9004,
    ComponentsConfiguration = (WORD) 0x9101,
    CompressedBitsPerPixel = (WORD) 0x9102,
    ShutterSpeedValue = (WORD) 0x9201,
    ApertureValue = (WORD) 0x9202,
    BrightnessValue = (WORD) 0x9203,
    ExposureCompensation = (WORD) 0x9204,
    MaxApertureValue = (WORD) 0x9205,
    SubjectDistance = (WORD) 0x9206,
    MeteringMode = (WORD) 0x9207,
    LightSource = (WORD) 0x9208,
    Flash = (WORD) 0x9209,
    FocalLength = (WORD) 0x920a,
    FlashEnergy = (WORD) 0x920b,
    SpatialFrequencyResponse = (WORD) 0x920c,
    Noise = (WORD) 0x920d,
    FocalPlaneXResolution = (WORD) 0x920e,
    FocalPlaneYResolution = (WORD) 0x920f,
    FocalPlaneResolutionUnit = (WORD) 0x9210,
    ImageNumber = (WORD) 0x9211,
    SecurityClassification = (WORD) 0x9212,
    ImageHistory = (WORD) 0x9213,
    SubjectLocation = (WORD) 0x9214,
    ExposureIndex = (WORD) 0x9215,
    TIFF_EPStandardID = (WORD) 0x9216,
    SensingMethod = (WORD) 0x9217,
    StoNits = (WORD) 0x923f,
    MakerNote = (WORD) 0x927c,
    UserComment = (WORD) 0x9286,
    SubSecTime = (WORD) 0x9290,
    SubSecTimeOriginal = (WORD) 0x9291,
    SubSecTimeDigitized = (WORD) 0x9292,
    ImageSourceData = (WORD) 0x935c,
    XPTitle = (WORD) 0x9c9b,
    XPComment = (WORD) 0x9c9c,
    XPAuthor = (WORD) 0x9c9d,
    XPKeywords = (WORD) 0x9c9e,
    XPSubject = (WORD) 0x9c9f,
    FlashpixVersion = (WORD) 0xa000,
    ColorSpace = (WORD) 0xa001,
    ExifImageWidth = (WORD) 0xa002,
    ExifImageLength = (WORD) 0xa003,
    RelatedSoundFile = (WORD) 0xa004,
    InteropOffset = (WORD) 0xa005,
    FlashEnergy2 = (WORD) 0xa20b,
    SpatialFrequencyResponse2 = (WORD) 0xa20c,
    Noise2 = (WORD) 0xa20d,
    FocalPlaneXResolution2 = (WORD) 0xa20e,
    FocalPlaneYResolution2 = (WORD) 0xa20f,
    FocalPlaneResolutionUnit2 = (WORD) 0xa210,
    ImageNumber2 = (WORD) 0xa211,
    SecurityClassification2 = (WORD) 0xa212,
    ImageHistory2 = (WORD) 0xa213,
    SubjectLocation2 = (WORD) 0xa214,
    ExposureIndex2 = (WORD) 0xa215,
    TIFF_EPStandardID2 = (WORD) 0xa216,
    SensingMethod2 = (WORD) 0xa217,
    FileSource = (WORD) 0xa300,
    SceneType = (WORD) 0xa301,
    CFAPattern = (WORD) 0xa302,
    CustomRendered = (WORD) 0xa401,
    ExposureMode = (WORD) 0xa402,
    WhiteBalance = (WORD) 0xa403,
    DigitalZoomRatio = (WORD) 0xa404,
    FocalLengthIn35mmFormat = (WORD) 0xa405,
    SceneCaptureType = (WORD) 0xa406,
    GainControl = (WORD) 0xa407,
    Contrast = (WORD) 0xa408,
    Saturation = (WORD) 0xa409,
    Sharpness = (WORD) 0xa40a,
    DeviceSettingDescription = (WORD) 0xa40b,
    SubjectDistanceRange = (WORD) 0xa40c,
    ImageUniqueID = (WORD) 0xa420,
    GDALMetadata = (WORD) 0xa480,
    GDALNoData = (WORD) 0xa481,
    Gamma = (WORD) 0xa500,
    FilmProductCode = (WORD) 0xc350,
    ImageSourceEK = (WORD) 0xc351,
    CaptureConditionsPAR = (WORD) 0xc352,
    CameraOwner = (WORD) 0xc353,
    SerialNumber = (WORD) 0xc354,
    UserSelectGroupTitle = (WORD) 0xc355,
    DealerIDNumber = (WORD) 0xc356,
    CaptureDeviceFID = (WORD) 0xc357,
    EnvelopeNumber = (WORD) 0xc358,
    FrameNumber = (WORD) 0xc359,
    FilmCategory = (WORD) 0xc35a,
    FilmGencode = (WORD) 0xc35b,
    ModelAndVersion = (WORD) 0xc35c,
    FilmSize = (WORD) 0xc35d,
    SBA_RGBShifts = (WORD) 0xc35e,
    SBAInputImageColorspace = (WORD) 0xc35f,
    SBAInputImageBitDepth = (WORD) 0xc360,
    SBAExposureRecord = (WORD) 0xc361,
    UserAdjSBA_RGBShifts = (WORD) 0xc362,
    ImageRotationStatus = (WORD) 0xc363,
    RollGuidElements = (WORD) 0xc364,
    MetadataNumber = (WORD) 0xc365,
    EditTagArray = (WORD) 0xc366,
    Magnification = (WORD) 0xc367,
    NativeXResolution = (WORD) 0xc36c,
    NativeYResolution = (WORD) 0xc36d,
    KodakEffectsIFD = (WORD) 0xc36e,
    KodakBordersIFD = (WORD) 0xc36f,
    NativeResolutionUnit = (WORD) 0xc37a,
    SourceImageDirectory = (WORD) 0xc418,
    SourceImageFileName = (WORD) 0xc419,
    SourceImageVolumeName = (WORD) 0xc41a,
    OceScanjobDesc = (WORD) 0xc427,
    OceApplicationSelector = (WORD) 0xc428,
    OceIDNumber = (WORD) 0xc429,
    OceImageLogic = (WORD) 0xc42a,
    Annotations = (WORD) 0xc44f,
    PrintQuality = (WORD) 0xc46c,
    ImagePrintStatus = (WORD) 0xc46e,
    PrintIM = (WORD) 0xc4a5,
    DNGVersion = (WORD) 0xc612,
    DNGBackwardVersion = (WORD) 0xc613,
    UniqueCameraModel = (WORD) 0xc614,
    LocalizedCameraModel = (WORD) 0xc615,
    CFAPlaneColor = (WORD) 0xc616,
    CFALayout = (WORD) 0xc617,
    LinearizationTable = (WORD) 0xc618,
    BlackLevelRepeatDim = (WORD) 0xc619,
    BlackLevel = (WORD) 0xc61a,
    BlackLevelDeltaH = (WORD) 0xc61b,
    BlackLevelDeltaV = (WORD) 0xc61c,
    WhiteLevel = (WORD) 0xc61d,
    DefaultScale = (WORD) 0xc61e,
    DefaultCropOrigin = (WORD) 0xc61f,
    DefaultCropSize = (WORD) 0xc620,
    ColorMatrix1 = (WORD) 0xc621,
    ColorMatrix2 = (WORD) 0xc622,
    CameraCalibration1 = (WORD) 0xc623,
    CameraCalibration2 = (WORD) 0xc624,
    ReductionMatrix1 = (WORD) 0xc625,
    ReductionMatrix2 = (WORD) 0xc626,
    AnalogBalance = (WORD) 0xc627,
    AsShotNeutral = (WORD) 0xc628,
    AsShotWhiteXY = (WORD) 0xc629,
    BaselineExposure = (WORD) 0xc62a,
    BaselineNoise = (WORD) 0xc62b,
    BaselineSharpness = (WORD) 0xc62c,
    BayerGreenSplit = (WORD) 0xc62d,
    LinearResponseLimit = (WORD) 0xc62e,
    DNGCameraSerialNumber = (WORD) 0xc62f,
    DNGLensInfo = (WORD) 0xc630,
    ChromaBlurRadius = (WORD) 0xc631,
    AntiAliasStrength = (WORD) 0xc632,
    ShadowScale = (WORD) 0xc633,
    DNGPrivateData = (WORD) 0xc634,
    MakerNoteSafety = (WORD) 0xc635,
    CalibrationIlluminant1 = (WORD) 0xc65a,
    CalibrationIlluminant2 = (WORD) 0xc65b,
    BestQualityScale = (WORD) 0xc65c,
    AliasLayerMetadata = (WORD) 0xc660,
    OwnerName = (WORD) 0xfde8,
    SerialNumber2 = (WORD) 0xfde9,
    Lens = (WORD) 0xfdea,
    RawFile = (WORD) 0xfe4c,
    Converter = (WORD) 0xfe4d,
    WhiteBalance2 = (WORD) 0xfe4e,
    Exposure = (WORD) 0xfe51,
    Shadows = (WORD) 0xfe52,
    Brightness = (WORD) 0xfe53,
    Contrast2 = (WORD) 0xfe54,
    Saturation2 = (WORD) 0xfe55,
    Sharpness2 = (WORD) 0xfe56,
    Smoothness = (WORD) 0xfe57,
    MoireFilter = (WORD) 0xfe58,
};
std::vector<WORD> tagExifTag_values = { InteropIndex, InteropVersion, SubfileType, OldSubfileType, ImageWidth, ImageHeight, BitsPerSample, Compression, PhotometricInterpretation, Thresholding, CellWidth, CellLength, FillOrder, DocumentName, ImageDescription, Make, Model, StripOffsets, Orientation, SamplesPerPixel, RowsPerStrip, StripByteCounts, MinSampleValue, MaxSampleValue, XResolution, YResolution, PlanarConfiguration, PageName, XPosition, YPosition, FreeOffsets, FreeByteCounts, GrayResponseUnit, GrayResponseCurve, T4Options, T6Options, ResolutionUnit, PageNumber, ColorResponseUnit, TransferFunction, Software, ModifyDate, Artist, HostComputer, Predictor, WhitePoint, PrimaryChromaticities, ColorMap, HalftoneHints, TileWidth, TileLength, TileOffsets, TileByteCounts, BadFaxLines, CleanFaxData, ConsecutiveBadFaxLines, SubIFD, InkSet, InkNames, NumberofInks, DotRange, TargetPrinter, ExtraSamples, SampleFormat, SMinSampleValue, SMaxSampleValue, TransferRange, ClipPath, XClipPathUnits, YClipPathUnits, Indexed, JPEGTables, OPIProxy, GlobalParametersIFD, ProfileType, FaxProfile, CodingMethods, VersionYear, ModeNumber, Decode, DefaultImageColor, JPEGProc, ThumbnailOffset, ThumbnailLength, JPEGRestartInterval, JPEGLosslessPredictors, JPEGPointTransforms, JPEGQTables, JPEGDCTables, JPEGACTables, YCbCrCoefficients, YCbCrSubSampling, YCbCrPositioning, ReferenceBlackWhite, StripRowCounts, ApplicationNotes, RelatedImageFileFormat, RelatedImageWidth, RelatedImageLength, ImageID, WangAnnotation, Matteing, DataType, ImageDepth, TileDepth, Model2, CFARepeatPatternDim, CFAPattern2, BatteryLevel, Copyright, ExposureTime, FNumber, PixelScale, IPTC_NAA, IntergraphPacketData, IntergraphFlagRegisters, IntergraphMatrix, ModelTiePoint, Site, ColorSequence, IT8Header, RasterPadding, BitsPerRunLength, BitsPerExtendedRunLength, ColorTable, ImageColorIndicator, BackgroundColorIndicator, ImageColorValue, BackgroundColorValue, PixelIntensityRange, TransparencyIndicator, ColorCharacterization, HCUsage, IPTC_NAA2, ModelTransform, PhotoshopSettings, ExifOffset, ICC_Profile, ImageLayer, GeoTiffDirectory, GeoTiffDoubleParams, GeoTiffAsciiParams, ExposureProgram, SpectralSensitivity, GPSInfo, ISO, OptoElectricConvFactor, Interlace, TimeZoneOffset, SelfTimerMode, FaxRecvParams, FaxSubAddress, FaxRecvTime, ExifVersion, DateTimeOriginal, CreateDate, ComponentsConfiguration, CompressedBitsPerPixel, ShutterSpeedValue, ApertureValue, BrightnessValue, ExposureCompensation, MaxApertureValue, SubjectDistance, MeteringMode, LightSource, Flash, FocalLength, FlashEnergy, SpatialFrequencyResponse, Noise, FocalPlaneXResolution, FocalPlaneYResolution, FocalPlaneResolutionUnit, ImageNumber, SecurityClassification, ImageHistory, SubjectLocation, ExposureIndex, TIFF_EPStandardID, SensingMethod, StoNits, MakerNote, UserComment, SubSecTime, SubSecTimeOriginal, SubSecTimeDigitized, ImageSourceData, XPTitle, XPComment, XPAuthor, XPKeywords, XPSubject, FlashpixVersion, ColorSpace, ExifImageWidth, ExifImageLength, RelatedSoundFile, InteropOffset, FlashEnergy2, SpatialFrequencyResponse2, Noise2, FocalPlaneXResolution2, FocalPlaneYResolution2, FocalPlaneResolutionUnit2, ImageNumber2, SecurityClassification2, ImageHistory2, SubjectLocation2, ExposureIndex2, TIFF_EPStandardID2, SensingMethod2, FileSource, SceneType, CFAPattern, CustomRendered, ExposureMode, WhiteBalance, DigitalZoomRatio, FocalLengthIn35mmFormat, SceneCaptureType, GainControl, Contrast, Saturation, Sharpness, DeviceSettingDescription, SubjectDistanceRange, ImageUniqueID, GDALMetadata, GDALNoData, Gamma, FilmProductCode, ImageSourceEK, CaptureConditionsPAR, CameraOwner, SerialNumber, UserSelectGroupTitle, DealerIDNumber, CaptureDeviceFID, EnvelopeNumber, FrameNumber, FilmCategory, FilmGencode, ModelAndVersion, FilmSize, SBA_RGBShifts, SBAInputImageColorspace, SBAInputImageBitDepth, SBAExposureRecord, UserAdjSBA_RGBShifts, ImageRotationStatus, RollGuidElements, MetadataNumber, EditTagArray, Magnification, NativeXResolution, NativeYResolution, KodakEffectsIFD, KodakBordersIFD, NativeResolutionUnit, SourceImageDirectory, SourceImageFileName, SourceImageVolumeName, OceScanjobDesc, OceApplicationSelector, OceIDNumber, OceImageLogic, Annotations, PrintQuality, ImagePrintStatus, PrintIM, DNGVersion, DNGBackwardVersion, UniqueCameraModel, LocalizedCameraModel, CFAPlaneColor, CFALayout, LinearizationTable, BlackLevelRepeatDim, BlackLevel, BlackLevelDeltaH, BlackLevelDeltaV, WhiteLevel, DefaultScale, DefaultCropOrigin, DefaultCropSize, ColorMatrix1, ColorMatrix2, CameraCalibration1, CameraCalibration2, ReductionMatrix1, ReductionMatrix2, AnalogBalance, AsShotNeutral, AsShotWhiteXY, BaselineExposure, BaselineNoise, BaselineSharpness, BayerGreenSplit, LinearResponseLimit, DNGCameraSerialNumber, DNGLensInfo, ChromaBlurRadius, AntiAliasStrength, ShadowScale, DNGPrivateData, MakerNoteSafety, CalibrationIlluminant1, CalibrationIlluminant2, BestQualityScale, AliasLayerMetadata, OwnerName, SerialNumber2, Lens, RawFile, Converter, WhiteBalance2, Exposure, Shadows, Brightness, Contrast2, Saturation2, Sharpness2, Smoothness, MoireFilter };

typedef enum tagExifTag ExifTag;
std::vector<WORD> ExifTag_values = { InteropIndex, InteropVersion, SubfileType, OldSubfileType, ImageWidth, ImageHeight, BitsPerSample, Compression, PhotometricInterpretation, Thresholding, CellWidth, CellLength, FillOrder, DocumentName, ImageDescription, Make, Model, StripOffsets, Orientation, SamplesPerPixel, RowsPerStrip, StripByteCounts, MinSampleValue, MaxSampleValue, XResolution, YResolution, PlanarConfiguration, PageName, XPosition, YPosition, FreeOffsets, FreeByteCounts, GrayResponseUnit, GrayResponseCurve, T4Options, T6Options, ResolutionUnit, PageNumber, ColorResponseUnit, TransferFunction, Software, ModifyDate, Artist, HostComputer, Predictor, WhitePoint, PrimaryChromaticities, ColorMap, HalftoneHints, TileWidth, TileLength, TileOffsets, TileByteCounts, BadFaxLines, CleanFaxData, ConsecutiveBadFaxLines, SubIFD, InkSet, InkNames, NumberofInks, DotRange, TargetPrinter, ExtraSamples, SampleFormat, SMinSampleValue, SMaxSampleValue, TransferRange, ClipPath, XClipPathUnits, YClipPathUnits, Indexed, JPEGTables, OPIProxy, GlobalParametersIFD, ProfileType, FaxProfile, CodingMethods, VersionYear, ModeNumber, Decode, DefaultImageColor, JPEGProc, ThumbnailOffset, ThumbnailLength, JPEGRestartInterval, JPEGLosslessPredictors, JPEGPointTransforms, JPEGQTables, JPEGDCTables, JPEGACTables, YCbCrCoefficients, YCbCrSubSampling, YCbCrPositioning, ReferenceBlackWhite, StripRowCounts, ApplicationNotes, RelatedImageFileFormat, RelatedImageWidth, RelatedImageLength, ImageID, WangAnnotation, Matteing, DataType, ImageDepth, TileDepth, Model2, CFARepeatPatternDim, CFAPattern2, BatteryLevel, Copyright, ExposureTime, FNumber, PixelScale, IPTC_NAA, IntergraphPacketData, IntergraphFlagRegisters, IntergraphMatrix, ModelTiePoint, Site, ColorSequence, IT8Header, RasterPadding, BitsPerRunLength, BitsPerExtendedRunLength, ColorTable, ImageColorIndicator, BackgroundColorIndicator, ImageColorValue, BackgroundColorValue, PixelIntensityRange, TransparencyIndicator, ColorCharacterization, HCUsage, IPTC_NAA2, ModelTransform, PhotoshopSettings, ExifOffset, ICC_Profile, ImageLayer, GeoTiffDirectory, GeoTiffDoubleParams, GeoTiffAsciiParams, ExposureProgram, SpectralSensitivity, GPSInfo, ISO, OptoElectricConvFactor, Interlace, TimeZoneOffset, SelfTimerMode, FaxRecvParams, FaxSubAddress, FaxRecvTime, ExifVersion, DateTimeOriginal, CreateDate, ComponentsConfiguration, CompressedBitsPerPixel, ShutterSpeedValue, ApertureValue, BrightnessValue, ExposureCompensation, MaxApertureValue, SubjectDistance, MeteringMode, LightSource, Flash, FocalLength, FlashEnergy, SpatialFrequencyResponse, Noise, FocalPlaneXResolution, FocalPlaneYResolution, FocalPlaneResolutionUnit, ImageNumber, SecurityClassification, ImageHistory, SubjectLocation, ExposureIndex, TIFF_EPStandardID, SensingMethod, StoNits, MakerNote, UserComment, SubSecTime, SubSecTimeOriginal, SubSecTimeDigitized, ImageSourceData, XPTitle, XPComment, XPAuthor, XPKeywords, XPSubject, FlashpixVersion, ColorSpace, ExifImageWidth, ExifImageLength, RelatedSoundFile, InteropOffset, FlashEnergy2, SpatialFrequencyResponse2, Noise2, FocalPlaneXResolution2, FocalPlaneYResolution2, FocalPlaneResolutionUnit2, ImageNumber2, SecurityClassification2, ImageHistory2, SubjectLocation2, ExposureIndex2, TIFF_EPStandardID2, SensingMethod2, FileSource, SceneType, CFAPattern, CustomRendered, ExposureMode, WhiteBalance, DigitalZoomRatio, FocalLengthIn35mmFormat, SceneCaptureType, GainControl, Contrast, Saturation, Sharpness, DeviceSettingDescription, SubjectDistanceRange, ImageUniqueID, GDALMetadata, GDALNoData, Gamma, FilmProductCode, ImageSourceEK, CaptureConditionsPAR, CameraOwner, SerialNumber, UserSelectGroupTitle, DealerIDNumber, CaptureDeviceFID, EnvelopeNumber, FrameNumber, FilmCategory, FilmGencode, ModelAndVersion, FilmSize, SBA_RGBShifts, SBAInputImageColorspace, SBAInputImageBitDepth, SBAExposureRecord, UserAdjSBA_RGBShifts, ImageRotationStatus, RollGuidElements, MetadataNumber, EditTagArray, Magnification, NativeXResolution, NativeYResolution, KodakEffectsIFD, KodakBordersIFD, NativeResolutionUnit, SourceImageDirectory, SourceImageFileName, SourceImageVolumeName, OceScanjobDesc, OceApplicationSelector, OceIDNumber, OceImageLogic, Annotations, PrintQuality, ImagePrintStatus, PrintIM, DNGVersion, DNGBackwardVersion, UniqueCameraModel, LocalizedCameraModel, CFAPlaneColor, CFALayout, LinearizationTable, BlackLevelRepeatDim, BlackLevel, BlackLevelDeltaH, BlackLevelDeltaV, WhiteLevel, DefaultScale, DefaultCropOrigin, DefaultCropSize, ColorMatrix1, ColorMatrix2, CameraCalibration1, CameraCalibration2, ReductionMatrix1, ReductionMatrix2, AnalogBalance, AsShotNeutral, AsShotWhiteXY, BaselineExposure, BaselineNoise, BaselineSharpness, BayerGreenSplit, LinearResponseLimit, DNGCameraSerialNumber, DNGLensInfo, ChromaBlurRadius, AntiAliasStrength, ShadowScale, DNGPrivateData, MakerNoteSafety, CalibrationIlluminant1, CalibrationIlluminant2, BestQualityScale, AliasLayerMetadata, OwnerName, SerialNumber2, Lens, RawFile, Converter, WhiteBalance2, Exposure, Shadows, Brightness, Contrast2, Saturation2, Sharpness2, Smoothness, MoireFilter };

enum tagCasioTag2 : WORD {
    PreviewThumbnailDimensions = (WORD) 0x0002,
    PreviewThumbnailSize = (WORD) 0x0003,
    PreviewThumbnailOffset = (WORD) 0x0004,
    CSQualityMode = (WORD) 0x0008,
    CsImageSize = (WORD) 0x0009,
    CSFocusMode = (WORD) 0x000D,
    CsIsoSensitivity = (WORD) 0x0014,
    CsWhiteBalance = (WORD) 0x0019,
    CsFocalLength = (WORD) 0x001D,
    CsSaturation = (WORD) 0x001F,
    CsContrast = (WORD) 0x0020,
    CsSharpness = (WORD) 0x0021,
    CsPrintImageMatchingInfo = (WORD) 0x0E00,
    CasioPreviewThumbnail = (WORD) 0x2000,
    CsWhiteBalanceBias = (WORD) 0x2011,
    CsFlashMode = (WORD) 0x2012,
    CsObjectDistance = (WORD) 0x2022,
    CsFlashDistance = (WORD) 0x2034,
    CsRecordMode = (WORD) 0x3000,
    CsSelfTimer = (WORD) 0x3001,
    CsQuality = (WORD) 0x3002,
    CsMeteringMode2 = (WORD) 0x3003,
    CsTimeZone = (WORD) 0x3006,
    CsBestshotMode = (WORD) 0x3007,
    CsCCDISOSensitivity = (WORD) 0x3014,
    CsColourMode = (WORD) 0x3015,
    CsEnhancement = (WORD) 0x3016,
    CsFilter = (WORD) 0x3017,
};
std::vector<WORD> tagCasioTag2_values = { PreviewThumbnailDimensions, PreviewThumbnailSize, PreviewThumbnailOffset, CSQualityMode, CsImageSize, CSFocusMode, CsIsoSensitivity, CsWhiteBalance, CsFocalLength, CsSaturation, CsContrast, CsSharpness, CsPrintImageMatchingInfo, CasioPreviewThumbnail, CsWhiteBalanceBias, CsFlashMode, CsObjectDistance, CsFlashDistance, CsRecordMode, CsSelfTimer, CsQuality, CsMeteringMode2, CsTimeZone, CsBestshotMode, CsCCDISOSensitivity, CsColourMode, CsEnhancement, CsFilter };

typedef enum tagCasioTag2 CasioTag2;
std::vector<WORD> CasioTag2_values = { PreviewThumbnailDimensions, PreviewThumbnailSize, PreviewThumbnailOffset, CSQualityMode, CsImageSize, CSFocusMode, CsIsoSensitivity, CsWhiteBalance, CsFocalLength, CsSaturation, CsContrast, CsSharpness, CsPrintImageMatchingInfo, CasioPreviewThumbnail, CsWhiteBalanceBias, CsFlashMode, CsObjectDistance, CsFlashDistance, CsRecordMode, CsSelfTimer, CsQuality, CsMeteringMode2, CsTimeZone, CsBestshotMode, CsCCDISOSensitivity, CsColourMode, CsEnhancement, CsFilter };

enum tagDataFormat : WORD {
    uByte = (WORD) 1,
    ascString,
    uShort,
    uLong1,
    uRatio,
    sByte,
    undefined = (WORD) 7,
    sShort,
    sLong = (WORD) 9,
    sRatio,
    sFloat,
    dFloat,
};
std::vector<WORD> tagDataFormat_values = { uByte, ascString, uShort, uLong1, uRatio, sByte, undefined, sShort, sLong, sRatio, sFloat, dFloat };

typedef enum tagDataFormat DataFormat;
std::vector<WORD> DataFormat_values = { uByte, ascString, uShort, uLong1, uRatio, sByte, undefined, sShort, sLong, sRatio, sFloat, dFloat };

enum IFD_dirtype {
    IFD_TYPE_EXIF = 1,
    IFD_TYPE_GEOTAG,
    IFD_TYPE_CASIO_QV_R62,
};

enum GeoTag : WORD {
    GPSVersionID,
    GPSLatitudeRef,
    GPSLatitude,
    GPSLongitudeRef,
    GPSLongitude,
    GPSAltitudeRef,
    GPSAltitude,
    GPSTimeStamp,
    GPSSatellites,
    GPSStatus,
    GPSMeasureMode,
    GPSDOP,
    GPSSpeedRef,
    GPSSpeed,
    GPSTrackRef,
    GPSTrack,
    GPSImgDirectionRef,
    GPSImgDirection,
    GPSMapDatum,
    GPSDestLatitudeRef,
    GPSDestLatitude,
    GPSDestLongitudeRef,
    GPSDestLongitude,
    GPSDestBearingRef,
    GPSDestBearing,
    GPSDestDistanceRef,
    GPSDestDistance,
    GPSProcessingMehotd,
    GPSAreaInformation,
    GPSDateStamp,
    GPSDifferential,
};
std::vector<WORD> GeoTag_values = { GPSVersionID, GPSLatitudeRef, GPSLatitude, GPSLongitudeRef, GPSLongitude, GPSAltitudeRef, GPSAltitude, GPSTimeStamp, GPSSatellites, GPSStatus, GPSMeasureMode, GPSDOP, GPSSpeedRef, GPSSpeed, GPSTrackRef, GPSTrack, GPSImgDirectionRef, GPSImgDirection, GPSMapDatum, GPSDestLatitudeRef, GPSDestLatitude, GPSDestLongitudeRef, GPSDestLongitude, GPSDestBearingRef, GPSDestBearing, GPSDestDistanceRef, GPSDestDistance, GPSProcessingMehotd, GPSAreaInformation, GPSDateStamp, GPSDifferential };

enum CIFFTagStg {
    kStg_InHeapSpace,
    kStg_InRecordEntry,
    kStg_reversed2,
    kStg_reversed3,
};

enum CIFFTagDataType {
    kDT_BYTE = 0x0000,
    kDT_ASCII = 0x0800,
    kDT_WORD = 0x1000,
    kDT_DWORD = 0x1800,
    kDT_BYTE2 = 0x2000,
    kDT_HeapTypeProperty1 = 0x2800,
    kDT_HeapTypeProperty2 = 0x3000,
};

enum CIFFTagType : uint16 {
    kTC_Null = (uint16) 0,
    kTC_Free,
    kTC_ExFree,
    kTC_Description = (uint16) 0x0805,
    kTC_ModelName = (uint16) 0x080a,
    kTC_FirmwareVersion = (uint16) 0x080b,
    kTC_ComponentVersion = (uint16) 0x080c,
    kTC_ROMOperationMode = (uint16) 0x080d,
    kTC_OwnerName = (uint16) 0x0810,
    kTC_ImageFileName = (uint16) 0x0816,
    kTC_ThumbnailFileName = (uint16) 0x0817,
    kTC_TargetImageType = (uint16) 0x100a,
    kTC_SR_ReleaseMethod = (uint16) 0x1010,
    kTC_SR_ReleaseTiming = (uint16) 0x1011,
    kTC_ReleaseSetting = (uint16) 0x1016,
    kTC_BodySensitivity = (uint16) 0x101c,
    kTC_ImageFormat = (uint16) 0x1803,
    kTC_RecordID = (uint16) 0x1804,
    kTC_SelfTimerTime = (uint16) 0x1806,
    kTC_SR_TargetDistanceSetting = (uint16) 0x1807,
    kTC_BodyID = (uint16) 0x180b,
    kTC_CapturedTime = (uint16) 0x180e,
    kTC_ImageSpec = (uint16) 0x1810,
    kTC_SR_EF = (uint16) 0x1813,
    kTC_MI_EV = (uint16) 0x1814,
    kTC_SerialNumber = (uint16) 0x1817,
    kTC_CameraObject = (uint16) 0x2807,
    kTC_ShootingRecord = (uint16) 0x3002,
    kTC_MeasuredInfo = (uint16) 0x3003,
    kTC_CameraSpecification = (uint16) 0x3004,
};
std::vector<uint16> CIFFTagType_values = { kTC_Null, kTC_Free, kTC_ExFree, kTC_Description, kTC_ModelName, kTC_FirmwareVersion, kTC_ComponentVersion, kTC_ROMOperationMode, kTC_OwnerName, kTC_ImageFileName, kTC_ThumbnailFileName, kTC_TargetImageType, kTC_SR_ReleaseMethod, kTC_SR_ReleaseTiming, kTC_ReleaseSetting, kTC_BodySensitivity, kTC_ImageFormat, kTC_RecordID, kTC_SelfTimerTime, kTC_SR_TargetDistanceSetting, kTC_BodyID, kTC_CapturedTime, kTC_ImageSpec, kTC_SR_EF, kTC_MI_EV, kTC_SerialNumber, kTC_CameraObject, kTC_ShootingRecord, kTC_MeasuredInfo, kTC_CameraSpecification };
 const std::vector<int> dataFormatLength = { 0, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 4, 8 };

class uint16_class {
    int small;
    std::vector<uint16> known_values;
    uint16 value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(uint16);
    uint16 operator () () { return value; }
    uint16_class(int small, std::vector<uint16> known_values = {}) : small(small), known_values(known_values) {}

    uint16 generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(uint16), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(uint16), 0, known_values);
        }
        return value;
    }

    uint16 generate(std::vector<uint16> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(uint16), 0, possible_values);
        return value;
    }
};



class WORD_class {
    int small;
    std::vector<WORD> known_values;
    WORD value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(WORD);
    WORD operator () () { return value; }
    WORD_class(int small, std::vector<WORD> known_values = {}) : small(small), known_values(known_values) {}

    WORD generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(WORD), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(WORD), 0, known_values);
        }
        return value;
    }

    WORD generate(std::vector<WORD> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(WORD), 0, possible_values);
        return value;
    }
};



class char_class {
    int small;
    std::vector<char> known_values;
    char value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(char);
    char operator () () { return value; }
    char_class(int small, std::vector<char> known_values = {}) : small(small), known_values(known_values) {}

    char generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(char), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(char), 0, known_values);
        }
        return value;
    }

    char generate(std::vector<char> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(char), 0, possible_values);
        return value;
    }
};



class char_array_class {
    char_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<char>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    char operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    char_array_class(char_class& element, std::unordered_map<int, std::vector<char>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    char_array_class(char_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (!element_known_values.size()) {
            if (size == 0)
                 return "";
            value = file_acc.file_string(size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(char), 0, known->second));
                _sizeof += sizeof(char);
            }
        }
        return value;
    }
};



class byte_class {
    int small;
    std::vector<byte> known_values;
    byte value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(byte);
    byte operator () () { return value; }
    byte_class(int small, std::vector<byte> known_values = {}) : small(small), known_values(known_values) {}

    byte generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(byte), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(byte), 0, known_values);
        }
        return value;
    }

    byte generate(std::vector<byte> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(byte), 0, possible_values);
        return value;
    }
};



class APP0 {
    std::vector<APP0*>& instances;

    uint16 marker_var;
    WORD szSection_var;
    std::string App0Type_var;
    byte versionHigh_var;
    byte versionLow_var;
    byte units_var;
    uint16 Xdensity_var;
    uint16 Ydensity_var;
    byte xThumbnail_var;
    byte yThumbnail_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool App0Type_exists = false;
    bool versionHigh_exists = false;
    bool versionLow_exists = false;
    bool units_exists = false;
    bool Xdensity_exists = false;
    bool Ydensity_exists = false;
    bool xThumbnail_exists = false;
    bool yThumbnail_exists = false;

    uint16 marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string App0Type() {
        assert_cond(App0Type_exists, "struct field App0Type does not exist");
        return App0Type_var;
    }
    byte versionHigh() {
        assert_cond(versionHigh_exists, "struct field versionHigh does not exist");
        return versionHigh_var;
    }
    byte versionLow() {
        assert_cond(versionLow_exists, "struct field versionLow does not exist");
        return versionLow_var;
    }
    byte units() {
        assert_cond(units_exists, "struct field units does not exist");
        return units_var;
    }
    uint16 Xdensity() {
        assert_cond(Xdensity_exists, "struct field Xdensity does not exist");
        return Xdensity_var;
    }
    uint16 Ydensity() {
        assert_cond(Ydensity_exists, "struct field Ydensity does not exist");
        return Ydensity_var;
    }
    byte xThumbnail() {
        assert_cond(xThumbnail_exists, "struct field xThumbnail does not exist");
        return xThumbnail_var;
    }
    byte yThumbnail() {
        assert_cond(yThumbnail_exists, "struct field yThumbnail does not exist");
        return yThumbnail_var;
    }

  
    std::vector<std::string> tmp;
    std::string chunk_type;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    APP0& operator () () { return *instances.back(); }
    APP0* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    APP0(std::vector<APP0*>& instances) : instances(instances) { instances.push_back(this); }
    ~APP0() {
        if (generated == 2)
            return;
        while (instances.size()) {
            APP0* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    APP0* generate();
};


M_ID M_ID_generate() {
    return (M_ID) file_acc.file_integer(sizeof(WORD), 0, M_ID_values);
}

M_ID M_ID_generate(std::vector<WORD> known_values) {
    return (M_ID) file_acc.file_integer(sizeof(WORD), 0, known_values);
}


class byte_array_class {
    byte_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<byte>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    byte operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    byte_array_class(byte_class& element, std::unordered_map<int, std::vector<byte>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    byte_array_class(byte_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(byte), 0, known->second));
                _sizeof += sizeof(byte);
            }
        }
        return value;
    }
};



class DWORD_class {
    int small;
    std::vector<DWORD> known_values;
    DWORD value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(DWORD);
    DWORD operator () () { return value; }
    DWORD_class(int small, std::vector<DWORD> known_values = {}) : small(small), known_values(known_values) {}

    DWORD generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(DWORD), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(DWORD), 0, known_values);
        }
        return value;
    }

    DWORD generate(std::vector<DWORD> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(DWORD), 0, possible_values);
        return value;
    }
};


ExifTag ExifTag_generate() {
    return (ExifTag) file_acc.file_integer(sizeof(WORD), 0, ExifTag_values);
}

ExifTag ExifTag_generate(std::vector<WORD> known_values) {
    return (ExifTag) file_acc.file_integer(sizeof(WORD), 0, known_values);
}

GeoTag GeoTag_generate() {
    return (GeoTag) file_acc.file_integer(sizeof(WORD), 0, GeoTag_values);
}

GeoTag GeoTag_generate(std::vector<WORD> known_values) {
    return (GeoTag) file_acc.file_integer(sizeof(WORD), 0, known_values);
}

CasioTag2 CasioTag2_generate() {
    return (CasioTag2) file_acc.file_integer(sizeof(WORD), 0, CasioTag2_values);
}

CasioTag2 CasioTag2_generate(std::vector<WORD> known_values) {
    return (CasioTag2) file_acc.file_integer(sizeof(WORD), 0, known_values);
}

DataFormat DataFormat_generate() {
    return (DataFormat) file_acc.file_integer(sizeof(WORD), 0, DataFormat_values);
}

DataFormat DataFormat_generate(std::vector<WORD> known_values) {
    return (DataFormat) file_acc.file_integer(sizeof(WORD), 0, known_values);
}

enum ExposureProgram_enum : short {
    EP_Not_defined,
    EP_Manual,
    EP_Normal_program,
    EP_Aperture_priority,
    EP_Shutter_priority,
    EP_Creative_program,
    EP_Action_program,
    EP_Portrait_mode,
    EP_Landscape_mode,
};
std::vector<short> ExposureProgram_enum_values = { EP_Not_defined, EP_Manual, EP_Normal_program, EP_Aperture_priority, EP_Shutter_priority, EP_Creative_program, EP_Action_program, EP_Portrait_mode, EP_Landscape_mode };

ExposureProgram_enum ExposureProgram_enum_generate() {
    return (ExposureProgram_enum) file_acc.file_integer(sizeof(short), 0, ExposureProgram_enum_values);
}

ExposureProgram_enum ExposureProgram_enum_generate(std::vector<short> known_values) {
    return (ExposureProgram_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}

enum MeteringMode_enum : short {
    MM_unknown,
    MM_Average,
    MM_CenterWeightedAverage,
    MM_Spot,
    MM_MultiSpot,
    MM_Pattern,
    MM_Partial,
    MM_other = (short) 255,
};
std::vector<short> MeteringMode_enum_values = { MM_unknown, MM_Average, MM_CenterWeightedAverage, MM_Spot, MM_MultiSpot, MM_Pattern, MM_Partial, MM_other };

MeteringMode_enum MeteringMode_enum_generate() {
    return (MeteringMode_enum) file_acc.file_integer(sizeof(short), 0, MeteringMode_enum_values);
}

MeteringMode_enum MeteringMode_enum_generate(std::vector<short> known_values) {
    return (MeteringMode_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}

enum LightSource_enum : short {
    LS_unknown,
    LS_Daylight,
    LS_Fluorescent,
    LS_Tungsten,
    LS_Flash,
    LS_Fine_weather = (short) 9,
    LS_Cloudy_weather,
    LS_Shade,
    LS_Daylight_fluorescent,
    LS_Day_white_fluorescent,
    LS_Cool_white_fluorescent,
    LS_White_fluorescent,
    LS_Standard_light_A,
    LS_Standard_light_B,
    LS_Standard_light_C,
    LS_D55,
    LS_D65,
    LS_D75,
    LS_D50,
    LS_ISO_studio_tungsten,
    LS_other_light_scoure = (short) 255,
};
std::vector<short> LightSource_enum_values = { LS_unknown, LS_Daylight, LS_Fluorescent, LS_Tungsten, LS_Flash, LS_Fine_weather, LS_Cloudy_weather, LS_Shade, LS_Daylight_fluorescent, LS_Day_white_fluorescent, LS_Cool_white_fluorescent, LS_White_fluorescent, LS_Standard_light_A, LS_Standard_light_B, LS_Standard_light_C, LS_D55, LS_D65, LS_D75, LS_D50, LS_ISO_studio_tungsten, LS_other_light_scoure };

LightSource_enum LightSource_enum_generate() {
    return (LightSource_enum) file_acc.file_integer(sizeof(short), 0, LightSource_enum_values);
}

LightSource_enum LightSource_enum_generate(std::vector<short> known_values) {
    return (LightSource_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}


class short_bitfield {
    int small;
    std::vector<short> known_values;
    short value;
public:
    short operator () () { return value; }
    short_bitfield(int small, std::vector<short> known_values = {}) : small(small), known_values(known_values) {}

    short generate(unsigned bits) {
        if (!bits)
            return 0;
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(short), bits, small);
        } else {
            value = file_acc.file_integer(sizeof(short), bits, known_values);
        }
        return value;
    }

    short generate(unsigned bits, std::vector<short> possible_values) {
        if (!bits)
            return 0;
        value = file_acc.file_integer(sizeof(short), bits, possible_values);
        return value;
    }
};


enum ExposureMode_enum : short {
    EM_Auto_exposure,
    EM_Manual_exposure,
    EM_Auto_bracket,
};
std::vector<short> ExposureMode_enum_values = { EM_Auto_exposure, EM_Manual_exposure, EM_Auto_bracket };

ExposureMode_enum ExposureMode_enum_generate() {
    return (ExposureMode_enum) file_acc.file_integer(sizeof(short), 0, ExposureMode_enum_values);
}

ExposureMode_enum ExposureMode_enum_generate(std::vector<short> known_values) {
    return (ExposureMode_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}

enum WhiteBalance_enum : short {
    WB_Auto_white_balance,
    WB_Manual_white_balance,
};
std::vector<short> WhiteBalance_enum_values = { WB_Auto_white_balance, WB_Manual_white_balance };

WhiteBalance_enum WhiteBalance_enum_generate() {
    return (WhiteBalance_enum) file_acc.file_integer(sizeof(short), 0, WhiteBalance_enum_values);
}

WhiteBalance_enum WhiteBalance_enum_generate(std::vector<short> known_values) {
    return (WhiteBalance_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}

enum SceneCaptureType_enum : short {
    SCT_Standard,
    SCT_Landscape,
    SCT_Portrait,
    SCT_Night_scene,
};
std::vector<short> SceneCaptureType_enum_values = { SCT_Standard, SCT_Landscape, SCT_Portrait, SCT_Night_scene };

SceneCaptureType_enum SceneCaptureType_enum_generate() {
    return (SceneCaptureType_enum) file_acc.file_integer(sizeof(short), 0, SceneCaptureType_enum_values);
}

SceneCaptureType_enum SceneCaptureType_enum_generate(std::vector<short> known_values) {
    return (SceneCaptureType_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}

enum SubjectDistanceRange_enum : short {
    SDR_unknown,
    SDR_Macro,
    SDR_Close_view,
    SDR_Distant_view,
};
std::vector<short> SubjectDistanceRange_enum_values = { SDR_unknown, SDR_Macro, SDR_Close_view, SDR_Distant_view };

SubjectDistanceRange_enum SubjectDistanceRange_enum_generate() {
    return (SubjectDistanceRange_enum) file_acc.file_integer(sizeof(short), 0, SubjectDistanceRange_enum_values);
}

SubjectDistanceRange_enum SubjectDistanceRange_enum_generate(std::vector<short> known_values) {
    return (SubjectDistanceRange_enum) file_acc.file_integer(sizeof(short), 0, known_values);
}


class uchar_class {
    int small;
    std::vector<uchar> known_values;
    uchar value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(uchar);
    uchar operator () () { return value; }
    uchar_class(int small, std::vector<uchar> known_values = {}) : small(small), known_values(known_values) {}

    uchar generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(uchar), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(uchar), 0, known_values);
        }
        return value;
    }

    uchar generate(std::vector<uchar> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(uchar), 0, possible_values);
        return value;
    }
};



class uchar_array_class {
    uchar_class& element;
    std::vector<std::string> known_values;
    std::unordered_map<int, std::vector<uchar>> element_known_values;
    std::string value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::string operator () () { return value; }
    uchar operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    uchar_array_class(uchar_class& element, std::unordered_map<int, std::vector<uchar>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}
    uchar_array_class(uchar_class& element, std::vector<std::string> known_values)
        : element(element), known_values(known_values) {}

    std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
        check_array_length(size);
        _startof = FTell();
        value = "";
        if (possible_values.size()) {
            value = file_acc.file_string(possible_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (known_values.size()) {
            value = file_acc.file_string(known_values);
            assert(value.length() == size);
            _sizeof = size;
            return value;
        }
        if (!element_known_values.size()) {
            if (size == 0)
                 return "";
            value = file_acc.file_string(size);
            _sizeof = size;
            return value;
        }
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(uchar), 0, known->second));
                _sizeof += sizeof(uchar);
            }
        }
        return value;
    }
};



class tgDIRENTRY_strAscii_struct {
    std::vector<tgDIRENTRY_strAscii_struct*>& instances;

    std::string oneByteData_var;

public:
    bool oneByteData_exists = false;

    std::string oneByteData() {
        assert_cond(oneByteData_exists, "struct field oneByteData does not exist");
        return oneByteData_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgDIRENTRY_strAscii_struct& operator () () { return *instances.back(); }
    tgDIRENTRY_strAscii_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgDIRENTRY_strAscii_struct(std::vector<tgDIRENTRY_strAscii_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgDIRENTRY_strAscii_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgDIRENTRY_strAscii_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgDIRENTRY_strAscii_struct* generate();
};



class StrAscii1 {
    std::vector<StrAscii1*>& instances;

    std::string oneByteData_var;

public:
    bool oneByteData_exists = false;

    std::string oneByteData() {
        assert_cond(oneByteData_exists, "struct field oneByteData does not exist");
        return oneByteData_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    StrAscii1& operator () () { return *instances.back(); }
    StrAscii1* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    StrAscii1(std::vector<StrAscii1*>& instances) : instances(instances) { instances.push_back(this); }
    ~StrAscii1() {
        if (generated == 2)
            return;
        while (instances.size()) {
            StrAscii1* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    StrAscii1* generate();
};



class ushort_class {
    int small;
    std::vector<ushort> known_values;
    ushort value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(ushort);
    ushort operator () () { return value; }
    ushort_class(int small, std::vector<ushort> known_values = {}) : small(small), known_values(known_values) {}

    ushort generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(ushort), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(ushort), 0, known_values);
        }
        return value;
    }

    ushort generate(std::vector<ushort> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(ushort), 0, possible_values);
        return value;
    }
};



class ulong_class {
    int small;
    std::vector<ulong> known_values;
    ulong value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(ulong);
    ulong operator () () { return value; }
    ulong_class(int small, std::vector<ulong> known_values = {}) : small(small), known_values(known_values) {}

    ulong generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(ulong), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(ulong), 0, known_values);
        }
        return value;
    }

    ulong generate(std::vector<ulong> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(ulong), 0, possible_values);
        return value;
    }
};



class tgDIRENTRY_strSByte_struct {
    std::vector<tgDIRENTRY_strSByte_struct*>& instances;

    std::string sBValue_var;

public:
    bool sBValue_exists = false;

    std::string sBValue() {
        assert_cond(sBValue_exists, "struct field sBValue does not exist");
        return sBValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgDIRENTRY_strSByte_struct& operator () () { return *instances.back(); }
    tgDIRENTRY_strSByte_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgDIRENTRY_strSByte_struct(std::vector<tgDIRENTRY_strSByte_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgDIRENTRY_strSByte_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgDIRENTRY_strSByte_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgDIRENTRY_strSByte_struct* generate();
};



class short_class {
    int small;
    std::vector<short> known_values;
    short value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(short);
    short operator () () { return value; }
    short_class(int small, std::vector<short> known_values = {}) : small(small), known_values(known_values) {}

    short generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(short), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(short), 0, known_values);
        }
        return value;
    }

    short generate(std::vector<short> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(short), 0, possible_values);
        return value;
    }
};



class short_array_class {
    short_class& element;
    std::unordered_map<int, std::vector<short>> element_known_values;
    std::vector<short> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<short> operator () () { return value; }
    short operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    short_array_class(short_class& element, std::unordered_map<int, std::vector<short>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<short> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(short), 0, known->second));
                _sizeof += sizeof(short);
            }
        }
        return value;
    }
};



class tgDIRENTRY_strSShort_struct {
    std::vector<tgDIRENTRY_strSShort_struct*>& instances;

    std::vector<short> sisValue_var;

public:
    bool sisValue_exists = false;

    std::vector<short> sisValue() {
        assert_cond(sisValue_exists, "struct field sisValue does not exist");
        return sisValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgDIRENTRY_strSShort_struct& operator () () { return *instances.back(); }
    tgDIRENTRY_strSShort_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgDIRENTRY_strSShort_struct(std::vector<tgDIRENTRY_strSShort_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgDIRENTRY_strSShort_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgDIRENTRY_strSShort_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgDIRENTRY_strSShort_struct* generate();
};



class float_class {
    int small;
    std::vector<float> known_values;
    float value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(float);
    float operator () () { return value; }
    float_class(int small, std::vector<float> known_values = {}) : small(small), known_values(known_values) {}

    float generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(float), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(float), 0, known_values);
        }
        return value;
    }

    float generate(std::vector<float> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(float), 0, possible_values);
        return value;
    }
};



class DIRENTRY {
    std::vector<DIRENTRY*>& instances;

    WORD tagNumber_var;
    WORD dataFormat_var;
    DWORD nComponent_var;
    short ExposureProgram__var;
    short MeteringMode__var;
    short LightSource__var;
    short unused_var : 9;
    short red_eye_mode_var : 1;
    short flash_function_var : 1;
    short flash_mode_var : 2;
    short flash_return_var : 2;
    short flash_fired_var : 1;
    short ExposureMode__var;
    short WhiteBalance__var;
    short SceneCaptureType__var;
    short SubjectDistanceRange__var;
    ushort usValue_var;
    ulong ulValue_var;
    tgDIRENTRY_strSByte_struct* strSByte_var;
    tgDIRENTRY_strSShort_struct* strSShort_var;
    ulong siLValue_var;
    float flValue_var;
    std::string padding_var;
    DWORD offsetData_var;

public:
    bool tagNumber_exists = false;
    bool dataFormat_exists = false;
    bool nComponent_exists = false;
    bool ExposureProgram__exists = false;
    bool MeteringMode__exists = false;
    bool LightSource__exists = false;
    bool unused_exists = false;
    bool red_eye_mode_exists = false;
    bool flash_function_exists = false;
    bool flash_mode_exists = false;
    bool flash_return_exists = false;
    bool flash_fired_exists = false;
    bool ExposureMode__exists = false;
    bool WhiteBalance__exists = false;
    bool SceneCaptureType__exists = false;
    bool SubjectDistanceRange__exists = false;
    bool usValue_exists = false;
    bool ulValue_exists = false;
    bool strSByte_exists = false;
    bool strSShort_exists = false;
    bool siLValue_exists = false;
    bool flValue_exists = false;
    bool padding_exists = false;
    bool offsetData_exists = false;

    WORD tagNumber() {
        assert_cond(tagNumber_exists, "struct field tagNumber does not exist");
        return tagNumber_var;
    }
    WORD dataFormat() {
        assert_cond(dataFormat_exists, "struct field dataFormat does not exist");
        return dataFormat_var;
    }
    DWORD nComponent() {
        assert_cond(nComponent_exists, "struct field nComponent does not exist");
        return nComponent_var;
    }
    short ExposureProgram_() {
        assert_cond(ExposureProgram__exists, "struct field ExposureProgram_ does not exist");
        return ExposureProgram__var;
    }
    short MeteringMode_() {
        assert_cond(MeteringMode__exists, "struct field MeteringMode_ does not exist");
        return MeteringMode__var;
    }
    short LightSource_() {
        assert_cond(LightSource__exists, "struct field LightSource_ does not exist");
        return LightSource__var;
    }
    short unused() {
        assert_cond(unused_exists, "struct field unused does not exist");
        return unused_var;
    }
    short red_eye_mode() {
        assert_cond(red_eye_mode_exists, "struct field red_eye_mode does not exist");
        return red_eye_mode_var;
    }
    short flash_function() {
        assert_cond(flash_function_exists, "struct field flash_function does not exist");
        return flash_function_var;
    }
    short flash_mode() {
        assert_cond(flash_mode_exists, "struct field flash_mode does not exist");
        return flash_mode_var;
    }
    short flash_return() {
        assert_cond(flash_return_exists, "struct field flash_return does not exist");
        return flash_return_var;
    }
    short flash_fired() {
        assert_cond(flash_fired_exists, "struct field flash_fired does not exist");
        return flash_fired_var;
    }
    short ExposureMode_() {
        assert_cond(ExposureMode__exists, "struct field ExposureMode_ does not exist");
        return ExposureMode__var;
    }
    short WhiteBalance_() {
        assert_cond(WhiteBalance__exists, "struct field WhiteBalance_ does not exist");
        return WhiteBalance__var;
    }
    short SceneCaptureType_() {
        assert_cond(SceneCaptureType__exists, "struct field SceneCaptureType_ does not exist");
        return SceneCaptureType__var;
    }
    short SubjectDistanceRange_() {
        assert_cond(SubjectDistanceRange__exists, "struct field SubjectDistanceRange_ does not exist");
        return SubjectDistanceRange__var;
    }
    ushort usValue() {
        assert_cond(usValue_exists, "struct field usValue does not exist");
        return usValue_var;
    }
    ulong ulValue() {
        assert_cond(ulValue_exists, "struct field ulValue does not exist");
        return ulValue_var;
    }
    tgDIRENTRY_strSByte_struct& strSByte() {
        assert_cond(strSByte_exists, "struct field strSByte does not exist");
        return *strSByte_var;
    }
    tgDIRENTRY_strSShort_struct& strSShort() {
        assert_cond(strSShort_exists, "struct field strSShort does not exist");
        return *strSShort_var;
    }
    ulong siLValue() {
        assert_cond(siLValue_exists, "struct field siLValue does not exist");
        return siLValue_var;
    }
    float flValue() {
        assert_cond(flValue_exists, "struct field flValue does not exist");
        return flValue_var;
    }
    std::string padding() {
        assert_cond(padding_exists, "struct field padding does not exist");
        return padding_var;
    }
    DWORD offsetData() {
        assert_cond(offsetData_exists, "struct field offsetData does not exist");
        return offsetData_var;
    }

  
    unsigned int j;
    int length;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    DIRENTRY& operator () () { return *instances.back(); }
    DIRENTRY* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    DIRENTRY(std::vector<DIRENTRY*>& instances) : instances(instances) { instances.push_back(this); }
    ~DIRENTRY() {
        if (generated == 2)
            return;
        while (instances.size()) {
            DIRENTRY* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    DIRENTRY* generate();
};



class DIRENTRY_array_class {
    DIRENTRY& element;
    std::vector<DIRENTRY*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<DIRENTRY*> operator () () { return value; }
    DIRENTRY operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    DIRENTRY_array_class(DIRENTRY& element) : element(element) {}

    std::vector<DIRENTRY*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class StrAscii {
    std::vector<StrAscii*>& instances;

    std::string oneByteData_var;

public:
    bool oneByteData_exists = false;

    std::string oneByteData() {
        assert_cond(oneByteData_exists, "struct field oneByteData does not exist");
        return oneByteData_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    StrAscii& operator () () { return *instances.back(); }
    StrAscii* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    StrAscii(std::vector<StrAscii*>& instances) : instances(instances) { instances.push_back(this); }
    ~StrAscii() {
        if (generated == 2)
            return;
        while (instances.size()) {
            StrAscii* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    StrAscii* generate(int& i);
};



class tgIFD_strAscii_struct {
    std::vector<tgIFD_strAscii_struct*>& instances;

    std::string oneByteData_var;

public:
    bool oneByteData_exists = false;

    std::string oneByteData() {
        assert_cond(oneByteData_exists, "struct field oneByteData does not exist");
        return oneByteData_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strAscii_struct& operator () () { return *instances.back(); }
    tgIFD_strAscii_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strAscii_struct(std::vector<tgIFD_strAscii_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strAscii_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strAscii_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strAscii_struct* generate(int& i);
};



class ushort_array_class {
    ushort_class& element;
    std::unordered_map<int, std::vector<ushort>> element_known_values;
    std::vector<ushort> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<ushort> operator () () { return value; }
    ushort operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    ushort_array_class(ushort_class& element, std::unordered_map<int, std::vector<ushort>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<ushort> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(ushort), 0, known->second));
                _sizeof += sizeof(ushort);
            }
        }
        return value;
    }
};



class tgIFD_strUShort_struct {
    std::vector<tgIFD_strUShort_struct*>& instances;

    std::vector<ushort> usValue_var;

public:
    bool usValue_exists = false;

    std::vector<ushort> usValue() {
        assert_cond(usValue_exists, "struct field usValue does not exist");
        return usValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strUShort_struct& operator () () { return *instances.back(); }
    tgIFD_strUShort_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strUShort_struct(std::vector<tgIFD_strUShort_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strUShort_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strUShort_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strUShort_struct* generate(int& i);
};



class ulong_array_class {
    ulong_class& element;
    std::unordered_map<int, std::vector<ulong>> element_known_values;
    std::vector<ulong> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<ulong> operator () () { return value; }
    ulong operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    ulong_array_class(ulong_class& element, std::unordered_map<int, std::vector<ulong>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<ulong> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(ulong), 0, known->second));
                _sizeof += sizeof(ulong);
            }
        }
        return value;
    }
};



class tgIFD_strULong_struct {
    std::vector<tgIFD_strULong_struct*>& instances;

    std::vector<ulong> ulValue_var;

public:
    bool ulValue_exists = false;

    std::vector<ulong> ulValue() {
        assert_cond(ulValue_exists, "struct field ulValue does not exist");
        return ulValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strULong_struct& operator () () { return *instances.back(); }
    tgIFD_strULong_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strULong_struct(std::vector<tgIFD_strULong_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strULong_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strULong_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strULong_struct* generate(int& i);
};



class URatio_uRValue_struct {
    std::vector<URatio_uRValue_struct*>& instances;

    DWORD num_var;
    DWORD den_var;

public:
    bool num_exists = false;
    bool den_exists = false;

    DWORD num() {
        assert_cond(num_exists, "struct field num does not exist");
        return num_var;
    }
    DWORD den() {
        assert_cond(den_exists, "struct field den does not exist");
        return den_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    URatio_uRValue_struct& operator () () { return *instances.back(); }
    URatio_uRValue_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    URatio_uRValue_struct(std::vector<URatio_uRValue_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~URatio_uRValue_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            URatio_uRValue_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    URatio_uRValue_struct* generate();
};



class URatio_uRValue_struct_array_class {
    URatio_uRValue_struct& element;
    std::vector<URatio_uRValue_struct*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<URatio_uRValue_struct*> operator () () { return value; }
    URatio_uRValue_struct operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    URatio_uRValue_struct_array_class(URatio_uRValue_struct& element) : element(element) {}

    std::vector<URatio_uRValue_struct*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class URatio {
    std::vector<URatio*>& instances;

    std::vector<URatio_uRValue_struct*> uRValue_var;

public:
    bool uRValue_exists = false;

    std::vector<URatio_uRValue_struct*> uRValue() {
        assert_cond(uRValue_exists, "struct field uRValue does not exist");
        return uRValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    URatio& operator () () { return *instances.back(); }
    URatio* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    URatio(std::vector<URatio*>& instances) : instances(instances) { instances.push_back(this); }
    ~URatio() {
        if (generated == 2)
            return;
        while (instances.size()) {
            URatio* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    URatio* generate(int& i);
};



class tgIFD_strSByte_struct {
    std::vector<tgIFD_strSByte_struct*>& instances;

    std::string sBValue_var;

public:
    bool sBValue_exists = false;

    std::string sBValue() {
        assert_cond(sBValue_exists, "struct field sBValue does not exist");
        return sBValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strSByte_struct& operator () () { return *instances.back(); }
    tgIFD_strSByte_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strSByte_struct(std::vector<tgIFD_strSByte_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strSByte_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strSByte_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strSByte_struct* generate(int& i);
};



class tgIFD_strSShort_struct {
    std::vector<tgIFD_strSShort_struct*>& instances;

    std::vector<short> sisValue_var;

public:
    bool sisValue_exists = false;

    std::vector<short> sisValue() {
        assert_cond(sisValue_exists, "struct field sisValue does not exist");
        return sisValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strSShort_struct& operator () () { return *instances.back(); }
    tgIFD_strSShort_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strSShort_struct(std::vector<tgIFD_strSShort_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strSShort_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strSShort_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strSShort_struct* generate(int& i);
};



class tgIFD_strSLong_struct {
    std::vector<tgIFD_strSLong_struct*>& instances;

    std::vector<ulong> siLValue_var;

public:
    bool siLValue_exists = false;

    std::vector<ulong> siLValue() {
        assert_cond(siLValue_exists, "struct field siLValue does not exist");
        return siLValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strSLong_struct& operator () () { return *instances.back(); }
    tgIFD_strSLong_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strSLong_struct(std::vector<tgIFD_strSLong_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strSLong_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strSLong_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strSLong_struct* generate(int& i);
};



class int_class {
    int small;
    std::vector<int> known_values;
    int value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(int);
    int operator () () { return value; }
    int_class(int small, std::vector<int> known_values = {}) : small(small), known_values(known_values) {}

    int generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(int), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(int), 0, known_values);
        }
        return value;
    }

    int generate(std::vector<int> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(int), 0, possible_values);
        return value;
    }
};



class strSRatio_struct_siRValue_struct {
    std::vector<strSRatio_struct_siRValue_struct*>& instances;

    int num_var;
    int den_var;

public:
    bool num_exists = false;
    bool den_exists = false;

    int num() {
        assert_cond(num_exists, "struct field num does not exist");
        return num_var;
    }
    int den() {
        assert_cond(den_exists, "struct field den does not exist");
        return den_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    strSRatio_struct_siRValue_struct& operator () () { return *instances.back(); }
    strSRatio_struct_siRValue_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    strSRatio_struct_siRValue_struct(std::vector<strSRatio_struct_siRValue_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~strSRatio_struct_siRValue_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            strSRatio_struct_siRValue_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    strSRatio_struct_siRValue_struct* generate();
};



class strSRatio_struct_siRValue_struct_array_class {
    strSRatio_struct_siRValue_struct& element;
    std::vector<strSRatio_struct_siRValue_struct*> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<strSRatio_struct_siRValue_struct*> operator () () { return value; }
    strSRatio_struct_siRValue_struct operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return *value[index];
    }
    strSRatio_struct_siRValue_struct_array_class(strSRatio_struct_siRValue_struct& element) : element(element) {}

    std::vector<strSRatio_struct_siRValue_struct*> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            value.push_back(element.generate());
            _sizeof += element._sizeof;
        }
        return value;
    }
};



class tgIFD_strSRatio_struct {
    std::vector<tgIFD_strSRatio_struct*>& instances;

    std::vector<strSRatio_struct_siRValue_struct*> siRValue_var;

public:
    bool siRValue_exists = false;

    std::vector<strSRatio_struct_siRValue_struct*> siRValue() {
        assert_cond(siRValue_exists, "struct field siRValue does not exist");
        return siRValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strSRatio_struct& operator () () { return *instances.back(); }
    tgIFD_strSRatio_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strSRatio_struct(std::vector<tgIFD_strSRatio_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strSRatio_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strSRatio_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strSRatio_struct* generate(int& i);
};



class float_array_class {
    float_class& element;
    std::unordered_map<int, std::vector<float>> element_known_values;
    std::vector<float> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<float> operator () () { return value; }
    float operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    float_array_class(float_class& element, std::unordered_map<int, std::vector<float>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<float> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(float), 0, known->second));
                _sizeof += sizeof(float);
            }
        }
        return value;
    }
};



class tgIFD_strsFloat_struct {
    std::vector<tgIFD_strsFloat_struct*>& instances;

    std::vector<float> flValue_var;

public:
    bool flValue_exists = false;

    std::vector<float> flValue() {
        assert_cond(flValue_exists, "struct field flValue does not exist");
        return flValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strsFloat_struct& operator () () { return *instances.back(); }
    tgIFD_strsFloat_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strsFloat_struct(std::vector<tgIFD_strsFloat_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strsFloat_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strsFloat_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strsFloat_struct* generate(int& i);
};



class double_class {
    int small;
    std::vector<double> known_values;
    double value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(double);
    double operator () () { return value; }
    double_class(int small, std::vector<double> known_values = {}) : small(small), known_values(known_values) {}

    double generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(double), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(double), 0, known_values);
        }
        return value;
    }

    double generate(std::vector<double> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(double), 0, possible_values);
        return value;
    }
};



class double_array_class {
    double_class& element;
    std::unordered_map<int, std::vector<double>> element_known_values;
    std::vector<double> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<double> operator () () { return value; }
    double operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    double_array_class(double_class& element, std::unordered_map<int, std::vector<double>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<double> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(double), 0, known->second));
                _sizeof += sizeof(double);
            }
        }
        return value;
    }
};



class tgIFD_strdFloat_struct {
    std::vector<tgIFD_strdFloat_struct*>& instances;

    std::vector<double> dFValue_var;

public:
    bool dFValue_exists = false;

    std::vector<double> dFValue() {
        assert_cond(dFValue_exists, "struct field dFValue does not exist");
        return dFValue_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tgIFD_strdFloat_struct& operator () () { return *instances.back(); }
    tgIFD_strdFloat_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tgIFD_strdFloat_struct(std::vector<tgIFD_strdFloat_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tgIFD_strdFloat_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tgIFD_strdFloat_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tgIFD_strdFloat_struct* generate(int& i);
};


class IFD;



class uint16_array_class {
    uint16_class& element;
    std::unordered_map<int, std::vector<uint16>> element_known_values;
    std::vector<uint16> value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    std::vector<uint16> operator () () { return value; }
    uint16 operator [] (int index) {
        assert_cond((unsigned)index < value.size(), "array index out of bounds");
        return value[index];
    }
    uint16_array_class(uint16_class& element, std::unordered_map<int, std::vector<uint16>> element_known_values = {})
        : element(element), element_known_values(element_known_values) {}

    std::vector<uint16> generate(unsigned size) {
        check_array_length(size);
        _startof = FTell();
        value = {};
        for (unsigned i = 0; i < size; ++i) {
            auto known = element_known_values.find(i);
            if (known == element_known_values.end()) {
                value.push_back(element.generate());
                _sizeof += element._sizeof;
            } else {
                value.push_back(file_acc.file_integer(sizeof(uint16), 0, known->second));
                _sizeof += sizeof(uint16);
            }
        }
        return value;
    }
};



class QuanTable {
    std::vector<QuanTable*>& instances;

    uchar PqTq_var;

public:
    bool PqTq_exists = false;

    uchar PqTq() {
        assert_cond(PqTq_exists, "struct field PqTq does not exist");
        return PqTq_var;
    }

   
    uchar availableA;
    uchar availableB;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    QuanTable& operator () () { return *instances.back(); }
    QuanTable* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    QuanTable(std::vector<QuanTable*>& instances) : instances(instances) { instances.push_back(this); }
    ~QuanTable() {
        if (generated == 2)
            return;
        while (instances.size()) {
            QuanTable* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    QuanTable* generate();
};



class DQT {
    std::vector<DQT*>& instances;

    uint16 marker_var;
    uint16 szSection_var;
    QuanTable* qtable_var;
    uint16 newSize_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool qtable_exists = false;
    bool newSize_exists = false;

    uint16 marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    uint16 szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    QuanTable& qtable() {
        assert_cond(qtable_exists, "struct field qtable does not exist");
        return *qtable_var;
    }
    uint16 newSize() {
        assert_cond(newSize_exists, "struct field newSize does not exist");
        return newSize_var;
    }

    
    uint16 sizePos;
    uint16 curPos;
    uint16 size;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    DQT& operator () () { return *instances.back(); }
    DQT* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    DQT(std::vector<DQT*>& instances) : instances(instances) { instances.push_back(this); }
    ~DQT() {
        if (generated == 2)
            return;
        while (instances.size()) {
            DQT* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    DQT* generate();
};



class ubyte_class {
    int small;
    std::vector<ubyte> known_values;
    ubyte value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(ubyte);
    ubyte operator () () { return value; }
    ubyte_class(int small, std::vector<ubyte> known_values = {}) : small(small), known_values(known_values) {}

    ubyte generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(ubyte), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(ubyte), 0, known_values);
        }
        return value;
    }

    ubyte generate(std::vector<ubyte> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(ubyte), 0, possible_values);
        return value;
    }
};



class COMPSOF {
    std::vector<COMPSOF*>& instances;

    ubyte compId_var;
    ubyte HorzVert_var;
    ubyte compNr_var;

public:
    bool compId_exists = false;
    bool HorzVert_exists = false;
    bool compNr_exists = false;

    ubyte compId() {
        assert_cond(compId_exists, "struct field compId does not exist");
        return compId_var;
    }
    ubyte HorzVert() {
        assert_cond(HorzVert_exists, "struct field HorzVert does not exist");
        return HorzVert_var;
    }
    ubyte compNr() {
        assert_cond(compNr_exists, "struct field compNr does not exist");
        return compNr_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    COMPSOF& operator () () { return *instances.back(); }
    COMPSOF* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    COMPSOF(std::vector<COMPSOF*>& instances) : instances(instances) { instances.push_back(this); }
    ~COMPSOF() {
        if (generated == 2)
            return;
        while (instances.size()) {
            COMPSOF* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    COMPSOF* generate(ubyte& c);
};



class SOFx {
    std::vector<SOFx*>& instances;

    uint16 marker_var;
    uint16 szSection_var;
    ubyte precision_var;
    WORD Y_image_var;
    WORD X_image_var;
    ubyte nr_comp_var;
    COMPSOF* comp_sof_var;
    uint16 newSize_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool precision_exists = false;
    bool Y_image_exists = false;
    bool X_image_exists = false;
    bool nr_comp_exists = false;
    bool comp_sof_exists = false;
    bool newSize_exists = false;

    uint16 marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    uint16 szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    ubyte precision() {
        assert_cond(precision_exists, "struct field precision does not exist");
        return precision_var;
    }
    WORD Y_image() {
        assert_cond(Y_image_exists, "struct field Y_image does not exist");
        return Y_image_var;
    }
    WORD X_image() {
        assert_cond(X_image_exists, "struct field X_image does not exist");
        return X_image_var;
    }
    ubyte nr_comp() {
        assert_cond(nr_comp_exists, "struct field nr_comp does not exist");
        return nr_comp_var;
    }
    COMPSOF& comp_sof() {
        assert_cond(comp_sof_exists, "struct field comp_sof does not exist");
        return *comp_sof_var;
    }
    uint16 newSize() {
        assert_cond(newSize_exists, "struct field newSize does not exist");
        return newSize_var;
    }

    
    uint16 sizePos;
    ubyte c;
    uint16 curPos;
    uint16 size;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    SOFx& operator () () { return *instances.back(); }
    SOFx* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    SOFx(std::vector<SOFx*>& instances) : instances(instances) { instances.push_back(this); }
    ~SOFx() {
        if (generated == 2)
            return;
        while (instances.size()) {
            SOFx* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    SOFx* generate();
};



class COMPSOS {
    std::vector<COMPSOS*>& instances;

    ubyte compId_var;
    ubyte ACDC_var;

public:
    bool compId_exists = false;
    bool ACDC_exists = false;

    ubyte compId() {
        assert_cond(compId_exists, "struct field compId does not exist");
        return compId_var;
    }
    ubyte ACDC() {
        assert_cond(ACDC_exists, "struct field ACDC does not exist");
        return ACDC_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    COMPSOS& operator () () { return *instances.back(); }
    COMPSOS* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    COMPSOS(std::vector<COMPSOS*>& instances) : instances(instances) { instances.push_back(this); }
    ~COMPSOS() {
        if (generated == 2)
            return;
        while (instances.size()) {
            COMPSOS* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    COMPSOS* generate(ubyte& c_2);
};



class SOS {
    std::vector<SOS*>& instances;

    uint16 marker_var;
    WORD szSection_var;
    ubyte nr_comp_var;
    COMPSOS* comp_var;
    uchar Ss_var;
    uchar Se_var;
    uchar AhAl_var;
    uint16 newSize_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool nr_comp_exists = false;
    bool comp_exists = false;
    bool Ss_exists = false;
    bool Se_exists = false;
    bool AhAl_exists = false;
    bool newSize_exists = false;

    uint16 marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    ubyte nr_comp() {
        assert_cond(nr_comp_exists, "struct field nr_comp does not exist");
        return nr_comp_var;
    }
    COMPSOS& comp() {
        assert_cond(comp_exists, "struct field comp does not exist");
        return *comp_var;
    }
    uchar Ss() {
        assert_cond(Ss_exists, "struct field Ss does not exist");
        return Ss_var;
    }
    uchar Se() {
        assert_cond(Se_exists, "struct field Se does not exist");
        return Se_var;
    }
    uchar AhAl() {
        assert_cond(AhAl_exists, "struct field AhAl does not exist");
        return AhAl_var;
    }
    uint16 newSize() {
        assert_cond(newSize_exists, "struct field newSize does not exist");
        return newSize_var;
    }

  
    uint16 sizePos;
    ubyte c_2;
    uint16 curPos;
    uint16 size;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    SOS& operator () () { return *instances.back(); }
    SOS* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    SOS(std::vector<SOS*>& instances) : instances(instances) { instances.push_back(this); }
    ~SOS() {
        if (generated == 2)
            return;
        while (instances.size()) {
            SOS* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    SOS* generate();
};


class JPGFILE;



class IFD {
    std::vector<IFD*>& instances;

    WORD nDirEntry_var;
    std::vector<DIRENTRY*> dirEntry_var;
    DWORD nextIFDoffset_var;
    tgIFD_strUShort_struct* strUShort_var;
    tgIFD_strULong_struct* strULong_var;
    URatio* strURatio_var;
    tgIFD_strSByte_struct* strSByte_var;
    tgIFD_strSShort_struct* strSShort_var;
    tgIFD_strSLong_struct* strSLong_var;
    tgIFD_strSRatio_struct* strSRatio_var;
    tgIFD_strsFloat_struct* strsFloat_var;
    tgIFD_strdFloat_struct* strdFloat_var;
    IFD* subDir_var;
    std::string Header_var;
    IFD* CasioIFD_var;
    JPGFILE* CasioMakerThumbnail_var;

public:
    bool nDirEntry_exists = false;
    bool dirEntry_exists = false;
    bool nextIFDoffset_exists = false;
    bool strUShort_exists = false;
    bool strULong_exists = false;
    bool strURatio_exists = false;
    bool strSByte_exists = false;
    bool strSShort_exists = false;
    bool strSLong_exists = false;
    bool strSRatio_exists = false;
    bool strsFloat_exists = false;
    bool strdFloat_exists = false;
    bool subDir_exists = false;
    bool Header_exists = false;
    bool CasioIFD_exists = false;
    bool CasioMakerThumbnail_exists = false;

    WORD nDirEntry() {
        assert_cond(nDirEntry_exists, "struct field nDirEntry does not exist");
        return nDirEntry_var;
    }
    std::vector<DIRENTRY*> dirEntry() {
        assert_cond(dirEntry_exists, "struct field dirEntry does not exist");
        return dirEntry_var;
    }
    DWORD nextIFDoffset() {
        assert_cond(nextIFDoffset_exists, "struct field nextIFDoffset does not exist");
        return nextIFDoffset_var;
    }
    tgIFD_strUShort_struct& strUShort() {
        assert_cond(strUShort_exists, "struct field strUShort does not exist");
        return *strUShort_var;
    }
    tgIFD_strULong_struct& strULong() {
        assert_cond(strULong_exists, "struct field strULong does not exist");
        return *strULong_var;
    }
    URatio& strURatio() {
        assert_cond(strURatio_exists, "struct field strURatio does not exist");
        return *strURatio_var;
    }
    tgIFD_strSByte_struct& strSByte() {
        assert_cond(strSByte_exists, "struct field strSByte does not exist");
        return *strSByte_var;
    }
    tgIFD_strSShort_struct& strSShort() {
        assert_cond(strSShort_exists, "struct field strSShort does not exist");
        return *strSShort_var;
    }
    tgIFD_strSLong_struct& strSLong() {
        assert_cond(strSLong_exists, "struct field strSLong does not exist");
        return *strSLong_var;
    }
    tgIFD_strSRatio_struct& strSRatio() {
        assert_cond(strSRatio_exists, "struct field strSRatio does not exist");
        return *strSRatio_var;
    }
    tgIFD_strsFloat_struct& strsFloat() {
        assert_cond(strsFloat_exists, "struct field strsFloat does not exist");
        return *strsFloat_var;
    }
    tgIFD_strdFloat_struct& strdFloat() {
        assert_cond(strdFloat_exists, "struct field strdFloat does not exist");
        return *strdFloat_var;
    }
    IFD& subDir() {
        assert_cond(subDir_exists, "struct field subDir does not exist");
        return *subDir_var;
    }
    std::string Header() {
        assert_cond(Header_exists, "struct field Header does not exist");
        return Header_var;
    }
    IFD& CasioIFD() {
        assert_cond(CasioIFD_exists, "struct field CasioIFD does not exist");
        return *CasioIFD_var;
    }
    JPGFILE& CasioMakerThumbnail();

    
    int i;
    int pos;
    std::vector<std::string> values22;
    std::vector<std::string> values6;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    IFD& operator () () { return *instances.back(); }
    IFD* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    IFD(std::vector<IFD*>& instances) : instances(instances) { instances.push_back(this); }
    ~IFD() {
        if (generated == 2)
            return;
        while (instances.size()) {
            IFD* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    IFD* generate(quad& offset);
};



class APP1 {
    std::vector<APP1*>& instances;

    WORD marker_var;
    WORD szSection_var;
    std::string EXIF_var;
    std::string align_var;
    WORD tagMark_var;
    DWORD offsetFirstIFD_var;
    IFD* ifdMainImage_var;
    IFD* ifdThumbnailImage_var;
    JPGFILE* thumbnail_var;
    std::string imageData_var;
    std::string XAP_var;
    std::string remain_var;
    std::string unknown_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool EXIF_exists = false;
    bool align_exists = false;
    bool tagMark_exists = false;
    bool offsetFirstIFD_exists = false;
    bool ifdMainImage_exists = false;
    bool ifdThumbnailImage_exists = false;
    bool thumbnail_exists = false;
    bool imageData_exists = false;
    bool XAP_exists = false;
    bool remain_exists = false;
    bool unknown_exists = false;

    WORD marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string EXIF() {
        assert_cond(EXIF_exists, "struct field EXIF does not exist");
        return EXIF_var;
    }
    std::string align() {
        assert_cond(align_exists, "struct field align does not exist");
        return align_var;
    }
    WORD tagMark() {
        assert_cond(tagMark_exists, "struct field tagMark does not exist");
        return tagMark_var;
    }
    DWORD offsetFirstIFD() {
        assert_cond(offsetFirstIFD_exists, "struct field offsetFirstIFD does not exist");
        return offsetFirstIFD_var;
    }
    IFD& ifdMainImage() {
        assert_cond(ifdMainImage_exists, "struct field ifdMainImage does not exist");
        return *ifdMainImage_var;
    }
    IFD& ifdThumbnailImage() {
        assert_cond(ifdThumbnailImage_exists, "struct field ifdThumbnailImage does not exist");
        return *ifdThumbnailImage_var;
    }
    JPGFILE& thumbnail();
    std::string imageData() {
        assert_cond(imageData_exists, "struct field imageData does not exist");
        return imageData_var;
    }
    std::string XAP() {
        assert_cond(XAP_exists, "struct field XAP does not exist");
        return XAP_var;
    }
    std::string remain() {
        assert_cond(remain_exists, "struct field remain does not exist");
        return remain_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }

    
    std::vector<std::string> values5;
    std::vector<std::string> values29;
    quad offset;
    int i;
    int thumbOffset;
    int thumbLength;
    int compression;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    APP1& operator () () { return *instances.back(); }
    APP1* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    APP1(std::vector<APP1*>& instances) : instances(instances) { instances.push_back(this); }
    ~APP1() {
        if (generated == 2)
            return;
        while (instances.size()) {
            APP1* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    APP1* generate();
};



class APP2 {
    std::vector<APP2*>& instances;

    WORD marker_var;
    WORD szSection_var;
    std::string FPXR_var;
    uchar version_var;
    std::string remain_var;
    std::string ICC_PROFILE_var;
    uchar block_num_var;
    uchar block_total_var;
    std::string data_var;
    std::string unknown_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool FPXR_exists = false;
    bool version_exists = false;
    bool remain_exists = false;
    bool ICC_PROFILE_exists = false;
    bool block_num_exists = false;
    bool block_total_exists = false;
    bool data_exists = false;
    bool unknown_exists = false;

    WORD marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string FPXR() {
        assert_cond(FPXR_exists, "struct field FPXR does not exist");
        return FPXR_var;
    }
    uchar version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    std::string remain() {
        assert_cond(remain_exists, "struct field remain does not exist");
        return remain_var;
    }
    std::string ICC_PROFILE() {
        assert_cond(ICC_PROFILE_exists, "struct field ICC_PROFILE does not exist");
        return ICC_PROFILE_var;
    }
    uchar block_num() {
        assert_cond(block_num_exists, "struct field block_num does not exist");
        return block_num_var;
    }
    uchar block_total() {
        assert_cond(block_total_exists, "struct field block_total does not exist");
        return block_total_var;
    }
    std::string data() {
        assert_cond(data_exists, "struct field data does not exist");
        return data_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }

    
    std::vector<std::string> values5;
    std::vector<std::string> values12;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    APP2& operator () () { return *instances.back(); }
    APP2* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    APP2(std::vector<APP2*>& instances) : instances(instances) { instances.push_back(this); }
    ~APP2() {
        if (generated == 2)
            return;
        while (instances.size()) {
            APP2* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    APP2* generate();
};


enum tag_enum : uint16 {
    DK_End,
    DK_Quality,
    DK_Comment,
    DK_Copyright,
};
std::vector<uint16> tag_enum_values = { DK_End, DK_Quality, DK_Comment, DK_Copyright };

tag_enum tag_enum_generate() {
    return (tag_enum) file_acc.file_integer(sizeof(uint16), 0, tag_enum_values);
}

tag_enum tag_enum_generate(std::vector<uint16> known_values) {
    return (tag_enum) file_acc.file_integer(sizeof(uint16), 0, known_values);
}


class uint32_class {
    int small;
    std::vector<uint32> known_values;
    uint32 value;
public:
    int64 _startof = 0;
    std::size_t _sizeof = sizeof(uint32);
    uint32 operator () () { return value; }
    uint32_class(int small, std::vector<uint32> known_values = {}) : small(small), known_values(known_values) {}

    uint32 generate() {
        _startof = FTell();
        if (known_values.empty()) {
            value = file_acc.file_integer(sizeof(uint32), 0, small);
        } else {
            value = file_acc.file_integer(sizeof(uint32), 0, known_values);
        }
        return value;
    }

    uint32 generate(std::vector<uint32> possible_values) {
        _startof = FTell();
        value = file_acc.file_integer(sizeof(uint32), 0, possible_values);
        return value;
    }
};



class tagAPP12_entry_struct {
    std::vector<tagAPP12_entry_struct*>& instances;

    uint16 tag_var;
    uint16 len_var;
    uint32 value_var;
    uint32 count_var;
    std::string comment_var;
    std::string unknown_var;

public:
    bool tag_exists = false;
    bool len_exists = false;
    bool value_exists = false;
    bool count_exists = false;
    bool comment_exists = false;
    bool unknown_exists = false;

    uint16 tag() {
        assert_cond(tag_exists, "struct field tag does not exist");
        return tag_var;
    }
    uint16 len() {
        assert_cond(len_exists, "struct field len does not exist");
        return len_var;
    }
    uint32 value() {
        assert_cond(value_exists, "struct field value does not exist");
        return value_var;
    }
    uint32 count() {
        assert_cond(count_exists, "struct field count does not exist");
        return count_var;
    }
    std::string comment() {
        assert_cond(comment_exists, "struct field comment does not exist");
        return comment_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tagAPP12_entry_struct& operator () () { return *instances.back(); }
    tagAPP12_entry_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tagAPP12_entry_struct(std::vector<tagAPP12_entry_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tagAPP12_entry_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tagAPP12_entry_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tagAPP12_entry_struct* generate();
};



class APP12 {
    std::vector<APP12*>& instances;

    WORD marker_var;
    WORD szSection_var;
    std::string Ducky_var;
    tagAPP12_entry_struct* entry_var;
    std::string unknown_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool Ducky_exists = false;
    bool entry_exists = false;
    bool unknown_exists = false;

    WORD marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string Ducky() {
        assert_cond(Ducky_exists, "struct field Ducky does not exist");
        return Ducky_var;
    }
    tagAPP12_entry_struct& entry() {
        assert_cond(entry_exists, "struct field entry does not exist");
        return *entry_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }

    
    std::vector<std::string> values5;
    WORD s;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    APP12& operator () () { return *instances.back(); }
    APP12* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    APP12(std::vector<APP12*>& instances) : instances(instances) { instances.push_back(this); }
    ~APP12() {
        if (generated == 2)
            return;
        while (instances.size()) {
            APP12* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    APP12* generate();
};



class tagAPP13_block_struct {
    std::vector<tagAPP13_block_struct*>& instances;

    std::string type_var;
    std::string unknown_var;
    uint16 tag_var;
    uchar namelen_var;
    std::string name_var;
    char padding_var;
    uint32 size_var;
    std::string data_var;

public:
    bool type_exists = false;
    bool unknown_exists = false;
    bool tag_exists = false;
    bool namelen_exists = false;
    bool name_exists = false;
    bool padding_exists = false;
    bool size_exists = false;
    bool data_exists = false;

    std::string type() {
        assert_cond(type_exists, "struct field type does not exist");
        return type_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }
    uint16 tag() {
        assert_cond(tag_exists, "struct field tag does not exist");
        return tag_var;
    }
    uchar namelen() {
        assert_cond(namelen_exists, "struct field namelen does not exist");
        return namelen_var;
    }
    std::string name() {
        assert_cond(name_exists, "struct field name does not exist");
        return name_var;
    }
    char padding() {
        assert_cond(padding_exists, "struct field padding does not exist");
        return padding_var;
    }
    uint32 size() {
        assert_cond(size_exists, "struct field size does not exist");
        return size_var;
    }
    std::string data() {
        assert_cond(data_exists, "struct field data does not exist");
        return data_var;
    }

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    tagAPP13_block_struct& operator () () { return *instances.back(); }
    tagAPP13_block_struct* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    tagAPP13_block_struct(std::vector<tagAPP13_block_struct*>& instances) : instances(instances) { instances.push_back(this); }
    ~tagAPP13_block_struct() {
        if (generated == 2)
            return;
        while (instances.size()) {
            tagAPP13_block_struct* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    tagAPP13_block_struct* generate(int& remainsize);
};



class APP13 {
    std::vector<APP13*>& instances;

    WORD marker_var;
    WORD szSection_var;
    std::string adobe_cm_var;
    uchar AdobeCMType_var;
    std::string unknown_var;
    std::string photoshop30_var;
    tagAPP13_block_struct* block_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool adobe_cm_exists = false;
    bool AdobeCMType_exists = false;
    bool unknown_exists = false;
    bool photoshop30_exists = false;
    bool block_exists = false;

    WORD marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string adobe_cm() {
        assert_cond(adobe_cm_exists, "struct field adobe_cm does not exist");
        return adobe_cm_var;
    }
    uchar AdobeCMType() {
        assert_cond(AdobeCMType_exists, "struct field AdobeCMType does not exist");
        return AdobeCMType_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }
    std::string photoshop30() {
        assert_cond(photoshop30_exists, "struct field photoshop30 does not exist");
        return photoshop30_var;
    }
    tagAPP13_block_struct& block() {
        assert_cond(block_exists, "struct field block does not exist");
        return *block_var;
    }

   
    std::vector<std::string> values9;
    std::vector<std::string> values14;
    int remainsize;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    APP13& operator () () { return *instances.back(); }
    APP13* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    APP13(std::vector<APP13*>& instances) : instances(instances) { instances.push_back(this); }
    ~APP13() {
        if (generated == 2)
            return;
        while (instances.size()) {
            APP13* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    APP13* generate();
};



class APP14 {
    std::vector<APP14*>& instances;

    WORD marker_var;
    WORD szSection_var;
    std::string adobe_var;
    uint16 version_var;
    uint16 flag0_var;
    uint16 flag1_var;
    uchar color_transform_code_var;
    std::string unknown_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool adobe_exists = false;
    bool version_exists = false;
    bool flag0_exists = false;
    bool flag1_exists = false;
    bool color_transform_code_exists = false;
    bool unknown_exists = false;

    WORD marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string adobe() {
        assert_cond(adobe_exists, "struct field adobe does not exist");
        return adobe_var;
    }
    uint16 version() {
        assert_cond(version_exists, "struct field version does not exist");
        return version_var;
    }
    uint16 flag0() {
        assert_cond(flag0_exists, "struct field flag0 does not exist");
        return flag0_var;
    }
    uint16 flag1() {
        assert_cond(flag1_exists, "struct field flag1 does not exist");
        return flag1_var;
    }
    uchar color_transform_code() {
        assert_cond(color_transform_code_exists, "struct field color_transform_code does not exist");
        return color_transform_code_var;
    }
    std::string unknown() {
        assert_cond(unknown_exists, "struct field unknown does not exist");
        return unknown_var;
    }

    
    std::vector<std::string> values5;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    APP14& operator () () { return *instances.back(); }
    APP14* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    APP14(std::vector<APP14*>& instances) : instances(instances) { instances.push_back(this); }
    ~APP14() {
        if (generated == 2)
            return;
        while (instances.size()) {
            APP14* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    APP14* generate();
};



class COMMENT {
    std::vector<COMMENT*>& instances;

    WORD CommentMarker_var;
    WORD szSection_var;
    std::string comment_var;

public:
    bool CommentMarker_exists = false;
    bool szSection_exists = false;
    bool comment_exists = false;

    WORD CommentMarker() {
        assert_cond(CommentMarker_exists, "struct field CommentMarker does not exist");
        return CommentMarker_var;
    }
    WORD szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    std::string comment() {
        assert_cond(comment_exists, "struct field comment does not exist");
        return comment_var;
    }

    
    std::string comments;
    int i;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    COMMENT& operator () () { return *instances.back(); }
    COMMENT* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    COMMENT(std::vector<COMMENT*>& instances) : instances(instances) { instances.push_back(this); }
    ~COMMENT() {
        if (generated == 2)
            return;
        while (instances.size()) {
            COMMENT* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    COMMENT* generate();
};



class Huffmann_Table {
    std::vector<Huffmann_Table*>& instances;

    ubyte htInfo_var;
    ubyte lengthEntry_var;
    ubyte random_var;
    ubyte HTV_var;

public:
    bool htInfo_exists = false;
    bool lengthEntry_exists = false;
    bool random_exists = false;
    bool HTV_exists = false;

    ubyte htInfo() {
        assert_cond(htInfo_exists, "struct field htInfo does not exist");
        return htInfo_var;
    }
    ubyte lengthEntry() {
        assert_cond(lengthEntry_exists, "struct field lengthEntry does not exist");
        return lengthEntry_var;
    }
    ubyte random() {
        assert_cond(random_exists, "struct field random does not exist");
        return random_var;
    }
    ubyte HTV() {
        assert_cond(HTV_exists, "struct field HTV does not exist");
        return HTV_var;
    }

    
    uint16 i;
    uint16 sum;
    ubyte tmpByte;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    Huffmann_Table& operator () () { return *instances.back(); }
    Huffmann_Table* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    Huffmann_Table(std::vector<Huffmann_Table*>& instances) : instances(instances) { instances.push_back(this); }
    ~Huffmann_Table() {
        if (generated == 2)
            return;
        while (instances.size()) {
            Huffmann_Table* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    Huffmann_Table* generate();
};



class DHT {
    std::vector<DHT*>& instances;

    uint16 marker_var;
    uint16 szSection_var;
    Huffmann_Table* huff_table_var;
    uint16 newSize_var;

public:
    bool marker_exists = false;
    bool szSection_exists = false;
    bool huff_table_exists = false;
    bool newSize_exists = false;

    uint16 marker() {
        assert_cond(marker_exists, "struct field marker does not exist");
        return marker_var;
    }
    uint16 szSection() {
        assert_cond(szSection_exists, "struct field szSection does not exist");
        return szSection_var;
    }
    Huffmann_Table& huff_table() {
        assert_cond(huff_table_exists, "struct field huff_table does not exist");
        return *huff_table_var;
    }
    uint16 newSize() {
        assert_cond(newSize_exists, "struct field newSize does not exist");
        return newSize_var;
    }

   
    uint16 sizePos;
    uint16 curPos;
    uint16 size;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    DHT& operator () () { return *instances.back(); }
    DHT* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    DHT(std::vector<DHT*>& instances) : instances(instances) { instances.push_back(this); }
    ~DHT() {
        if (generated == 2)
            return;
        while (instances.size()) {
            DHT* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    DHT* generate();
};



class JPGFILE {
    std::vector<JPGFILE*>& instances;

    uint16 StartMarker_var;
    COMMENT* comment_var;
    DQT* dqt_var;
    SOFx* sof0_var;
    DHT* dht_var;
    SOS* scanStart_var;
    ubyte scanData_var;

public:
    bool StartMarker_exists = false;
    bool comment_exists = false;
    bool dqt_exists = false;
    bool sof0_exists = false;
    bool dht_exists = false;
    bool scanStart_exists = false;
    bool scanData_exists = false;

    uint16 StartMarker() {
        assert_cond(StartMarker_exists, "struct field StartMarker does not exist");
        return StartMarker_var;
    }
    COMMENT& comment() {
        assert_cond(comment_exists, "struct field comment does not exist");
        return *comment_var;
    }
    DQT& dqt() {
        assert_cond(dqt_exists, "struct field dqt does not exist");
        return *dqt_var;
    }
    SOFx& sof0() {
        assert_cond(sof0_exists, "struct field sof0 does not exist");
        return *sof0_var;
    }
    DHT& dht() {
        assert_cond(dht_exists, "struct field dht does not exist");
        return *dht_var;
    }
    SOS& scanStart() {
        assert_cond(scanStart_exists, "struct field scanStart does not exist");
        return *scanStart_var;
    }
    ubyte scanData() {
        assert_cond(scanData_exists, "struct field scanData does not exist");
        return scanData_var;
    }

   
    int was_bigendian;
    std::vector<ushort> possibleValues;
    ushort nextMarker;
    std::vector<WORD> markers;
    ubyte c;
    byte ammount;
    int dataLen;
    ubyte lastScanData;

    unsigned char generated = 0;
    int64 _startof = 0;
    std::size_t _sizeof = 0;
    JPGFILE& operator () () { return *instances.back(); }
    JPGFILE* operator [] (int index) {
        assert_cond((unsigned)index < instances.size(), "instance index out of bounds");
        return instances[index];
    }
    JPGFILE(std::vector<JPGFILE*>& instances) : instances(instances) { instances.push_back(this); }
    ~JPGFILE() {
        if (generated == 2)
            return;
        while (instances.size()) {
            JPGFILE* instance = instances.back();
            instances.pop_back();
            if (instance->generated == 2)
                delete instance;
        }
    }
    JPGFILE* generate();
};

JPGFILE& IFD::CasioMakerThumbnail() {
    assert_cond(CasioMakerThumbnail_exists, "struct field CasioMakerThumbnail does not exist");
    return *CasioMakerThumbnail_var;
}
JPGFILE& APP1::thumbnail() {
    assert_cond(thumbnail_exists, "struct field thumbnail does not exist");
    return *thumbnail_var;
}
std::vector<byte> ReadByteInitValues;
std::vector<ubyte> ReadUByteInitValues;
std::vector<short> ReadShortInitValues;
std::vector<ushort> ReadUShortInitValues;
std::vector<int> ReadIntInitValues;
std::vector<uint> ReadUIntInitValues;
std::vector<int64> ReadQuadInitValues;
std::vector<uint64> ReadUQuadInitValues;
std::vector<int64> ReadInt64InitValues;
std::vector<uint64> ReadUInt64InitValues;
std::vector<hfloat> ReadHFloatInitValues;
std::vector<float> ReadFloatInitValues;
std::vector<double> ReadDoubleInitValues;
std::vector<std::string> ReadBytesInitValues;


std::vector<APP0*> APP0_app0_instances;
std::vector<tgDIRENTRY_strAscii_struct*> tgDIRENTRY_strAscii_struct_strAscii_instances;
std::vector<StrAscii1*> StrAscii1_strAscii__instances;
std::vector<tgDIRENTRY_strSByte_struct*> tgDIRENTRY_strSByte_struct_strSByte_instances;
std::vector<tgDIRENTRY_strSShort_struct*> tgDIRENTRY_strSShort_struct_strSShort_instances;
std::vector<DIRENTRY*> DIRENTRY_dirEntry_element_instances;
std::vector<StrAscii*> StrAscii_strAscii___instances;
std::vector<tgIFD_strAscii_struct*> tgIFD_strAscii_struct_strAscii____instances;
std::vector<tgIFD_strUShort_struct*> tgIFD_strUShort_struct_strUShort_instances;
std::vector<tgIFD_strULong_struct*> tgIFD_strULong_struct_strULong_instances;
std::vector<URatio_uRValue_struct*> URatio_uRValue_struct_uRValue_element_instances;
std::vector<URatio*> URatio_strURatio_instances;
std::vector<tgIFD_strSByte_struct*> tgIFD_strSByte_struct_strSByte__instances;
std::vector<tgIFD_strSShort_struct*> tgIFD_strSShort_struct_strSShort__instances;
std::vector<tgIFD_strSLong_struct*> tgIFD_strSLong_struct_strSLong_instances;
std::vector<strSRatio_struct_siRValue_struct*> strSRatio_struct_siRValue_struct_siRValue_element_instances;
std::vector<tgIFD_strSRatio_struct*> tgIFD_strSRatio_struct_strSRatio_instances;
std::vector<tgIFD_strsFloat_struct*> tgIFD_strsFloat_struct_strsFloat_instances;
std::vector<tgIFD_strdFloat_struct*> tgIFD_strdFloat_struct_strdFloat_instances;
std::vector<QuanTable*> QuanTable_qtable_instances;
std::vector<DQT*> DQT_dqt_instances;
std::vector<COMPSOF*> COMPSOF_comp_sof_instances;
std::vector<SOFx*> SOFx_sof0_instances;
std::vector<COMPSOS*> COMPSOS_comp_instances;
std::vector<SOS*> SOS_scanStart_instances;
std::vector<IFD*> IFD_subDir_instances;
std::vector<IFD*> IFD_CasioIFD_instances;
std::vector<IFD*> IFD_ifdMainImage_instances;
std::vector<IFD*> IFD_ifdThumbnailImage_instances;
std::vector<APP1*> APP1_app1_instances;
std::vector<APP2*> APP2_app2_instances;
std::vector<tagAPP12_entry_struct*> tagAPP12_entry_struct_entry_instances;
std::vector<APP12*> APP12_app0__instances;
std::vector<tagAPP13_block_struct*> tagAPP13_block_struct_block_instances;
std::vector<APP13*> APP13_app1__instances;
std::vector<APP14*> APP14_app2__instances;
std::vector<COMMENT*> COMMENT_comment__instances;
std::vector<Huffmann_Table*> Huffmann_Table_huff_table_instances;
std::vector<DHT*> DHT_dht_instances;
std::vector<JPGFILE*> JPGFILE_CasioMakerThumbnail_instances;
std::vector<JPGFILE*> JPGFILE_thumbnail_instances;
std::vector<JPGFILE*> JPGFILE_jpgfile_instances;


std::unordered_map<std::string, std::string> variable_types = { { "StartMarker", "uint16_class" }, { "marker", "uint16_class" }, { "szSection", "WORD_class" }, { "App0Type", "char_array_class" }, { "versionHigh", "byte_class" }, { "versionLow", "byte_class" }, { "units", "byte_class" }, { "Xdensity", "uint16_class" }, { "Ydensity", "uint16_class" }, { "xThumbnail", "byte_class" }, { "yThumbnail", "byte_class" }, { "app0", "APP0" }, { "EXIF", "char_array_class" }, { "align", "byte_array_class" }, { "tagMark", "WORD_class" }, { "offsetFirstIFD", "DWORD_class" }, { "nDirEntry", "WORD_class" }, { "tagNumber", "CasioTag2" }, { "dataFormat", "DataFormat" }, { "nComponent", "DWORD_class" }, { "ExposureProgram_", "ExposureProgram_enum" }, { "MeteringMode_", "MeteringMode_enum" }, { "LightSource_", "LightSource_enum" }, { "unused", "short_bitfield9" }, { "red_eye_mode", "short_bitfield1" }, { "flash_function", "short_bitfield1" }, { "flash_mode", "short_bitfield2" }, { "flash_return", "short_bitfield2" }, { "flash_fired", "short_bitfield1" }, { "ExposureMode_", "ExposureMode_enum" }, { "WhiteBalance_", "WhiteBalance_enum" }, { "SceneCaptureType_", "SceneCaptureType_enum" }, { "SubjectDistanceRange_", "SubjectDistanceRange_enum" }, { "oneByteData", "uchar_array_class" }, { "strAscii", "tgDIRENTRY_strAscii_struct" }, { "oneByteData_", "char_array_class" }, { "strAscii_", "StrAscii1" }, { "usValue", "ushort_class" }, { "ulValue", "ulong_class" }, { "sBValue", "char_array_class" }, { "strSByte", "tgDIRENTRY_strSByte_struct" }, { "sisValue", "short_array_class" }, { "strSShort", "tgDIRENTRY_strSShort_struct" }, { "siLValue", "ulong_class" }, { "flValue", "float_class" }, { "padding", "uchar_array_class" }, { "offsetData", "DWORD_class" }, { "dirEntry", "DIRENTRY_array_class" }, { "nextIFDoffset", "DWORD_class" }, { "strAscii__", "StrAscii" }, { "strAscii___", "tgIFD_strAscii_struct" }, { "usValue_", "ushort_array_class" }, { "strUShort", "tgIFD_strUShort_struct" }, { "ulValue_", "ulong_array_class" }, { "strULong", "tgIFD_strULong_struct" }, { "num", "DWORD_class" }, { "den", "DWORD_class" }, { "uRValue", "URatio_uRValue_struct_array_class" }, { "strURatio", "URatio" }, { "strSByte_", "tgIFD_strSByte_struct" }, { "strSShort_", "tgIFD_strSShort_struct" }, { "siLValue_", "ulong_array_class" }, { "strSLong", "tgIFD_strSLong_struct" }, { "num_", "int_class" }, { "den_", "int_class" }, { "siRValue", "strSRatio_struct_siRValue_struct_array_class" }, { "strSRatio", "tgIFD_strSRatio_struct" }, { "flValue_", "float_array_class" }, { "strsFloat", "tgIFD_strsFloat_struct" }, { "dFValue", "double_array_class" }, { "strdFloat", "tgIFD_strdFloat_struct" }, { "Header", "char_array_class" }, { "szSection_", "uint16_class" }, { "PqTq", "uchar_class" }, { "qTable", "byte_array_class" }, { "qTable_", "uint16_array_class" }, { "qtable", "QuanTable" }, { "newSize", "uint16_class" }, { "dqt", "DQT" }, { "precision", "ubyte_class" }, { "Y_image", "WORD_class" }, { "X_image", "WORD_class" }, { "nr_comp", "ubyte_class" }, { "compId", "ubyte_class" }, { "HorzVert", "ubyte_class" }, { "compNr", "ubyte_class" }, { "comp_sof", "COMPSOF" }, { "sof0", "SOFx" }, { "ACDC", "ubyte_class" }, { "comp", "COMPSOS" }, { "Ss", "uchar_class" }, { "Se", "uchar_class" }, { "AhAl", "uchar_class" }, { "scanStart", "SOS" }, { "subDir", "IFD" }, { "CasioIFD", "IFD" }, { "ifdMainImage", "IFD" }, { "ifdThumbnailImage", "IFD" }, { "imageData", "char_array_class" }, { "XAP", "char_array_class" }, { "remain", "char_array_class" }, { "unknown", "char_array_class" }, { "app1", "APP1" }, { "FPXR", "char_array_class" }, { "version", "uchar_class" }, { "ICC_PROFILE", "char_array_class" }, { "block_num", "uchar_class" }, { "block_total", "uchar_class" }, { "data", "char_array_class" }, { "app2", "APP2" }, { "Ducky", "char_array_class" }, { "tag", "tag_enum" }, { "len", "uint16_class" }, { "value", "uint32_class" }, { "count", "uint32_class" }, { "comment", "char_array_class" }, { "entry", "tagAPP12_entry_struct" }, { "app0_", "APP12" }, { "adobe_cm", "char_array_class" }, { "AdobeCMType", "uchar_class" }, { "photoshop30", "char_array_class" }, { "type", "char_array_class" }, { "namelen", "uchar_class" }, { "name", "char_array_class" }, { "padding_", "char_class" }, { "size", "uint32_class" }, { "block", "tagAPP13_block_struct" }, { "app1_", "APP13" }, { "adobe", "char_array_class" }, { "version_", "uint16_class" }, { "flag0", "uint16_class" }, { "flag1", "uint16_class" }, { "color_transform_code", "uchar_class" }, { "app2_", "APP14" }, { "CommentMarker", "M_ID" }, { "comment_", "COMMENT" }, { "htInfo", "ubyte_class" }, { "lengthEntry", "ubyte_class" }, { "random", "ubyte_class" }, { "HTV", "ubyte_class" }, { "huff_table", "Huffmann_Table" }, { "dht", "DHT" }, { "scanData", "ubyte_class" }, { "CasioMakerThumbnail", "JPGFILE" }, { "thumbnail", "JPGFILE" }, { "jpgfile", "JPGFILE" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 0, 0xFF } };

class globals_class {
public:
    int colorId;
    int colorSelect;
    DWORD clr;
     std::vector<DWORD> jetMap;
    std::string CameraMake;
     std::string CameraModel;
  std::string stack_IFD_dirtype;
     ubyte DHTLevel;
     ubyte DQTLevel;
     byte colorFlag;
    uint16_class StartMarker;
    uint16_class marker;
    WORD_class szSection;
    char_class App0Type_element;
    char_array_class App0Type;
    byte_class versionHigh;
    byte_class versionLow;
    byte_class units;
    uint16_class Xdensity;
    uint16_class Ydensity;
    byte_class xThumbnail;
    byte_class yThumbnail;
    APP0 app0;
    char_class EXIF_element;
    char_array_class EXIF;
    byte_class align_element;
    byte_array_class align;
    WORD_class tagMark;
    DWORD_class offsetFirstIFD;
    WORD_class nDirEntry;
    DWORD_class nComponent;
    short_bitfield unused;
    short_bitfield red_eye_mode;
    short_bitfield flash_function;
    short_bitfield flash_mode;
    short_bitfield flash_return;
    short_bitfield flash_fired;
    uchar_class oneByteData_element;
    uchar_array_class oneByteData;
    tgDIRENTRY_strAscii_struct strAscii;
    char_class oneByteData__element;
    char_array_class oneByteData_;
    StrAscii1 strAscii_;
    ushort_class usValue;
    ulong_class ulValue;
    char_class sBValue_element;
    char_array_class sBValue;
    tgDIRENTRY_strSByte_struct strSByte;
    short_class sisValue_element;
    short_array_class sisValue;
    tgDIRENTRY_strSShort_struct strSShort;
    ulong_class siLValue;
    float_class flValue;
    uchar_class padding_element;
    uchar_array_class padding;
    DWORD_class offsetData;
    DIRENTRY dirEntry_element;
    DIRENTRY_array_class dirEntry;
    DWORD_class nextIFDoffset;
    StrAscii strAscii__;
    tgIFD_strAscii_struct strAscii___;
    ushort_class usValue__element;
    ushort_array_class usValue_;
    tgIFD_strUShort_struct strUShort;
    ulong_class ulValue__element;
    ulong_array_class ulValue_;
    tgIFD_strULong_struct strULong;
    DWORD_class num;
    DWORD_class den;
    URatio_uRValue_struct uRValue_element;
    URatio_uRValue_struct_array_class uRValue;
    URatio strURatio;
    tgIFD_strSByte_struct strSByte_;
    tgIFD_strSShort_struct strSShort_;
    ulong_class siLValue__element;
    ulong_array_class siLValue_;
    tgIFD_strSLong_struct strSLong;
    int_class num_;
    int_class den_;
    strSRatio_struct_siRValue_struct siRValue_element;
    strSRatio_struct_siRValue_struct_array_class siRValue;
    tgIFD_strSRatio_struct strSRatio;
    float_class flValue__element;
    float_array_class flValue_;
    tgIFD_strsFloat_struct strsFloat;
    double_class dFValue_element;
    double_array_class dFValue;
    tgIFD_strdFloat_struct strdFloat;
    char_class Header_element;
    char_array_class Header;
    uint16_class szSection_;
    uchar_class PqTq;
    byte_class qTable_element;
    byte_array_class qTable;
    uint16_class qTable__element;
    uint16_array_class qTable_;
    QuanTable qtable;
    uint16_class newSize;
    DQT dqt;
    ubyte_class precision;
    WORD_class Y_image;
    WORD_class X_image;
    ubyte_class nr_comp;
    ubyte_class compId;
    ubyte_class HorzVert;
    ubyte_class compNr;
    COMPSOF comp_sof;
    SOFx sof0;
    ubyte_class ACDC;
    COMPSOS comp;
    uchar_class Ss;
    uchar_class Se;
    uchar_class AhAl;
    SOS scanStart;
    IFD subDir;
    IFD CasioIFD;
    IFD ifdMainImage;
    IFD ifdThumbnailImage;
    char_class imageData_element;
    char_array_class imageData;
    char_class XAP_element;
    char_array_class XAP;
    char_class remain_element;
    char_array_class remain;
    char_class unknown_element;
    char_array_class unknown;
    APP1 app1;
    char_class FPXR_element;
    char_array_class FPXR;
    uchar_class version;
    char_class ICC_PROFILE_element;
    char_array_class ICC_PROFILE;
    uchar_class block_num;
    uchar_class block_total;
    char_class data_element;
    char_array_class data;
    APP2 app2;
    char_class Ducky_element;
    char_array_class Ducky;
    uint16_class len;
    uint32_class value;
    uint32_class count;
    char_class comment_element;
    char_array_class comment;
    tagAPP12_entry_struct entry;
    APP12 app0_;
    char_class adobe_cm_element;
    char_array_class adobe_cm;
    uchar_class AdobeCMType;
    char_class photoshop30_element;
    char_array_class photoshop30;
    char_class type_element;
    char_array_class type;
    uchar_class namelen;
    char_class name_element;
    char_array_class name;
    char_class padding_;
    uint32_class size;
    tagAPP13_block_struct block;
    APP13 app1_;
    char_class adobe_element;
    char_array_class adobe;
    uint16_class version_;
    uint16_class flag0;
    uint16_class flag1;
    uchar_class color_transform_code;
    APP14 app2_;
    COMMENT comment_;
    ubyte_class htInfo;
    ubyte_class lengthEntry;
    ubyte_class random;
    ubyte_class HTV;
    Huffmann_Table huff_table;
    DHT dht;
    ubyte_class scanData;
    JPGFILE CasioMakerThumbnail;
    JPGFILE thumbnail;
    JPGFILE jpgfile;


    globals_class() :
        CameraMake(32, 0),
        CameraModel(40, 0),
        StartMarker(1),
        marker(1),
        szSection(1, { 12 }),
        App0Type_element(false),
        App0Type(App0Type_element),
        versionHigh(1),
        versionLow(1),
        units(1),
        Xdensity(1),
        Ydensity(1),
        xThumbnail(1),
        yThumbnail(1),
        app0(APP0_app0_instances),
        EXIF_element(false),
        EXIF(EXIF_element),
        align_element(false),
        align(align_element),
        tagMark(1),
        offsetFirstIFD(1, { 8 }),
        nDirEntry(1),
        nComponent(1, { 1 }),
        unused(1),
        red_eye_mode(1),
        flash_function(1),
        flash_mode(1),
        flash_return(1),
        flash_fired(1),
        oneByteData_element(false),
        oneByteData(oneByteData_element),
        strAscii(tgDIRENTRY_strAscii_struct_strAscii_instances),
        oneByteData__element(false),
        oneByteData_(oneByteData__element),
        strAscii_(StrAscii1_strAscii__instances),
        usValue(1),
        ulValue(1),
        sBValue_element(false),
        sBValue(sBValue_element),
        strSByte(tgDIRENTRY_strSByte_struct_strSByte_instances),
        sisValue_element(false),
        sisValue(sisValue_element),
        strSShort(tgDIRENTRY_strSShort_struct_strSShort_instances),
        siLValue(1),
        flValue(1),
        padding_element(false),
        padding(padding_element),
        offsetData(1),
        dirEntry_element(DIRENTRY_dirEntry_element_instances),
        dirEntry(dirEntry_element),
        nextIFDoffset(1),
        strAscii__(StrAscii_strAscii___instances),
        strAscii___(tgIFD_strAscii_struct_strAscii____instances),
        usValue__element(false),
        usValue_(usValue__element),
        strUShort(tgIFD_strUShort_struct_strUShort_instances),
        ulValue__element(false),
        ulValue_(ulValue__element),
        strULong(tgIFD_strULong_struct_strULong_instances),
        num(1),
        den(1),
        uRValue_element(URatio_uRValue_struct_uRValue_element_instances),
        uRValue(uRValue_element),
        strURatio(URatio_strURatio_instances),
        strSByte_(tgIFD_strSByte_struct_strSByte__instances),
        strSShort_(tgIFD_strSShort_struct_strSShort__instances),
        siLValue__element(false),
        siLValue_(siLValue__element),
        strSLong(tgIFD_strSLong_struct_strSLong_instances),
        num_(1),
        den_(1),
        siRValue_element(strSRatio_struct_siRValue_struct_siRValue_element_instances),
        siRValue(siRValue_element),
        strSRatio(tgIFD_strSRatio_struct_strSRatio_instances),
        flValue__element(false),
        flValue_(flValue__element),
        strsFloat(tgIFD_strsFloat_struct_strsFloat_instances),
        dFValue_element(false),
        dFValue(dFValue_element),
        strdFloat(tgIFD_strdFloat_struct_strdFloat_instances),
        Header_element(false),
        Header(Header_element),
        szSection_(1),
        PqTq(1),
        qTable_element(false),
        qTable(qTable_element),
        qTable__element(false),
        qTable_(qTable__element),
        qtable(QuanTable_qtable_instances),
        newSize(1),
        dqt(DQT_dqt_instances),
        precision(1),
        Y_image(1),
        X_image(1),
        nr_comp(1),
        compId(1),
        HorzVert(1),
        compNr(1),
        comp_sof(COMPSOF_comp_sof_instances),
        sof0(SOFx_sof0_instances),
        ACDC(1),
        comp(COMPSOS_comp_instances),
        Ss(1),
        Se(1),
        AhAl(1),
        scanStart(SOS_scanStart_instances),
        subDir(IFD_subDir_instances),
        CasioIFD(IFD_CasioIFD_instances),
        ifdMainImage(IFD_ifdMainImage_instances),
        ifdThumbnailImage(IFD_ifdThumbnailImage_instances),
        imageData_element(false),
        imageData(imageData_element),
        XAP_element(false),
        XAP(XAP_element),
        remain_element(false),
        remain(remain_element),
        unknown_element(false),
        unknown(unknown_element),
        app1(APP1_app1_instances),
        FPXR_element(false),
        FPXR(FPXR_element),
        version(1),
        ICC_PROFILE_element(false),
        ICC_PROFILE(ICC_PROFILE_element),
        block_num(1),
        block_total(1),
        data_element(false),
        data(data_element),
        app2(APP2_app2_instances),
        Ducky_element(false),
        Ducky(Ducky_element),
        len(1),
        value(1),
        count(1),
        comment_element(false),
        comment(comment_element),
        entry(tagAPP12_entry_struct_entry_instances),
        app0_(APP12_app0__instances),
        adobe_cm_element(false),
        adobe_cm(adobe_cm_element),
        AdobeCMType(1),
        photoshop30_element(false),
        photoshop30(photoshop30_element),
        type_element(false),
        type(type_element, { "8BIM", "PHUT", "DCSR", "AgHg" }),
        namelen(1),
        name_element(false),
        name(name_element),
        padding_(1),
        size(1),
        block(tagAPP13_block_struct_block_instances),
        app1_(APP13_app1__instances),
        adobe_element(false),
        adobe(adobe_element),
        version_(1),
        flag0(1),
        flag1(1),
        color_transform_code(1),
        app2_(APP14_app2__instances),
        comment_(COMMENT_comment__instances),
        htInfo(1),
        lengthEntry(1),
        random(1),
        HTV(1),
        huff_table(Huffmann_Table_huff_table_instances),
        dht(DHT_dht_instances),
        scanData(3),
        CasioMakerThumbnail(JPGFILE_CasioMakerThumbnail_instances),
        thumbnail(JPGFILE_thumbnail_instances),
        jpgfile(JPGFILE_jpgfile_instances)
    {}
};

globals_class* g;

std::string ReadStringN(int64 pos, int n, std::vector<std::string>& possible_values) {
    std::string s;
    ReadBytes(s, pos, n, possible_values);
    return (s);
}
void ChangeColor(byte bChangeColor) {
    if ((bChangeColor == 1)) {
        ::g->colorSelect++;
        ::g->colorId = 0;
    };
    ::g->clr = ::g->jetMap[(((::g->colorSelect % 3) * 6) + (::g->colorId % 6))];
    SetBackColor(::g->clr);
    ::g->colorId++;
}
void Stack_push(std::string& s, int x) {
    s += (char)x;
}
int Stack_top(std::string& s) {
    return (s[(Strlen(s) - 1)]);
}
void Stack_pop(std::string& s) {
    s = SubStr(s, 0, (Strlen(s) - 1));
}

APP0* APP0::generate() {
    if (generated == 1) {
        APP0* new_instance = new APP0(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, ::g->marker.generate({ 65504 }));
    GENERATE_VAR(szSection, ::g->szSection.generate({ 16 }));
    tmp = { std::string("JFIF\0", 5) };
    ReadBytes(chunk_type, FTell(), 5, tmp, tmp);
    GENERATE_VAR(App0Type, ::g->App0Type.generate(5));
    GENERATE_VAR(versionHigh, ::g->versionHigh.generate({ 1 }));
    GENERATE_VAR(versionLow, ::g->versionLow.generate({ 1 }));
    GENERATE_VAR(units, ::g->units.generate({ 1 }));
    GENERATE_VAR(Xdensity, ::g->Xdensity.generate());
    GENERATE_VAR(Ydensity, ::g->Ydensity.generate());
    GENERATE_VAR(xThumbnail, ::g->xThumbnail.generate({ 0 }));
    GENERATE_VAR(yThumbnail, ::g->yThumbnail.generate({ 0 }));

    _sizeof = FTell() - _startof;
    return this;
}


tgDIRENTRY_strAscii_struct* tgDIRENTRY_strAscii_struct::generate() {
    if (generated == 1) {
        tgDIRENTRY_strAscii_struct* new_instance = new tgDIRENTRY_strAscii_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(oneByteData, ::g->oneByteData.generate(::g->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


StrAscii1* StrAscii1::generate() {
    if (generated == 1) {
        StrAscii1* new_instance = new StrAscii1(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(oneByteData, ::g->oneByteData_.generate(::g->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgDIRENTRY_strSByte_struct* tgDIRENTRY_strSByte_struct::generate() {
    if (generated == 1) {
        tgDIRENTRY_strSByte_struct* new_instance = new tgDIRENTRY_strSByte_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(sBValue, ::g->sBValue.generate(::g->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgDIRENTRY_strSShort_struct* tgDIRENTRY_strSShort_struct::generate() {
    if (generated == 1) {
        tgDIRENTRY_strSShort_struct* new_instance = new tgDIRENTRY_strSShort_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(sisValue, ::g->sisValue.generate(::g->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


DIRENTRY* DIRENTRY::generate() {
    if (generated == 1) {
        DIRENTRY* new_instance = new DIRENTRY(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    ChangeColor(0);
    switch (Stack_top(::g->stack_IFD_dirtype)) {
    case IFD_TYPE_EXIF:
        GENERATE_VAR(tagNumber, ExifTag_generate());
        break;
    case IFD_TYPE_GEOTAG:
        GENERATE_VAR(tagNumber, GeoTag_generate());
        break;
    case IFD_TYPE_CASIO_QV_R62:
        GENERATE_VAR(tagNumber, CasioTag2_generate());
        break;
    };
    GENERATE_VAR(dataFormat, DataFormat_generate());
    GENERATE_VAR(nComponent, ::g->nComponent.generate());
    j = 0;
    length = -1;
    if (((1 <= dataFormat()) && (dataFormat() < 13))) {
    length = (dataFormatLength[dataFormat()] * nComponent());
    } else {
    ;
    };
    if (((((1 <= dataFormat()) && (dataFormat() < 13)) && (0 <= length)) && (length <= 4))) {
        switch (tagNumber()) {
        case ExposureProgram:
            GENERATE_VAR(ExposureProgram_, ExposureProgram_enum_generate());
            break;
        case MeteringMode:
            GENERATE_VAR(MeteringMode_, MeteringMode_enum_generate());
            break;
        case LightSource:
            GENERATE_VAR(LightSource_, LightSource_enum_generate());
            break;
        case Flash:
            GENERATE_VAR(unused, ::g->unused.generate(9));
            GENERATE_VAR(red_eye_mode, ::g->red_eye_mode.generate(1));
            GENERATE_VAR(flash_function, ::g->flash_function.generate(1));
            GENERATE_VAR(flash_mode, ::g->flash_mode.generate(2));
            GENERATE_VAR(flash_return, ::g->flash_return.generate(2));
            GENERATE_VAR(flash_fired, ::g->flash_fired.generate(1));
            break;
        case ExposureMode:
            GENERATE_VAR(ExposureMode_, ExposureMode_enum_generate());
            break;
        case WhiteBalance:
            GENERATE_VAR(WhiteBalance_, WhiteBalance_enum_generate());
            break;
        case SceneCaptureType:
            GENERATE_VAR(SceneCaptureType_, SceneCaptureType_enum_generate());
            break;
        case SubjectDistanceRange:
            GENERATE_VAR(SubjectDistanceRange_, SubjectDistanceRange_enum_generate());
            break;
        default:
            switch (dataFormat()) {
            case uByte:
                GENERATE(strAscii, ::g->strAscii.generate());
                break;
            case ascString:
                GENERATE(strAscii, ::g->strAscii_.generate());
                break;
            case undefined:
                GENERATE(strAscii, ::g->strAscii.generate());
                break;
            case uShort:
                for (j = 0; (j < nComponent()); j++) {
                    GENERATE_VAR(usValue, ::g->usValue.generate());
                };
                break;
            case uLong1:
                if ((nComponent() == 1)) {
                    GENERATE_VAR(ulValue, ::g->ulValue.generate());
                };
                break;
            case sByte:
                GENERATE_VAR(strSByte, ::g->strSByte.generate());
                break;
            case sShort:
                GENERATE_VAR(strSShort, ::g->strSShort.generate());
                break;
            case sLong:
                if ((nComponent() == 1)) {
                    GENERATE_VAR(siLValue, ::g->siLValue.generate());
                };
                break;
            case sFloat:
                if ((nComponent() == 1)) {
                    GENERATE_VAR(flValue, ::g->flValue.generate());
                };
                break;
            };
            break;
        };
        if ((length != 4)) {
            GENERATE_VAR(padding, ::g->padding.generate((4 - length)));
        };
    } else {
        GENERATE_VAR(offsetData, ::g->offsetData.generate());
    };

    _sizeof = FTell() - _startof;
    return this;
}


StrAscii* StrAscii::generate(int& i) {
    if (generated == 1) {
        StrAscii* new_instance = new StrAscii(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(oneByteData, ::g->oneByteData_.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strAscii_struct* tgIFD_strAscii_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strAscii_struct* new_instance = new tgIFD_strAscii_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(oneByteData, ::g->oneByteData.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strUShort_struct* tgIFD_strUShort_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strUShort_struct* new_instance = new tgIFD_strUShort_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(usValue, ::g->usValue_.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strULong_struct* tgIFD_strULong_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strULong_struct* new_instance = new tgIFD_strULong_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(ulValue, ::g->ulValue_.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


URatio_uRValue_struct* URatio_uRValue_struct::generate() {
    if (generated == 1) {
        URatio_uRValue_struct* new_instance = new URatio_uRValue_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(num, ::g->num.generate());
    GENERATE_VAR(den, ::g->den.generate());

    _sizeof = FTell() - _startof;
    return this;
}


URatio* URatio::generate(int& i) {
    if (generated == 1) {
        URatio* new_instance = new URatio(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(uRValue, ::g->uRValue.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strSByte_struct* tgIFD_strSByte_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strSByte_struct* new_instance = new tgIFD_strSByte_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(sBValue, ::g->sBValue.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strSShort_struct* tgIFD_strSShort_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strSShort_struct* new_instance = new tgIFD_strSShort_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(sisValue, ::g->sisValue.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strSLong_struct* tgIFD_strSLong_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strSLong_struct* new_instance = new tgIFD_strSLong_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(siLValue, ::g->siLValue_.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


strSRatio_struct_siRValue_struct* strSRatio_struct_siRValue_struct::generate() {
    if (generated == 1) {
        strSRatio_struct_siRValue_struct* new_instance = new strSRatio_struct_siRValue_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(num, ::g->num_.generate());
    GENERATE_VAR(den, ::g->den_.generate());

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strSRatio_struct* tgIFD_strSRatio_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strSRatio_struct* new_instance = new tgIFD_strSRatio_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(siRValue, ::g->siRValue.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strsFloat_struct* tgIFD_strsFloat_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strsFloat_struct* new_instance = new tgIFD_strsFloat_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(flValue, ::g->flValue_.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


tgIFD_strdFloat_struct* tgIFD_strdFloat_struct::generate(int& i) {
    if (generated == 1) {
        tgIFD_strdFloat_struct* new_instance = new tgIFD_strdFloat_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(i);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(dFValue, ::g->dFValue.generate(::g->dirEntry()[i]->nComponent()));

    _sizeof = FTell() - _startof;
    return this;
}


QuanTable* QuanTable::generate() {
    if (generated == 1) {
        QuanTable* new_instance = new QuanTable(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    availableA = (0 + ::g->DQTLevel);
    availableB = (16 + ::g->DQTLevel);
    GENERATE_VAR(PqTq, ::g->PqTq.generate({ availableA, availableB }));
    if ((PqTq() < 16)) {
        GENERATE(qTable, ::g->qTable.generate(64));
    } else {
        GENERATE(qTable, ::g->qTable_.generate(64));
    };

    _sizeof = FTell() - _startof;
    return this;
}


DQT* DQT::generate() {
    if (generated == 1) {
        DQT* new_instance = new DQT(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, ::g->marker.generate({ 65499 }));
    sizePos = FTell();
    GENERATE_VAR(szSection, ::g->szSection_.generate());
    ChangeColor(0);
    GENERATE_VAR(qtable, ::g->qtable.generate());
    curPos = FTell();
    FSeek(sizePos);
    size = (curPos - sizePos);
    GENERATE_VAR(newSize, ::g->newSize.generate({ size }));
    FSeek(curPos);
    ::g->DQTLevel = 1;

    _sizeof = FTell() - _startof;
    return this;
}


COMPSOF* COMPSOF::generate(ubyte& c) {
    if (generated == 1) {
        COMPSOF* new_instance = new COMPSOF(instances);
        new_instance->generated = 2;
        return new_instance->generate(c);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(compId, ::g->compId.generate({ c }));
    GENERATE_VAR(HorzVert, ::g->HorzVert.generate({ 17 }));
    GENERATE_VAR(compNr, ::g->compNr.generate({ 0 }));

    _sizeof = FTell() - _startof;
    return this;
}


SOFx* SOFx::generate() {
    if (generated == 1) {
        SOFx* new_instance = new SOFx(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, ::g->marker.generate({ 65472 }));
    sizePos = FTell();
    GENERATE_VAR(szSection, ::g->szSection_.generate());
    GENERATE_VAR(precision, ::g->precision.generate({ 8 }));
    GENERATE_VAR(Y_image, ::g->Y_image.generate());
    GENERATE_VAR(X_image, ::g->X_image.generate());
    if (::g->colorFlag) {
        GENERATE_VAR(nr_comp, ::g->nr_comp.generate({ 3 }));
    } else {
        GENERATE_VAR(nr_comp, ::g->nr_comp.generate({ 1 }));
    };
    ChangeColor(0);
    c = 1;
    for ( ; (c <= nr_comp()); c++) {
            GENERATE_VAR(comp_sof, ::g->comp_sof.generate(c));
    ;
    };
    curPos = FTell();
    FSeek(sizePos);
    size = (curPos - sizePos);
    GENERATE_VAR(newSize, ::g->newSize.generate({ size }));
    FSeek(curPos);

    _sizeof = FTell() - _startof;
    return this;
}


COMPSOS* COMPSOS::generate(ubyte& c_2) {
    if (generated == 1) {
        COMPSOS* new_instance = new COMPSOS(instances);
        new_instance->generated = 2;
        return new_instance->generate(c_2);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(compId, ::g->compId.generate({ c_2 }));
    GENERATE_VAR(ACDC, ::g->ACDC.generate({ 0 }));

    _sizeof = FTell() - _startof;
    return this;
}


SOS* SOS::generate() {
    if (generated == 1) {
        SOS* new_instance = new SOS(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, ::g->marker.generate({ 65498 }));
    sizePos = FTell();
    GENERATE_VAR(szSection, ::g->szSection.generate());
    if (::g->colorFlag) {
        GENERATE_VAR(nr_comp, ::g->nr_comp.generate({ 3 }));
    } else {
        GENERATE_VAR(nr_comp, ::g->nr_comp.generate({ 1 }));
    };
    ChangeColor(0);
    c_2 = 1;
    for ( ; (c_2 <= nr_comp()); c_2++) {
            GENERATE_VAR(comp, ::g->comp.generate(c_2));
    ;
    };
    GENERATE_VAR(Ss, ::g->Ss.generate({ 0 }));
    GENERATE_VAR(Se, ::g->Se.generate({ 63 }));
    GENERATE_VAR(AhAl, ::g->AhAl.generate({ 0 }));
    curPos = FTell();
    FSeek(sizePos);
    size = (curPos - sizePos);
    GENERATE_VAR(newSize, ::g->newSize.generate({ size }));
    FSeek(curPos);

    _sizeof = FTell() - _startof;
    return this;
}


IFD* IFD::generate(quad& offset) {
    if (generated == 1) {
        IFD* new_instance = new IFD(instances);
        new_instance->generated = 2;
        return new_instance->generate(offset);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(nDirEntry, ::g->nDirEntry.generate());
    GENERATE_VAR(dirEntry, ::g->dirEntry.generate(nDirEntry()));
    GENERATE_VAR(nextIFDoffset, ::g->nextIFDoffset.generate());
    i = 0;
    pos = FTell();
    for (i = 0; (i < nDirEntry()); i++) {
            ChangeColor(0);
        switch (dirEntry()[i]->tagNumber()) {
        case Make:
            values22 = { "CASIO COMPUTER CO.,LTD" };
            ReadBytes(::g->CameraMake, (offset + dirEntry()[i]->offsetData()), dirEntry()[i]->nComponent(), values22);
            Printf("Maker: %s\n", std::string(::g->CameraMake).c_str());
            break;
        case Model:
            values6 = { "QV-R62" };
            ReadBytes(::g->CameraModel, (offset + dirEntry()[i]->offsetData()), dirEntry()[i]->nComponent(), values6);
            Printf("Model: %s\n", std::string(::g->CameraModel).c_str());
            break;
        };
        if (!((1 <= dirEntry()[i]->dataFormat()) && (dirEntry()[i]->dataFormat() < 13))) {
        continue;
        };
        if (((dataFormatLength[dirEntry()[i]->dataFormat()] * dirEntry()[i]->nComponent()) <= 4)) {
            continue;
        };
        FSeek((offset + dirEntry()[i]->offsetData()));
        switch (dirEntry()[i]->tagNumber()) {
        default:
            switch (dirEntry()[i]->dataFormat()) {
            case ascString:
                GENERATE(strAscii, ::g->strAscii__.generate(i));
                break;
            case undefined:
                GENERATE(strAscii, ::g->strAscii___.generate(i));
                break;
            case uShort:
                GENERATE_VAR(strUShort, ::g->strUShort.generate(i));
                break;
            case uLong1:
                GENERATE_VAR(strULong, ::g->strULong.generate(i));
                break;
            case uRatio:
                GENERATE_VAR(strURatio, ::g->strURatio.generate(i));
                break;
            case sByte:
                GENERATE_VAR(strSByte, ::g->strSByte_.generate(i));
                break;
            case sShort:
                GENERATE_VAR(strSShort, ::g->strSShort_.generate(i));
                break;
            case sLong:
                GENERATE_VAR(strSLong, ::g->strSLong.generate(i));
                break;
            case sRatio:
                GENERATE_VAR(strSRatio, ::g->strSRatio.generate(i));
                break;
            case sFloat:
                GENERATE_VAR(strsFloat, ::g->strsFloat.generate(i));
                break;
            case dFloat:
                GENERATE_VAR(strdFloat, ::g->strdFloat.generate(i));
                break;
            };
        };
    ;
    };
    for (i = 0; (i < nDirEntry()); i++) {
            ChangeColor(0);
        switch (dirEntry()[i]->tagNumber()) {
        case ExifOffset:
            FSeek((offset + dirEntry()[i]->ulValue()));
            Stack_push(::g->stack_IFD_dirtype, IFD_TYPE_EXIF);
            GENERATE_VAR(subDir, ::g->subDir.generate(offset));
            Stack_pop(::g->stack_IFD_dirtype);
            break;
        case GPSInfo:
            FSeek((offset + dirEntry()[i]->ulValue()));
            Stack_push(::g->stack_IFD_dirtype, IFD_TYPE_GEOTAG);
            GENERATE_VAR(subDir, ::g->subDir.generate(offset));
            Stack_pop(::g->stack_IFD_dirtype);
            break;
        case InteropOffset:
            FSeek((offset + dirEntry()[i]->ulValue()));
            Stack_push(::g->stack_IFD_dirtype, IFD_TYPE_EXIF);
            GENERATE_VAR(subDir, ::g->subDir.generate(offset));
            Stack_pop(::g->stack_IFD_dirtype);
            break;
        case MakerNote:
            if ((!Strncmp("CASIO COMPUTER CO.,LTD", ::g->CameraMake, 22) && !Strncmp("QV-R62", ::g->CameraModel, 6))) {
                FSeek((offset + dirEntry()[i]->ulValue()));
                GENERATE_VAR(Header, ::g->Header.generate(6));
                Stack_push(::g->stack_IFD_dirtype, IFD_TYPE_CASIO_QV_R62);
                GENERATE_VAR(CasioIFD, ::g->CasioIFD.generate(offset));
                Stack_pop(::g->stack_IFD_dirtype);
            };
            break;
        case CasioPreviewThumbnail:
            FSeek((offset + dirEntry()[i]->ulValue()));
            Printf("Casio Thumbnail Offset = %#Lx\n", (offset + dirEntry()[i]->ulValue()));
            GENERATE_VAR(CasioMakerThumbnail, ::g->CasioMakerThumbnail.generate());
            break;
        };
    ;
    };
    FSeek(pos);

    _sizeof = FTell() - _startof;
    return this;
}


APP1* APP1::generate() {
    if (generated == 1) {
        APP1* new_instance = new APP1(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, M_ID_generate({ 0xFFE0 }));
    GENERATE_VAR(szSection, ::g->szSection.generate());
    values5 = { std::string("Exif\0", 5), "http:" };
    values29 = { std::string("http://ns.adobe.com/xap/1.0/\0", 29) };
    if ((ReadStringN(FTell(), 5, values5) == std::string("Exif\0", 5))) {
        GENERATE_VAR(EXIF, ::g->EXIF.generate(6));
        offset = FTell();
        GENERATE_VAR(align, ::g->align.generate(2));
        if ((align()[0] == 'I')) {
            LittleEndian();
        };
        GENERATE_VAR(tagMark, ::g->tagMark.generate());
        GENERATE_VAR(offsetFirstIFD, ::g->offsetFirstIFD.generate());
        if ((offsetFirstIFD() != 8)) {
        FSeek((offset + offsetFirstIFD()));
        };
        ChangeColor(0);
        Stack_push(::g->stack_IFD_dirtype, IFD_TYPE_EXIF);
        GENERATE_VAR(ifdMainImage, ::g->ifdMainImage.generate(offset));
        Stack_pop(::g->stack_IFD_dirtype);
        if (ifdMainImage().nextIFDoffset()) {
            FSeek((offset + ifdMainImage().nextIFDoffset()));
            ChangeColor(0);
            Stack_push(::g->stack_IFD_dirtype, IFD_TYPE_EXIF);
            GENERATE_VAR(ifdThumbnailImage, ::g->ifdThumbnailImage.generate(offset));
            Stack_pop(::g->stack_IFD_dirtype);
            i = 0;
            thumbOffset = 0;
            thumbLength = 0;
            compression = 10;
            for ( ; (i < ifdThumbnailImage().nDirEntry()); i++) {
                    switch (ifdThumbnailImage().dirEntry()[i]->tagNumber()) {
                case Compression:
                    compression = ifdThumbnailImage().dirEntry()[i]->usValue();
                    break;
                case ThumbnailOffset:
                case StripOffsets:
                    thumbOffset = ifdThumbnailImage().dirEntry()[i]->ulValue();
                    break;
                case ThumbnailLength:
                case StripByteCounts:
                    thumbLength = ifdThumbnailImage().dirEntry()[i]->ulValue();
                    break;
                };
            ;
            };
            if ((thumbLength && thumbOffset)) {
                FSeek((offset + thumbOffset));
                Printf("Thumbnail Offset = %#Lx\n", (offset + thumbOffset));
                if ((compression == 6)) {
                    GENERATE_VAR(thumbnail, ::g->thumbnail.generate());
                } else {
                    GENERATE_VAR(imageData, ::g->imageData.generate(thumbLength));
                };
            };
        };
        FSeek(((offset + szSection()) - 8));
        if ((align()[0] == 'I')) {
            BigEndian();
        };
    } else {
    if ((ReadStringN(FTell(), 29, values29) == std::string("http://ns.adobe.com/xap/1.0/\0", 29))) {
        GENERATE_VAR(XAP, ::g->XAP.generate(29));
        GENERATE_VAR(remain, ::g->remain.generate((szSection() - 31)));
    } else {
        GENERATE_VAR(unknown, ::g->unknown.generate((szSection() - 2)));
    };
    };

    _sizeof = FTell() - _startof;
    return this;
}


APP2* APP2::generate() {
    if (generated == 1) {
        APP2* new_instance = new APP2(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, M_ID_generate({ 0xFFE2 }));
    GENERATE_VAR(szSection, ::g->szSection.generate());
    values5 = { std::string("FPXR\0", 5), "ICC_P" };
    values12 = { std::string("ICC_PROFILE\0", 12) };
    if ((ReadStringN(FTell(), 5, values5) == std::string("FPXR\0", 5))) {
        GENERATE_VAR(FPXR, ::g->FPXR.generate(5));
        GENERATE_VAR(version, ::g->version.generate());
        GENERATE_VAR(remain, ::g->remain.generate((szSection() - 8)));
    } else {
    if ((ReadStringN(FTell(), 12, values12) == std::string("ICC_PROFILE\0", 12))) {
        GENERATE_VAR(ICC_PROFILE, ::g->ICC_PROFILE.generate(12));
        GENERATE_VAR(block_num, ::g->block_num.generate());
        GENERATE_VAR(block_total, ::g->block_total.generate());
        GENERATE_VAR(data, ::g->data.generate((szSection() - 16)));
    } else {
        GENERATE_VAR(unknown, ::g->unknown.generate((szSection() - 2)));
    };
    };

    _sizeof = FTell() - _startof;
    return this;
}


tagAPP12_entry_struct* tagAPP12_entry_struct::generate() {
do {
    if (generated == 1) {
        tagAPP12_entry_struct* new_instance = new tagAPP12_entry_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(tag, tag_enum_generate());
    if ((tag() == DK_End)) {
    break;
    };
    GENERATE_VAR(len, ::g->len.generate());
    switch (tag()) {
    case DK_End:
        break;
    case DK_Quality:
        GENERATE_VAR(value, ::g->value.generate());
        break;
    case DK_Comment:
        GENERATE_VAR(count, ::g->count.generate());
        GENERATE_VAR(comment, ::g->comment.generate((len() - 4)));
        break;
    case DK_Copyright:
        GENERATE_VAR(count, ::g->count.generate());
        GENERATE_VAR(comment, ::g->comment.generate((len() - 4)));
        break;
    default:
        GENERATE_VAR(unknown, ::g->unknown.generate(len()));
        break;
    };
} while (false);

    _sizeof = FTell() - _startof;
    return this;
}


APP12* APP12::generate() {
    if (generated == 1) {
        APP12* new_instance = new APP12(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, M_ID_generate());
    GENERATE_VAR(szSection, ::g->szSection.generate());
    values5 = { "Ducky" };
    if ((ReadStringN(FTell(), 5, values5) == "Ducky")) {
        GENERATE_VAR(Ducky, ::g->Ducky.generate(5));
        s = szSection();
        while ((s > 0)) {
            GENERATE_VAR(entry, ::g->entry.generate());
            if ((entry().tag() == DK_End)) {
            break;
            };
            s -= entry()._sizeof;
        };
    } else {
        GENERATE_VAR(unknown, ::g->unknown.generate((szSection() - 2)));
    };

    _sizeof = FTell() - _startof;
    return this;
}


tagAPP13_block_struct* tagAPP13_block_struct::generate(int& remainsize) {
do {
    if (generated == 1) {
        tagAPP13_block_struct* new_instance = new tagAPP13_block_struct(instances);
        new_instance->generated = 2;
        return new_instance->generate(remainsize);
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(type, ::g->type.generate(4));
    if ((type() == "8BIM")) {
    ;
    } else {
    if ((((type() == "PHUT") || (type() == "DCSR")) || (type() == "AgHg"))) {
    ;
    } else {
        GENERATE_VAR(unknown, ::g->unknown.generate((remainsize - 4)));
        break;
    };
    };
    GENERATE_VAR(tag, tag_enum_generate());
    GENERATE_VAR(namelen, ::g->namelen.generate());
    if (namelen()) {
        GENERATE_VAR(name, ::g->name.generate(namelen()));
    };
    if (((namelen() % 2) != 1)) {
        GENERATE_VAR(padding, ::g->padding_.generate());
    };
    GENERATE_VAR(size, ::g->size.generate());
    if (size()) {
        GENERATE_VAR(data, ::g->data.generate(size()));
    };
    if (((size() % 2) != 0)) {
        GENERATE_VAR(padding, ::g->padding_.generate());
    };
} while (false);

    _sizeof = FTell() - _startof;
    return this;
}


APP13* APP13::generate() {
    if (generated == 1) {
        APP13* new_instance = new APP13(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, M_ID_generate());
    GENERATE_VAR(szSection, ::g->szSection.generate());
    values9 = { std::string("Adobe_CM\0", 9), "Photoshop" };
    values14 = { std::string("Photoshop 3.0\0", 14) };
    if ((ReadStringN(FTell(), 9, values9) == std::string("Adobe_CM\0", 9))) {
        GENERATE_VAR(adobe_cm, ::g->adobe_cm.generate(9));
        GENERATE_VAR(AdobeCMType, ::g->AdobeCMType.generate());
        if ((szSection() != 12)) {
            GENERATE_VAR(unknown, ::g->unknown.generate((szSection() - 12)));
        };
    } else {
    if ((ReadStringN(FTell(), 14, values14) == std::string("Photoshop 3.0\0", 14))) {
        GENERATE_VAR(photoshop30, ::g->photoshop30.generate(14));
        remainsize = (szSection() - 16);
        while ((remainsize > 0)) {
            GENERATE_VAR(block, ::g->block.generate(remainsize));
            remainsize -= block()._sizeof;
        };
    } else {
        GENERATE_VAR(unknown, ::g->unknown.generate((szSection() - 2)));
    };
    };

    _sizeof = FTell() - _startof;
    return this;
}


APP14* APP14::generate() {
    if (generated == 1) {
        APP14* new_instance = new APP14(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, M_ID_generate());
    GENERATE_VAR(szSection, ::g->szSection.generate());
    values5 = { "Adobe" };
    if ((ReadStringN(FTell(), 5, values5) == "Adobe")) {
        GENERATE_VAR(adobe, ::g->adobe.generate(5));
        GENERATE_VAR(version, ::g->version_.generate());
        GENERATE_VAR(flag0, ::g->flag0.generate());
        GENERATE_VAR(flag1, ::g->flag1.generate());
        GENERATE_VAR(color_transform_code, ::g->color_transform_code.generate());
        if ((FTell() < (szSection() + ::g->szSection._startof))) {
            GENERATE_VAR(unknown, ::g->unknown.generate(((szSection() + ::g->szSection._startof) - FTell())));
        };
    } else {
        GENERATE_VAR(unknown, ::g->unknown.generate((szSection() - 2)));
    };

    _sizeof = FTell() - _startof;
    return this;
}


COMMENT* COMMENT::generate() {
    if (generated == 1) {
        COMMENT* new_instance = new COMMENT(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(CommentMarker, M_ID_generate());
    GENERATE_VAR(szSection, ::g->szSection.generate());
    GENERATE_VAR(comment, ::g->comment.generate((szSection() - 2)));
    comments = { 0 };
    i = 0;
    Memcpy(comments, comment(), (szSection() - 2));
    for (i = 0; (i < (szSection() - 1)); i++) {
            if ((comments[i] == 0)) {
        comments[i] = 'x';
        };
    ;
    };
    comments[(szSection() - 2)] = 0;
    Printf("\nCOMMENT :\n%s\n\n", std::string(comments).c_str());

    _sizeof = FTell() - _startof;
    return this;
}


Huffmann_Table* Huffmann_Table::generate() {
    if (generated == 1) {
        Huffmann_Table* new_instance = new Huffmann_Table(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(htInfo, ::g->htInfo.generate({ ::g->DHTLevel }));
    sum = 0;
    for (i = 0; (i < 16); i++) {
            GENERATE_VAR(lengthEntry, ::g->lengthEntry.generate({ 1 }));
        sum = (sum + lengthEntry());
    ;
    };
    for (i = 0; (i < sum); i++) {
            GENERATE_VAR(random, ::g->random.generate());
        if ((::g->DHTLevel < 2)) {
            FSeek((FTell() - 1));
            tmpByte = (random() % 16);
            GENERATE_VAR(HTV, ::g->HTV.generate({ tmpByte }));
        };
    ;
    };

    _sizeof = FTell() - _startof;
    return this;
}


DHT* DHT::generate() {
    if (generated == 1) {
        DHT* new_instance = new DHT(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    GENERATE_VAR(marker, ::g->marker.generate({ 65476 }));
    sizePos = FTell();
    GENERATE_VAR(szSection, ::g->szSection_.generate());
    ChangeColor(0);
    GENERATE_VAR(huff_table, ::g->huff_table.generate());
    switch (::g->DHTLevel) {
    case 0:
        ::g->DHTLevel = 16;
        break;
    case 16:
        ::g->DHTLevel = 1;
        break;
    case 1:
        ::g->DHTLevel = 17;
        break;
    default:
        ::g->DHTLevel = 0;
        break;
    };
    curPos = FTell();
    FSeek(sizePos);
    size = (curPos - sizePos);
    GENERATE_VAR(newSize, ::g->newSize.generate({ size }));
    FSeek(curPos);

    _sizeof = FTell() - _startof;
    return this;
}


JPGFILE* JPGFILE::generate() {
    if (generated == 1) {
        JPGFILE* new_instance = new JPGFILE(instances);
        new_instance->generated = 2;
        return new_instance->generate();
    }
    if (!generated)
        generated = 1;
    _startof = FTell();

    was_bigendian = IsBigEndian();
    BigEndian();
    GENERATE_VAR(StartMarker, ::g->StartMarker.generate({ M_SOI }));
    possibleValues = { M_APP0, M_DQT };
    while ((ReadUShort(FTell(), possibleValues) != M_DQT)) {
        nextMarker = ReadUShort(FTell(), possibleValues);
        switch (nextMarker) {
        case M_APP0:
            GENERATE(app0, ::g->app0.generate());
            break;
        case M_APP1:
            GENERATE(app1, ::g->app1.generate());
            break;
        case M_APP2:
            GENERATE(app2, ::g->app2.generate());
            break;
        case M_APP12:
            GENERATE(app0, ::g->app0_.generate());
            break;
        case M_APP13:
            GENERATE(app1, ::g->app1_.generate());
            break;
        case M_APP14:
            GENERATE(app2, ::g->app2_.generate());
            break;
        case M_COMM:
            GENERATE_VAR(comment, ::g->comment_.generate());
            break;
        };
        VectorRemove(possibleValues, { nextMarker });
    };
    GENERATE_VAR(dqt, ::g->dqt.generate());
    markers = { M_SOF0, M_DQT };
    if ((ReadUShort(FTell(), markers) == M_DQT)) {
        ::g->colorFlag = 1;
        GENERATE_VAR(dqt, ::g->dqt.generate());
    };
    GENERATE_VAR(sof0, ::g->sof0.generate());
    c = 0;
    ammount = 2;
    if (::g->colorFlag) {
    ammount = 4;
    };
    for ( ; (c < ammount); c++) {
        GENERATE_VAR(dht, ::g->dht.generate());
    };
    GENERATE_VAR(scanStart, ::g->scanStart.generate());
    Printf("Start of Scan Marker\n");
    dataLen = 0;
    lastScanData = 0;
    while (true) {
        if ((dataLen < 1024)) {
            GENERATE_VAR(scanData, ::g->scanData.generate());
        } else {
            GENERATE_VAR(scanData, ::g->scanData.generate({ 0xFF, 0xD9 }));
        };
        if (((lastScanData == 0xFF) && (scanData() == 0xD9))) {
        break;
        };
        lastScanData = scanData();
        ++dataLen;
    };
    if (!was_bigendian) {
    LittleEndian();
    };

    _sizeof = FTell() - _startof;
    return this;
}



void jpg_generate_file() {
    ::g = new globals_class();

    LittleEndian();
    BitfieldLeftToRight();
    BigEndian();
    BitfieldLeftToRight();
    ::g->colorId = 0;
    ::g->colorSelect = 0;
    ::g->clr = 0;
    ::g->jetMap = { 0x0000cc, 0x0000ff, 0x0033ff, 0x0066ff, 0x0099ff, 0x00ccff, 0x00ffff, 0x33ffcc, 0x66ff99, 0x99ff66, 0xccff33, 0xffff00, 0xffcc00, 0xff9900, 0xff6600, 0xff3300, 0xff0000, 0xcc0000 };
    ::g->stack_IFD_dirtype = "";
    ::g->DHTLevel = 0;
    ::g->DQTLevel = 0;
    SetBackColor(::g->jetMap[0]);
    ::g->colorFlag = 0;
    GENERATE(jpgfile, ::g->jpgfile.generate());

    file_acc.finish();
    jpg_delete_globals();
}

void jpg_delete_globals() { delete ::g; }

*/
