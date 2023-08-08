#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "MvCameraControl.h"
#include <opencv2/opencv.hpp>

#include <Windows.h>
#include <experimental/filesystem>
#include <iostream>
#include <direct.h>
#include <vector>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>

//#include "putTextZH.h"
namespace fs = std::experimental::filesystem;

using namespace std;
#undef max
#undef min

// 
// 有没有自动化的能够配置VS项目的工具
// VS 插件是怎么做的？

// Draw a mask on the <image>.
// Inputs: image:		the test image
//		   result:      a single detection result
// Modify: image:       draw a mask on the image.
// Output: None
void drawMask(cv::Mat& image, const DetectionResult& info)
{

    cv::Mat imgMask = info.mask;
    auto x0 = std::max(std::floor(info.box.x0) - 1, 0.f);
    auto y0 = std::max(std::floor(info.box.y0) - 1, 0.f);
    cv::Rect roi((int)x0, (int)y0, info.mask_width, info.mask_height);

    // split the RGB channels, overlay mask to a specific color channel
    cv::Mat ch[3];
    split(image, ch);
    int col = 0;
    cv::bitwise_or(imgMask, ch[col](roi), ch[col](roi));
    merge(ch, 3, image);

}


// Display test images in a pop-up window
// Inputs: image:		the test image
//		   res:         all detection results on <image> 
// Modify: Display <image> and all detection results (masks)
// Output: None
void visualResult(cv::Mat& image, const std::vector<DetectionResult>& info, const std::string& window_name)
{
    if (image.empty())
    {
        std::cout << "input is empty, please check the path!" << std::endl;
        return;
    }
    int fontface = cv::FONT_HERSHEY_PLAIN;
    double fontscale = 1;
    int thickness = 1;

    for (int i = 0; i < info.size(); i++)
    {
        cv::Point p1(info[i].box.x0, info[i].box.y0), p2(info[i].box.x1, info[i].box.y1);
        //putTextZH(image, (info[i].label).c_str(), p1, cv::Scalar(0, 0, 255), 50, "宋体", false, false);
        cv::putText(image, (info[i].label).c_str(), p1, fontface, fontscale, cv::Scalar(125, 125, 125), thickness);
        if (info[i].mask.empty()) {
            std::vector<std::vector<cv::Point>> points;
            cv::rectangle(image, p1, p2, cv::Scalar(0, 255, 0), 2);
        }

        drawMask(image, info[i]);
    }

    cv::namedWindow(window_name, cv::WINDOW_FREERATIO);
    cv::imshow(window_name, image);
    cv::waitKey(300);
    cv::destroyAllWindows();
}


// Wait for key press
void WaitForKeyPress(void)
{
    while (!_kbhit())
    {
        Sleep(10);
    }
    _getch();
}


