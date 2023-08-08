
#ifndef _MV_OBSOLETE_CAM_PARAMS_H_
#define _MV_OBSOLETE_CAM_PARAMS_H_

#include "PixelType.h"

/// \~chinese ���֡����Ϣ             \~english Output Frame Information
typedef struct _MV_FRAME_OUT_INFO_
{
    unsigned short      nWidth;             ///< [OUT]  \~chinese ͼ���            \~english Image Width
    unsigned short      nHeight;            ///< [OUT]  \~chinese ͼ���            \~english Image Height
    enum MvGvspPixelType    enPixelType;    ///< [OUT]  \~chinese ���ظ�ʽ          \~english Pixel Type

    unsigned int        nFrameNum;          ///< [OUT]  \~chinese ֡��              \~english Frame Number
    unsigned int        nDevTimeStampHigh;  ///< [OUT]  \~chinese ʱ�����32λ      \~english Timestamp high 32 bits
    unsigned int        nDevTimeStampLow;   ///< [OUT]  \~chinese ʱ�����32λ      \~english Timestamp low 32 bits
    unsigned int        nReserved0;         ///< [OUT]  \~chinese ������8�ֽڶ���   \~english Reserved, 8-byte aligned
    int64_t             nHostTimeStamp;     ///< [OUT]  \~chinese �������ɵ�ʱ���  \~english Host-generated timestamp

    unsigned int        nFrameLen;

    unsigned int        nLostPacket;  // ��֡������
    unsigned int        nReserved[2];
}MV_FRAME_OUT_INFO;

/// \~chinese ����ͼƬ����            \~english Save image type
typedef struct _MV_SAVE_IMAGE_PARAM_T_
{
    unsigned char*      pData;              ///< [IN]   \~chinese �������ݻ���      \~english Input Data Buffer
    unsigned int        nDataLen;           ///< [IN]   \~chinese �������ݴ�С      \~english Input Data Size
    enum MvGvspPixelType    enPixelType;    ///< [IN]   \~chinese �������ظ�ʽ      \~english Input Data Pixel Format
    unsigned short      nWidth;             ///< [IN]   \~chinese ͼ���            \~english Image Width
    unsigned short      nHeight;            ///< [IN]   \~chinese ͼ���            \~english Image Height

    unsigned char*      pImageBuffer;       ///< [OUT]  \~chinese ���ͼƬ����      \~english Output Image Buffer
    unsigned int        nImageLen;          ///< [OUT]  \~chinese ���ͼƬ��С      \~english Output Image Size
    unsigned int        nBufferSize;        ///< [IN]   \~chinese �ṩ�������������С  \~english Output buffer size provided
    enum MV_SAVE_IAMGE_TYPE enImageType;    ///< [IN]   \~chinese ���ͼƬ��ʽ      \~english Output Image Format

}MV_SAVE_IMAGE_PARAM;

typedef struct _MV_IMAGE_BASIC_INFO_
{
    unsigned short      nWidthValue;
    unsigned short      nWidthMin;
    unsigned int        nWidthMax;
    unsigned int        nWidthInc;

    unsigned int        nHeightValue;
    unsigned int        nHeightMin;
    unsigned int        nHeightMax;
    unsigned int        nHeightInc;

    float               fFrameRateValue;
    float               fFrameRateMin;
    float               fFrameRateMax;

    unsigned int        enPixelType;        ///< [OUT]  \~chinese ��ǰ�����ظ�ʽ    \~english Current pixel format
    unsigned int        nSupportedPixelFmtNum;  ///< [OUT]  \~chinese ֧�ֵ����ظ�ʽ����    \~english Support pixel format
    unsigned int        enPixelList[MV_MAX_XML_SYMBOLIC_NUM];
    unsigned int        nReserved[8];

}MV_IMAGE_BASIC_INFO;


/// \~chinese ������������    \~english Noise feature type
typedef enum _MV_CC_BAYER_NOISE_FEATURE_TYPE
{
    MV_CC_BAYER_NOISE_FEATURE_TYPE_INVALID = 0, ///<        \~chinese ��Чֵ                        \~english Invalid
    MV_CC_BAYER_NOISE_FEATURE_TYPE_PROFILE = 1, ///<        \~chinese ��������                      \~english Noise curve
    MV_CC_BAYER_NOISE_FEATURE_TYPE_LEVEL   = 2, ///<        \~chinese ����ˮƽ                      \~english Noise level
    MV_CC_BAYER_NOISE_FEATURE_TYPE_DEFAULT = 1, ///<        \~chinese Ĭ��ֵ                        \~english Default

}MV_CC_BAYER_NOISE_FEATURE_TYPE;

