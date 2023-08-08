#ifndef HIKCAMERA_H_
#define HIKCAMERA_H_

#include "camera.h"
#include "MvCameraControl.h"
#include <vector>
#include <map>



class HIKCamera :public Camera
{
public:
	HIKCamera();
	~HIKCamera();
	int scanDevice();
	int bind(std::string macAddress);
	int initGrab(int mode);
	int startGrab(int mode, int triggerMode);
	int stopGrab();
	int close();
	int destroy();
	void softTrigger();
	static void callBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
	int getDeviceInfo(std::vector<std::map<std::string, std::string>>& deviceInfo);
private:
	int runMode;
	int saveImage(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo);
	void* handle;
	MV_CC_DEVICE_INFO* choicedDevice;
	MV_CC_DEVICE_INFO_LIST deviceLists;
};


//HIKCamera::HIKCamera()
//{
//	choicedDevice = NULL;
//	memset(&deviceLists, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
//}
//
//HIKCamera::~HIKCamera()
//{
//	delete choicedDevice;
//	delete handle;
//}
//
//int HIKCamera::scanDevice()
//{
//
//	int res = MV_OK;
//	res = MV_CC_EnumDevices(MV_GIGE_DEVICE, &deviceLists);
//	if (res != MV_OK)
//	{
//		std::cout << "scan device fail!" << std::endl;
//		return SCAN_ERROR;
//	}
//	else
//	{
//		return OK;
//	}
//}
//
//int HIKCamera::bind(std::string macAddress)
//{
//	for (unsigned int i = 0;i < deviceLists.nDeviceNum;++i)
//	{
//		MV_CC_DEVICE_INFO* tempDevice = deviceLists.pDeviceInfo[i];
//		std::string macAdd;
//		std::stringstream buffer;
//		buffer << std::hex << tempDevice->nMacAddrHigh << tempDevice->nMacAddrLow;
//		buffer >> macAdd;
//		int realLength = macAdd.length();
//		for (int j = 0;j < (12 - realLength);++j)
//		{
//			macAdd = "0" + macAdd;
//		}
//		if (!strcmp(macAddress.c_str(), macAdd.c_str()))
//		{
//			choicedDevice = tempDevice;
//			break;
//		}
//		else
//		{
//			continue;
//		}
//	}
//	if (choicedDevice == NULL)
//	{
//		return BIND_ERROR;
//	}
//	else
//	{
//		int res = MV_CC_CreateHandle(&handle, choicedDevice);
//		if (res != MV_OK)
//		{
//			return BIND_ERROR;
//		}
//		return OK;
//	}
//}
//
//int HIKCamera::startGrab(int mode)
//{
//	if (mode == STEP)
//	{
//		//open the device
//		int res = MV_CC_OpenDevice(handle);
//		if (res != MV_OK)
//		{
//			std::cout << "open device error" << std::hex << res << std::endl;
//			return OPEN_ERROR;
//		}
//		if (choicedDevice->nTLayerType == MV_GIGE_DEVICE)
//		{
//			int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
//			if (nPacketSize > 0)
//			{
//				res = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
//				if (res != MV_OK)
//				{
//					printf("Warning: Set Packet Size fail nRet [0x%x]!", res);
//					return SET_PACKET_FAIL;
//				}
//			}
//			else
//			{
//				printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
//				return GET_PACKET_FAIL;
//			}
//		}
//
//
//		//close trigger
//		res = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_OFF);
//		if (MV_OK != res)
//		{
//			printf("Set Trigger Mode fail! nRet [0x%x]\n", res);
//			stopGrab();
//			close();
//			return CLOSE_TRIGGER_FAIL;
//		}
//
//		//start grab
//		res = MV_CC_StartGrabbing(handle);
//		if (MV_OK != res)
//		{
//			printf("Start Grabbing fail! nRet [0x%x]\n", res);
//			stopGrab();
//			close();
//			return START_GRAB_FAIL;
//		}
//
//		//get image data��delay 1000ms
//		MV_FRAME_OUT stOutFrame = { 0 };
//		res = MV_CC_GetImageBuffer(handle, &stOutFrame, 1000);
//
//		if (res == MV_OK)
//		{
//			printf("Get Image Buffer: Width[%d], Height[%d], FrameNum[%d]\n",
//				stOutFrame.stFrameInfo.nWidth, stOutFrame.stFrameInfo.nHeight, stOutFrame.stFrameInfo.nFrameNum);
//			res = saveImage(stOutFrame.pBufAddr, &(stOutFrame.stFrameInfo));
//			if (OK != res)
//			{
//				return res;
//			}
//			res = MV_CC_FreeImageBuffer(handle, &stOutFrame);
//			std::cout << "FREE buffer after" << std::endl;
//			if (res != MV_OK)
//			{
//				printf("Free Image Buffer fail! nRet [0x%x]\n", res);
//				stopGrab();
//				close();
//				return FREE_IMAGEBUFFER_FAIL;
//			}
//			else
//			{
//				stopGrab();
//				close();
//				return OK;
//			}
//		}
//		else
//		{
//			printf("No data[0x%x]\n", res);
//			stopGrab();
//			close();
//			return GET_IMAGEDATA_FAIL;
//		}
//	}
//	else if (mode = SERIES)
//	{
//		runMode = SERIES;
//		//open the device
//		int res = MV_CC_OpenDevice(handle);
//		if (res != MV_OK)
//		{
//			std::cout << "open device error" << std::hex << res << std::endl;
//			return OPEN_ERROR;
//		}
//		if (choicedDevice->nTLayerType == MV_GIGE_DEVICE)
//		{
//			int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
//			if (nPacketSize > 0)
//			{
//				res = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
//				if (res != MV_OK)
//				{
//					printf("Warning: Set Packet Size fail nRet [0x%x]!", res);
//					return SET_PACKET_FAIL;
//				}
//			}
//			else
//			{
//				printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
//				return GET_PACKET_FAIL;
//			}
//		}
//		else
//		{
//			return CHOICE_DEVICE_TYPE_ERROR;
//		}
//		//open trigger
//		res = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_ON);
//		if (MV_OK != res)
//		{
//			printf("open Trigger Mode fail! nRet [0x%x]\n", res);
//			close();
//			return OPEN_TRIGGER_FAIL;
//		}
//
//		// config the trigger source
//		res = MV_CC_SetTriggerSource(handle, MV_TRIGGER_SOURCE_LINE0);
//		if (MV_OK != res)
//		{
//			printf("Set Trigger Mode fail! nRet [0x%x]\n", res);
//			close();
//			return SET_TRIGGER_FAIL;
//		}
//
//		// Register image callback
//		res = MV_CC_RegisterImageCallBackEx(handle, callBack, this);
//		if (MV_OK != res)
//		{
//			printf("Register Image CallBack fail! nRet [0x%x]\n", res);
//			stopGrab();
//			close();
//			return REGISTER_CALLBACK_FAIL;
//		}
//
//		//start grab
//		res = MV_CC_StartGrabbing(handle);
//		if (MV_OK != res)
//		{
//			printf("Start Grabbing fail! nRet [0x%x]\n", res);
//			stopGrab();
//			close();
//			return START_GRAB_FAIL;
//		}
//		return OK;
//	}
//	else
//	{
//		std::cout << "input mode is error" << std::endl;
//		return INPUT_MODE_ERROR;
//	}
//}
//
//void HIKCamera::callBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
//{
//	if (pFrameInfo)
//	{
//		((HIKCamera*)(pUser))->saveImage(pData, pFrameInfo);
//	}
//	//if (pFrameInfo)
//	//{
//	//	printf("Get One Frame: Width[%d], Height[%d], nFrameNum[%d]\n",
//	//		pFrameInfo->nWidth, pFrameInfo->nHeight, pFrameInfo->nFrameNum);
//	//	//�Ҷ�ͼ����
//	//	std::set<int> imageType;
//	//	imageType.insert(PixelType_Gvsp_Mono1p);
//	//	imageType.insert(PixelType_Gvsp_Mono2p);
//	//	imageType.insert(PixelType_Gvsp_Mono4p);
//	//	imageType.insert(PixelType_Gvsp_Mono8);
//	//	imageType.insert(PixelType_Gvsp_Mono8_Signed);
//	//	imageType.insert(PixelType_Gvsp_Mono10);
//	//	imageType.insert(PixelType_Gvsp_Mono10_Packed);
//	//	imageType.insert(PixelType_Gvsp_Mono12);
//	//	imageType.insert(PixelType_Gvsp_Mono12_Packed);
//	//	imageType.insert(PixelType_Gvsp_Mono14);
//	//	imageType.insert(PixelType_Gvsp_Mono16);
//
//
//
//	//	if (pFrameInfo)
//	//	{
//	//		//����ǻҶ�ͼ
//	//		if (imageType.count(pFrameInfo->enPixelType) != 0)
//	//		{
//
//	//		}
//	//		else
//	//		{
//	//			//std::cout << "i am color image" << std::endl;
//	//			//std::cout << "i am color image" << ((HIKCamera*)pUser)->imgPath << std::endl;
//	//			int res = ((HIKCamera*)pUser)->saveImage(pData,pFrameInfo);
//	//			std::cout << "i am color image1" << std::endl;
//	//			if (res)
//	//			{
//	//				(*(((HIKCamera*)pUser)->processer))(((HIKCamera*)pUser)->imgUrl, ((HIKCamera*)pUser)->userPtr);
//	//			}
//	//		}
//
//	//	}
//	//	else
//	//	{
//	//		std::cout << "save image info is error!" << std::endl;
//
//	//	}
//	//}
//}
//
//int HIKCamera::saveImage(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo)
//{
//	//�Ҷ�ͼ����
//	std::set<int> imageType;
//	imageType.insert(PixelType_Gvsp_Mono1p);
//	imageType.insert(PixelType_Gvsp_Mono2p);
//	imageType.insert(PixelType_Gvsp_Mono4p);
//	imageType.insert(PixelType_Gvsp_Mono8);
//	imageType.insert(PixelType_Gvsp_Mono8_Signed);
//	imageType.insert(PixelType_Gvsp_Mono10);
//	imageType.insert(PixelType_Gvsp_Mono10_Packed);
//	imageType.insert(PixelType_Gvsp_Mono12);
//	imageType.insert(PixelType_Gvsp_Mono12_Packed);
//	imageType.insert(PixelType_Gvsp_Mono14);
//	imageType.insert(PixelType_Gvsp_Mono16);
//
//	if (pFrameInfo)
//	{
//		//����ǻҶ�ͼ
//		if (imageType.count(pFrameInfo->enPixelType) != 0)
//		{
//			cv::Mat input = cv::Mat::zeros(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1);
//			memcpy(input.data, pData, pFrameInfo->nHeight*pFrameInfo->nWidth);
//			imageQ.push(input);
//		}
//		else
//		{
//			cv::Mat input = cv::Mat::zeros(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
//
//			MV_CC_PIXEL_CONVERT_PARAM stParam;
//			memset(&stParam, 0, sizeof(MV_CC_PIXEL_CONVERT_PARAM));
//			stParam.pSrcData = pData;
//			stParam.nSrcDataLen = pFrameInfo->nWidth*pFrameInfo->nHeight * 3;
//			stParam.enSrcPixelType = pFrameInfo->enPixelType;
//			stParam.nWidth = pFrameInfo->nWidth;
//			stParam.nHeight = pFrameInfo->nHeight;
//			stParam.enDstPixelType = PixelType_Gvsp_BGR8_Packed;
//			stParam.nDstBufferSize = pFrameInfo->nWidth*pFrameInfo->nHeight * 3;
//			stParam.pDstBuffer = input.data;
//
//			int res = MV_CC_ConvertPixelType(handle, &stParam);
//
//
//			if (res != MV_OK)
//			{
//				std::cout << "save error" << std::endl;
//				stopGrab();
//				return CONVERT_PIXEL_FAIL;
//			}
//			else
//			{
//				imageQ.push(input);
//				return OK;
//			}
//		}
//	}
//	else
//	{
//		std::cout << "save image info is error!" << std::endl;
//		return IMAGE_DATA_ERROR;
//	}
//}
//
//
//
//int HIKCamera::stopGrab()
//{
//	std::cout << "mode" << runMode << std::endl;
//	int res;
//	if (runMode == SERIES)
//	{
//		res = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_OFF);
//		if (MV_OK != res)
//		{
//			printf("Close trigger Mode [0x%x]\n", res);
//			return CLOSE_TRIGGER_FAIL;
//		}
//	}
//	res = MV_CC_StopGrabbing(handle);
//	if (MV_OK != res)
//	{
//		printf("Stop Grabbing fail! nRet [0x%x]\n", res);
//		return STOP_GRAB_ERROR;
//	}
//	if (runMode == SERIES)
//	{
//		std::cout << "unregister" << std::endl;
//		res = MV_CC_RegisterImageCallBackEx(handle, NULL, NULL);
//		if (MV_OK != res)
//		{
//			printf("Unregister Image CallBack fail! nRet [0x%x]\n", res);
//			return UNREGISTER_CALLBACK_ERROR;
//		}
//	}
//	return OK;
//}
//
//
//
//int HIKCamera::close()
//{
//	int res = MV_CC_CloseDevice(handle);
//	if (MV_OK != res)
//	{
//		printf("ClosDevice fail! nRet [0x%x]\n", res);
//		return CLOSE_DEVICE_ERROR;
//	}
//	return OK;
//}
//
//
//
//int HIKCamera::destroy()
//{
//	int res = MV_CC_DestroyHandle(handle);
//	if (MV_OK != res)
//	{
//		printf("Destroy Handle fail! nRet [0x%x]\n", res);
//		return DESTROY_HANDLE_ERROR;
//	}
//	return OK;
//}
//
//
//
//
//int HIKCamera::getDeviceInfo(std::vector<std::map<std::string, std::string>>& deviceInfo)
//{
//	if (deviceLists.nDeviceNum > 0)
//	{
//		std::map<std::string, std::string> tempMap;
//		for (int i = 0;i < deviceLists.nDeviceNum;++i)
//		{
//			MV_CC_DEVICE_INFO* temp = deviceLists.pDeviceInfo[i];
//			int nIp1 = ((temp->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
//			int nIp2 = ((temp->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
//			int nIp3 = ((temp->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
//			int nIp4 = (temp->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);
//			std::string ip;
//			std::stringstream ss;
//			ss << std::to_string(nIp1) << "."
//				<< std::to_string(nIp2) << "."
//				<< std::to_string(nIp3) << "."
//				<< std::to_string(nIp4);
//			ss >> ip;
//			std::string macAdd;
//			std::stringstream buffer;
//			buffer << std::hex << temp->nMacAddrHigh << temp->nMacAddrLow;
//			buffer >> macAdd;
//			int realLength = macAdd.length();
//			for (int j = 0;j < (12 - realLength);++j)
//			{
//				macAdd = "0" + macAdd;
//			}
//			tempMap["ip"] = ip;
//			tempMap["mac"] = macAdd;
//			tempMap["type"] = "HIK";
//			deviceInfo.push_back(tempMap);
//		}
//		return OK;
//	}
//	else
//	{
//		return DEVICE_LIST_EMPTY;
//	}
//	return OK;
//}








#endif

