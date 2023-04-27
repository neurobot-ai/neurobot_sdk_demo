/*************************************************

Copyright: NeuroBot. All rights reserved.

Author: jiang000

Date: 2023-04-27

Description: This file a demo for using the model. 

**************************************************/

#include <Windows.h>
#include <experimental/filesystem>
#include <iostream>
#include <direct.h>
#include <vector>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>
#include "putTextZH.h"

namespace fs = std::experimental::filesystem;
#undef max
#undef min


int getFilesName(const std::string dir, std::vector<std::string>& vFileNames, bool extension = 1)
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
	if (vFileNames.empty()) return 0;
	return vFileNames.size();

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
	double fontscale = 2.5f;
	int thickness = 2;

	for (int i = 0; i < info.size(); i++)
	{
		cv::Point p1(info[i].box.x0, info[i].box.y0), p2(info[i].box.x1, info[i].box.y1);
		cv::putText(image, (info[i].label).c_str(), p1, fontface, fontscale, cv::Scalar(125, 125, 125), thickness);
		//putTextZH(image, (info[i].label).c_str(), p1, cv::Scalar(0, 0, 255), 50, "ºÚÌå", false, false);

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

int main() {


	// model_path is the path of the model,    such as "C:\\Users\\NeuroBot\\A"
	// file_path  is the path of the pictures, such as "C:\\Users\\NeuroBot\\picture"

	std::string device_name = "cuda";
	std::string model_path  = "C:\\Users\\Administrator\\Downloads\\F45208C28A5E55FC886875E387C7C5B2171132349";
	std::string file_path   = "C:\\Users\\Administrator\\Desktop\\zy\\560WKD94";
	std::vector<cv::Mat> mats(1);                             
	std::vector<std::string> img_paths;                       // list of the pictures' name 
	int status = 0;                                           // the state after loading the model, and the default is zero.
	const char* model_name = "neuro_deteor";                  // fixed model name 
	const int num_img = getFilesName(file_path, img_paths);   // total num of the images
	load_model(model_name, model_path.c_str(), status);      

	if (status) {
		fprintf(stderr, "failed to create detector, code: %d\n", (int)status);
		return 1;
	}

	// predict and print the result.

	for (int i = 0; i < num_img; ++i) {
		auto img = cv::imread(file_path + "\\" + img_paths[i]);
		if (!img.data) {
			fprintf(stderr, "failed to load image: %s\n", img_paths[i].c_str());
			continue;
		}
		mats[0] = img;
		std::vector<std::vector<DetectionResult>> out_results;
		DWORD start = GetTickCount64();        // beginning time
		if (predict_model(model_name, mats, out_results)) {
			continue;
		}
		DWORD end = GetTickCount64();          // end time
		std::cout << "predict time : " << end - start << std::endl;

		// Define the results to be printed.
		// 
		// for OCR and object Detection, results are rectangle box, confidence level,category.
		// 
		// for Pixel Segmentation, results are rectangle box, confidence level,category, pixel segmentation image.

		for (auto r : out_results[0]) {
			std::cout << r.label_index << "-" << r.label.length() << "-" << r.label << "-" << r.score << ":" << r.box.x0 << "-" << r.box.y0 << "-" << r.box.x1 << "-" << r.box.y1 << std::endl;
		}
		visualResult(mats[0], out_results[0], "show");
	}
	destroy_model(model_name);
	return 0;
}