/// \~chinese Bayer��ʽ����������Ϣ    \~english Denoise profile info
typedef struct _MV_CC_BAYER_NOISE_PROFILE_INFO_T_
{
    unsigned int        nVersion;           ///<  \~chinese �汾                           \~english version
    MV_CC_BAYER_NOISE_FEATURE_TYPE enNoiseFeatureType;  ///<  \~chinese ������������       \~english noise feature type
    enum MvGvspPixelType    enPixelType;    ///<  \~chinese ͼ���ʽ                       \~english image format
    int                 nNoiseLevel;        ///<  \~chinese ƽ������ˮƽ                   \~english noise level
    unsigned int        nCurvePointNum;     ///<  \~chinese ���ߵ���                       \~english curve point number
    int*                nNoiseCurve;        ///<  \~chinese ��������                       \~english noise curve
    int*                nLumCurve;          ///<  \~chinese ��������                       \~english luminance curve

    unsigned int        nRes[8];            ///<       \~chinese Ԥ��                           \~english Reserved

}MV_CC_BAYER_NOISE_PROFILE_INFO;

/// \~chinese Bayer��ʽ�������Ʋ���    \~english Bayer noise estimate param
typedef struct _MV_CC_BAYER_NOISE_ESTIMATE_PARAM_T_
{
    unsigned int        nWidth;             ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Width
    unsigned int        nHeight;            ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Height
    enum MvGvspPixelType    enPixelType;    ///< [IN]  \~chinese ���ظ�ʽ                       \~english Pixel format

    unsigned char*      pSrcData;           ///< [IN]  \~chinese �������ݻ���                   \~english Input data buffer
    unsigned int        nSrcDataLen;        ///< [IN]  \~chinese �������ݴ�С                   \~english Input data size

    unsigned int        nNoiseThreshold;    ///< [IN]  \~chinese ������ֵ(0-4095)               \~english Noise Threshold

    unsigned char*      pCurveBuf;          ///< [IN]  \~chinese ���ڴ洢�������ߺ��������ߣ���Ҫ�ⲿ���䣬�����С��4096 * sizeof(int) * 2��     \~english Buffer used to store noise and brightness curves, size:4096 * sizeof(int) * 2)
    MV_CC_BAYER_NOISE_PROFILE_INFO stNoiseProfile; ///< [OUT]  \~chinese ����������Ϣ               \~english Denoise profile

    unsigned int        nThreadNum;         ///< [IN]  \~chinese �߳�������0��ʾ�㷨�����Ӳ������Ӧ��1��ʾ���̣߳�Ĭ�ϣ�������1��ʾ�߳���Ŀ      \~english Thread number, 0 means that the library is adaptive to the hardware, 1 means single thread(Default value), Greater than 1 indicates the number of threads

    unsigned int        nRes[8];            ///<       \~chinese Ԥ��                           \~english Reserved

}MV_CC_BAYER_NOISE_ESTIMATE_PARAM;

