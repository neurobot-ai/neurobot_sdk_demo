#include <Windows.h>
#include <experimental/filesystem>
#include <iostream>
#include <direct.h>
#include <vector>
#include <string>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <queue>

namespace fs = std::experimental::filesystem;
using std::string;
using std::vector;
using std::max;
using std::floor;
using std::cout;
using std::exception;
using std::to_string;
using std::priority_queue;
using std::pair;
using std::less;


// comparator used in a priotity queue to find largest k masks
// <index, mask area(#pixels)>
struct greaterComp {
    bool operator() (const pair<int, int>& p1, const pair<int, int>& p2) {
        return p1.second > p2.second;
    }
};


// Return all image file names in the path <dir_path>.
// Inputs: dirPath:		the path of folder containing all test images
//		   extension:   whether the image name has an extension or not
// Modify: None
// Output: A vector of strings (image file names)
vector<string> get_file_names(const string& dir_path, bool extension = true);


// Draw a mask on the <image>.
// Inputs: image:		the test image
//		   result:      a single detection result
// Modify: image:       draw a mask on the image.
// Output: None
void draw_mask(cv::Mat& image, const DetectionResult& result);


// Draw a box on the <image>.
// Inputs: image:		the test image
//		   res:         a single detection result
// Modify: image:       draw a box on the image.
// Output: None
void draw_box(cv::Mat& image, const DetectionResult& result);

// Draw detection information on the <image>.
// Inputs: image:		the test image
//		   res:         a single detection result
// Modify: image:       draw information (labels, label indices, and confidence scores) on the image.
// Output: None
void draw_info(cv::Mat& image, const DetectionResult& result);


// Display test images in a pop-up window
// Inputs: image:		the test image
//		   res:         all detection results on <image> 
// Modify: Display <image> and all detection results (masks)
// Output: None
void display_results(cv::Mat& image, const vector<DetectionResult>& results, const string& window_name = "Prediction result");


// print detection information in the terminal
// Inputs: results:      detection results of a single test image
// Modify: None
// Output: None
void print_info(const vector<DetectionResult>& results);


// filter out masks which doesn't meet certain requirements
// Inputs: results:                detection results of a single test image
//         top_k:                  specify how many largest masks need to be kept
//         mask_area_lowerbound    ignore masks whose area < mask_area_lowerbound
//         mask_area_upperbound    ignore masks whose area > mask_area_upperbound
// Modify: None
// Output: a vector of (filtered) detection results
vector<DetectionResult> filter_mask(const vector<DetectionResult>& results, int top_k, int mask_area_lowerbound, int mask_area_upperbound);