// Print Device Information
// Inputs: MV_CC_DEVICE_INFO：		device list
// 
// Modify: None
// Output: None
bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // print current ip and user defined name
        printf("CurrentIp: %d.%d.%d.%d\n", nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("UserDefinedName: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
        printf("Serial Number: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chSerialNumber);
        printf("Device Number: %d\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.nDeviceNumber);
    }
    else
    {
        printf("Not support.\n");
    }

    return true;
}


// Check which color is
// Inputs: MvGvspPixelType：		Type
// 
// Modify: None
// Output: None
bool IsColor(MvGvspPixelType enType)
{
    switch (enType)
    {
    case PixelType_Gvsp_BGR8_Packed:
    case PixelType_Gvsp_YUV422_Packed:
    case PixelType_Gvsp_YUV422_YUYV_Packed:
    case PixelType_Gvsp_BayerGR8:
    case PixelType_Gvsp_BayerRG8:
    case PixelType_Gvsp_BayerGB8:
    case PixelType_Gvsp_BayerBG8:
    case PixelType_Gvsp_BayerGB10:
    case PixelType_Gvsp_BayerGB10_Packed:
    case PixelType_Gvsp_BayerBG10:
    case PixelType_Gvsp_BayerBG10_Packed:
    case PixelType_Gvsp_BayerRG10:
    case PixelType_Gvsp_BayerRG10_Packed:
    case PixelType_Gvsp_BayerGR10:
    case PixelType_Gvsp_BayerGR10_Packed:
    case PixelType_Gvsp_BayerGB12:
    case PixelType_Gvsp_BayerGB12_Packed:
    case PixelType_Gvsp_BayerBG12:
    case PixelType_Gvsp_BayerBG12_Packed:
    case PixelType_Gvsp_BayerRG12:
    case PixelType_Gvsp_BayerRG12_Packed:
    case PixelType_Gvsp_BayerGR12:
    case PixelType_Gvsp_BayerGR12_Packed:
        return true;
    default:
        return false;
    }
}

bool IsMono(MvGvspPixelType enType)
{
    switch (enType)
    {
    case PixelType_Gvsp_Mono10:
    case PixelType_Gvsp_Mono10_Packed:
    case PixelType_Gvsp_Mono12:
    case PixelType_Gvsp_Mono12_Packed:
        return true;
    default:
        return false;
    }
}



// The color data obtained by this camera is stored in RGB formatand needs to be converted to BGR format
// Inputs: pRgbData：		RGB data
//         nWidth  :        wdith
//         Height  :        Height
// Modify: None
// Output: None
int RGB2BGR(unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight)
{
    if (NULL == pRgbData)
    {
        return MV_E_PARAMETER;  //0x80000004：错误的参数
    }
    //将R通道与B通道元素交换
    for (unsigned int j = 0; j < nHeight; j++)
    {
        for (unsigned int i = 0; i < nWidth; i++)
        {
            unsigned char red = pRgbData[j * (nWidth * 3) + i * 3];//每个位置第一个通道值
            pRgbData[j * (nWidth * 3) + i * 3] = pRgbData[j * (nWidth * 3) + i * 3 + 2];//每个位置第三个通道值
            pRgbData[j * (nWidth * 3) + i * 3 + 2] = red;
        }
    }

    return MV_OK;
}


// BGR format To Mat
// Inputs: pstImageInfo：		device information
//         pData       :        data address
//         i           :        index 
//         mymat       :        Mat Object
// Modify: mymat
// Output: bool
bool Convert2Mat(MV_FRAME_OUT_INFO_EX* pstImageInfo, unsigned char* pData, int i,cv::Mat &mymat)
{
    if (pstImageInfo->enPixelType == PixelType_Gvsp_Mono8)//获取当前采集到的图像格式
    {	//获取的是单通道灰度图
        mymat = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC1, pData);
    }
    else if (pstImageInfo->enPixelType == PixelType_Gvsp_RGB8_Packed)
    {	//三通道RGB图像
        RGB2BGR(pData, pstImageInfo->nWidth, pstImageInfo->nHeight);
        mymat = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC3, pData);
        imshow("srcImage", mymat);
        cv::waitKey(1000);

    }
    else
    {
        printf("unsupported pixel format\n");
        return false;
    }

    if (NULL == mymat.data)
    {
        return false;
    }
    char ch[256] = { 0 };
    sprintf_s(ch, "C:\\Users\\NeuroBot\\Desktop\\disney\\camera\\00000%d.jpg", i);
    imwrite(ch, mymat);
}