/// \~chinese Bayer��ʽ���������    \~english Bayer spatial Denoise param
typedef struct _MV_CC_BAYER_SPATIAL_DENOISE_PARAM_T_
{
    unsigned int        nWidth;             ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Width
    unsigned int        nHeight;            ///< [IN]  \~chinese ͼ���(���ڵ���8)              \~english Height
    enum MvGvspPixelType    enPixelType;        ///< [IN]  \~chinese ���ظ�ʽ                       \~english Pixel format

    unsigned char*      pSrcData;           ///< [IN]  \~chinese �������ݻ���                   \~english Input data buffer
    unsigned int        nSrcDataLen;        ///< [IN]  \~chinese �������ݴ�С                   \~english Input data size

    unsigned char*      pDstBuf;            ///< [OUT] \~chinese �������������               \~english Output data buffer
    unsigned int        nDstBufSize;        ///< [IN]  \~chinese �ṩ�������������С           \~english Provided output buffer size
    unsigned int        nDstBufLen;         ///< [OUT] \~chinese ������������ݳ���           \~english Output data length

    MV_CC_BAYER_NOISE_PROFILE_INFO stNoiseProfile; ///< [IN]  \~chinese ����������Ϣ(��Դ����������)   \~english Denoise profile
    unsigned int        nDenoiseStrength;   ///< [IN]  \~chinese ����ǿ��(0-100)                \~english nDenoise Strength   
    unsigned int        nSharpenStrength;   ///< [IN]  \~chinese ��ǿ��(0-32)                 \~english Sharpen Strength
    unsigned int        nNoiseCorrect;      ///< [IN]  \~chinese ����У��ϵ��(0-1280)           \~english Noise Correct  

    unsigned int        nThreadNum;         ///< [IN]  \~chinese �߳�������0��ʾ�㷨�����Ӳ������Ӧ��1��ʾ���̣߳�Ĭ�ϣ�������1��ʾ�߳���Ŀ         \~english Thread number, 0 means that the library is adaptive to the hardware, 1 means single thread(Default value), Greater than 1 indicates the number of threads

    unsigned int        nRes[8];            ///<       \~chinese Ԥ��                           \~english Reserved

}MV_CC_BAYER_SPATIAL_DENOISE_PARAM;

/// \~chinese ĳ���ڵ��Ӧ���ӽڵ�������ֵ    \~english The maximum number of child nodes corresponding to a node
#define MV_MAX_XML_NODE_NUM_C       128

/// \~chinese �ڵ������ַ�����󳤶�            \~english The maximum length of node name string
#define MV_MAX_XML_NODE_STRLEN_C    64

/// \~chinese �ڵ�Stringֵ��󳤶�              \~english The maximum length of Node String
#define MV_MAX_XML_STRVALUE_STRLEN_C 64

/// \~chinese �ڵ������ֶ���󳤶�              \~english The maximum length of the node description field
#define MV_MAX_XML_DISC_STRLEN_C    512

/// \~chinese ���ĵ�Ԫ��                      \~english The maximum number of units
#define MV_MAX_XML_ENTRY_NUM        10

/// \~chinese ���ڵ��������                    \~english The maximum number of parent nodes
#define MV_MAX_XML_PARENTS_NUM      8

/// \~chinese ÿ���Ѿ�ʵ�ֵ�Ԫ�����Ƴ���        \~english The length of the name of each unit that has been implemented
#define MV_MAX_XML_SYMBOLIC_STRLEN_C 64

enum MV_XML_Visibility
{
    V_Beginner      = 0,    ///< Always visible
    V_Expert        = 1,    ///< Visible for experts or Gurus
    V_Guru          = 2,    ///< Visible for Gurus
    V_Invisible     = 3,    ///< Not Visible
    V_Undefined     = 99    ///< Object is not yet initialized
};

/// \~chinese �����ڵ�������� | en:Single Node Basic Attributes
typedef struct _MV_XML_NODE_FEATURE_
{
    enum MV_XML_InterfaceType   enType;                             ///< \~chinese �ڵ�����         \~english Node Type
    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Is visibility
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ�����,Ŀǰ�ݲ�֧��   \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    unsigned int        nReserved[4];
}MV_XML_NODE_FEATURE;

/// \~chinese �ڵ��б� | en:Node List
typedef struct _MV_XML_NODES_LIST_
{
    unsigned int        nNodeNum;       ///< \~chinese �ڵ����             \~english Node Number
    MV_XML_NODE_FEATURE stNodes[MV_MAX_XML_NODE_NUM_C];
}MV_XML_NODES_LIST;

typedef struct _MV_XML_FEATURE_Value_
{
    enum MV_XML_InterfaceType   enType;                             ///< \~chinese �ڵ�����         \~english Node Type
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ�����,Ŀǰ�ݲ�֧��   \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice
    unsigned int        nReserved[4];
}MV_XML_FEATURE_Value;

typedef struct _MV_XML_FEATURE_Base_
{
    enum MV_XML_AccessMode enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
}MV_XML_FEATURE_Base;

