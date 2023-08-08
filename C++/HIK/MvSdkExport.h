#ifndef _MV_SDK_EXPORT_H__
#define _MV_SDK_EXPORT_H__

#include "MvErrorDefine.h"
#include "CameraParams.h"
#include "ObsoleteCamParams.h"

#ifndef MVSDKEXPORT_API

    #ifdef _WIN32
        #if defined(MVSDKEXPORT_EXPORTS)
            #define MVSDKEXPORT_API __declspec(dllexport)
        #else
            #define MVSDKEXPORT_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif

        #ifndef MVSDKEXPORT_API
            #define  MVSDKEXPORT_API
        #endif
    #endif

#endif

#ifndef IN
    #define IN
#endif

#ifndef OUT
    #define OUT
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
/************************************************************************/
/* �豸�Ļ���ָ��Ͳ���                                         		*/
/* Camera basic instructions and operations                             */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡSDK�汾��
 *  @return ����4�ֽڰ汾��
            |��    |��    |����  |  ����|
             8bits  8bits  8bits  8bits
 *  @remarks ���緵��ֵΪ0x01000001����SDK�汾��ΪV1.0.0.1��
 
 *  @~english
 *  @brief  Get SDK Version
 *  @return Always return 4 Bytes of version number 
            |Main    |Sub    |Rev  |  Test|
             8bits  8bits  8bits  8bits
 *  @remarks For example, if the return value is 0x01000001, the SDK version is V1.0.0.1.
 ************************************************************************/
MVSDKEXPORT_API unsigned int __stdcall MV_CC_GetSDKVersion();

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ֧�ֵĴ����
 *  @return ֧�ֵĴ������ 

 *  @~english
 *  @brief  Get supported Transport Layer
 *  @return Supported Transport Layer number
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_EnumerateTls();

/********************************************************************//**
 *  @~chinese
 *  @brief  ö���豸
 *  @param  nTLayerType                 [IN]            ö�ٴ����
 *  @param  pstDevList                  [OUT]           �豸�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �豸�б���ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź����룬\n
             ���龡��������߳�ö�ٲ�����

 *  @~english
 *  @brief  Enumerate Device
 *  @param  nTLayerType                 [IN]            Enumerate TLs
 *  @param  pstDevList                  [OUT]           Device List
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the device list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.\n
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_EnumDevices(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ݳ�������ö���豸
 *  @param  nTLayerType                 [IN]            ö�ٴ����
 *  @param  pstDevList                  [OUT]           �豸�б�
 *  @param  strManufacturerName           [IN]            ��������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �豸�б���ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź����룬\n
             ���龡��������߳�ö�ٲ�����

 *  @~english
 *  @brief  Enumerate device according to manufacture name
 *  @param  nTLayerType                 [IN]            Transmission layer of enumeration
 *  @param  pstDevList                  [OUT]           Device list
 *  @param  strManufacturerName           [IN]            Manufacture Name
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the device list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.\n
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_EnumDevicesEx(IN unsigned int nTLayerType, IN OUT MV_CC_DEVICE_INFO_LIST* pstDevList, IN const char* strManufacturerName);

/********************************************************************//**
 *  @~chinese
 *  @brief  �豸�Ƿ�ɴ�
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @param  nAccessMode                 [IN]            ����Ȩ��
 *  @return �ɴ����true�����ɴ����false
 *  @remarks ��ȡ�豸CCP�Ĵ�����ֵ���жϵ�ǰ״̬�Ƿ����ĳ�ַ���Ȩ�ޡ� \n
             ����豸��֧��MV_ACCESS_ExclusiveWithSwitch��MV_ACCESS_ControlWithSwitch��MV_ACCESS_ControlSwitchEnableWithKey������ģʽ���ӿڷ���false��Ŀǰ�豸��֧����3����ռģʽ�������������ĳ��̵��豸Ҳ���ݲ�֧����3��ģʽ�� \n
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Is the device accessible
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @param  nAccessMode                 [IN]            Access Right
 *  @return Access, return true. Not access, return false
 *  @remarks Read device CCP register value and determine current access permission.\n 
             Return false if the device does not support the modes MV_ACCESS_ExclusiveWithSwitch, MV_ACCESS_ControlWithSwitch, MV_ACCESS_ControlSwitchEnableWithKey. Currently the device does not support the 3 preemption modes, neither do the devices from other mainstream manufacturers. \n
             This API is not supported by CameraLink device. 
 ************************************************************************/
