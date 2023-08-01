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


void getFilesName(const std::string dir, std::vector<std::string>& vFileNames, bool extension = 1)
{
    for (const auto& entry : fs::directory_iterator(dir))
    {
        if (1 == extension)
        {
            // with extension
            vFileNames.push_back(entry.path().filename().string());
        }
        else if (0 == extension)
        {
            // without extension
            std::string fileName;
            fileName = entry.path().filename().string();
            int pos = fileName.rfind(".");
            vFileNames.push_back(std::string(fileName, 0, pos));
            fileName.clear();
        }
    }
}

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
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int sdkPredict (string device_name) {
	device_name = "cpu";
	//模型文件路径
	std::string model_path = "D:\\HM\\vison_sdk_local\\vision-sdk-local\\neuro_det_sdkcpu\\neuro_det_sdk\\onnx";//模型路径";
	//图片文件路径
	std::string file_path = "D:\\HM\\vison_sdk_local\\vision-sdk-local\\neuro_det_sdkcpu\\neuro_det_sdk\\onnx\\test";

	const char* model_name = "neuro_deteor";

    int status=load_model(model_name, model_path.c_str(), device_name.c_str());
    if (status != 0) {
        fprintf(stderr, "failed to create detector, code: %d\n", (int)status);
        system("pause");
        return 1;
    }

    std::vector<std::string> img_paths;
    getFilesName(file_path, img_paths);

    // read images and process batch inference
    std::vector<cv::Mat> images;
    std::vector<int> image_ids;
    std::vector<cv::Mat> mats;

    for (int j = 0; j < 1; j++) {
        for (int i = 0; i < (int)img_paths.size(); ++i) {
            auto img = cv::imread(file_path + "\\" + img_paths[i]);
            if (!img.data) {
                fprintf(stderr, "failed to load image: %s\n", img_paths[i].c_str());
                continue;
            }
            images.push_back(img);
            image_ids.push_back(i);
            mats.push_back(img);

            // process batch inference
            if ((int)mats.size() == get_batch(model_name)) {
                std::vector<std::vector<DetectionResult>> out_results{};
                DWORD start = GetTickCount64();
                int status=predict_model(model_name, mats, out_results,-1);
                if (status != 0) {
                    continue;
                }
                DWORD end = GetTickCount64();
                std::cout << "predict time : " << end - start << std::endl;
                std::cout << "reuslt size ===================================== : " << out_results.size() << std::endl;
                int k = 0;
                for (auto res : out_results) {
                    std::cout << "reuslt size ++++++++++++++++++++++++++++++++ : " << res.size() << std::endl;
                    for (auto r : res) {
                        std::cout << r.label_index << "-" << r.label << "-" << r.score << ":" << r.box.x0 << "-" << r.box.y0 << "-" << r.box.x1 << "-" << r.box.y1 << std::endl;
                    }
                    visualResult(mats[k], res, "show");
                    k++;
                }
                // clear buffer for next batch
                mats.clear();
                image_ids.clear();
                images.clear();


            }
        }
    }
    // process batch inference if there are still unhandled images
    if (!mats.empty()) {
        std::vector<std::vector<DetectionResult>> out_results{};
        (void)predict_model(model_name, mats, out_results);
    }

    destroy_model(model_name);
    system("pause");
    return 0;
}
