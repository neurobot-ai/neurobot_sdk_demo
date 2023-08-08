

#include <Windows.h>
#include <experimental/filesystem>
#include <iostream>
#include <direct.h>
#include <vector>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>
namespace fs = std::experimental::filesystem;


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
//         


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
    cv::bitwise_or(imgMask, ch[col](roi), ch[col](roi));
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


// Rotate the image according to the angle
// 
// Parameters
// 
//         image           [IN]           the image.
//         angle           [OUT]          according to the angle to rotate the image 
// 
// Returns  
//         Rotate the image according to the angle
// 
// 


cv::Mat rotate(cv::Mat image, double angle)
{
    cv::Point2f center(image.cols / 2, image.rows / 2);

    // Get the rotation matrix
    float scale = 0.3;
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Size newSize(image.cols * scale, image.rows * scale);
    // Perform the rotation
    cv::Mat rotatedImage;
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());

    cv::Mat resizedImage1;
    cv::resize(image, resizedImage1, newSize);
    cv::Mat resizedImage2;
    cv::resize(rotatedImage, resizedImage2, newSize);
    cv::imshow("old image", resizedImage1);
    cv::imshow("new image", resizedImage2);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return rotatedImage;
}



double getAngle(float t)
{
    return atan(t) * 180 / (3.1415926);
}


// TEST function getAngle()


int testmain()
{
    std::cout << getAngle(1) << std::endl;
    return 1;
    system("pause");
}


// TEST function rotate()


int testrotate()
{
    cv::Mat myImage = cv::imread("E:\\A\\1.jpg");
    rotate(myImage, 51);

}


int main() {

    // TODO: change to your device name
    std::string device_name = "cpu";            
    // TODO: change to your model folder path
    std::string model_path = "C:\\Users\\NeuroBot\\Desktop\\disney\\angle";//模型路径";
    // TODO: change to your test image folder path
    std::string file_path = "C:\\Users\\NeuroBot\\Desktop\\disney\\angle_pic";

    // TODO: change to your model name
    const char* model_name = "neuro_deteor";

    int status = load_model(model_name, model_path.c_str(), device_name.c_str());
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
                int status = predict_model(model_name, mats, out_results, -1);
                if (status != 0) {
                    continue;
                }
                //  
                DWORD end = GetTickCount64();
                std::cout << "predict time : " << end - start << std::endl;
                std::cout << "reuslt size ===================================== : " << out_results.size() << std::endl;
                int k = 0;
                for (auto res : out_results) {
                    std::cout << "reuslt size ++++++++++++++++++++++++++++++++ : " << res.size() << std::endl;
                    for (auto r : res) {
                        float angle = (r.box.y1 - r.box.y0) / (r.box.x1 - r.box.x0);
                        double angleres = getAngle(angle);
                        if (r.label_index == 1) angleres = 360 - angleres;
                        std::cout << r.label_index << "  " << r.label_index << std::endl << "angle  " << angleres << std::endl;
                        rotate(mats[0], angleres);

                        std::cout << "label:                              " << r.label << std::endl;
                        std::cout << "Label_index:                        " << r.label_index << std::endl;
                        std::cout << "Confidential score:                 " << r.score << std::endl;
                        std::cout << "Position of result(x0,y0,x1,y1):    " << r.box.x0 << "  " << r.box.y0 << "  " << r.box.x1 << "  " << r.box.y1 << std::endl;
                        std::cout << "Row_index:                          " << r.row_index << std::endl;
                        std::cout << "Col_index:                          " << r.col_index << std::endl;
                        std::cout << "Mask_width:                         " << r.mask_width << std::endl;
                        std::cout << "Mask_height:                        " << r.mask_height << std::endl << std::endl << std::endl;

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