MVSDKEXPORT_API bool __stdcall MV_CC_IsDeviceAccessible(IN MV_CC_DEVICE_INFO* pstDevInfo, IN unsigned int nAccessMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸���
 *  @param  handle                      [OUT]           �豸���
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����������豸��Ϣ���������ڲ��������Դ�ͳ�ʼ���ڲ�ģ�顣ͨ���ýӿڴ������������SDK�ӿڣ���Ĭ������SDK��־�ļ����������Ҫ������־�ļ�������ͨ��MV_CC_CreateHandleWithoutLog���������
 
 *  @~english
 *  @brief  Create Device Handle
 *  @param  handle                      [OUT]           Device handle
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Create required resources within library and initialize internal module according to input device information. Create handle and call SDK interface through this interface, and SDK log file will be created by default. Creating handle through MV_CC_CreateHandleWithoutLog will not generate log files.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_CreateHandle(OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸�������������־
 *  @param  handle                      [OUT]           �豸���
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����������豸��Ϣ���������ڲ��������Դ�ͳ�ʼ���ڲ�ģ�顣ͨ���ýӿڴ������������SDK�ӿڣ�����Ĭ������SDK��־�ļ��������Ҫ������־�ļ�����ͨ��MV_CC_CreateHandle�����������־�ļ��Զ����ɡ�
 
 *  @~english
 *  @brief  Create Device Handle without log
 *  @param  handle                      [OUT]           Device handle
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Create required resources within library and initialize internal module according to input device information. Create handle and call SDK interface through this interface, and SDK log file will not be created. To create logs, create handle through MV_CC_CreateHandle, and log files will be automatically generated.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_CreateHandleWithoutLog(OUT void ** handle, IN const MV_CC_DEVICE_INFO* pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸���
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Destroy Device Handle
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_DestroyHandle(IN void * handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���豸
 *  @param  handle                      [IN]            �豸���
 *  @param  nAccessMode                 [IN]            ����Ȩ��
 *  @param  nSwitchoverKey              [IN]            �л�����Ȩ��ʱ����Կ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �������õ��豸�������ҵ���Ӧ���豸�������豸��\n 
             ���ýӿ�ʱ�ɲ�����nAccessMode��nSwitchoverKey����ʱĬ���豸����ģʽΪ��ռȨ�ޡ�Ŀǰ�豸�ݲ�֧��MV_ACCESS_ExclusiveWithSwitch��MV_ACCESS_ControlWithSwitch��MV_ACCESS_ControlSwitchEnable��MV_ACCESS_ControlSwitchEnableWithKey��������ռģʽ��\n 
             ����U3V�豸��nAccessMode��nSwitchoverKey������������Ч�� 
 
 *  @~english
 *  @brief  Open Device
 *  @param  handle                      [IN]            Device handle
 *  @param  nAccessMode                 [IN]            Access Right
 *  @param  nSwitchoverKey              [IN]            Switch key of access right
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Find specific device and connect according to set device parameters. \n
             When calling the interface, the input of nAccessMode and nSwitchoverKey is optional, and the device access mode is exclusive. Currently the device does not support the following preemption modes: MV_ACCESS_ExclusiveWithSwitch, MV_ACCESS_ControlWithSwitch, MV_ACCESS_ControlSwitchEnableWithKey.\n 
             For USB3Vision device, nAccessMode, nSwitchoverKey are invalid. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_OpenDevice(IN void* handle, IN unsigned int nAccessMode, IN unsigned short nSwitchoverKey);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ر��豸
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ��MV_CC_OpenDevice�����豸�󣬿���ͨ���ýӿڶϿ��豸���ӣ��ͷ���Դ
 
 *  @~english
 *  @brief  Close Device
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After connecting to device through MV_CC_OpenDevice, use this interface to disconnect and release resources.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_CloseDevice(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ж��豸�Ƿ�������״̬
 *  @param  handle                      [IN]            �豸���
 *  @return �豸��������״̬������true��û���ӻ�ʧȥ���ӣ�����false
 
 *  @~english
 *  @brief  Is The Device Connected
 *  @param  handle                      [IN]            Device handle
 *  @return Connected, return true. Not Connected or DIsconnected, return false
 ***********************************************************************/
MVSDKEXPORT_API bool __stdcall MV_CC_IsDeviceConnected(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ͼ�����ݻص�
 *  @param  handle                      [IN]            �豸���
 *  @param  cbOutput                    [IN]            �ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ���ýӿڿ�������ͼ�����ݻص���������MV_CC_CreateHandle֮�󼴿ɵ��á� \n
             ͼ�����ݲɼ������ַ�ʽ�����ַ�ʽ���ܸ��ã�\n
             ��ʽһ������MV_CC_RegisterImageCallBackEx����ͼ�����ݻص�������Ȼ�����MV_CC_StartGrabbing��ʼ�ɼ����ɼ���ͼ�����������õĻص������з��ء�\n
             ��ʽ��������MV_CC_StartGrabbing��ʼ�ɼ���Ȼ����Ӧ�ò�ѭ������MV_CC_GetOneFrameTimeout��ȡָ�����ظ�ʽ��֡���ݣ���ȡ֡����ʱ�ϲ�Ӧ�ó�����Ҫ����֡�ʿ��ƺõ��øýӿڵ�Ƶ�ʡ� \n
             �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  Register the image callback function
 *  @param  handle                      [IN]            Device handle
 *  @param  cbOutput                    [IN]            Callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After MV_CC_CreateHandle, call this interface to set image data callback function.\n 
             There are two available image data acquisition modes, and cannot be used together: \n
             Mode 1: Call MV_CC_RegisterImageCallBack to set image data callback function, and then callMV_CC_StartGrabbing to start acquiring. The acquired image data will return in the set callback function.\n
             Mode 2: Call MV_CC_StartGrabbing to start acquiring, and then call MV_CC_GetOneFrameTimeout repeatedly in application layer to get frame data of specified pixel format. When getting frame data, the frequency of calling this interface should be controlled by upper layer application according to frame rate. \n
             This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBackEx(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),
                                                         void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ͼ�����ݻص���RGB
 *  @param  handle                      [IN]            �豸���
 *  @param  cbOutput                    [IN]            �ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ���ýӿڿ�������ͼ�����ݻص���������MV_CC_CreateHandle֮�󼴿ɵ��á� \n
             ͼ�����ݲɼ������ַ�ʽ�����ַ�ʽ���ܸ��ã�\n
             ��ʽһ������MV_CC_RegisterImageCallBackForRGB����RGB24��ʽͼ�����ݻص�������Ȼ�����MV_CC_StartGrabbing��ʼ�ɼ����ɼ���ͼ�����������õĻص������з��ء�\n
             ��ʽ��������MV_CC_StartGrabbing��ʼ�ɼ���Ȼ����Ӧ�ò�ѭ������MV_CC_GetImageForRGB��ȡRGB24��ʽ��֡���ݣ���ȡ֡����ʱ�ϲ�Ӧ�ó�����Ҫ����֡�ʿ��ƺõ��øýӿڵ�Ƶ�ʡ� \n
             �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  register image data callback, RGB
 *  @param  handle                      [IN]            Device handle
 *  @param  cbOutput                    [IN]            Callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to set image data callback function, you should call this API MV_CC_CreateHandle. \n
             There are two image acquisition modes, the two modes cannot be reused: \n
             Mode 1: Call MV_CC_RegisterImageCallBackForRGB to set RGB24 format image data callback function, and then call MV_CC_StartGrabbing to start acquisition, the collected image data will be returned in the configured callback function.\n
             Mode 2: Call MV_CC_StartGrabbing to start acquisition, and the call MV_CC_GetImageForRGB repeatedly in application layer to get frame data with RGB24 format. When getting frame data, the upper application program should control the frequency of calling this API according to frame rate. \n
             This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBackForRGB(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),
                                                         void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ͼ�����ݻص���BGR
 *  @param  handle                      [IN]            �豸���
 *  @param  cbOutput                    [IN]            �ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ͨ���ýӿڿ�������ͼ�����ݻص���������MV_CC_CreateHandle֮�󼴿ɵ��á�\n
             ͼ�����ݲɼ������ַ�ʽ�����ַ�ʽ���ܸ��ã�\n
             ��ʽһ������MV_CC_RegisterImageCallBackForBGR����BGR24ͼ�����ݻص�������Ȼ�����MV_CC_StartGrabbing��ʼ�ɼ����ɼ���ͼ�����������õĻص������з��ء�\n
             ��ʽ��������MV_CC_StartGrabbing��ʼ�ɼ���Ȼ����Ӧ�ò�ѭ������MV_CC_GetImageForBGR��ȡBGR24��ʽ��֡���ݣ���ȡ֡����ʱ�ϲ�Ӧ�ó�����Ҫ����֡�ʿ��ƺõ��øýӿڵ�Ƶ�ʡ� \n
             �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  register image data callback, BGR
 *  @param  handle                      [IN]            Device handle
 *  @param  cbOutput                    [IN]            Callback function pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to set image data callback function, you should call this API MV_CC_CreateHandle. \n
             There are two image acquisition modes, the two modes cannot be reused: \n
             Mode 1: Call MV_CC_RegisterImageCallBackForBGR to set RGB24 format image data callback function, and then call MV_CC_StartGrabbing to start acquisition, the collected image data will be returned in the configured callback function.\n
             Mode 2: Call MV_CC_StartGrabbing to start acquisition, and the call MV_CC_GetImageForBGR repeatedly in application layer to get frame data with BGR24 format. When getting frame data, the upper application program should control the frequency of calling this API according to frame rate.\n 
             This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBackForBGR(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser),
                                                         void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʼȡ��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Start Grabbing
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_StartGrabbing(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ֹͣȡ��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  Stop Grabbing
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_StopGrabbing(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡһ֡RGB���ݣ��˺���Ϊ��ѯʽ��ȡ��ÿ�ε��ò�ѯ�ڲ�
            �����������ݣ����������ȡ���ݣ������ݷ��ش�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [OUT]           ͼ�����ݽ���ָ��
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pstFrameInfo                [OUT]           ͼ����Ϣ�ṹ��
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ÿ�ε��øýӿڣ�����ѯ�ڲ������Ƿ������ݣ������������ת����RGB24��ʽ���أ����û�������򷵻ش����롣��Ϊͼ��ת����RGB24��ʽ�к�ʱ�����Ե�����֡�ʹ���ʱ�ýӿڿ��ܻᵼ�¶�֡��\n 
             ���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ����ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ�ʡ� \n
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Get one frame of RGB data, this function is using query to get data
            query whether the internal cache has data, get data if there has, return error code if no data
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [OUT]           Image data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pstFrameInfo                [OUT]           Image information structure
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Each time the API is called, the internal cache is checked for data. If there is data, it will be transformed as RGB24 format for return, if there is no data, return error code. As time-consuming exists when transform the image to RGB24 format, this API may cause frame loss when the data frame rate is too high. \n
             Before calling this API to get image data frame, call MV_CC_StartGrabbing to start image acquisition. This API can get frame data actively, the upper layer program should control the frequency of calling this API according to the frame rate. \n
             This API is not supported by CameraLink device.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetImageForRGB(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pstFrameInfo, int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡһ֡BGR���ݣ��˺���Ϊ��ѯʽ��ȡ��ÿ�ε��ò�ѯ�ڲ�
            �����������ݣ����������ȡ���ݣ������ݷ��ش�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [OUT]           ͼ�����ݽ���ָ��
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pstFrameInfo                [OUT]           ͼ����Ϣ�ṹ��
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ÿ�ε��øýӿڣ�����ѯ�ڲ������Ƿ������ݣ������������ת����BGR24��ʽ���أ����û�������򷵻ش����롣��Ϊͼ��ת����BGR24��ʽ�к�ʱ�����Ե�����֡�ʹ���ʱ�ýӿڿ��ܻᵼ�¶�֡�� \n
             ���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ����ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ�ʡ�\n 
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Get one frame of BGR data, this function is using query to get data
            query whether the internal cache has data, get data if there has, return error code if no data
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [OUT]           Image data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pstFrameInfo                [OUT]           Image information structure
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to set image data callback function, you should call this API MV_CC_CreateHandle. \n
             There are two image acquisition modes, the two modes cannot be reused: \n
             Mode 1: Call MV_CC_RegisterImageCallBackForBGR to set RGB24 format image data callback function, and then call MV_CC_StartGrabbing to start acquisition, the collected image data will be returned in the configured callback function.\n
             Mode 2: Call MV_CC_StartGrabbing to start acquisition, and the call MV_CC_GetImageForBGR repeatedly in application layer to get frame data with BGR24 format. When getting frame data, the upper application program should control the frequency of calling this API according to frame rate. \n
             This API is not supported by CameraLink device.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetImageForBGR(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pstFrameInfo, int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ʹ���ڲ������ȡһ֡ͼƬ����MV_CC_Display����ͬʱʹ�ã�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFrame                    [OUT]           ͼ�����ݺ�ͼ����Ϣ
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ�䣬����INFINITEʱ��ʾ���޵ȴ���ֱ���յ�һ֡���ݻ���ֹͣȡ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ����ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ�ʡ��ýӿ�֧�����ó�ʱʱ�䣬SDK�ڲ��ȴ�ֱ��������ʱ���أ���������ȡ��ƽ���ԣ��ʺ����ڶ�ƽ����Ҫ��ϸߵĳ��ϡ� \n
             �ýӿ���MV_CC_FreeImageBuffer����ʹ�ã���������ȡ�������ݺ���Ҫ��MV_CC_FreeImageBuffer�ӿڽ�pFrame�ڵ�����ָ��Ȩ�޽����ͷš� \n
             �ýӿ���MV_CC_GetOneFrameTimeout��ȣ����Ÿ��ߵ�Ч�ʡ�����ȡ������ķ�������sdk�ڲ��Զ�����ģ���MV_CC_GetOneFrameTimeout�ӿ�����Ҫ�ͻ����з��䡣\n 
             �ýӿ��ڵ���MV_CC_Display���޷�ȡ���� \n
             �ýӿڶ���U3V��GIGE�豸����֧�֡� \n
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Get a frame of an image using an internal cache
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFrame                    [OUT]           Image data and image information
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to get image data frame, you should call MV_CC_StartGrabbing to start image acquisition. This API can get frame data actively, the upper layer program should control the frequency of calling this API according to the frame rate. This API support setting timeout, and SDK will wait to return until data appears. This function will increase the streaming stability, which can be used in the situation with high stability requirement. \n
             This API and MV_CC_FreeImageBuffer should be called in pairs, after processing the acquired data, you should call MV_CC_FreeImageBuffer to release the data pointer permission of pFrame. \n
             This interface is more efficient than MV_CC_GetOneFrameTimeout. The allocation of the stream cache is automatically allocated within the SDK.The MV_CC_GetOneFrameTimeout interface needs to be allocated by customers themselves. \n
             This API cannot be called to stream after calling MV_CC_Display. \n
             This API is not supported by CameraLink device. \n
             This API is supported by both USB3 vision camera and GigE camera. \n
 **********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetImageBuffer(IN void* handle, OUT MV_FRAME_OUT* pstFrame, IN int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  �ͷ�ͼ�񻺴�(�˽ӿ������ͷŲ���ʹ�õ�ͼ�񻺴棬��MV_CC_GetImageBuffer����ʹ��)
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFrame                    [IN]            ͼ�����ݺ�ͼ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ���MV_CC_GetImageBuffer����ʹ�ã�ʹ��MV_CC_GetImageBuffer�ӿ�ȡ����ͼ������pFrame����Ҫ��MV_CC_FreeImageBuffer�ӿڽ���Ȩ���ͷš� \n
             �ýӿڶ���ȡ��Ч�ʸ���GetOneFrameTimeout�ӿڣ���GetImageBuffer�ڲ�����Free������£����֧������Ľڵ�����SetImageNode�ӿ������õĽڵ�����ȣ�Ĭ�Ͻڵ�����1��\n 
             �ýӿڶ���U3V��GIGE�豸����֧�֡� \n
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Free image buffer(this interface can free image buffer, used with MV_CC_GetImageBuffer)
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFrame                    [IN]            Image data and image information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API and MV_CC_GetImageBuffer should be called in pairs, before calling MV_CC_GetImageBuffer to get image data pFrame, you should call MV_CC_FreeImageBuffer to release the permission. \n
             Compared with API MV_CC_GetOneFrameTimeout, this API has higher efficiency of image acquisition. The max. number of nodes can be outputted is same as the "nNum" of API MV_CC_SetImageNodeNum, default value is 1. \n
             This API is not supported by CameraLink device. \n
             This API is supported by both USB3 vision camera and GigE camera. 
 **********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_FreeImageBuffer(IN void* handle, IN MV_FRAME_OUT* pstFrame);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ó�ʱ���ƻ�ȡһ֡ͼƬ��SDK�ڲ��ȴ�ֱ��������ʱ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [OUT]           ͼ�����ݽ���ָ��
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pstFrameInfo                [OUT]           ͼ����Ϣ�ṹ��
 *  @param  nMsec                       [IN]            �ȴ���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ���øýӿڻ�ȡͼ������֮֡ǰ��Ҫ�ȵ���MV_CC_StartGrabbing����ͼ��ɼ����ýӿ�Ϊ����ʽ��ȡ֡���ݣ��ϲ�Ӧ�ó�����Ҫ����֡�ʣ����ƺõ��øýӿڵ�Ƶ�ʡ��ýӿ�֧�����ó�ʱʱ�䣬SDK�ڲ��ȴ�ֱ��������ʱ���أ���������ȡ��ƽ���ԣ��ʺ����ڶ�ƽ����Ҫ��ϸߵĳ��ϡ�\n 
             �ýӿڶ���U3V��GIGE�豸����֧�֡�\n 
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Timeout mechanism is used to get image, and the SDK waits inside until the data is returned
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [OUT]           Image data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pstFrameInfo                [OUT]           Image information structure
 *  @param  nMsec                       [IN]            Waiting timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Before calling this API to get image data frame, call MV_CC_StartGrabbing to start image acquisition. This API can get frame data actively, the upper layer program should control the frequency of calling this API according to the frame rate. This API supports setting timeout, SDK will wait to return until data appears. This function will increase the streaming stability, which can be used in the situation with high stability requirement. \n
             Both the USB3Vision and GIGE camera can support this API. \n
             This API is not supported by CameraLink device.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetOneFrameTimeout(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pstFrameInfo, unsigned int nMsec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ȡ�����ݻ���
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ������û��ڲ�ֹͣȡ����ʱ�򣬾�����������в���Ҫ��ͼ��\n
             �ýӿ�������ģʽ�д���ģʽ�󣬿��������ʷ���ݡ�
 
 *  @~english
 *  @brief  if Image buffers has retrieved the data��Clear them
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface allows user to clear the unnecessary images from the buffer memory without stopping acquisition. \n
             This interface allows user to clear previous data after switching from continuous mode to trigger mode. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_ClearImageBuffer(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʾһ֡ͼ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstDisplayInfo              [IN]            ͼ����Ϣ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڶ���U3V��GIGE�豸����֧�֡�\n 
             �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  Display one frame image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstDisplayInfo              [IN]            Frame Info
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is valid for USB3Vision camera and GIGE camera. \n
             This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_DisplayOneFrame(IN void* handle, IN MV_DISPLAY_FRAME_INFO* pstDisplayInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����SDK�ڲ�ͼ�񻺴�ڵ���������ڵ���1����ץͼǰ����
 *  @param  handle                      [IN]            �豸���
 *  @param  nNum                        [IN]            ����ڵ����
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ���øýӿڿ�������SDK�ڲ�ͼ�񻺴�ڵ�������ڵ���MV_CC_StartGrabbing��ʼץͼǰ���á�\n
             ��SDK��Ĭ����1���ڵ㡣\n
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Set the number of the internal image cache nodes in SDK, Greater than or equal to 1, to be called before the capture
 *  @param  handle                      [IN]            Device handle
 *  @param  nNum                        [IN]            Image Node Number
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this interface to set the number of SDK internal image buffer nodes. The interface should be called before calling MV_CC_StartGrabbing for capturing. \n
             This API is not supported by CameraLink device. 
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetImageNodeNum(IN void* handle, unsigned int nNum);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ȡ������
 *  @param  handle                      [IN]            �豸���
 *  @param  enGrabStrategy              [IN]            ����ö��ֵ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڶ���������ȡ�����ԣ��û����Ը���ʵ���������ѡ�񡣾����������£�
             -OneByOne:�Ӿɵ���һ֡һ֡�Ĵ���������б��л�ȡͼ�񣬴��豸��Ĭ��Ϊ�ò���
             -LatestImagesOnly:������������б��л�ȡ���µ�һ֡ͼ��ͬʱ�����������б�
             -LatestImages:����������б��л�ȡ���µ�OutputQueueSize֡ͼ������OutputQueueSize��ΧΪ1-ImageNodeNum������MV_CC_SetOutputQueueSize�ӿ����ã�ImageNodeNumĬ��Ϊ1������MV_CC_SetImageNodeNum�ӿ����� OutputQueueSize���ó�1��ͬ��LatestImagesOnly���ԣ�OutputQueueSize���ó�ImageNodeNum��ͬ��OneByOne����
             -UpcomingImage:�ڵ���ȡ���ӿ�ʱ������������б�������ͼ�񣬲��ȴ��豸�������ɵ�һ֡ͼ�񡣸ò���ֻ֧��GigE�豸����֧��U3V�豸
 
 *  @~english
 *  @brief  Set Grab Strategy
 *  @param  handle                      [IN]            Device handle
 *  @param  enGrabStrategy              [IN]            The value of Grab Strategy
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is set by four image acquisition approaches, the user may choose one as needed. Specific details are as followed: 
             -OneByOne:Obtain image from output cache list frame by frame in order, this function is default strategy when device is on.
             -LatestImagesOnly:Obtain the latest image from output cache list only, meanwhile clear output cache list.
             -LatestImages:Obtain the latest OutputQueueSize image from output cache list, the range of OutputQueueSize is 1-ImageNodeNum, the user may set the value of MV_CC_SetOutputQueueSizeinterface,the default value of ImageNodeNum is 1,If the user usesMV_CC_SetImageNodeNuminterface to set up OutputQueueSize,when the value of OutputQueueSize is set to be 1, the function will be same as LatestImagesOnly; if the value of OutputQueueSize is set to be ImageNodeNum, the function will be same as OneByOne.
             -UpcomingImage:Ignore all images in output cache list when calling image acuiqisiotn interface, wait the next upcoming image generated. Support for GigE camera only, not support for U3V camera.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetGrabStrategy(IN void* handle, IN MV_GRAB_STRATEGY enGrabStrategy);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����������������ֻ����MV_GrabStrategy_LatestImages�����²���Ч����Χ��1-ImageNodeNum��
 *  @param  handle                      [IN]            �豸���
 *  @param  nOutputQueueSize            [IN]            ����������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿ�����LatestImagesȡ���������׵��ã���������LatestImages���������������ͼ��ĸ�����������ȡ�������ж�̬��������������
 
 *  @~english
 *  @brief  Set The Size of Output Queue(Only work under the strategy of MV_GrabStrategy_LatestImages��rang��1-ImageNodeNum)
 *  @param  handle                      [IN]            Device handle
 *  @param  nOutputQueueSize            [IN]            The Size of Output Queue
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface must be used with LatestImages Grab strategy, it is used for setting the maximum allowance queue size of the image under the LatestImages strategy. The user may change the output queue size while grabbing images.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetOutputQueueSize(IN void* handle, IN unsigned int nOutputQueueSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸��Ϣ��ȡ��֮ǰ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pstDevInfo                  [IN][OUT]       ���ظ��������й��豸��Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ֧���û��ڴ��豸���ȡ�豸��Ϣ��\n 
             �����豸��GigE�豸������øýӿڴ����������գ���˲�������ȡ�������е��øýӿڡ�
 
 *  @~english
 *  @brief  Get device information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstDevInfo                  [IN][OUT]       Structure pointer of device information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks The API support users to access device information after opening the device. \n
             If the device is a GigE camera, there is a blocking risk in calling the interface, so it is not recommended to call the interface during the fetching process. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceInfo(IN void * handle, IN OUT MV_CC_DEVICE_INFO* pstDevInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�������͵���Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInfo                     [IN][OUT]       ���ظ��������й��豸�������͵���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ӿ�����������Ҫ��ȡ����Ϣ���ͣ�ָ��MV_ALL_MATCH_INFO�ṹ���е�nType���ͣ�����ȡ��Ӧ����Ϣ����MV_ALL_MATCH_INFO�ṹ����pInfo�ﷵ�أ��� \n
             �ýӿڵĵ���ǰ������ȡ��������ȡ����Ϣ���ͣ���ȡGigE�豸��MV_MATCH_TYPE_NET_DETECT��Ϣ���ڿ���ץͼ֮����ã���ȡU3V�豸��MV_MATCH_TYPE_USB_DETECT��Ϣ���ڴ��豸֮����á� \n
             �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  Get various type of information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [IN][OUT]       Structure pointer of various type of information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Input required information type (specify nType in structure MV_ALL_MATCH_INFO) in the interface and get corresponding information (return in pInfo of structure MV_ALL_MATCH_INFO). \n
             The calling precondition of this interface is determined by obtained information type. Call after enabling capture to get MV_MATCH_TYPE_NET_DETECT information of GigE device, and call after starting device to get MV_MATCH_TYPE_USB_DETECT information of USB3Vision device. \n
             This API is not supported by CameraLink device. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAllMatchInfo(IN void* handle, IN OUT MV_ALL_MATCH_INFO* pstInfo);


/************************************************************************/
/* ���úͻ�ȡ�豸���������ܽӿ�                                         */
/* General interface for getting and setting camera parameters          */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡInteger����ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ�����Ϣ��Ϊ"Width"
 *  @param  pstIntValue                 [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡint���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IInteger���Ľڵ�ֵ������ͨ���ýӿڻ�ȡ��strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Get Integer value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value, for example, using "Width" to get width
 *  @param  pstIntValue                 [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks You can call this API to get the value of camera node with integer type after connecting the device. For strKey value, refer to MvCameraNode. All the node values of "IInteger" in the list can be obtained via this API. strKey corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetIntValueEx(IN void* handle,IN const char* strKey,OUT MVCC_INTVALUE_EX *pstIntValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Integer������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ�����Ϣ��Ϊ"Width"
 *  @param  nValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������int���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IInteger���Ľڵ�ֵ������ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Set Integer value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value, for example, using "Width" to set width
 *  @param  nValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks You can call this API to get the value of camera node with integer type after connecting the device. For strKey value, refer to MvCameraNode. All the node values of "IInteger" in the list can be obtained via this API. strKey corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetIntValueEx(IN void* handle,IN const char* strKey,IN int64_t nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡEnum����ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  pstEnumValue                [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡEnum���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IEnumeration���Ľڵ�ֵ������ͨ���ýӿڻ�ȡ��strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Get Enum value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to get pixel format
 *  @param  pstEnumValue                [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified Enum nodes. For value of strKey, see MvCameraNode, The node values of IEnumeration can be obtained through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetEnumValue(IN void* handle,IN const char* strKey,OUT MVCC_ENUMVALUE *pstEnumValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Enum������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  nValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������Enum���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IEnumeration���Ľڵ�ֵ������ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Set Enum value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to set pixel format
 *  @param  nValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified Enum nodes. For value of strKey, see MvCameraNode, The node values of IEnumeration can be obtained through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetEnumValue(IN void* handle,IN const char* strKey,IN unsigned int nValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Enum������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ�����ȡ���ظ�ʽ��Ϣ��Ϊ"PixelFormat"
 *  @param  strValue                    [IN]            ��Ҫ���õ��豸�������ַ���
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������Enum���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IEnumeration���Ľڵ�ֵ������ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Set Enum value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value, for example, using "PixelFormat" to set pixel format
 *  @param  strValue                    [IN]            Feature String to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this API after connecting the device. All the values of nodes with IEnumeration type can be set via this API.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetEnumValueByString(IN void* handle,IN const char* strKey,IN const char* strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡFloat����ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  pstFloatValue               [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡfloat���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IFloat���Ľڵ�ֵ������ͨ���ýӿڻ�ȡ��strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Get Float value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @param  pstFloatValue               [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified float node. For detailed strKey value see: MvCameraNode. The node values of IFloat can be obtained through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetFloatValue(IN void* handle,IN const char* strKey,OUT MVCC_FLOATVALUE *pstFloatValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����float������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  fValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������float���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IFloat���Ľڵ�ֵ������ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Set float value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @param  fValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified float node. For detailed strKey value see: MvCameraNode. The node values of IFloat can be set through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetFloatValue(IN void* handle,IN const char* strKey,IN float fValue);
	
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡBoolean����ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  pbValue                     [IN][OUT]       ���ظ��������й��豸����ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡbool���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IBoolean���Ľڵ�ֵ������ͨ���ýӿڻ�ȡ��strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Get Boolean value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @param  pbValue                     [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified bool nodes. For value of strKey, see MvCameraNode. The node values of IBoolean can be obtained through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBoolValue(IN void* handle,IN const char* strKey,OUT bool *pbValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Boolean������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  bValue                      [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������bool���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IBoolean���Ľڵ�ֵ������ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Set Boolean value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @param  bValue                      [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified bool nodes. For value of strKey, see MvCameraNode. The node values of IBoolean can be set through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBoolValue(IN void* handle,IN const char* strKey,IN bool bValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡString����ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  pstStringValue              [IN][OUT]       ���ظ��������й��豸���Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ��Ի�ȡstring���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IString���Ľڵ�ֵ������ͨ���ýӿڻ�ȡ��strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Get String value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @param  pstStringValue              [IN][OUT]       Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to get specified string nodes. For value of strKey, see MvCameraNode. The node values of IString can be obtained through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetStringValue(IN void* handle,IN const char* strKey,OUT MVCC_STRINGVALUE *pstStringValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����String������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @param  strValue                    [IN]            ��Ҫ���õ��豸������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������string���͵�ָ���ڵ��ֵ��strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��IString���Ľڵ�ֵ������ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Set String value
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @param  strValue                    [IN]            Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified string nodes. For value of strKey, see MvCameraNode. The node values of IString can be set through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetStringValue(IN void* handle,IN const char* strKey,IN const char * strValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Command������ֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  strKey                      [IN]            ���Լ�ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸֮����øýӿڿ�������ָ����Command���ͽڵ㡣strKeyȡֵ���Բο�XML�ڵ���������б����������������Ϊ��ICommand���Ľڵ㶼����ͨ���ýӿ����ã�strKey����ȡֵ��Ӧ�б�����ġ����ơ�һ�С�
 
 *  @~english
 *  @brief  Send Command
 *  @param  handle                      [IN]            Device handle
 *  @param  strKey                      [IN]            Key value
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set specified Command nodes. For value of strKey, see MvCameraNode. The node values of ICommand can be set through this interface, strKey value corresponds to the Name column.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetCommandValue(IN void* handle,IN const char* strKey);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���GenICam�ڵ㻺��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @~english
 *  @brief  Invalidate GenICam Nodes
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_InvalidateNodes(IN void* handle);


/************************************************************************/
/* �豸���� �� �Ĵ�����д ���쳣���¼��ص�                            	*/
/* Device upgrade, register read and write and exception callback       */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  �豸��������
 *  @param  handle                      [IN]            �豸���
 *  @param  strFilePathName             [IN]            �ļ���
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿڿ��Խ������̼��ļ����͸��豸�����������ýӿ���Ҫ�ȴ������̼��ļ��ɹ������豸��֮���ٷ��أ���Ӧʱ����ܽϳ���
 
 *  @~english
 *  @brief  Device Local Upgrade
 *  @param  handle                      [IN]            Device handle
 *  @param  strFilePathName             [IN]            File name
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this API to send the upgrade firmware to the device for upgrade. This API will wait for return until the upgrade firmware is sent to the device, this response may take a long time. \n
             For CameraLink device, it keeps sending upgrade firmware continuously. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_LocalUpgrade(IN void* handle, const void *strFilePathName);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnProcess                   [OUT]           ���Ƚ��յ�ַ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @~english
 *  @brief  Get Upgrade Progress
 *  @param  handle                      [IN]            Device handle
 *  @param  pnProcess                   [OUT]           Progress receiving address
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetUpgradeProcess(IN void* handle, unsigned int* pnProcess);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ڴ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pBuffer                     [IN][OUT]       ��Ϊ����ֵʹ�ã�����������ڴ�ֵ��GEV�豸�ڴ�ֵ�ǰ��մ��ģʽ�洢�ģ�����Э���豸����С�˴洢��
 *  @param  nAddress                    [IN]            ����ȡ���ڴ��ַ���õ�ַ���Դ��豸��Camera.xml�ļ��л�ȡ������xxx_RegAddr��xml�ڵ�ֵ
 *  @param  nLength                     [IN]            ����ȡ���ڴ泤��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸����ȡĳ�μĴ��������ݡ�
 
 *  @~english
 *  @brief  Read Memory
 *  @param  handle                      [IN]            Device Handle
 *  @param  pBuffer                     [IN][OUT]       Used as a return value, save the read-in memory value ( Memory value is stored in accordance with the big end model)
 *  @param  nAddress                    [IN]            Memory address to be read, which can be obtained from the Camera.xml file of the device, the form xml node value of xxx_RegAddr
 *  @param  nLength                     [IN]            Length of the memory to be read
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Access device, read the data from certain register.
*************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_ReadMemory(IN void* handle , void *pBuffer, int64_t nAddress, int64_t nLength);

/********************************************************************//**
 *  @~chinese
 *  @brief  д�ڴ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pBuffer                     [IN]            ��д����ڴ�ֵ��ע��GEV�豸�ڴ�ֵҪ���մ��ģʽ�洢������Э���豸����С�˴洢��
 *  @param  nAddress                    [IN]            ��д����ڴ��ַ���õ�ַ���Դ��豸��Camera.xml�ļ��л�ȡ������xxx_RegAddr��xml�ڵ�ֵ
 *  @param  nLength                     [IN]            ��д����ڴ泤��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �����豸����һ������д��ĳ�μĴ�����
 
 *  @~english
 *  @brief  Write Memory
 *  @param  handle                      [IN]            Device Handle
 *  @param  pBuffer                     [IN]            Memory value to be written ( Note the memory value to be stored in accordance with the big end model)
 *  @param  nAddress                    [IN]            Memory address to be written, which can be obtained from the Camera.xml file of the device, the form xml node value of xxx_RegAddr
 *  @param  nLength                     [IN]            Length of the memory to be written
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Access device, write a piece of data into a certain segment of register.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_WriteMemory(IN void* handle , const void *pBuffer, int64_t nAddress, int64_t nLength);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע���쳣��Ϣ�ص����ڴ��豸֮�����
 *  @param  handle                      [IN]            �豸���
 *  @param  cbException                 [IN]            �쳣�ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ���Ҫ��MV_CC_OpenDevice���豸֮����á��豸�쳣�Ͽ����Ӻ�����ڻص������ȡ���쳣��Ϣ��GigE�豸����֮����Ҫ�ȵ���MV_CC_CloseDevice�ӿڹر��豸���ٵ���MV_CC_OpenDevice�ӿ����´��豸��
 
 *  @~english
 *  @brief  Register Exception Message CallBack, call after open device
 *  @param  handle                      [IN]            Device handle
 *  @param  cbException                 [IN]            Exception Message CallBack Function Pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Call this interface after the device is opened by MV_CC_OpenDevice. When device is exceptionally disconnected, the exception message can be obtained from callback function. For Disconnected GigE device, first call MV_CC_CloseDevice to shut device, and then call MV_CC_OpenDevice to reopen the device. 
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterExceptionCallBack(IN void* handle, 
                                                             void(__stdcall* cbException)(unsigned int nMsgType, void* pUser), void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע��ȫ���¼��ص����ڴ��豸֮�����
 *  @param  handle                      [IN]            �豸���
 *  @param  cbEvent                     [IN]            �¼��ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿ������¼��ص��������ڻص����������ȡ�ɼ����ع���¼���Ϣ�� \n
             �ýӿڲ�֧��CameraLink�豸��
 
 *  @~english
 *  @brief  Register event callback, which is called after the device is opened
 *  @param  handle                      [IN]            Device handle
 *  @param  cbEvent                     [IN]            Event CallBack Function Pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Call this API to set the event callback function to get the event information, e.g., acquisition, exposure, and so on. \n
             This API is not supported by CameraLink device.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterAllEventCallBack(void* handle, void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser);

/********************************************************************//**
 *  @~chinese
 *  @brief  ע�ᵥ���¼��ص����ڴ��豸֮�����
 *  @param  handle                      [IN]            �豸���
 *  @param  strEventName                [IN]            �¼�����
 *  @param  cbEvent                     [IN]            �¼��ص�����ָ��
 *  @param  pUser                       [IN]            �û��Զ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿ������¼��ص��������ڻص����������ȡ�ɼ����ع���¼���Ϣ��\n 
             �ýӿڲ�֧��CameraLink�豸����֧��"�豸����"��һ���¼��� 
 
 *  @~english
 *  @brief  Register single event callback, which is called after the device is opened
 *  @param  handle                      [IN]            Device handle
 *  @param  strEventName                [IN]            Event name
 *  @param  cbEvent                     [IN]            Event CallBack Function Pointer
 *  @param  pUser                       [IN]            User defined variable
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Call this API to set the event callback function to get the event information, e.g., acquisition, exposure, and so on. \n
             This API is not supported by CameraLink device .
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterEventCallBackEx(void* handle, const char* strEventName,
                                                         void(__stdcall* cbEvent)(MV_EVENT_OUT_INFO * pEventInfo, void* pUser), void* pUser);


/************************************************************************/
/* GigEVision �豸���еĽӿ�                                     		*/
/* GigEVision device specific interface                                 */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ǿ��IP
 *  @param  handle                      [IN]            �豸���
 *  @param  nIP                         [IN]            ���õ�IP
 *  @param  nSubNetMask                 [IN]            ��������
 *  @param  nDefaultGateWay             [IN]            Ĭ������
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ǿ�������豸�������������IP���������롢Ĭ�����أ���ǿ������֮����Ҫ���´����豸�������GigEVision�豸֧�֡�\n
             ����豸ΪDHCP��״̬�����øýӿ�ǿ�������豸�������֮���豸����������
 
 *  @~english
 *  @brief  Force IP
 *  @param  handle                      [IN]            Device handle
 *  @param  nIP                         [IN]            IP to set
 *  @param  nSubNetMask                 [IN]            Subnet mask
 *  @param  nDefaultGateWay             [IN]            Default gateway
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Force setting camera network parameter (including IP address, subnet mask, default gateway). After forced setting, device handle should be created again. This function is only supported by GigEVision camera.\n
             If device is in DHCP status, after calling this API to force setting camera network parameter, the device will restart.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_ForceIpEx(IN void* handle, unsigned int nIP, unsigned int nSubNetMask, unsigned int nDefaultGateWay);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����IP��ʽ
 *  @param  handle                      [IN]            �豸���
 *  @param  nType                       [IN]            IP���ͣ���MV_IP_CFG_x
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �������������豸��IP��ʽ����DHCP��LLA�ȣ���GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  IP configuration method
 *  @param  handle                      [IN]            Device handle
 *  @param  nType                       [IN]            IP type, refer to MV_IP_CFG_x
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Send command to set camera IP mode, such as DHCP and LLA, only supported by GigEVision.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetIpConfig(IN void* handle, unsigned int nType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ý�ʹ��ĳ��ģʽ,type: MV_NET_TRANS_x��������ʱ��Ĭ������ʹ��driver
 *  @param  handle                      [IN]            �豸���
 *  @param  nType                       [IN]            ���紫��ģʽ����MV_NET_TRANS_x
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿڿ�������SDK�ڲ�����ʹ�õ�����ģʽ��Ĭ������ʹ������ģʽ����GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  Set to use only one mode,type: MV_NET_TRANS_x. When do not set, priority is to use driver by default
 *  @param  handle                      [IN]            Device handle
 *  @param  nType                       [IN]            Net transmission mode, refer to MV_NET_TRANS_x
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarksSet SDK internal priority network mode through this interface, drive mode by default, only supported by GigEVision camera.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetNetTransMode(IN void* handle, unsigned int nType);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ���紫����Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInfo                     [OUT]           ��Ϣ�ṹ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ͨ���ýӿڿ��Ի�ȡ���紫�������Ϣ�������ѽ������ݴ�С����֡�����ȣ���MV_CC_StartGrabbing�����ɼ�֮����á���GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  Get net transmission information
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [OUT]           Information Structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Get network transmission information through this API, including received data size, number of lost frames. Call this API after starting image acquiring through MV_CC_StartGrabbing. This API is supported only by GigEVision Camera.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetNetTransInfo(IN void* handle, MV_NETTRANS_INFO* pstInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ö������Ļظ�������
 *  @param  nMode                       [IN]            �ظ������ͣ�Ĭ�Ϲ㲥����0-������1-�㲥
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ��GigE�����Ч��

 *  @~english
 *  @brief  Setting the ACK mode of devices Discovery.
 *  @param  nMode                       [IN]            ACK mode��Default-Broadcast��,0-Unicast,1-Broadcast.
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is ONLY effective on GigE cameras. \n
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetDiscoveryMode(unsigned int nMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����GVSPȡ����ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ��ʱʱ�䣬Ĭ��300ms����Χ��>10ms
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����豸֮��ȡ����������ǰ�����øýӿڿ�������GVSPȡ����ʱʱ�䡣GVSPȡ����ʱ���ù��̿������ͼ���쳣�����ù����������ȡ��ʱ��䳤��
 
 *  @~english
 *  @brief  Set GVSP streaming timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout, default 300ms, range: >10ms
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, and just before start streaming, 
 *           call this interface to set GVSP streaming timeout value.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGvspTimeout(void* handle, unsigned int nMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡGVSPȡ����ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMillisec                  [OUT]           ��ʱʱ��ָ�룬�Ժ���λ��λ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��GVSPȡ����ʱʱ��
 
 *  @~english
 *  @brief  Get GVSP streaming timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMillisec                  [OUT]           Timeout, ms as unit
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get the current GVSP streaming timeout.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGvspTimeout(IN void* handle, unsigned int* pnMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����GVCP���ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ��ʱʱ�䣬Ĭ��500ms����Χ��0-10000ms
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����豸֮����øýӿڿ�������GVCP���ʱʱ�䡣
 
 *  @~english
 *  @brief  Set GVCP cammand timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout, default 500ms, range: 0-10000ms
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set GVCP command timeout time.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGvcpTimeout(void* handle, unsigned int nMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡGVCP���ʱʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMillisec                  [OUT]           ��ʱʱ��ָ�룬�Ժ���λ��λ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��GVCP��ʱʱ�䡣
 
 *  @~english
 *  @brief  Get GVCP cammand timeout
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMillisec                  [OUT]           Timeout, ms as unit
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get the current GVCP timeout.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGvcpTimeout(void* handle, unsigned int* pnMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����ش�GVCP�������
 *  @param  handle                      [IN]            �豸���
 *  @param  nRetryGvcpTimes             [IN]            �ش���������Χ��0-100
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�������GVCP�������쳣ʱ�������ش��Ĵ�������һ���̶��Ͽ��Ա����豸���ߣ���ΧΪ0-100��
 
 *  @~english
 *  @brief  Set the number of retry GVCP cammand
 *  @param  handle                      [IN]            Device handle
 *  @param  nRetryGvcpTimes             [IN]            The number of retries��rang��0-100
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to increase The Times of retransmission when GVCP packet transmission is abnormal,and to some extent, it can avoid dropping the camera, with a range of 0-100.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetRetryGvcpTimes(void* handle, unsigned int nRetryGvcpTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ش�GVCP�������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnRetryGvcpTimes            [OUT]           �ش�����ָ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��GVCP�ش�������Ĭ��3�Ρ�
 
 *  @~english
 *  @brief  Get the number of retry GVCP cammand
 *  @param  handle                      [IN]            Device handle
 *  @param  pnRetryGvcpTimes            [OUT]           The number of retries
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to get the current number of GVCP retransmissions, which defaults to 3.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetRetryGvcpTimes(void* handle, unsigned int* pnRetryGvcpTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ��ѵ�packet size���ýӿ�Ŀǰֻ֧��GigE�豸
 *  @param  handle                      [IN]            �豸���
 *  @return ���packetsize
 *  @remarks ��ȡ��ѵ�packet size����ӦGigEVision�豸��SCPS����ӦU3V�豸��ÿ�δ�������ȡ�İ���С���ô�С�������ϴ���һ�����Ĵ�С���ýӿ���Ҫ��MV_CC_OpenDevice֮��MV_CC_StartGrabbing֮ǰ���á� \n
             �ýӿڲ�֧��CameraLink�豸�� 
 
 *  @~english
 *  @brief  Get the optimal Packet Size, Only support GigE Camera
 *  @param  handle                      [IN]            Device handle
 *  @return Optimal packetsize
 *  @remarks To get optimized packet size, for GigEVision device is SCPS, for USB3Vision device is the size of packet read from drive each time, and it is the size of a packet transported on the network. The interface should be called after MV_CC_OpenDevice and before MV_CC_StartGrabbing. \n
             This API is not supported by CameraLink device. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetOptimalPacketSize(IN void* handle);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����Ƿ���ط���֧�֣����ط�������
 *  @param  handle                      [IN]            �豸���
 *  @param  bEnable                     [IN]            �Ƿ�֧���ط���
 *  @param  nMaxResendPercent           [IN]            ����ط���
 *  @param  nResendTimeout              [IN]            �ط���ʱʱ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����豸֮����øýӿڿ��������ط������ԣ���GigEVision�豸֧�֡�
 
 *  @~english
 *  @brief  Set whethe to enable resend, and set resend
 *  @param  handle                      [IN]            Device handle
 *  @param  bEnable                     [IN]            enable resend
 *  @param  nMaxResendPercent           [IN]            Max resend persent
 *  @param  nResendTimeout              [IN]            Resend timeout
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After the device is connected, call this interface to set resend packet properties, only supported by GigEVision camera.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetResend(void* handle, unsigned int bEnable, unsigned int nMaxResendPercent, unsigned int nResendTimeout);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����ش���������Դ���
 *  @param  handle                      [IN]            �豸���
 *  @param  nRetryTimes                 [IN]            �ش���������Դ�����Ĭ��20
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  set the max resend retry times
 *  @param  handle                      [IN]            Device handle
 *  @param  nRetryTimes                 [IN]            The max times to retry resending lost packets��default 20
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend, \n
 *           otherwise would fail and return MV_E_CALLORDER.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall  MV_GIGE_SetResendMaxRetryTimes (void* handle, unsigned int nRetryTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ش���������Դ���
 *  @param  handle                      [IN]            �豸���
 *  @param  pnRetryTimes                [OUT]           �ش���������Դ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  get the max resend retry times
 *  @param  handle                      [IN]            Device handle
 *  @param  pnRetryTimes                [OUT]           The max times to retry resending lost packets
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend, \n
 *           otherwise would fail and return MV_E_CALLORDER. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall  MV_GIGE_GetResendMaxRetryTimes (void* handle, unsigned int* pnRetryTimes);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͬһ�ش����������֮���ʱ����
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ͬһ�ش����������֮���ʱ������Ĭ��10ms
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  set time interval between same resend requests
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            The time interval between same resend requests,default 10ms
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend, \n
 *           otherwise would fail and return MV_E_CALLORDER. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall  MV_GIGE_SetResendTimeInterval (void* handle, unsigned int nMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡͬһ�ش����������֮���ʱ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pnMillisec                  [OUT]           ͬһ�ش����������֮���ʱ����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿڱ����ڵ���MV_GIGE_SetResend�����ش�������֮����ã�����ʧ���ҷ���MV_E_CALLORDER
 
 *  @~english
 *  @brief  get time interval between same resend requests
 *  @param  handle                      [IN]            Device handle
 *  @param  pnMillisec                  [OUT]           The time interval between same resend requests
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface MUST be called after enabling resending lost packets by calling MV_GIGE_SetResend, \n
 *           otherwise would fail and return MV_E_CALLORDER. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall  MV_GIGE_GetResendTimeInterval (void* handle, unsigned int* pnMillisec);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ô���ģʽ������Ϊ����ģʽ���鲥ģʽ��
 *  @param  handle                      [IN]            �豸���
 *  @param  stTransmissionType          [IN]            ����ģʽ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ͨ���ýӿڿ������ô���ģʽΪ�������鲥��ģʽ����GigEVision�豸֧�֡�

 *  @~english
 *  @brief  Set transmission type,Unicast or Multicast
 *  @param  handle                      [IN]            Device handle
 *  @param  stTransmissionType          [IN]            Struct of transmission type
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Call this API to set the transmission mode as single cast mode and multicast mode. And this API is only valid for GigEVision camera. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetTransmissionType(void* handle, MV_TRANSMISSION_TYPE * pstTransmissionType);

/********************************************************************//**
 *  @~chinese
 *  @brief   ������������
 *  @param   pstActionCmdInfo           [IN]            ����������Ϣ
 *  @param   pstActionCmdResults        [OUT]           �����������Ϣ�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ��GigEVision�豸֧�֡�

 *  @~english
 *  @brief  Issue Action Command
 *  @param   pstActionCmdInfo           [IN]            Action Command
 *  @param   pstActionCmdResults        [OUT]           Action Command Result List
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is supported only by GigEVision camera.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_IssueActionCommand(IN MV_ACTION_CMD_INFO* pstActionCmdInfo, OUT MV_ACTION_CMD_RESULT_LIST* pstActionCmdResults);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�鲥״̬
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��
 *  @param  pbStatus                    [OUT]           �鲥״̬,true:�鲥״̬��false:���鲥
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ������ж��豸��ǰ�Ƿ����鲥״̬������ͻ���ö��ʱ��Ҫ���豸�ж��鲥�����⡣

 *  @~english
 *  @brief  Get Multicast Status
 *  @param  pstDevInfo                  [IN]            Device Information Structure
 *  @param  pbStatus                    [OUT]           Status of Multicast
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This interface is used to determine whether the camera is currently in multicast state, and to solve the problem that the client needs to turn on the camera to determine multicast when enumerating.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetMulticastStatus(IN MV_CC_DEVICE_INFO* pstDevInfo, OUT bool* pbStatus);


/************************************************************************/
/* CameraLink �豸���еĽӿ�                                            */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸������
 *  @param  handle                      [IN]            �豸���
 *  @param  nBaudrate                   [IN]            ���õĲ�����ֵ����ֵ�ο�CameraParams.h�к궨�壬��#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ�֧�����豸δ����ʱ���á�
 
 *  @~english
 *  @brief  Set device baudrate using one of the CL_BAUDRATE_XXXX value
 *  @param  handle                      [IN]            Device handle
 *  @param  nBaudrate                   [IN]            baud rate to set. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API is supported only by CameraLink device.\n
             This API support calls when devices are not connected.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_SetDeviceBaudrate(IN void* handle, unsigned int nBaudrate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnCurrentBaudrate           [OUT]           ��������Ϣָ�룬��ֵ�ο�CameraParams.h�к궨�壬��#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ�֧�����豸δ����ʱ���á�
 
 *  @~english
 *  @brief  Returns the current device baudrate, using one of the CL_BAUDRATE_XXXX value
 *  @param  handle                      [IN]            Device handle
 *  @param  pnCurrentBaudrate           [OUT]           Return pointer of baud rate to user. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API is supported only by CameraLink device.\n
             This API support calls when devices are not connected.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_GetDeviceBaudrate(IN void* handle,unsigned int* pnCurrentBaudrate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������������֧�ֵĲ�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pnBaudrateAblity            [OUT]           ֧�ֵĲ�������Ϣ��ָ�롣��֧�ֲ����ʵĻ���������������ֵ�ο�CameraParams.h�к궨�壬��MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ�֧�����豸δ����ʱ���á�
 
 *  @~english
 *  @brief  Returns supported baudrates of the combined device and host interface
 *  @param  handle                      [IN]            Device handle
 *  @param  pnBaudrateAblity            [OUT]           Return pointer of the supported baudrates to user. 'OR' operation results of the supported baudrates. Refer to the 'CameraParams.h' for single value definitions, for example, MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This API is supported only by CameraLink device.\n
             This API support calls when devices are not connected.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_GetSupportBaudrates(IN void* handle,unsigned int* pnBaudrateAblity);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ô��ڲ����ȴ�ʱ��
 *  @param  handle                      [IN]            �豸���
 *  @param  nMillisec                   [IN]            ���ڲ����ĵȴ�ʱ��, ��λΪms
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����

 *  @~english
 *  @brief  Sets the timeout for operations on the serial port
 *  @param  handle                      [IN]            Device handle
 *  @param  nMillisec                   [IN]            Timeout in [ms] for operations on the serial port.
 *  @return Success, return MV_OK. Failure, return error code 
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_SetGenCPTimeOut(IN void* handle, unsigned int nMillisec);


/************************************************************************/
/* U3V �豸���еĽӿ�                                            */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ����U3V�Ĵ������С
 *  @param  handle                      [IN]            �豸���
 *  @param  nTransferSize               [IN]            ����İ���С, Byte��Ĭ��Ϊ1M��rang��>=0x10000
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ���Ӵ������С�����ʵ�����ȡ��ʱ��CPUռ���ʡ�����ͬ��PC�Ͳ�ͬUSB��չ�����ڲ�ͬ�ļ����ԣ�����ò������ù�����ܻ����ȡ����ͼ��ķ��ա�
 
 *  @~english
 *  @brief  Set transfer size of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  nTransferSize               [IN]            Transfer size��Byte��default��1M��rang��>=0x10000
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Increasing the transmission packet size can reduce the CPU utilization at the time of fetching. However, different PCS and different USB extension CARDS have different compatibility, and if this parameter is set too large, there may be the risk of not getting the image.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_USB_SetTransferSize(IN void* handle, unsigned int nTransferSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡU3V�Ĵ������С
 *  @param  handle                      [IN]            �豸���
 *  @param  pnTransferSize              [OUT]           ����İ���Сָ��, Byte
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��U3V�������С��Ĭ��1M��
 
 *  @~english
 *  @brief  Get transfer size of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  pnTransferSize              [OUT]           Transfer size��Byte
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is used to get the current U3V transfer packet size, default 1M.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_USB_GetTransferSize(IN void* handle, unsigned int* pnTransferSize);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����U3V�Ĵ���ͨ������
 *  @param  handle                      [IN]            �豸���
 *  @param  nTransferWays               [IN]            ����ͨ����������Χ��1-10
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �û����Ը���PC�����ܡ��豸��ͼ֡�ʡ�ͼ���С���ڴ�ʹ���ʵ����ضԸò������е��ڡ�����ͬ��PC�Ͳ�ͬ��USB��չ�����ڲ�ͬ�ļ����ԡ�
 
 *  @~english
 *  @brief  Set transfer ways of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  nTransferWays               [IN]            Transfer ways��rang��1-10
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks Users can adjust this parameter according to PC performance, camera image frame rate, image size, memory utilization and other factors. But different PCS and different USB expansion CARDS have different compatibility.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_USB_SetTransferWays(IN void* handle, unsigned int nTransferWays);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡU3V�Ĵ���ͨ������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnTransferWays              [OUT]           ����ͨ������ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks �ýӿ����ڻ�ȡ��ǰ��U3V�첽ȡ���ڵ������2000W�豸��MONO8Ĭ��Ϊ3����YUVΪĬ��2����RGBΪĬ��1�����������Ĭ��8���ڵ㡣
 
 *  @~english
 *  @brief  Get transfer ways of U3V device
 *  @param  handle                      [IN]            Device handle
 *  @param  pnTransferWays              [OUT]           Transfer ways
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks This interface is used to get the current number of U3V asynchronous feed nodes. For 2000W camera, MONO8 defaults to 3, YUV defaults to 2, RGB defaults to 1, and other cases default to 8 nodes.
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_USB_GetTransferWays(IN void* handle, unsigned int* pnTransferWays);

/************************************************************************/
/* GenTL��ؽӿڣ������ӿڿ��Ը��ã����ֽӿڲ�֧�֣�                    */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ��GenTLö��Interfaces
 *  @param  pstIFList                   [OUT]           Interfaces�б�
 *  @param  strGenTLPath                [IN]            GenTL��cti�ļ�·��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks Interfaces�б���ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź����룬\n
             ���龡��������߳�ö�ٲ�����
 
 *  @~english
 *  @brief  Enumerate Interfaces with GenTL
 *  @param  pstIFList                   [OUT]           Interfaces List
 *  @param  strGenTLPath                [IN]            GenTL cti file path
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the Interfaces list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.\n
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_EnumInterfacesByGenTL(IN OUT MV_GENTL_IF_INFO_LIST* pstIFList, IN const char * strGenTLPath);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ��GenTL Interfaceö���豸
 *  @param  pstIFInfo                   [IN]            Interface��Ϣ
 *  @param  pstDevList                  [OUT]           �豸�б�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �豸�б���ڴ�����SDK�ڲ�����ģ����̵߳��øýӿ�ʱ������豸�б��ڴ���ͷź����룬\n
             ���龡��������߳�ö�ٲ�����
 
 *  @~english
 *  @brief  Enumerate Devices with GenTL interface
 *  @param  pstIFInfo                   [IN]            Interface information
 *  @param  pstDevList                  [OUT]           Device List
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks The memory of the list is allocated within the SDK. When the interface is invoked by multiple threads, the memory of the device list will be released and applied.\n
             It is recommended to avoid multithreaded enumeration operations as much as possible.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_EnumDevicesByGenTL(IN MV_GENTL_IF_INFO* pstIFInfo, IN OUT MV_GENTL_DEV_INFO_LIST* pstDevList);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͨ��GenTL�豸��Ϣ�����豸���
 *  @param  handle                      [OUT]           �豸���
 *  @param  pstDevInfo                  [IN]            �豸��Ϣ�ṹ��ָ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����������豸��Ϣ���������ڲ��������Դ�ͳ�ʼ���ڲ�ģ�顣
 
 *  @~english
 *  @brief  Create Device Handle with GenTL Device Info
 *  @param  handle                      [OUT]           Device handle
 *  @param  pstDevInfo                  [IN]            Device Information
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Create required resources within library and initialize internal module according to input device information.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_CreateHandleByGenTL(OUT void ** handle, IN const MV_GENTL_DEV_INFO* pstDevInfo);


/************************************************************************/
/* XML������������                                                      */
/* XML parse tree generation                                            */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������XML
 *  @param  handle                      [IN]            �豸���
 *  @param  pData                       [OUT]           XML���ݽ��ջ���
 *  @param  nDataSize                   [IN]            ���ջ����С
 *  @param  pnDataLen                   [OUT]           ʵ�����ݴ�С
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks ��pDataΪNULL��nDataSize��ʵ�ʵ�xml�ļ�Сʱ�����������ݣ���pnDataLen����xml�ļ���С��\n
             ��pDataΪ��Ч�����ַ���һ����㹻��ʱ�������������ݱ����ڸû������棬����pnDataLen����xml�ļ�ʵ�ʴ�С��
 
 *  @~english
 *  @brief  Get camera feature tree XML
 *  @param  handle                      [IN]            Device handle
 *  @param  pData                       [OUT]           XML data receiving buffer
 *  @param  nDataSize                   [IN]            Buffer size
 *  @param  pnDataLen                   [OUT]           Actual data length
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks When pData is NULL or nDataSize than the actual XML file hours, do not copy the data, returned by pnDataLen XML file size.\n
             When pData is a valid cache address and the cache is large enough, copy the full data into the cache, and pnDataLen returns the actual size of the XML file.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_GetGenICamXML(IN void* handle, IN OUT unsigned char* pData, IN unsigned int nDataSize, OUT unsigned int* pnDataLen);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��õ�ǰ�ڵ�ķ���ģʽ
 *  @param  handle                      [IN]            �豸���
 *  @param  strName                     [IN]            �ڵ�����
 *  @param  penAccessMode               [OUT]           �ڵ�ķ���ģʽ
 *  @return �ɹ�������MV_OK�����󣬷��ش�����

 *  @~english
 *  @brief  Get Access mode of cur node
 *  @param  handle                      [IN]            Device handle
 *  @param  strName                     [IN]            Name of node
 *  @param  penAccessMode               [OUT]           Access mode of the node
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_GetNodeAccessMode(IN void* handle, IN const char * pstrName, OUT MV_XML_AccessMode *penAccessMode);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��õ�ǰ�ڵ������
 *  @param  handle                      [IN]            �豸���
 *  @param  strName                     [IN]            �ڵ�����
 *  @param  penInterfaceType            [OUT]           �ڵ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 *  @remarks �ýӿڿ����ڵ������ܽӿ�֮ǰ����ǰ֪���ڵ����ͣ������û�ѡ����ʵ����ܽӿڽ��нڵ�ֵ�����úͻ�ȡ��

 *  @~english
 *  @brief  Get Interface Type of cur node
 *  @param  handle                      [IN]            Device handle
 *  @param  strName                     [IN]            Name of node
 *  @param  penInterfaceType            [OUT]           Interface Type of the node
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks The interface can know the node type in advance before calling the universal interface, so as to facilitate users to select the appropriate universal interface for setting and obtaining the node value.
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_GetNodeInterfaceType(IN void* handle, IN const char * pstrName, OUT MV_XML_InterfaceType *penInterfaceType);

/************************************************************************/
/* ���ӽӿ�                                   							*/
/* Additional interface                                                 */
/************************************************************************/
/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͼƬ��֧��Bmp��Jpeg.
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSaveParam                [IN][OUT]       ����ͼƬ�����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ͨ�����ӿڿ��Խ����豸�ɼ�����ԭʼͼ������ת����JPEG����BMP�ȸ�ʽ�������ָ���ڴ��У�Ȼ���û����Խ�ת��֮�������ֱ�ӱ����ͼƬ�ļ����ýӿڵ����޽ӿ�˳��Ҫ����ͼ��Դ���ݾͿ��Խ���ת���������ȵ���MV_CC_GetOneFrameTimeout����MV_CC_RegisterImageCallBackEx���ûص���������ȡһ֡ͼ�����ݣ�Ȼ����ͨ���ýӿ�ת����ʽ�� \n
             MV_CC_SaveImageEx2��MV_CC_SaveImageEx���Ӳ���handle��Ϊ�˱�֤�������ӿڵ�ͳһ��
 
 *  @~english
 *  @brief  Save image, support Bmp and Jpeg.
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSaveParam                [IN][OUT]       Save image parameters structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Once there is image data, you can call this API to convert the data. \n
             You can also call MV_CC_GetOneFrameTimeout or MV_CC_RegisterImageCallBackEx or MV_CC_GetImageBuffer to get one image frame and set the callback function, and then call this API to convert the format. \n
             Comparing with the API MV_CC_SaveImageEx, this API added the parameter handle to ensure the unity with other API. 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SaveImageEx2(IN void* handle, MV_SAVE_IMAGE_PARAM_EX* pstSaveParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����ͼ���ļ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSaveFileParam            [IN][OUT]       ����ͼƬ�ļ������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�֧��BMP/JPEG/PNG/TIFF��
 
 *  @~english
 *  @brief  Save the image file.
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSaveFileParam            [IN][OUT]       Save the image file parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API support BMP/JPEG/PNG/TIFF.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SaveImageToFile(IN void* handle, MV_SAVE_IMG_TO_FILE_PARAM* pstSaveFileParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����3D�������ݣ�֧��PLY��CSV��OBJ���ָ�ʽ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstPointDataParam           [IN][OUT]       ����������ݲ����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks 3D���ݸ�ʽ�����3D�ļ���ʽ��֧��PLY/CSV/OBJ��/n
             Ŀǰ֧��PixelType_Gvsp_Coord3D_ABC32��PixelType_Gvsp_Coord3D_ABC32f��PixelType_Gvsp_Coord3D_AB32��PixelType_Gvsp_Coord3D_AB32f��PixelType_Gvsp_Coord3D_AC32��PixelType_Gvsp_Coord3D_AC32f,�ݲ�֧������3D��ʽ��
 
 *  @~english
 *  @brief  Save 3D point data, support PLY��CSV and OBJ
 *  @param  handle                      [IN]            Device handle
 *  @param  pstPointDataParam           [IN][OUT]       Save 3D point data parameters structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Save the 3D data format to 3D file format��support PLY��CSV and OBJ��/n
             only support PixelType_Gvsp_Coord3D_ABC32��PixelType_Gvsp_Coord3D_ABC32f��PixelType_Gvsp_Coord3D_AB32��PixelType_Gvsp_Coord3D_AB32f��PixelType_Gvsp_Coord3D_AC32��PixelType_Gvsp_Coord3D_AC32f,Other 3D format is not supported now.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SavePointCloudData(IN void* handle, MV_SAVE_POINT_CLOUD_PARAM* pstPointDataParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ����ת
 *  @param  handle                      [IN]            �豸���
 *  @param  pstRotateParam              [IN][OUT]       ͼ����ת�����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ֧��MONO8/RGB24/BGR24��ʽ���ݵ�90/180/270����ת��
 
 *  @~english
 *  @brief  Rotate Image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstRotateParam              [IN][OUT]       Rotate image parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API only support 90/180/270 rotation of data in the MONO8/RGB24/BGR24 format.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RotateImage(IN void* handle, IN OUT MV_CC_ROTATE_IMAGE_PARAM* pstRotateParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ��ת
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFlipParam                [IN][OUT]       ͼ��ת�����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ֧��MONO8/RGB24/BGR24��ʽ���ݵĴ�ֱ��ˮƽ��ת��
 
 *  @~english
 *  @brief  Flip Image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFlipParam                [IN][OUT]       Flip image parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API only support vertical and horizontal reverse of data in the MONO8/RGB24/BGR24 format.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_FlipImage(IN void* handle, IN OUT MV_CC_FLIP_IMAGE_PARAM* pstFlipParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ظ�ʽת��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCvtParam                 [IN][OUT]       ���ظ�ʽת�������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ͨ�����ӿڿ��Խ����豸�ɼ�����ԭʼͼ������ת�����û���������ظ�ʽ�������ָ���ڴ��С��ýӿڵ����޽ӿ�˳��Ҫ����ͼ��Դ���ݾͿ��Խ���ת���������ȵ���MV_CC_GetOneFrameTimeout����MV_CC_RegisterImageCallBackEx���ûص���������ȡһ֡ͼ�����ݣ�Ȼ����ͨ���ýӿ�ת����ʽ������豸��ǰ�ɼ�ͼ����JPEGѹ���ĸ�ʽ����֧�ֵ��øýӿڽ���ת���� \n
 
 *  @~english
 *  @brief  Pixel format conversion
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCvtParam                 [IN][OUT]       Convert Pixel Type parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API is used to transform the collected original data to pixel format and save to specified memory. There is no order requirement to call this API, the transformation will execute when there is image data. First call MV_CC_GetOneFrameTimeout or MV_CC_RegisterImageCallBackEx to set callback function, and get a frame of image data, then call this API to transform the format. \n
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_ConvertPixelType(IN void* handle, IN OUT MV_CC_PIXEL_CONVERT_PARAM* pstCvtParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ò�ֵ�㷨����
 *  @param  handle                      [IN]            �豸���
 *  @param  nBayerCvtQuality            [IN]            Bayer�Ĳ�ֵ����  0-���� 1-���� 2-���ţ�Ĭ��Ϊ���ţ�
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �����ڲ�ͼ��ת���ӿڵ�Bayer��ֵ�㷨���Ͳ�����MV_CC_ConvertPixelType��MV_CC_GetImageForRGB/BGR�ӿ��ڲ�ʹ�õĲ�ֵ�㷨�Ǹýӿ����趨�ġ�
 
 *  @~english
 *  @brief  Interpolation algorithm type setting
 *  @param  handle                      [IN]            Device handle
 *  @param  nBayerCvtQuality            [IN]            Bayer interpolation method  0-Fast 1-Equilibrium 2-Optimal
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Set the bell interpolation quality parameters of the internal image conversion interface, and the interpolation algorithm used in the MV_CC_ConvertPixelType and MV_CC_GetImageForRGB/BGR interfaces is set by this interface.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerCvtQuality(IN void* handle, IN unsigned int nBayerCvtQuality);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��Gammaֵ
 *  @param  handle                      [IN]            �豸���
 *  @param  fBayerGammaValue            [IN]            Gammaֵ[0.1,4.0]
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���ø�ֵ���ڵ���MV_CC_ConvertPixelType��MV_CC_SaveImageEx2�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��
 
 *  @~english
 *  @brief  Set Gamma value
 *  @param  handle                      [IN]            Device handle
 *  @param  fBayerGammaValue            [IN]            Gamma value[0.1,4.0]
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After setting the value, it work in the calling MV_CC_ConvertPixelType\MV_CC_SaveImageEx2 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerGammaValue(IN void* handle, IN float fBayerGammaValue);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��Gamma��Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstGammaParam               [IN]            Gamma��Ϣ   
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���ø���Ϣ���ڵ���MV_CC_ConvertPixelType��MV_CC_SaveImageEx2�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��

 *  @~english
 *  @brief  Set Gamma param
 *  @param  handle                      [IN]            Device handle
 *  @param  pstGammaParam               [IN]            Gamma param
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After setting the param, it work in the calling MV_CC_ConvertPixelType\MV_CC_SaveImageEx2 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerGammaParam(IN void* handle, IN MV_CC_GAMMA_PARAM* pstGammaParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��CCMʹ�ܺ;�������ϵ��Ĭ��1024
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCCMParam                 [IN]            CCM����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����CCM������CCM������ڵ���MV_CC_ConvertPixelType��MV_CC_SaveImageEx2�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��
 
 *  @~english
 *  @brief  Set CCM param,Scale default 1024
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCCMParam                 [IN]            CCM parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After enable the color correction and set the color correction matrix, It work in the calling MV_CC_ConvertPixelType\MV_CC_SaveImageEx2 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerCCMParam(IN void* handle, IN MV_CC_CCM_PARAM* pstCCMParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��CCMʹ�ܺ;���
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCCMParam                 [IN]            CCM����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����CCM������CCM������ڵ���MV_CC_ConvertPixelType��MV_CC_SaveImageEx2�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��

 *  @~english
 *  @brief  Set CCM param
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCCMParam                 [IN]            CCM parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After enable the color correction and set the color correction matrix, It work in the calling MV_CC_ConvertPixelType\MV_CC_SaveImageEx2 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerCCMParamEx(IN void* handle, IN MV_CC_CCM_PARAM_EX* pstCCMParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����Bayer��ʽ��CLUTʹ�ܺ���Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstCLUTParam                [IN]            CLUT����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����CLUT������CLUT��Ϣ���ڵ���MV_CC_ConvertPixelType��MV_CC_SaveImageEx2�ӿڽ�Bayer8/10/12/16��ʽת��RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64ʱ��Ч��

 *  @~english
 *  @brief  Set CLUT param
 *  @param  handle                      [IN]            Device handle
 *  @param  pstCLUTParam                [IN]            CLUT parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks After enable the CLUT and set CLUT, It work in the calling MV_CC_ConvertPixelType\MV_CC_SaveImageEx2 API convert Bayer8/10/12/16 to RGB24/48�� RGBA32/64��BGR24/48��BGRA32/64.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBayerCLUTParam(IN void* handle, IN MV_CC_CLUT_PARAM* pstCLUTParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ��Աȶȵ���
 *  @param  handle                      [IN]            �豸���
 *  @param  pstContrastParam            [IN]            �Աȶȵ��ڲ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 

 *  @~english
 *  @brief  Adjust image contrast
 *  @param  handle                      [IN]            Device handle
 *  @param  pstContrastParam            [IN]            Contrast parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_ImageContrast(IN void* handle, IN OUT MV_CC_CONTRAST_PARAM* pstContrastParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ͼ����
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSharpenParam             [IN]            �񻯲���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 

 *  @~english
 *  @brief  Image sharpen
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSharpenParam             [IN]            Sharpen parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_ImageSharpen(IN void* handle, IN OUT MV_CC_SHARPEN_PARAM* pstSharpenParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ɫ��У��������CCM��CLUT��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstColorCorrectParam        [IN]            ɫ��У������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�֧�ֵ���CCM����CLUT��Ҳ֧��ͬʱ����CCM��CLUT���û�����ͨ��CCM��CLUT��Ϣ�е�ʹ�ܿ��ؽ���ѡ��

 *  @~english
 *  @brief  Color Correct(include CCM and CLUT)
 *  @param  handle                      [IN]            Device handle
 *  @param  pstColorCorrectParam        [IN]            Color Correct parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API supports CCM or CLUT alone, as well as CCM and CLUT at the same time. The user can select by means of the enable switch in CCM and CLUT information.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_ColorCorrect(IN void* handle, IN OUT MV_CC_COLOR_CORRECT_PARAM* pstColorCorrectParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��������
 *  @param  handle                      [IN]            �豸���
 *  @param  pstNoiseEstimateParam       [IN]            �������Ʋ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ����û�ѡ��ȫͼ���������ƣ�nROINum������0��pstROIRect���ÿա�

 *  @~english
 *  @brief  Noise Estimate
 *  @param  handle                      [IN]            Device handle
 *  @param  pstNoiseEstimateParam       [IN]            Noise Estimate parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks If the user selects the full image, nROINum can be typed with 0 and pstROIRect empty.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_NoiseEstimate(IN void* handle, IN OUT MV_CC_NOISE_ESTIMATE_PARAM* pstNoiseEstimateParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ������
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSpatialDenoiseParam      [IN]            ���������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 

 *  @~english
 *  @brief  Spatial Denoise
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSpatialDenoiseParam      [IN]            Spatial Denoise parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SpatialDenoise(IN void* handle, IN OUT MV_CC_SPATIAL_DENOISE_PARAM* pstSpatialDenoiseParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  LSC�궨
 *  @param  handle                      [IN]            �豸���
 *  @param  pstLSCCalibParam            [IN]            �궨����
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 

 *  @~english
 *  @brief  LSC Calib
 *  @param  handle                      [IN]            Device handle
 *  @param  pstLSCCalibParam            [IN]            LSC Calib parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_LSCCalib(IN void* handle, IN OUT MV_CC_LSC_CALIB_PARAM* pstLSCCalibParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  LSCУ��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstLSCCorrectParam          [IN]            У������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 

 *  @~english
 *  @brief  LSC Correct
 *  @param  handle                      [IN]            Device handle
 *  @param  pstLSCCorrectParam          [IN]            LSC Correct parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_LSCCorrect(IN void* handle, IN OUT MV_CC_LSC_CORRECT_PARAM* pstLSCCorrectParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  �������
 *  @param  handle                      [IN]            �豸���
 *  @param  pstDecodeParam              [IN][OUT]       �����������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks ���������ȡ��������ѹ����������������ݣ�ͬʱ֧�ֽ�����ǰ���ʵʱͼ���ˮӡ��Ϣ���������������������ǵ�ǰ������߲���ʵʱȡ���ģ���ˮӡ���������쳣��
 
 *  @~english
 *  @brief  High Bandwidth Decode
 *  @param  handle                      [IN]            Device handle
 *  @param  pstDecodeParam              [IN][OUT]       High Bandwidth Decode parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks Decode the lossless compressed data from the camera into raw data 
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_HB_Decode(IN void* handle, IN OUT MV_CC_HB_DECODE_PARAM* pstDecodeParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸����
 *  @param  handle                      [IN]            �豸���
 *  @param  strFileName                 [IN]            �����ļ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Save camera feature
 *  @param  handle                      [IN]            Device handle
 *  @param  strFileName                 [IN]            File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_FeatureSave(IN void* handle, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸����
 *  @param  handle                      [IN]            �豸���
 *  @param  strFileName                 [IN]            �����ļ���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Load camera feature
 *  @param  handle                      [IN]            Device handle
 *  @param  strFileName                 [IN]            File name
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_FeatureLoad(IN void* handle, IN const char* strFileName);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���豸��ȡ�ļ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Read the file from the camera
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_FileAccessRead(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);

/********************************************************************//**
 *  @~chinese
 *  @brief  ���ļ�д���豸
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFileAccess               [IN]            �ļ���ȡ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Write the file to camera
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFileAccess               [IN]            File access structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_FileAccessWrite(IN void* handle, IN MV_CC_FILE_ACCESS * pstFileAccess);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�ļ���ȡ�Ľ���
 *  @param  handle                      [IN]            �豸���
 *  @param  pstFileAccessProgress       [IN]            ��������
 *  @return �ɹ�������MV_OK�����󣬷��ش����� ����ǰ�ļ���ȡ��״̬��
 
 *  @~english
 *  @brief  Get File Access Progress 
 *  @param  handle                      [IN]            Device handle
 *  @param  pstFileAccessProgress       [IN]            File access Progress
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetFileAccessProgress(IN void* handle, OUT MV_CC_FILE_ACCESS_PROGRESS * pstFileAccessProgress);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ʼ¼��
 *  @param  handle                      [IN]            �豸���
 *  @param  pstRecordParam              [IN]            ¼������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Start Record
 *  @param  handle                      [IN]            Device handle
 *  @param  pstRecordParam              [IN]            Record param structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_StartRecord(IN void* handle, IN MV_CC_RECORD_PARAM* pstRecordParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  ����¼������
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInputFrameInfo           [IN]            ¼�����ݽṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Input RAW data to Record
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInputFrameInfo           [IN]            Record data structure
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_InputOneFrame(IN void* handle, IN MV_CC_INPUT_FRAME_INFO * pstInputFrameInfo);

/********************************************************************//**
 *  @~chinese
 *  @brief  ֹͣ¼��
 *  @param  handle                      [IN]            �豸���
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @~english
 *  @brief  Stop Record
 *  @param  handle                      [IN]            Device handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_StopRecord(IN void* handle);


/************************************************************************/
/* ������ʹ�õĽӿ�                     	                    		*/
/* Interfaces not recommended                                           */
/************************************************************************/
/************************************************************************
 *  @fn     MV_CC_GetImageInfo
 *  @brief  ��ȡͼ�������Ϣ
 *  @param  handle                      [IN]            �豸���
 *  @param  pstInfo                     [IN][OUT]       ���ظ��������й����ͼ�������Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @fn     MV_CC_GetImageInfo
 *  @brief  Get basic information of image
 *  @param  handle                      [IN]            Device handle
 *  @param  pstInfo                     [IN][OUT]       Structure pointer of image basic information
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetImageInfo(IN void* handle, IN OUT MV_IMAGE_BASIC_INFO* pstInfo);

/************************************************************************
 *  @fn     MV_CC_SetSDKLogPath()
 *  @brief  ����SDK��־·���������־����MvLogServer�����ã���ýӿ���Ч��Ĭ����־����Ϊ����״̬��
 *  @param  pSDKLogPath             [IN]           SDK��־·��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @fn     MV_CC_SetSDKLogPath()
 *  @brief  Set SDK log path
 *  @param  pSDKLogPath             [IN]           SDK log path
 *  @return Access, return true. Not access, return false
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetSDKLogPath(IN const char * pSDKLogPath);

/************************************************************************
 *  @fn     MV_CC_GetTlProxy
 *  @brief  ��ȡGenICam����
 *  @param  handle                 [IN]           �����ַ
 *  @return GenICam������ָ�� ����������ֵ��NULL���쳣����NULL
 
 *  @fn     MV_CC_GetTlProxy
 *  @brief  Get GenICam proxy
 *  @param  handle                 [IN]           Handle address
 *  @return GenICam proxy pointer, normal, return non-NULL; exception, return NULL
 ************************************************************************/
MVSDKEXPORT_API void* __stdcall MV_CC_GetTlProxy(IN void* handle);

/***********************************************************************
 *  @fn         MV_XML_GetRootNode
 *  @brief      ��ȡ���ڵ�
 *  @param       handle                 [IN]          ���
 *  @param       pstNode                [OUT]         ���ڵ���Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_XML_GetRootNode
 *  @brief      Get root node
 *  @param       handle                 [IN]          Handle
 *  @param       pstNode                [OUT]         Root node information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_GetRootNode(IN void* handle, IN OUT MV_XML_NODE_FEATURE* pstNode);

/***********************************************************************
 *  @fn         MV_XML_GetChildren
 *  @brief      ��xml�л�ȡָ���ڵ�������ӽڵ㣬���ڵ�ΪRoot
 *  @param       handle                 [IN]          ���
 *  @param       pstNode                [IN]          ���ڵ���Ϣ�ṹ��
 *  @param       pstNodesList           [OUT]         �ڵ��б�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_XML_GetChildren
 *  @brief      Get all children node of specific node from xml, root node is Root
 *  @param       handle                 [IN]          Handle
 *  @param       pstNode                [IN]          Root node information structure
 *  @param       pstNodesList           [OUT]         Node information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_GetChildren(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT MV_XML_NODES_LIST* pstNodesList);

/***********************************************************************
 *  @fn         MV_XML_GetNodeFeature
 *  @brief      ��õ�ǰ�ڵ������
 *  @param       handle                 [IN]          ���
 *  @param       pstNode                [IN]          ���ڵ���Ϣ�ṹ��
 *  @param       pstFeature             [OUT]         ��ǰ�ڵ����Խṹ�壬
                           pstFeature ����ṹ�����ݲο� MV_XML_FEATURE_x
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_XML_GetNodeFeature
 *  @brief      Get current node feature
 *  @param       handle                 [IN]          Handle
 *  @param       pstNode                [IN]          Root node information structure
 *  @param       pstFeature             [OUT]         Current node feature structure
                           Details of pstFeature refer to MV_XML_FEATURE_x
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_GetNodeFeature(IN void* handle, IN MV_XML_NODE_FEATURE* pstNode, IN OUT void* pstFeature);

/***********************************************************************
 *  @fn         MV_XML_UpdateNodeFeature
 *  @brief      ���½ڵ�
 *  @param       handle                 [IN]          ���
 *  @param       enType                 [IN]          �ڵ�����
 *  @param       pstFeature             [OUT]         ��ǰ�ڵ����Խṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_XML_UpdateNodeFeature
 *  @brief      Update node
 *  @param       handle                 [IN]          Handle
 *  @param       enType                 [IN]          Node type
 *  @param       pstFeature             [OUT]         Current node feature structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_UpdateNodeFeature(IN void* handle, IN enum MV_XML_InterfaceType enType, IN void* pstFeature);

// �нڵ���Ҫ����ʱ�Ļص�����
// ������MV_XML_UpdateNodeFeature�ӿڸ��½ڵ�����ʱ��ע��Ļص�����cbUpdate����pstNodesList�з�����֮������Ľڵ�
/***********************************************************************
 *  @fn         MV_XML_RegisterUpdateCallBack
 *  @brief      ע����»ص�
 *  @param       handle                 [IN]          ���
 *  @param       cbUpdate               [IN]          �ص�����ָ��
 *  @param       pUser                  [IN]          �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_XML_RegisterUpdateCallBack
 *  @brief      Register update callback
 *  @param       handle                 [IN]          Handle
 *  @param       cbUpdate               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_XML_RegisterUpdateCallBack(IN void* handle, 
                                                           IN void(__stdcall* cbUpdate)(enum MV_XML_InterfaceType enType, void* pstFeature, MV_XML_NODES_LIST* pstNodesList, void* pUser),
                                                           IN void* pUser);

/************************************************************************/
/* ���õĽӿڣ����ڸ��Ż��Ľӿڿ��滻��                     			*/
/* Abandoned interface                                                  */
/************************************************************************/
/***********************************************************************
 *  @fn         MV_CC_GetOneFrame
 *  @brief      ��ȡһ֡ͼ�񣬴˺���Ϊ��ѯʽ��ȡ��ÿ�ε��ò�ѯ�ڲ�������
                �����ݣ���������Χ���ݣ������ݷ��ش�����
                ���ýӿ������ã�������� MV_CC_GetOneFrameTimeOut�ӿڣ�
 *  @param       handle                 [IN]          ���
 *  @param       pData                  [OUT]         ͼ�����ݽ���ָ��
 *  @param       nDataSize              [IN]          ���ջ����С
 *  @param       pFrameInfo             [OUT]         ͼ����Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_CC_GetOneFrame
 *  @brief      Get one frame data, this function is using query to get data, 
                query whether the internal cache has data, return data if there has, return error code if no data
                (This interface is abandoned, it is recommended to use the MV_CC_GetOneFrameTimeOut)
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetOneFrame(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO* pFrameInfo);

/***********************************************************************
 *  @fn         MV_CC_GetOneFrameEx
 *  @brief      ��ȡһ֡trunck���ݣ��˺���Ϊ��ѯʽ��ȡ��ÿ�ε��ò�ѯ�ڲ�
                �����������ݣ���������Χ���ݣ������ݷ��ش�����
                ���ýӿ������ã�������� MV_CC_GetOneFrameTimeOut�ӿڣ�
 *  @param       handle                 [IN]          ���
 *  @param       pData                  [OUT]         ͼ�����ݽ���ָ��
 *  @param       nDataSize              [IN]          ���ջ����С
 *  @param       pFrameInfo             [OUT]         ͼ����Ϣ�ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_CC_GetOneFrameEx
 *  @brief      Get one frame of trunck data, this function is using query to get data, 
                query whether the internal cache has data, return data if there has, return error code if no data
                (This interface is abandoned, it is recommended to use the MV_CC_GetOneFrameTimeOut)
 *  @param       handle                 [IN]          Handle
 *  @param       pData                  [OUT]         Recevied image data pointer
 *  @param       nDataSize              [IN]          Recevied buffer size
 *  @param       pFrameInfo             [OUT]         Image information structure
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetOneFrameEx(IN void* handle, IN OUT unsigned char * pData , IN unsigned int nDataSize, IN OUT MV_FRAME_OUT_INFO_EX* pFrameInfo);

/***********************************************************************
 *  @fn         MV_CC_RegisterImageCallBack
 *  @brief      ע��ͼ�����ݻص����ýӿ������ã�������� MV_CC_RegisterImageCallBackEx�ӿڣ�
 *  @param       handle                 [IN]          ���
 *  @param       cbOutput               [IN]          �ص�����ָ��
 *  @param       pUser                  [IN]          �û��Զ������
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_CC_RegisterImageCallBack
 *  @brief      Register image data callback (This interface is abandoned, it is recommended to use the MV_CC_RegisterImageCallBackEx)
 *  @param       handle                 [IN]          Handle
 *  @param       cbOutput               [IN]          Callback function pointer
 *  @param       pUser                  [IN]          User defined variable
 *  @return Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterImageCallBack(void* handle, 
                                                         void(__stdcall* cbOutput)(unsigned char * pData, MV_FRAME_OUT_INFO* pFrameInfo, void* pUser),
                                                         void* pUser);

/************************************************************************
 *  @fn     MV_CC_SaveImage
 *  @brief  ����ͼƬ���ýӿ������ã�������� MV_CC_SaveImageEx2�ӿڣ�
 *  @param  pSaveParam             [IN][OUT]          ����ͼƬ�����ṹ��
                       pData;              // [IN]     �������ݻ���
                       nDataLen;           // [IN]     �������ݴ�С
                       enPixelType;        // [IN]     �������ݵ����ظ�ʽ
                       nWidth;             // [IN]     ͼ���
                       nHeight;            // [IN]     ͼ���
                       pImageBuffer;       // [OUT]    ���ͼƬ����
                       nImageLen;          // [OUT]    ���ͼƬ��С
                       nBufferSize;        // [IN]     �ṩ�������������С
                       enImageType;        // [IN]     ���ͼƬ��ʽ
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @fn     MV_CC_SaveImage
 *  @brief  Save image (This interface is abandoned, it is recommended to use the MV_CC_SaveImageEx)
 *  @param  pSaveParam             [IN][OUT]          Save image parameters structure
                       pData;              // [IN]     Input data buffer
                       nDataLen;           // [IN]     Input data size
                       enPixelType;        // [IN]     Input data pixel format
                       nWidth;             // [IN]     Width
                       nHeight;            // [IN]     Height
                       pImageBuffer;       // [OUT]    Output image buffer
                       nImageLen;          // [OUT]    Output image size
                       nBufferSize;        // [IN]     Provided output buffer size
                       enImageType;        // [IN]     Output image type
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SaveImage(IN OUT MV_SAVE_IMAGE_PARAM* pSaveParam);

/************************************************************************
 *  @fn     MV_CC_SaveImageEx
 *  @brief  ����ͼƬ��֧��Bmp��Jpeg.����������50-99֮ǰ ���ýӿ������ã�������� MV_CC_SaveImageEx2�ӿڣ�
 *  @param  pSaveParam             [IN][OUT]          ����ͼƬ�����ṹ��
                       pData;              // [IN]     �������ݻ���
                       nDataLen;           // [IN]     �������ݴ�С
                       enPixelType;        // [IN]     �������ݵ����ظ�ʽ
                       nWidth;             // [IN]     ͼ���
                       nHeight;            // [IN]     ͼ���
                       pImageBuffer;       // [OUT]    ���ͼƬ����
                       nImageLen;          // [OUT]    ���ͼƬ��С
                       nBufferSize;        // [IN]     �ṩ�������������С
                       enImageType;        // [IN]     ���ͼƬ��ʽ
                       nJpgQuality;        // [IN]     ��������, (50-99]
                       nReserved[4];
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 
 *  @fn     MV_CC_SaveImageEx
 *  @brief  Save image, support Bmp and Jpeg. Encoding quality, (50-99]
 *  @param  pSaveParam             [IN][OUT]           Save image parameters structure
                       pData;              // [IN]     Input data buffer
                       nDataLen;           // [IN]     Input data size
                       enPixelType;        // [IN]     Pixel format of input data
                       nWidth;             // [IN]     Image width
                       nHeight;            // [IN]     Image height
                       pImageBuffer;       // [OUT]    Output image buffer
                       nImageLen;          // [OUT]    Output image size
                       nBufferSize;        // [IN]     Output buffer size provided
                       enImageType;        // [IN]     Output image format
                       nJpgQuality;        // [IN]     Encoding quality, (50-99]
                       nReserved[4];
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SaveImageEx(IN OUT MV_SAVE_IMAGE_PARAM_EX* pSaveParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  Bayer�������ƣ��ýӿ������ã�������� MV_CC_NoiseEstimate�ӿڣ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstNoiseEstimateParam       [IN][OUT]       Bayer�������Ʋ����ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ֧��Bayer8/Bayer10/Bayer12��ʽ,����Bayer��ʽ����ת��Bayer8/Bayer10/Bayer12��ʽ��\n
             �ýӿ�ֻ���ڴ���˾�ض���ɫ�����ſ�������ʹ�ã���������Ͽ����ߵ��ߺ󣬼���ʹ�øýӿڻᱨ��
 
 *  @~english
 *  @brief  Noise estimate of Bayer format
 *  @param  handle                      [IN]            Device handle
 *  @param  pstNoiseEstimateParam       [IN][OUT]       Noise estimate parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API only support Bayer8/Bayer10/Bayer12 format, other Bayer format must Convert to Bayer8/Bayer10/Bayer12 format.\n
             This API is only available when the camera is turned on, and when the camera is disconnected or disconnected, continuing to use This API will return an error.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_BayerNoiseEstimate(IN void* handle, IN OUT MV_CC_BAYER_NOISE_ESTIMATE_PARAM* pstNoiseEstimateParam);

/********************************************************************//**
 *  @~chinese
 *  @brief  Bayer�����루�ýӿ������ã�������� MV_CC_SpatialDenoise�ӿڣ�
 *  @param  handle                      [IN]            �豸���
 *  @param  pstSpatialDenoiseParam      [IN][OUT]       Bayer����������ṹ��
 *  @return �ɹ�������MV_OK�����󣬷��ش����� 
 *  @remarks �ýӿ�ֻ֧��Bayer8/Bayer10/Bayer12��ʽ,����Bayer��ʽ����ת��Bayer8/Bayer10/Bayer12��ʽ��\n
             �ýӿ�ֻ���ڴ���˾�ض���ɫ�����ſ�������ʹ�ã���������Ͽ����ߵ��ߺ󣬼���ʹ�øýӿڻᱨ��
 
 *  @~english
 *  @brief  Spatial Denoise of Bayer format
 *  @param  handle                      [IN]            Device handle
 *  @param  pstSpatialDenoiseParam      [IN][OUT]       Spatial Denoise parameter structure
 *  @return Success, return MV_OK. Failure, return error code
 *  @remarks This API only support Bayer8/Bayer10/Bayer12 format, other Bayer format must Convert to Bayer8/Bayer10/Bayer12 format.\n
             This API is only available when the camera is turned on, and when the camera is disconnected or disconnected, continuing to use This API will return an error.
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_BayerSpatialDenoise(IN void* handle, IN OUT MV_CC_BAYER_SPATIAL_DENOISE_PARAM* pstSpatialDenoiseParam);

/************************************************************************
 *  @fn     MV_GIGE_ForceIp
 *  @brief  ǿ��IP���ýӿ������ã�������� MV_GIGE_ForceIpEx�ӿڣ�
 *  @param  handle���豸���
 *  @param  nIP               [IN]      ���õ�IP
 *  @return �����ش�����
 
 *  @fn     MV_GIGE_ForceIp
 *  @brief  Force IP (This interface is abandoned, it is recommended to use the MV_GIGE_ForceIpEx)
 *  @param  handle Handle
 *  @param  nIP               [IN]      IP to set
 *  @return Refer to error code
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_ForceIp(IN void* handle, unsigned int nIP);

/************************************************************************
 *  @fn     MV_CC_RegisterEventCallBack
 *  @brief  ע���¼��ص����ýӿ������ã�������� MV_CC_RegisterEventCallBackEx�ӿڣ�
 *  @param  handle���豸���
 *  @param  cbEvent           [IN]      �¼��ص�����ָ��
 *  @param  pUser             [IN]      �û��Զ������
 *  @return �����ش�����
 
 *  @fn     MV_CC_RegisterEventCallBack
 *  @brief  Register event callback (this interface has been deprecated and is recommended to be converted to the MV_CC_RegisterEventCallBackEx interface)
 *  @param  handle���豸���
 *  @param  cbEvent           [IN]      event callback pointer
 *  @param  pUser             [IN]      User defined value
 *  @return �����ش�����
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_RegisterEventCallBack(void* handle, void(__stdcall* cbEvent)(unsigned int nExternalEventId, void* pUser), void* pUser);

/***********************************************************************
 *  @fn         MV_CC_Display
 *  @brief      ��ʾͼ��ע����ʾ���ڣ��ڲ��Զ���ʾ����MV_CC_GetImageBuffer����ͬʱʹ�ã��������MV_CC_DisplayOneFrame�ӿڣ�
 *  @param       handle                 [IN]          ���
 *  @param       hWnd                   [IN]          ��ʾ���ھ��
 *  @return �ɹ�������MV_OK�����󣬷��ش�����
 
 *  @fn         MV_CC_Display
 *  @brief      Display one frame image, register display window, automatic display internally
 *  @param      handle                 [IN]          Handle
 *  @param      hWnd                   [IN]          Display Window Handle
 *  @return     Success, return MV_OK. Failure, return error code
 ***********************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_Display(IN void* handle, void* hWnd);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           OUT MVCC_INTVALUE *pIntValue);
 *  @brief  ��ȡInteger����ֵ���������MV_CC_GetIntValueEx�ӿڣ�
 *  @param  void* handle                [IN]        ������
 *  @param  char* strKey                [IN]        ���Լ�ֵ�����ȡ�����Ϣ��Ϊ"Width"
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�������Խṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           OUT MVCC_INTVALUE *pIntValue);
 *  @brief  Get Integer value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "Width" to get width
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of camera features
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetIntValue(IN void* handle,IN const char* strKey,OUT MVCC_INTVALUE *pIntValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           IN unsigned int nValue);
 *  @brief  ����Integer������ֵ���������MV_CC_SetIntValueEx�ӿڣ�
 *  @param  void* handle                [IN]        ������
 *  @param  char* strKey                [IN]        ���Լ�ֵ�����ȡ�����Ϣ��Ϊ"Width"
 *          const unsigned int nValue   [IN]        ��Ҫ���õ����������ֵ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetIntValue(IN void* handle,
                                                           IN const char* strKey,
                                                           IN unsigned int nValue);
 *  @brief  Set Integer value
 *  @param  void* handle                [IN]        Handle
 *  @param  char* strKey                [IN]        Key value, for example, using "Width" to set width
 *          const unsigned int nValue   [IN]        Feature value to set
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetIntValue(IN void* handle,IN const char* strKey,IN unsigned int nValue);


/************************************************************************/
/* ���������ȡ�����ã���ģ������нӿ��ѷ���������ʹ�����ܽӿڴ���   */
/* Get and set camara parameters, all interfaces of this module will be replaced by general interface*/
/************************************************************************/
/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡͼ����
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������ȵ���Ϣ�ṹ��ָ��
 *          ���ص�pstValue�ṹ�������
 *                  unsigned int    nCurValue;      // ���������ǰ�Ŀ��ֵ
 *                  unsigned int    nMax;           // ��ʾ���������������õĿ��ֵ
 *                  unsigned int    nMin;           // ��ʾ����������С�����õĿ��ֵ
 *                  unsigned int    nInc;           // ��ʾ������õĿ������������nInc�ı�����������Ч
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
 *          �������ͽṹ������Ľӿڿɲ��մ˽ӿ�
 
 * @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image width
 *  @param  void* handle                [IN]        Camera Handle
 *          MVCC_INTVALUE* pstValue     [IN][OUT]   Returns the information structure pointer about the camera's width for the caller
 *          The meaning of returns pstValue structure
 *                  unsigned int    nCurValue;      // Represents the current width value of the camera
 *                  unsigned int    nMax;           // Indicates the maximum settable width value allowed by the camera
 *                  unsigned int    nMin;           // Indicates the minimum settable width value allowed by the camera
 *                  unsigned int    nInc;           // Indicates that the width increment set by the camera must be a multiple of nInc, otherwise it is invalid
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other Integer structure parameters interface can refer to this interface
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetWidth(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
*  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);
*  @brief  ����ͼ����
*  @param  void* handle                [IN]        ������
*          const unsigned int nValue   [IN]        ��Ҫ���õ������ȵ�ֵ,ע��˿��ֵ������MV_CC_GetWidth�ӿڷ��ص�pstValue�е�nInc�ı����������óɹ�
*  @return �ɹ�,����MV_OK,���������Ƚ������Ϊ��Ӧֵ��ʧ��,���ش�����

* @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image width
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        To set the value of the camera width, note that the width value must be a multiple of nInc in the pstValue returned by the MV_CC_GetWidth interface
 *  @return Success, return MV_OK, and the camera width will change to the corresponding value. Failure, return error code
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetWidth(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡͼ��߶�
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�����߶ȵ���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�����߶���Ϣ���ص��ṹ���У�ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image height
 *  @param  void* handle                [IN]        Camera handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera height to user
 *  @return Success, return MV_OK, and return height information to the structure. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetHeight(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����ͼ��߶�
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ������ȵ�ֵ,ע��˿��ֵ������MV_CC_GetWidth�ӿڷ��ص�pstValue�е�nInc�ı����������óɹ�
 *  @return �ɹ�,����MV_OK,��������߶Ƚ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image height
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        Camera height value to set, note that this value must be times of nInc of pstValue returned by MV_CC_GetWidth
 *  @return Success, return MV_OK, and the camera height will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetHeight(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡͼ��Xƫ��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й����Xƫ�Ƶ���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image X offset
 *  @param  void* handle                [IN]        Camera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera X offset to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetX(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����ͼ��AOIƫ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ����AOI��ֵ
 *  @return �ɹ�,����MV_OK,�������AOIƫ�ƽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image X offset
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        Camera X offset value to set
 *  @return Success, return MV_OK, and the camera X offset will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡͼ��Yƫ��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й����Yƫ�Ƶ���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get image Y offset
 *  @param  void* handle                [IN]        Camera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera Y offset to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAOIoffsetY(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetX(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����ͼ��AOIƫ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ����AOI��ֵ
 *  @return �ɹ�,����MV_OK,�������AOIƫ�ƽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetY(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set image Y offset
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        Camera Y offset value to set
 *  @return Success, return MV_OK, and the camera Y offset will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetAOIoffsetY(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ�ع�����
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�����ع�ֵ���޽ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get exposure lower limit
 *  @param  void* handle                [IN]        Camera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera exposure lower to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeLower(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);
 *  @brief  �����ع�ֵ����
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ��ع�ֵ����
 *  @return �ɹ�,����MV_OK,��������ع����޽������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set exposure lower limit
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        Exposure lower to set
 *  @return Success, return MV_OK, and the camera exposure time lower limit value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeLower(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ�ع�����
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�����ع�ֵ���޽ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get exposure upper limit
 *  @param  void* handle                [IN]        Camera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera exposure upper to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAutoExposureTimeUpper(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);
 *  @brief  �����ع�ֵ����
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ��ع�ֵ����
 *  @return �ɹ�,����MV_OK,��������ع����޽������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set exposure upper limit
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        Exposure upper to set
 *  @return Success, return MV_OK, and the camera exposure time upper limit value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetAutoExposureTimeUpper(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ����ֵ
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�������Ƚṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get brightness
 *  @param  void* handle                [IN]        Camera Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Return pointer of information structure related to camera brightness to user
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBrightness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);
 *  @brief  ��������ֵ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ�����ֵ
 *  @return �ɹ�,����MV_OK,����������Ƚ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set brightness
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        Brightness upper to set
 *  @return Success, return MV_OK, and the camera brightness value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBrightness(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  ��ȡ֡��
 *  @param  void* handle                [IN]        ������
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   ���ظ��������й����֡�ʵ���Ϣ�ṹ��ָ��
 *          ���ص�pstValue�ṹ�������
 *                                      float           fCurValue;      // ��ʾ�����ǰ��֡��
 *                                      float           fMax;           // ��ʾ����������õ����֡��
 *                                      float           fMin;           // ��ʾ����������õ���С֡��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
 *          ���������ͽṹ������Ľӿڿɲ��մ˽ӿ�
 
 * @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get Frame Rate
 *  @param  void* handle                [IN]        Camera Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Return pointer of information structure related to camera frame rate to user
 *          The meaning of returns pstValue structure
 *                                      float           fCurValue;      // Indicates the current frame rate of the camera
 *                                      float           fMax;           // Indicates the maximum frame rate allowed by the camera
 *                                      float           fMin;           // Indicates the minimum frame rate allowed by the camera
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other interface of Float structure parameters can refer to this interface
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetFrameRate(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);
 *  @brief  ����֡��
 *  @param  void* handle                [IN]        ������
 *          const float fValue          [IN]        ��Ҫ���õ����֡��
 *  @return �ɹ�,����MV_OK,�������֡�ʽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 * @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);
 *  @brief  Set frame rate
 *  @param  void* handle                [IN]        Camera Handle
 *          const float fValue          [IN]        Camera frame rate to set 
 *  @return Success, return MV_OK, and camera frame rate will be changed to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetFrameRate(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  ��ȡ����
 *  @param  void* handle                [IN]        ������
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   ���ظ��������й�����������Ϣ�ṹ��ָ��
 *          ���ص�pstValue�ṹ�������
 *                                      float           fCurValue;      // ��ʾ�����ǰ��֡��
 *                                      float           fMax;           // ��ʾ����������õ����֡��
 *                                      float           fMin;           // ��ʾ����������õ���С֡��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
 *          ���������ͽṹ������Ľӿڿɲ��մ˽ӿ�
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get Gain
 *  @param  void* handle                [IN]        Camera Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Return pointer of information structure related to gain to user
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *                                      float           fCurValue;      // Camera current gain
 *                                      float           fMax;           // The maximum gain camera allowed
 *                                      float           fMin;           // The minimum gain camera allowed
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other interface of Float structure parameters can refer to this interface
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetGain(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);
 *  @brief  ����֡��
 *  @param  void* handle                [IN]        ������
 *          const float fValue          [IN]        ��Ҫ���õ����֡��
 *  @return �ɹ�,����MV_OK,�������֡�ʽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);
 *  @brief  Set Gain
 *  @param  void* handle                [IN]        Camera Handle
 *          const float fValue          [IN]        Gain value to set
 *  @return Success, return MV_OK, and the camera gain value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetGain(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  ��ȡ�ع�ʱ��
 *  @param  void* handle                [IN]        ������
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   ���ظ��������й�����ع�ʱ�����Ϣ�ṹ��ָ��
 *          ���ص�pstValue�ṹ�������
 *                                      float           fCurValue;      // ��ʾ�����ǰ��֡��
 *                                      float           fMax;           // ��ʾ����������õ����֡��
 *                                      float           fMin;           // ��ʾ����������õ���С֡��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
 *          ���������ͽṹ������Ľӿڿɲ��մ˽ӿ�
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get exposure time
 *  @param  void* handle                [IN]        Camera Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Return pointer of information structure related to exposure time to user
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *                                      float           fCurValue;      // Camera current exposure time
 *                                      float           fMax;           // The maximum exposure time camera allowed
 *                                      float           fMin;           // The minimum exposure time camera allowed
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Other interface of Float structure parameters can refer to this interface
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetExposureTime(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);
 *  @brief  �����ع�ʱ��
 *  @param  void* handle                [IN]        ������
 *          const float fValue          [IN]        ��Ҫ���õ����֡��
 *  @return �ɹ�,����MV_OK,�������֡�ʽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);
 *  @brief  Set exposure time
 *  @param  void* handle                [IN]        Camera Handle
 *          const float fValue          [IN]        Exposure time to set
 *  @return Success, return MV_OK, and the camera exposure time value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetExposureTime(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ���ظ�ʽ
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��й����ظ�ʽ����Ϣ�ṹ��ָ��
 *          ���ص�pstValue�ṹ�������
 *          unsigned int    nCurValue;                              //  �����ǰ�����ظ�ʽ����ö������,����˵PixelType_Gvsp_Mono8, �����õ���������ֵ,������ֵ����PixelType.h��MvGvspPixelTypeö������
 *          unsigned int    nSupportedNum;                          //  ���֧�ֵ����ظ�ʽ�ĸ���
 *          unsigned int    nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]; //  �������֧�ֵ����ظ�ʽ��Ӧ������ֵ�б�����Ҫ�������ظ�ʽʱ��������������������е�һ�֣�������Ч
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            ����ö�����Ͳ����ӿڿɲ��մ˽ӿڣ��й���Ӧ������ö�����Ͷ�Ӧ������ֵ�����PixelType.h �� CameraParams.h����Ӧ�Ķ���
 
 * @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get Pixel Format
 *  @param  void* handle                [IN]        Camera Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Returns the information structure pointer about pixel format for the caller
 *          The meaning of returns pstValue structure
 *          unsigned int    nCurValue;                              //  The current pixel format of the camera, is the enumeration type, such as PixelType_Gvsp_Mono8, here is the integer value, the specific value please refer to MvGvspPixelType enumeration type in PixelType.h
 *          unsigned int    nSupportedNum;                          //  Number of pixel formats supported by the camera
 *          unsigned int    nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]; //  The integer values list correspond to all supported pixel formats of the camera, followed by when set the pixel format, the parameter must be one of this list, otherwise invalid
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Other interface of Enumeration structure parameters can refer to this interface, look for the corresponding definition in PixelType.h and CameraParams.h for the integer values of the enum type parameter
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetPixelFormat(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);
 *  @brief  �������ظ�ʽ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õ����ظ�ʽ��Ӧ������ֵ�����ô˽ӿ�ʱ����ֱ����дö��ֵ����MV_CC_SetPixelFormat(m_handle, PixelType_Gvsp_RGB8_Packed);
 *  @return �ɹ�,����MV_OK,����������ظ�ʽ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 *  
 *          Ҫ���õ�ö�����ͱ�����Get�ӿڷ��ص�nSupportValue[MV_MAX_XML_SYMBOLIC_NUM]�е�һ�֣������ʧ��
 
 * @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Pixel Format
 *  @param  void* handle                [IN]        Camera Handle
 *          const unsigned int nValue   [IN]        The corresponding integer value for pixel format to be set, when calling this interface can be directly filled in enumeration values, such as MV_CC_SetPixelFormat(m_handle, PixelType_Gvsp_RGB8_Packed);
 *  @return Success, return MV_OK, and the camera pixel format will change to the corresponding value. Failure, return error code
 *  
 *          Other interface of Enumeration structure parameters can refer to this interface, the enumeration type to be set must be one of the nSupportValue [MV_MAX_XML_SYMBOLIC_NUM] returned by the Get interface, otherwise it will fail
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetPixelFormat(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ�ɼ�ģʽ
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��йزɼ�ģʽ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_ACQUISITION_MODE ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get acquisition mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of acquisition mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_ACQUISITION_MODE in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  �������ظ�ʽ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õĲɼ�ģʽ��Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,��������ɼ�ģʽ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set acquisition mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to acquisition mode
 *  @return Success, return MV_OK, and the camera acquisition mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ����ģʽ
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��й�����ģʽ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_GAIN_MODE ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get gain mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]    Structure pointer of gain mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_GAIN_MODE in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetGainMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  ��������ģʽ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õ�����ģʽ��Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,�����������ģʽ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set gain mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to gain mode
 *  @return Success, return MV_OK, and the camera gain mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetGainMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ�Զ��ع�ģʽ
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��й��Զ��ع�ģʽ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_EXPOSURE_AUTO_MODE ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get auto exposure mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of auto exposure mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_EXPOSURE_AUTO_MODE in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetExposureAutoMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  �����Զ��ع�ģʽ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õ��Զ��ع�ģʽ��Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,��������Զ��ع�ģʽ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set auto exposure mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to auto exposure mode
 *  @return Success, return MV_OK, and the camera auto exposure mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetExposureAutoMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ����ģʽ
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��йش���ģʽ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_TRIGGER_MODE ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get trigger mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of trigger mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_TRIGGER_MODE in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerMode(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ô���ģʽ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õĴ���ģʽ��Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,�����������ģʽ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set trigger mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to trigger mode
 *  @return Success, return MV_OK, and the camera trigger mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerMode(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  ��ȡ������ʱ
 *  @param  void* handle                [IN]        ������
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   ���ظ��������й����������ʱ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetFrameRate
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get tigger delay
 *  @param  void* handle                [IN]        Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Structure pointer of trigger delay
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Refer to MV_CC_GetFrameRate
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerDelay(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);
 *  @brief  ���ô�����ʱ
 *  @param  void* handle                [IN]        ������
 *          const float fValue          [IN]        ��Ҫ���õ����������ʱ
 *  @return �ɹ�,����MV_OK,�������������ʱ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);
 *  @brief  Set tigger delay
 *  @param  void* handle                [IN]        Handle
 *          const float fValue          [IN]        Trigger delay to set
 *  @return Success, return MV_OK, and the camera trigger delay will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerDelay(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ����Դ
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��йش���Դ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_TRIGGER_SOURCE ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get trigger source
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of trigger source
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_TRIGGER_SOURCE in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetTriggerSource(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ô���Դ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õĴ���Դ��Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,�����������Դ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set trigger source
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to trigger source
 *  @return Success, return MV_OK, and the camera trigger source will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetTriggerSource(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);
 *  @brief  ����һ�Σ��ӿڽ�����ѡ��Ĵ���ԴΪ�������ʱ��Ч��
 *  @param  void* handle                [IN]        ������
 *  @return �ɹ�,����MV_OK, ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);
 *  @brief  Execute software trigger once (this interface only valid when the trigger source is set to software)
 *  @param  void* handle                [IN]        Handle
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_TriggerSoftwareExecute(IN void* handle);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡGamma����
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��й�Gamma���͵���Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_GAMMA_SELECTOR ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get Gamma mode
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of gamma mode
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_GAMMA_SELECTOR in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetGammaSelector(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����Gamma����
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õ�Gamma���Ͷ�Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,�������Gamma���ͽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Gamma mode
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to gamma mode
 *  @return Success, return MV_OK, and the camera gamma mode will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetGammaSelector(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  ��ȡGammaֵ
 *  @param  void* handle                [IN]        ������
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   ���ظ��������й����Gammaֵ����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetFrameRate
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);
 *  @brief  Get Gamma value
 *  @param  void* handle                [IN]        Handle
 *          MVCC_FLOATVALUE* pstValue   [IN][OUT]   Structure pointer of gamma value
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
 *          Refer to MV_CC_GetFrameRate
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetGamma(IN void* handle, IN OUT MVCC_FLOATVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);
 *  @brief  ����Gammaֵ
 *  @param  void* handle                [IN]        ������
 *          const float fValue          [IN]        ��Ҫ���õ����Gammaֵ
 *  @return �ɹ�,����MV_OK,�������Gammaֵ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);
 *  @brief  Set Gamma value
 *  @param  void* handle                [IN]        Handle
 *          const float fValue          [IN]        Gamma value to set
 *  @return Success, return MV_OK, and the camera gamma value will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetGamma(IN void* handle, IN const float fValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ���
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������Ƚṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get sharpness
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of sharpness
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetSharpness(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);
 *  @brief  �������
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ����
 *  @return �ɹ�,����MV_OK,���������Ƚ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set sharpness
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Sharpness to set
 *  @return Success, return MV_OK, and the camera sharpness will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetSharpness(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ�Ҷ�
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�����ҶȽṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get Hue
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of Hue
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetHue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ûҶ�
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õĻҶ�
 *  @return �ɹ�,����MV_OK,��������ҶȽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Hue
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Hue to set
 *  @return Success, return MV_OK, and the camera Hue will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetHue(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ���Ͷ�
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�������ͶȽṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
  *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get Saturation
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of Saturation
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetSaturation(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ñ��Ͷ�
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õı��Ͷ�
 *  @return �ɹ�,����MV_OK,����������ͶȽ������Ϊ��Ӧֵ��ʧ��,���ش�����
 
*  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Saturation
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Saturation to set
 *  @return Success, return MV_OK, and the camera Saturation will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetSaturation(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  ��ȡ�Զ���ƽ��
 *  @param  void* handle                [IN]        ������
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   ���ظ������ߵ��й��Զ���ƽ�����Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,�������Ӧ������Ϣ�Ľṹ��, ʧ��, ���ش�����
 *  
            �ɲ��սӿ�MV_CC_GetPixelFormat���ο� CameraParam.h �е� MV_CAM_BALANCEWHITE_AUTO ����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);
 *  @brief  Get Auto white balance
 *  @param  void* handle                [IN]        Handle
 *          MVCC_ENUMVALUE* pstValue    [IN][OUT]   Structure pointer of auto white balance
 *  @return Success, return MV_OK, and get the structure of the corresponding parameters. Failure, return error code
 *  
            Refer to MV_CC_GetPixelFormat and definition of MV_CAM_BALANCEWHITE_AUTO in CameraParam.h
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceWhiteAuto(IN void* handle, IN OUT MVCC_ENUMVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);
 *  @brief  �����Զ���ƽ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        Ҫ���õ��Զ���ƽ���Ӧ������ֵ
 *  @return �ɹ�,����MV_OK,��������Զ���ƽ�⽫�����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set Auto white balance
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Integer value to set corresponding to auto white balance
 *  @return Success, return MV_OK, and the camera auto white balance will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceWhiteAuto(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ��ƽ�� ��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������ƽ�� ��ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get white balance red
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of white balance red
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioRed(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ð�ƽ�� ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õİ�ƽ�� ��
 *  @return �ɹ�,����MV_OK,���������ƽ�� �콫�����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set white balance red
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        White balance red to set
 *  @return Success, return MV_OK, and the camera white balance red will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioRed(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ��ƽ�� ��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������ƽ�� �̽ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get white balance green
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of white balance green
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioGreen(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ð�ƽ�� ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õİ�ƽ�� ��
 *  @return �ɹ�,����MV_OK,���������ƽ�� �̽������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set white balance green
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        White balance green to set
 *  @return Success, return MV_OK, and the camera white balance green will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioGreen(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ��ƽ�� ��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������ƽ�� ���ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get white balance blue
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of white balance blue
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBalanceRatioBlue(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);
 *  @brief  ���ð�ƽ�� ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õİ�ƽ�� ��
 *  @return �ɹ�,����MV_OK,���������ƽ�� ���������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set white balance blue
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        White balance blue to set
 *  @return Success, return MV_OK, and the camera white balance blue will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBalanceRatioBlue(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡˮӡ��Ϣ�ڰ�������Ϣ����
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й����ˮӡ��Ϣ�ڰ�������Ϣ���ͽṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get information type included by frame stamp
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of information type included by frame stamp
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetFrameSpecInfoAbility(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����ˮӡ��Ϣ�ڰ�������Ϣ����
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ�ˮӡ��Ϣ�ڰ�������Ϣ����
 *  @return �ɹ�,����MV_OK,�������ˮӡ��Ϣ�ڰ�������Ϣ���ͻ����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set information type included by frame stamp
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Information type included by frame stamp to set
 *  @return Success, return MV_OK, and the camera information type included by frame stamp will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetFrameSpecInfoAbility(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);
 *  @brief  ��ȡ�豸�Զ�������
 *  @param  void* handle                [IN]        ������
 *          MVCC_STRINGVALUE* pstValue  [IN OUT]    ���ظ��������й�������ֽṹ��ָ��
 *  @return �ɹ�,����MV_OK,���һ�ȡ��������Զ������֣�ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);
 *  @brief  Get device user defined name
 *  @param  void* handle                [IN]        Handle
 *          MVCC_STRINGVALUE* pstValue  [IN OUT]    Structure pointer of device name
 *  @return Success, return MV_OK, and get the camera user defined name. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetDeviceUserID(IN void* handle, IN OUT MVCC_STRINGVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);
 *  @brief  �����豸�Զ�������
 *  @param  void* handle                [IN]        ������
 *          IN const char* chValue      [IN]        �豸����
 *  @return �ɹ�,����MV_OK,���������豸�Զ������֣�ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);
 *  @brief  Set device user defined name
 *  @param  void* handle                [IN]        Handle
 *          IN const char* chValue      [IN]        Device name
 *  @return Success, return MV_OK, and set the camera user defined name. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetDeviceUserID(IN void* handle, IN const char* chValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡһ�δ�����֡��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й����һ�δ�����֡���ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get frame number trigger by once
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of frame number trigger by once
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetBurstFrameCount(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����һ�δ�����֡��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ�һ�δ�����֡��
 *  @return �ɹ�,����MV_OK,�������һ�δ�����֡�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set frame number trigger by once
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Frame number trigger by once to set
 *  @return Success, return MV_OK, and the camera frame number trigger by once will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetBurstFrameCount(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ��Ƶ
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������Ƶ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get line rate
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of line rate
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetAcquisitionLineRate(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);
 *  @brief  ������Ƶ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ���Ƶ
 *  @return �ɹ�,����MV_OK,���������Ƶ�����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set line rate
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Line rate to set
 *  @return Success, return MV_OK, and the camera line rate will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetAcquisitionLineRate(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ������Ϣ
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й����������Ϣ�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get heartbeat information
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of heartbeat information
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_GetHeartBeatTimeout(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);
 *  @brief  ����������Ϣ
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ�������Ϣ
 *  @return �ɹ�,����MV_OK,�������������Ϣ�����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set heartbeat information
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Heartbeat information to set
 *  @return Success, return MV_OK, and the camera heartbeat information will change to the corresponding value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CC_SetHeartBeatTimeout(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ�������С
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й�����������С�ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get network packet size
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of network packet size
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPSPacketSize(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);
 *  @brief  �����������С
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ��������С
 *  @return �ɹ�,����MV_OK,��������������С�����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set network packet size
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Packet size to set
 *  @return Success, return MV_OK, and change packet size to setting value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPSPacketSize(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  ��ȡ��������ͼ��
 *  @param  void* handle                [IN]        ������
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   ���ظ��������й������������ͼ���ṹ��ָ��
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  
 *          �ɲ��սӿ�MV_CC_GetWidth
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);
 *  @brief  Get network packet sending delay
 *  @param  void* handle                [IN]        Handle
 *  @param  MVCC_INTVALUE* pstValue     [IN][OUT]   Structure pointer of network packet sending delay
 *  @return Success, return MV_OK. Failure, return error code
 *  
 *          Refer to MV_CC_GetWidth
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCPD(IN void* handle, IN OUT MVCC_INTVALUE* pstValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);
 *  @brief  ������������ͼ��
 *  @param  void* handle                [IN]        ������
 *          const unsigned int nValue   [IN]        ��Ҫ���õ���������ͼ��
 *  @return �ɹ�,����MV_OK,���������������ͼ�������Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);
 *  @brief  Set network packet sending delay
 *  @param  void* handle                [IN]        Handle
 *          const unsigned int nValue   [IN]        Packet delay to set
 *  @return Success, return MV_OK, and change packet delay to setting value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCPD(IN void* handle, IN const unsigned int nValue);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);
 *  @brief  ��ȡ���ն�IP��ַ��0xa9fe0102 ��ʾ 169.254.1.2
 *  @param  void* handle                [IN]        ������
 *  @param  unsigned int* pnIP          [IN][OUT]   ���ظ������߽��ն�IP��ַ
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);
 *  @brief  Get receiver IP address, 0xa9fe0102 indicates 169.254.1.2
 *  @param  void* handle                [IN]        Handle
 *  @param  unsigned int* pnIP          [IN][OUT]   Receiver IP address
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCDA(IN void* handle, unsigned int* pnIP);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);
 *  @brief  ���ý��ն�IP��ַ
 *  @param  void* handle                [IN]        ������
 *          unsigned int nIP            [IN]        ��Ҫ���õĽ��ն�IP��ַ
 *  @return �ɹ�,����MV_OK,����������ն�IP��ַ�����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);
 *  @brief  Set receiver IP address
 *  @param  void* handle                [IN]        Handel
 *          unsigned int nIP            [IN]        Receiver IP address to set
 *  @return Success, return MV_OK, and change receiver IP address to setting value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCDA(IN void* handle, unsigned int nIP);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);
 *  @brief  ��ȡ���Ͷ˵Ķ˿ں�
 *  @param  void* handle                [IN]        ������
 *  @param  unsigned int* pnPort        [IN][OUT]   ���ظ������߷��Ͷ˵Ķ˿ں�
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);
 *  @brief  Get transmitter port number
 *  @param  void* handle                [IN]        Handle
 *  @param  unsigned int* pnPort        [IN][OUT]   Transmitter port number
 *  @return Success, return MV_OK. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_GetGevSCSP(IN void* handle, unsigned int* pnPort);

/************************************************************************
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);
 *  @brief  ���÷��Ͷ˵Ķ˿ں�
 *  @param  void* handle                [IN]        ������
 *          unsigned int nPort          [IN]        ��Ҫ���õķ��Ͷ˵Ķ˿ں�
 *  @return �ɹ�,����MV_OK,����������Ͷ˵Ķ˿ںŻ����Ϊ��Ӧֵ��ʧ��,���ش�����
 
 *  @fn     MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);
 *  @brief  Set transmitter port number
 *  @param  void* handle                [IN]        Handle
 *          unsigned int nPort          [IN]        Transmitter port number to set
 *  @return Success, return MV_OK, and change transmitter port number to setting value. Failure, return error code
 ************************************************************************/
MVSDKEXPORT_API int __stdcall MV_GIGE_SetGevSCSP(IN void* handle, unsigned int nPort);

/********************************************************************//**
 *  @~chinese
 *  @brief  �����豸������
 *  @param  handle                      [IN]            �豸���
 *  @param  nBaudrate                   [IN]            ���õĲ�����ֵ����ֵ�ο�CameraParams.h�к궨�壬��#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ���ýӿ������ã�������� MV_CAML_SetDeviceBaudrate�ӿڣ�
 
 *  @~english
 *  @brief  Set device baudrate using one of the CL_BAUDRATE_XXXX value
 *  @param  handle                      [IN]            Device handle
 *  @param  nBaudrate                   [IN]            baud rate to set. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks (This interface is abandoned, it is recommended to use the MV_CAML_SetDeviceBaudrate)
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_SetDeviceBauderate(IN void* handle, unsigned int nBaudrate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������
 *  @param  handle                      [IN]            �豸���
 *  @param  pnCurrentBaudrate           [OUT]           ��������Ϣָ�룬��ֵ�ο�CameraParams.h�к궨�壬��#define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ���ýӿ������ã�������� MV_CAML_GetDeviceBaudrate�ӿڣ�
 
 *  @~english
 *  @brief  Returns the current device baudrate, using one of the CL_BAUDRATE_XXXX value
 *  @param  handle                      [IN]            Device handle
 *  @param  pnCurrentBaudrate           [OUT]           Return pointer of baud rate to user. Refer to the 'CameraParams.h' for parameter definitions, for example, #define MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks (This interface is abandoned, it is recommended to use the MV_CAML_GetDeviceBaudrate)
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_GetDeviceBauderate(IN void* handle,unsigned int* pnCurrentBaudrate);

/********************************************************************//**
 *  @~chinese
 *  @brief  ��ȡ�豸������������֧�ֵĲ�����
 *  @param  handle                      [IN]            �豸���
 *  @param  pnBaudrateAblity            [OUT]           ֧�ֵĲ�������Ϣ��ָ�롣��֧�ֲ����ʵĻ���������������ֵ�ο�CameraParams.h�к궨�壬��MV_CAML_BAUDRATE_9600  0x00000001
 *  @return �ɹ�,����MV_OK,ʧ��,���ش�����
 *  @remarks ���ýӿ������ã�������� MV_CAML_GetSupportBaudrates�ӿڣ�
 
 *  @~english
 *  @brief  Returns supported baudrates of the combined device and host interface
 *  @param  handle                      [IN]            Device handle
 *  @param  pnBaudrateAblity            [OUT]           Return pointer of the supported baudrates to user. 'OR' operation results of the supported baudrates. Refer to the 'CameraParams.h' for single value definitions, for example, MV_CAML_BAUDRATE_9600  0x00000001
 *  @return Success, return MV_OK. Failure, return error code 
 *  @remarks (This interface is abandoned, it is recommended to use the MV_CAML_GetSupportBaudrates)
************************************************************************/
MVSDKEXPORT_API int __stdcall MV_CAML_GetSupportBauderates(IN void* handle,unsigned int* pnBaudrateAblity);

#ifdef __cplusplus
}
#endif 

#endif //_MV_SDK_EXPORT_H__