typedef struct _MV_XML_FEATURE_Integer_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int64_t             nValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value
    int64_t             nMinValue;                                  ///< \~chinese ��Сֵ           \~english Min Value
    int64_t             nMaxValue;                                  ///< \~chinese ���ֵ           \~english Max Value
    int64_t             nIncrement;                                 ///< \~chinese ����             \~english Increment

    unsigned int        nReserved[4];

}MV_XML_FEATURE_Integer;

typedef struct _MV_XML_FEATURE_Boolean_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    bool                bValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Boolean;

typedef struct _MV_XML_FEATURE_Command_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Command;

typedef struct _MV_XML_FEATURE_Float_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    double              dfValue;                                    ///< \~chinese ��ǰֵ           \~english Current Value
    double              dfMinValue;                                 ///< \~chinese ��Сֵ           \~english Min Value
    double              dfMaxValue;                                 ///< \~chinese ���ֵ           \~english Max Value
    double              dfIncrement;                                ///< \~chinese ����             \~english Increment

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Float;

typedef struct _MV_XML_FEATURE_String_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    char                strValue[MV_MAX_XML_STRVALUE_STRLEN_C];     ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_String;

typedef struct _MV_XML_FEATURE_Register_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int64_t             nAddrValue;                                 ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Register;

typedef struct _MV_XML_FEATURE_Category_
{
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ����� Ŀǰ�ݲ�֧��    \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Category;

typedef struct _MV_XML_FEATURE_EnumEntry_
{
    char                strName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese Ŀǰ�ݲ�֧��     \~english NOT SUPPORT NOW
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];
    int                 bIsImplemented;
    int                 nParentsNum;
    MV_XML_NODE_FEATURE stParentsList[MV_MAX_XML_PARENTS_NUM];

    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    int64_t             nValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value
    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int                 nReserved[8];

}MV_XML_FEATURE_EnumEntry;

typedef struct _MV_XML_FEATURE_Enumeration_
{
    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ����� Ŀǰ�ݲ�֧��    \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    int                 nSymbolicNum;                               ///< \~chinese ymbolic��        \~english Symbolic Number
    char                strCurrentSymbolic[MV_MAX_XML_SYMBOLIC_STRLEN_C];///< \~chinese ��ǰSymbolic����    \~english Current Symbolic Index
    char                strSymbolic[MV_MAX_XML_SYMBOLIC_NUM][MV_MAX_XML_SYMBOLIC_STRLEN_C];
    enum MV_XML_AccessMode   enAccessMode;                          ////< \~chinese ����ģʽ        \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW
    int64_t             nValue;                                     ///< \~chinese ��ǰֵ           \~english Current Value

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Enumeration;

typedef struct _MV_XML_FEATURE_Port_
{
    enum MV_XML_Visibility  enVisivility;                           ///< \~chinese �Ƿ�ɼ�         \~english Visible
    char                strDescription[MV_MAX_XML_DISC_STRLEN_C];   ///< \~chinese �ڵ�����,Ŀǰ�ݲ�֧��    \~english Node Description, NOT SUPPORT NOW
    char                strDisplayName[MV_MAX_XML_NODE_STRLEN_C];   ///< \~chinese ��ʾ����         \~english Display Name
    char                strName[MV_MAX_XML_NODE_STRLEN_C];          ///< \~chinese �ڵ���           \~english Node Name
    char                strToolTip[MV_MAX_XML_DISC_STRLEN_C];       ///< \~chinese ��ʾ             \~english Notice

    enum MV_XML_AccessMode  enAccessMode;                           ///< \~chinese ����ģʽ         \~english Access Mode
    int                 bIsLocked;                                  ///< \~chinese �Ƿ�������0-��1-��,Ŀǰ�ݲ�֧��    \~english Locked. 0-NO; 1-YES, NOT SUPPORT NOW

    unsigned int        nReserved[4];
}MV_XML_FEATURE_Port;

typedef struct _MV_XML_CAMERA_FEATURE_
{
    enum MV_XML_InterfaceType    enType;
    union
    {
        MV_XML_FEATURE_Integer      stIntegerFeature;
        MV_XML_FEATURE_Float        stFloatFeature;
        MV_XML_FEATURE_Enumeration  stEnumerationFeature;
        MV_XML_FEATURE_String       stStringFeature;
    }SpecialFeature;

}MV_XML_CAMERA_FEATURE;

#endif /* _MV_OBSOLETE_CAM_PARAMS_H_ */