// This demo shows, in a segementation task, how to filter out masks which doesn't meet certain requirements.
// For example, we only want to keep k largest masks in an image or keep masks whose area (#pixels) is larger than a threshold
int main(int argc, char** argv) {
    // TODO: change to your test image folder path
    string image_folder_path = "D:\\Intern\\test_image\\seg_test_image";
    // TODO: change to your model folder path
    // Warning: This demo only works for segmentation models
    string model_path = "D:\\Intern\\model\\seg_gpu";
    // TODO: change to your model name
    string model_name = "test";
    // TODO: change to your device name
    string device_name = "cuda";
    // TODO: change to your device index (Nonnegative int)
    int device_index = 0;
    // TODO: change to your detection threshold. Range: [0, 1] or -1 (default, which is 0.7)
    float detect_thres = -1;
    
    // Filter out masks which don't meet requirements
    // TODO: change to your top_k (if k<=0, ignore; if k>0, keep k largest masks)
    int top_k = 3;
    // TODO: change to your mask_area_lowerbound (-1 means unbounded)
    int mask_area_lowerbound = 100000;
    // TODO: change to your mask_area_upperbound 
    int mask_area_upperbound = 500000;

    cout << "\n\n";
    cout << "Test image folder path: " << image_folder_path << "\n";
    cout << "Model path: " << model_path << "\n";
    cout << "Model name: " << model_name << "\n";
    cout << "Device name: " << device_name << "\n";
    cout << "Device index: " << device_index << "\n";
    cout << "Top k choice: k = " << top_k<< "\n";
    cout << "mask_area_lowerbound: " << mask_area_lowerbound << "\n";
    cout << "mask_area_upperbound: " << mask_area_upperbound << "\n";
    cout << "\n\n";

    // check image_folder_path
    vector<string> file_names = get_file_names(image_folder_path, true);
    int num_files = file_names.size();
    if (num_files == 0) {
        cout << "Error: This test image folder is empty!\n";
        system("pause");
        return -1;
    }
    cout << "The total number of test images: " << num_files << "\n";

    // check device_name
    if (!(device_name == "cpu" || device_name == "cuda")) {
        cout << "Error: device_name is incorrect. It's either cpu or cuda!\n";
        system("pause");
        return -1;
    }

    // check deviceIndex
    if (device_index < 0) {
        cout << "Error: device_index should be a nonnegative integer\n";
        system("pause");
        return -1;
    }

    // check detectThres
    if (!(0 <= detect_thres && detect_thres <= 1) && detect_thres != -1){
        cout << "Error: the range of detectThres is [0, 1] or -1\n";
        system("pause");
        return -1;
    }

    // check mask_area_lowerbound and mask_area_upperbound
    if (!((0 <= mask_area_lowerbound) && (mask_area_lowerbound <= mask_area_upperbound))) {
        cout << "Error: It should be 0 <= mask_area_lowerbound <= mask_area_upperbound\n";
        system("pause");
        return -1;
    }

    // load model
    int load_status = load_model(model_name.c_str(), model_path.c_str(), device_name.c_str(), device_index);
    if (load_status != 0) {
        cout << "Error: Fail to load the model. Status code: " << load_status << "\n";
        system("pause");
        return load_status;
    }
    
    int batch_size = get_batch(model_name.c_str());
    cout << "Batch size: " << batch_size << "\n";
    
    for (int i_file = 0; i_file < num_files;) {
        vector<cv::Mat> images;
        vector<string> batch_names;
        vector<vector<DetectionResult>> out_results;

        // read [bacth_size] images
        for (int i_batch = 0; i_batch < batch_size; ++i_batch, ++i_file) {
            if (i_file >= num_files) break;

            string file_name = image_folder_path + "\\" + file_names[i_file];
            cout << "Reading the image: " << file_name << "\n";
            cv::Mat image = cv::imread(file_name);
            if (image.empty()) {
                cout << "Warning: Fail to read the image: " << file_name << "\n";
                --i_batch;
                continue;
            }
            
            images.push_back(image.clone());
            batch_names.push_back(file_name);
            cout << "Image size (height, width): " << image.rows << " " << image.cols << "\n";
        }

        // drop images if the number of images are less than [batch_size]
        if (images.size() != batch_size) {
            cout << "Warning: Last " << images.size() << " images will be dropped because the model's batch size is " 
                 << batch_size << "\n";
            for (auto& batch_name : batch_names) {
                cout << "Warning: image: " << batch_name << " will be dropped!\n";
            }
            continue;
        }

        // the number of inputs should match the number of input names
        assert(images.size() == batch_names.size());

        // predict
        clock_t start = clock();
        int predict_status = predict_model(model_name.c_str(), images, out_results, detect_thres);
        clock_t end = clock();
        double elapsed = double(end - start) / CLOCKS_PER_SEC;
        cout << "Model prediction takes " << elapsed << " seconds\n";
        if (predict_status != 0) {
            cout << "Error: Fail to perform model prediction. Status code: " << predict_status << "\n";
            system("pause");
            return predict_status;
        }

        // the number of results should match the number of inputs
        assert(images.size() == out_results.size());

        // show prediction results
        for (int i = 0; i < out_results.size(); ++i) {
            if (out_results[i].empty()) {
                cout << "Warning: This image has no prediction results!\n";
                cout << "Warning: Image name: " << batch_names[i] << "\n";
                continue;
            }
            
            vector<DetectionResult> filtered_results = filter_mask(out_results[i], top_k, mask_area_lowerbound, mask_area_upperbound);
            print_info(filtered_results);
            display_results(images[i], filtered_results);
        }
    }

    // destroy model
    destroy_model(model_name.c_str());
    cout << "Model cleared! Press any key to quit...\n";
    system("pause");
    return 0;
}


vector<string> get_file_names(const string& dir_path, bool extension) {
    vector<string> file_names;

    try {
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (extension) {
                file_names.push_back(entry.path().filename().string());
            }
            else {
                string file_name = entry.path().filename().string();
                int pos = file_name.rfind(".");
                file_names.push_back(file_name.substr(0, pos));
            }
        }
    }
    catch (const exception& e) {
        cout << "Error: Fail to read the directory: " << dir_path;
        cout << "Error messgae: " << e.what();
        file_names.clear();
    }

    return file_names;
}
 