int main()
{
    // TODO: to change device_name if you want, including cpu or cuda.
    std::string device_name = "cpu";
    // TODO: to change model_path if you want.
    std::string model_path = "C:\\Users\\NeuroBot\\Desktop\\disney\\mycarera_model";//模型路径";
    // TODO: to change model_name if you want.
    const char* model_name = "neuro_deteor";

     int status = load_model(model_name, model_path.c_str(), device_name.c_str());
    if (status != 0) {
        fprintf(stderr, "failed to create detector, code: %d\n", (int)status);
        system("pause");
        return 1;
    }

    std::vector<std::string> img_paths;

    // read images and process batch inference
    std::vector<cv::Mat> images;
    std::vector<int> image_ids;
    std::vector<cv::Mat> mats;

    int nRet = MV_OK;
    void* handle = NULL;
    unsigned char* pConvertData = NULL;
    unsigned int nConvertDataSize = 0;

    do
    {
        // Enum device, find all the available devices.
        MV_CC_DEVICE_INFO_LIST stDeviceList;
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
        nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
        if (MV_OK != nRet)
        {
            printf("Enum Devices fail! nRet [0x%x]\n", nRet);
            break;
        }

        if (stDeviceList.nDeviceNum > 0)
        {
            for (unsigned int i = 0; i < stDeviceList.nDeviceNum; i++)
            {
                printf("[device %d]:\n", i);
                MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
                if (NULL == pDeviceInfo)
                {
                    break;
                }
                PrintDeviceInfo(pDeviceInfo);
            }
        }
        else
        {
            printf("Find No Devices!\n");
            break;
        }
        // Input camera index you want to use.
        printf("Please Input camera index:");
        unsigned int nIndex = 0;
        scanf_s("%d", &nIndex);

        if (nIndex >= stDeviceList.nDeviceNum)
        {
            printf("Input error!\n");
            break;
        }

        // Select device and create handle
        nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[nIndex]);
        if (MV_OK != nRet)
        {
            printf("Create Handle fail! nRet [0x%x]\n", nRet);
            break;
        }

        // Open device
        nRet = MV_CC_OpenDevice(handle);
        if (MV_OK != nRet)
        {
            printf("Open Device fail! nRet [0x%x]\n", nRet);
            break;
        }

        // Detection network optimal package size(It only works for the GigE camera)
        if (stDeviceList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
        {
            int nPacketSize = MV_CC_GetOptimalPacketSize(handle);
            if (nPacketSize > 0)
            {
                nRet = MV_CC_SetIntValue(handle, "GevSCPSPacketSize", nPacketSize);
                if (nRet != MV_OK)
                {
                    printf("Warning: Set Packet Size fail nRet [0x%x]!", nRet);
                }
            }
            else
            {
                printf("Warning: Get Packet Size fail nRet [0x%x]!", nPacketSize);
            }
        }

        nRet = MV_CC_SetEnumValue(handle, "TriggerMode", MV_TRIGGER_MODE_OFF);
        if (MV_OK != nRet)
        {
            printf("Set Trigger Mode fail! nRet [0x%x]\n", nRet);
            break;
        }

        // Start grab image
        int index = 0;
        while (true) {
            nRet = MV_CC_StartGrabbing(handle);
            if (MV_OK != nRet)
            {
                printf("Start Grabbing fail! nRet [0x%x]\n", nRet);
                break;
            }

            MV_FRAME_OUT stImageInfo = { 0 };

            nRet = MV_CC_GetImageBuffer(handle, &stImageInfo, 1000);
            if (nRet == MV_OK)
            {
                printf("Get One Frame: Width[%d], Height[%d], nFrameNum[%d],address[%x]\n",
                    stImageInfo.stFrameInfo.nWidth, stImageInfo.stFrameInfo.nHeight, stImageInfo.stFrameInfo.nFrameNum, stImageInfo.pBufAddr);
                MvGvspPixelType enDstPixelType = PixelType_Gvsp_Undefined;
                unsigned int nChannelNum = 0;
                char chFileName[MAX_PATH] = { 0 };
                cv::Mat mymat;
                Convert2Mat(&stImageInfo.stFrameInfo, stImageInfo.pBufAddr, index, mymat);
                index++;
                int pqr = RGB2BGR(stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nWidth, stImageInfo.stFrameInfo.nHeight);

                auto img = mymat;
                images.push_back(img);
                mats.push_back(img);

                // process batch inference
                if ((int)mats.size() == get_batch(model_name)) {
                    std::vector<std::vector<DetectionResult>> out_results{};
                    DWORD start = GetTickCount64();
                    int status = predict_model(model_name, mats, out_results, -1);
                    if (status != 0) {
                        continue;
                    }
                    DWORD end = GetTickCount64();
                    std::cout <<    "predict time:                       " << end - start << std::endl;
                    int k = 0;
                    for (auto res : out_results) {
                        cout << endl << endl;
                        for (auto result : res) {
                            cout << "label:                              " << result.label << "\n";
                            cout << "label_index:                        " << result.label_index << "\n";
                            cout << "confidential score:                 " << result.score << "\n";
                            cout << "(x0, y0):                           " << "(" << result.box.x0 << "," << result.box.y0 << ")\n";
                            cout << "(x1, y1):                           " << "(" << result.box.x1 << "," << result.box.y1 << ")\n";
                            cout << "row_index:                          " << result.row_index << "\n";
                            cout << "col_index:                          " << result.col_index << "\n";
                            cout << "mask_width:                         " << result.mask_width << "\n";
                            cout << "mask_height:                        " << result.mask_height << "\n";
                            cout << "\n\n";

                        }
                        visualResult(mats[k], res, "show");
                        k++;
                    }
                    // clear buffer for next batch
                    mats.clear();
                    image_ids.clear();
                    images.clear();


                }

                if (IsColor(stImageInfo.stFrameInfo.enPixelType))
                {
                    nChannelNum = 3;
                    enDstPixelType = PixelType_Gvsp_RGB8_Packed;
                    sprintf_s(chFileName, "AfterConvert.rgb");
                }
                //If it's Mono, converted to Mono8 
                else if (IsMono(stImageInfo.stFrameInfo.enPixelType))
                {
                    nChannelNum = 1;
                    enDstPixelType = PixelType_Gvsp_Mono8;
                    sprintf_s(chFileName, "AfterConvert.gray");
                }
                else
                {
                    printf("Don't need to convert!\n");
                }

                if (enDstPixelType != PixelType_Gvsp_Undefined)
                {
                    pConvertData = (unsigned char*)malloc(stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight * nChannelNum);
                    if (NULL == pConvertData)
                    {
                        printf("malloc pConvertData fail!\n");
                        nRet = MV_E_RESOURCE;
                        break;
                    }
                    nConvertDataSize = stImageInfo.stFrameInfo.nWidth * stImageInfo.stFrameInfo.nHeight * nChannelNum;

                    // Convert pixel format 
                    MV_CC_PIXEL_CONVERT_PARAM stConvertParam = { 0 };

                    stConvertParam.nWidth = stImageInfo.stFrameInfo.nWidth;                 // image width
                    stConvertParam.nHeight = stImageInfo.stFrameInfo.nHeight;               // image height
                    stConvertParam.pSrcData = stImageInfo.pBufAddr;                         // input data buffer
                    stConvertParam.nSrcDataLen = stImageInfo.stFrameInfo.nFrameLen;         // input data size
                    stConvertParam.enSrcPixelType = stImageInfo.stFrameInfo.enPixelType;    // input pixel format
                    stConvertParam.enDstPixelType = enDstPixelType;                         // output pixel format
                    stConvertParam.pDstBuffer = pConvertData;                               // output data buffer
                    stConvertParam.nDstBufferSize = nConvertDataSize;                       // output buffer size
                    nRet = MV_CC_ConvertPixelType(handle, &stConvertParam);
                    if (MV_OK != nRet)
                    {
                        printf("Convert Pixel Type fail! nRet [0x%x]\n", nRet);
                        break;
                    }

                    FILE* fp = NULL;
                    errno_t err = fopen_s(&fp, chFileName, "wb");
                    if (0 != err || NULL == fp)
                    {
                        printf("Open file failed\n");
                        nRet = MV_E_RESOURCE;
                        break;
                    }
                    fwrite(stConvertParam.pDstBuffer, 1, stConvertParam.nDstLen, fp);
                    fclose(fp);
                    printf("Convert pixeltype succeed\n");
                }
                MV_CC_FreeImageBuffer(handle, &stImageInfo);
            }
            else
            {
                printf("No data[0x%x]\n", nRet);
            }

            // Stop grab image
            nRet = MV_CC_StopGrabbing(handle);
            if (MV_OK != nRet)
            {
                printf("Stop Grabbing fail! nRet [0x%x]\n", nRet);
                break;
            }
            Sleep(1000);
        }

        // Close device
        nRet = MV_CC_CloseDevice(handle);
        if (MV_OK != nRet)
        {
            printf("Close Device fail! nRet [0x%x]\n", nRet);
            break;
        }

        // Destroy handle
        nRet = MV_CC_DestroyHandle(handle);
        if (MV_OK != nRet)
        {
            printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
            break;
        }
    } while (0);

    if (pConvertData)
    {
        free(pConvertData);
        pConvertData = NULL;
    }

    if (nRet != MV_OK)
    {
        if (handle != NULL)
        {
            MV_CC_DestroyHandle(handle);
            handle = NULL;
        }
    }

    printf("Press a key to exit.\n");
    WaitForKeyPress();

    return 0;
}
