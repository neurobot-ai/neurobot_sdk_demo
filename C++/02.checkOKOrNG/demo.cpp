#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma comment(lib,"Msi.lib")
#include <iostream>
#include <string>
#include <Windows.h>
#include <experimental/filesystem>
#include <iostream>
#include <direct.h>
#include <vector>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>
#include "putTextZH.h"

#include <msi.h>

namespace fs = experimental::filesystem;

using namespace std;

// Get all the files's names in the dictionary, and the result will be put into the parameter vFileNames.
// 
// Parameters
// 
//         dir           [IN]           the name of dictionary.
//         vFileNames    [OUT]          the result will be put into it.
//         extension     [IN]           ZERO means having extension, such as A.jpg.
//                                      ONE means having no extension, such as A.
//  
// Returns  
//         The size of all the files.      


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
    if (vFileNames.empty()) cerr << "This path has no pictures, please check the path." << endl;
    return vFileNames.size();

}


// Mask is used to cover non areas of interest, highlight areas of interest, 
// and focus image processing only on the ROI part.
// 
// Here marks the results in the picture used for segmentation.
// 
// The rectangle box x0,y0 in the result is the upper left corner,
// and the height and width of the mask are the height and width.
// 
// Parameters
//         image           [IN]           the image in Mat format.
//         DetectionResult [IN]           the result after detection.
//  
//


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
    cv::bitwise_or(imgMask, ch[col](roi), ch[col](roi));   // The pixel value of each pixel is bitwise or
    merge(ch, 3, image);

}

// visualize the result by drawing the picture in the new window.
// 
// Parameters
//         image           [IN]           the image in Mat format. 
//         info            [IN]           the results after detection.
//         window_name     [IN]           the new window's name.                   
//  
// 


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
        //  Generate two points and show the label on the graph.
        cv::Point p1(info[i].box.x0, info[i].box.y0), p2(info[i].box.x1, info[i].box.y1);
        if (info[i].label.compare("OK")) {
            putTextZH(image, (info[i].label).c_str(), p1, cv::Scalar(0, 0, 255), 50, "Arial", false, false);
        }
        else {
            putTextZH(image, (info[i].label).c_str(), p1, cv::Scalar(0, 255, 0), 50, "Arial", false, false);
        }
        if (info[i].mask.empty()) {
            std::vector<std::vector<cv::Point>> points;
            cv::rectangle(image, p1, p2, cv::Scalar(0, 255, 0), 2);
        }
        drawMask(image, info[i]);
    }

    // create a new display window and specify the type of window and then show in the screen.
    cv::namedWindow(window_name, cv::WINDOW_FREERATIO);
    cv::imshow(window_name, image);

    // wait until user presses any key to exit.
    cv::waitKey(0);

    // to close the window and de-allocate any associated memory usage.
    // For a simple program, you do not really have to call these functions because all the resources and windows of the application are closed automatically by the operating system upon exit.
    cv::destroyAllWindows();
}



int main(int argc, char ** argv) {

    
    //  model_path is the path of the model,    such as "C:\\Users\\NeuroBot\\A"
    //  file_path  is the path of the pictures, such as "C:\\Users\\NeuroBot\\picture"
    string model_path = "C:\\Users\\NeuroBot\\A";
    string file_path  = "C:\\Users\\NeuroBot\\picture";

    string device_name = "cuda";
    string model_name = "neuro_deteor";                    // the model name, you can name it by yourself.

                                      // the state after loading the model, and the default is zero.
    int status = load_model(model_name.c_str(), model_path.c_str(), device_name.c_str());
    if (status != 0) {
        cerr << "failed to create detector, code: " << status << endl;
        return -1;
    }

    vector<string> img_paths;                             // the list of the pictures' name 
    getFilesName(file_path, img_paths);                   // get all the files's names in the dictionary,
    vector<cv::Mat> images;                               // the information in opencv mat format.
    vector<int> image_ids;                                // the image's id 
    vector<cv::Mat> mats;                                 // the information in opencv mat format.



    //  predict and print the result.
    //  batch_size is given in the file model.conf. the default is ONE.
    for (int i = 0; i < (int)img_paths.size(); ++i) {
        auto img = cv::imread(file_path + "\\" + img_paths[i]);
		if (!img.data) {
			cerr << "Load image: " << img_paths[i] << "is failed" << endl;
			continue;
		}
		else {
			cout << "Load image: " << img_paths[i] << "is successful" << endl;
		}
        images.push_back(img);
        image_ids.push_back(i);
        mats.push_back(img);

        if ((int)mats.size() == get_batch(model_name.c_str())) {
            vector<vector<DetectionResult>> out_results{};
			DWORD start = GetTickCount64();        // beginning time
			int predictStatus = predict_model(model_name.c_str(), mats, out_results);
			DWORD end = GetTickCount64();          //  end time
            if (predictStatus != 0) {
				cout << "This prediction is failed " << endl;
				cout << "Time cost:                          " << end - start << " ms" << endl << endl << endl;
				continue;
			}
            // The results to be printed.
            // 
            // for OCR and object Detection, results are rectangle box, confidence level,category.
            // 
            // for Pixel Segmentation, results are rectangle box, confidence level,category, pixel segmentation image.

            for (auto res : out_results) {
                for (auto r : res) {
                    // If OK, then print the position in console.
                    if (!r.label.compare("OK")) {  

                        cout << r.box.x0 << "-" << r.box.y0 << "-" << r.box.x1 << "-" << r.box.y1 << endl;
                    }
                    // If NG, then break.
                }
                // It will visual a result by a new window whose name is show.
                visualResult(mats[i], res, "show");
                i++;
            }
            mats.clear();
            image_ids.clear();
            images.clear();
        }
    }

	// Check the number of pictures before using predict_model function.
	// Be sure that the number of pictures equals to the batch.

	if (!mats.empty()) {
		int requested_batch = get_batch(model_name.c_str());
		// If the number does not equal to the Batch, use the last picture to fill it.
		cv::Mat last_pict = mats[mats.size() - 1];
		while (mats.size() < requested_batch) {
			mats.push_back(last_pict);
		}
		vector<vector<DetectionResult>> out_results{};
		(void)predict_model(model_name.c_str(), mats, out_results);
	}
	destroy_model(model_name.c_str());

    return 0;
}