void draw_mask(cv::Mat& image, const DetectionResult& result) {
    cv::Mat mask = result.mask;
    int x0 = static_cast<int>(max(floor(result.box.x0) - 1, 0.f));
    int y0 = static_cast<int>(max(floor(result.box.y0) - 1, 0.f));
    cv::Rect roi(x0, y0, result.mask_width, result.mask_height);
    
    // Split the BGR channels. Overlay mask to a specific color channel (blue)
    cv::Mat channels[3];
    cv::split(image, channels);
    cv::bitwise_or(mask, channels[0](roi), channels[0](roi));
    cv::merge(channels, 3, image);
}


void draw_box(cv::Mat& image, const DetectionResult& result) {
    cv::Point p1 = cv::Point(result.box.x0, result.box.y0);
    cv::Point p2 = cv::Point(result.box.x1, result.box.y1);
    // white. TODO: change it if you want
    cv::Scalar color = cv::Scalar(0, 255, 0);
    // thickness of your box line. TODO: change it if you want
    int thickness = 2;
    cv::rectangle(image, p1, p2, color, thickness);
}


void draw_info(cv::Mat& image, const DetectionResult& result) {
    string tag_label = "Label: " + result.label;
    string tag_label_index = "Label index: " + to_string(result.label_index);
    string tag_score = "Score: " + to_string(result.score);

    // TODO: change following values if you need to display texts clearly on your test images.
    // size of characters. TODO: change it if you want
    double fontScale = 3;
    // thickness of characters. TODO: change it if you want
    int thickness = 4;
    // white. TODO: change it if you want
    cv::Scalar color = cv::Scalar(255, 255, 255);
    // font. TODO: change it if you want
    auto font = cv::FONT_HERSHEY_PLAIN;
    // the position where to print tagLabel. TODO: change it if you want
    cv::Point up = cv::Point(result.box.x0, result.box.y0);
    // the position where to print tagLabelIndex. TODO: change it if you want
    cv::Point center = cv::Point(result.box.x0, (result.box.y0 + result.box.y1) / 2);
    // the position where to print tagScore. TODO: change it if you want
    cv::Point bottom = cv::Point(result.box.x0, result.box.y1);
    cv::putText(image, tag_label, up, font, fontScale, color, thickness);
    cv::putText(image, tag_label_index, center, font, fontScale, color, thickness);
    cv::putText(image, tag_score, bottom, font, fontScale, color, thickness);
}


void display_results(cv::Mat& image, const vector<DetectionResult>& results, const string &window_name) {
    cv::namedWindow(window_name, cv::WINDOW_FREERATIO);
    // TODO: you can change the size of the display window
    // cv::resizeWindow(window_name, 800, 1200);

    for (const auto& result : results) {
        draw_mask(image, result);
        draw_info(image, result);
    }

    cv::imshow(window_name, image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}


void print_info(const vector<DetectionResult>& results) {
    cout << "\n";
    for (auto& result : results) {
        cout << "label:                              " << result.label << "\n";
        cout << "label_index:                        " << result.label_index << "\n";
        cout << "confidential score:                 " << result.score << "\n";
        cout << "position of result(x0,y0,x1,y1):    " << "(" << result.box.x0 << ", " << result.box.y0 
                                                       << ", " << result.box.x1 << ", " << result.box.y1 << ")\n";
        cout << "row_index:                          " << result.row_index << "\n";
        cout << "col_index:                          " << result.col_index << "\n";
        cout << "mask_width:                         " << result.mask_width << "\n";
        cout << "mask_height:                        " << result.mask_height << "\n";
        cout << "mask area (#pixels)                 " << cv::countNonZero(result.mask) << "\n";
        cout << "\n\n";
    }   
}


vector<DetectionResult> filter_mask(const vector<DetectionResult>& results, int top_k, int mask_area_lowerbound, int mask_area_upperbound) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greaterComp> minPQ;
    
    for (int i = 0; i < results.size(); ++i) {
        // it should be a segmentation task
        assert(!results[i].mask.empty());
        
        // calculate mask area and filter out ones which don't meet requirements
        int white_pixel_count = cv::countNonZero(results[i].mask);
        if (mask_area_lowerbound <= white_pixel_count && white_pixel_count <= mask_area_upperbound) {
            minPQ.emplace(i, white_pixel_count);
        }

        // maintain current largest k masks
        if (top_k > 0 && minPQ.size() > top_k) minPQ.pop();
    }

    // output largest k results
    vector<DetectionResult> filtered_results;
    while (!minPQ.empty()) {
        int idx = minPQ.top().first;
        minPQ.pop();
        filtered_results.push_back(results[idx]);
    }

    return filtered_results;
}