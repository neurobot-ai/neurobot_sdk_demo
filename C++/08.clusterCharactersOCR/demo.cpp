#include <Windows.h>
#include <experimental/filesystem>
#include <iostream>
#include <direct.h>
#include <vector>
#include <string>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <unordered_set>

namespace fs = std::experimental::filesystem;
using std::string;
using std::vector;
using std::max;
using std::floor;
using std::cout;
using std::exception;
using std::to_string;
using std::sort;
using std::unordered_set;


class ClusterCharacters {
public:
    ClusterCharacters() {}
    vector<vector<string>> find_words(vector<DetectionResult>& results);
    bool is_on_same_line(const Boxes& box1, const Boxes& box2);
    bool is_different_text(const Boxes& box1, const Boxes& box2);
private:
    // comparator for sorting characters
    struct lessCompX {
        bool operator() (const DetectionResult& d1, const DetectionResult& d2) {
            return d1.box.x0 < d2.box.x0;
        }
    };

    // comparator for sorting characters
    struct lessCompY {
        bool operator() (const DetectionResult& d1, const DetectionResult& d2) {
            return d1.box.y0 < d2.box.y0;
        }
    };
};


// return clustered characters as words, line by line
vector<vector<string>> ClusterCharacters::find_words(vector<DetectionResult>& results) {
    vector<vector<string>> texts;
    if (results.empty()) return texts;

    sort(results.begin(), results.end(), lessCompY());
    unordered_set<int> group_id;

    for (int i = 0; i < results.size();) {
        int last_id = -1;
        for (int j = i + 1; j < results.size(); ++j) {
            if (is_on_same_line(results[i].box, results[j].box)) {
                if (group_id.count(i) == 0) {
                    group_id.insert(i);
                    last_id = i;
                }
                if (group_id.count(j) == 0) {
                    group_id.insert(j);
                    last_id = j;
                }
            }
        }

        if (group_id.empty()) {
            group_id.insert(i);
            last_id = i;
        }
        
        vector<DetectionResult> group;
        for (int id : group_id) group.push_back(results[id]);
        sort(group.begin(), group.end(), lessCompX());

        vector<string> text;
        string word= "";
        for (int j = 0; j < group.size(); ++j) {
            word += group[j].label;
            if (j <= group.size() - 1 &&is_different_text(group[j].box, group[j + 1].box)) {
                text.push_back(word);
                word.clear();
            }
        }
        text.push_back(word);
        texts.push_back(text);
        
        i = last_id + 1;
        group_id.clear();
    }

    int i = 0;
    return texts;
}

// return true if box2 is on the same line with box1
bool ClusterCharacters::is_on_same_line(const Boxes& box1, const Boxes& box2) {
    float box1_center_y = (box1.y0 + box1.y1) / 2;
    float box2_center_y = (box2.y0 + box2.y1) / 2;
    float height1 = box1.y1 - box1.y0;
    // around +/- half the character's height can be regarded as one line
    if (fabs(box1_center_y - box2_center_y) < 0.5 * height1) return true;
    else return false;
}


// return true if box1 and box2 are two different words
bool ClusterCharacters::is_different_text(const Boxes& box1, const Boxes& box2) {
    float width1 = box1.x1 - box1.x0;
    if (box2.x0 - box1.x1 > width1) return true;
    else return false;
}


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


// This demo shows how to cluster predicted characters return by an OCR model into words using clustering methods (k-means and DBSCAN)
int main(int argc, char** argv) {
    // TODO: change to your test image folder path
    string image_folder_path = "D:\\Intern\\test_image\\ocr_test_sort2";
    // TODO: change to your model folder path
    string model_path = "D:\\Intern\\model\\ocr_sort2_cpu";
    // TODO: change to your model name
    string model_name = "ocr";
    // TODO: change to your device name
    string device_name = "cpu";
    // TODO: change to your device index (Nonnegative int)
    int device_index = 0;
    // TODO: change to your detection threshold. Range: [0, 1] or -1 (default, which is 0.7)
    float detect_thres = -1;

    cout << "\n\n";
    cout << "Test image folder path: " << image_folder_path << "\n";
    cout << "Model path: " << model_path << "\n";
    cout << "Model name: " << model_name << "\n";
    cout << "Device name: " << device_name << "\n";
    cout << "Device index: " << device_index << "\n";
    cout << "Detection threshold: " << detect_thres << "\n";
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

    // check device_index
    if (device_index < 0) {
        cout << "Error: device_index should be a nonnegative integer\n";
        system("pause");
        return -1;
    }

    // check detect_thres
    if (!(0 <= detect_thres && detect_thres <= 1) && detect_thres != -1) {
        cout << "Error: the range of detectThres is [0, 1] or -1\n";
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

    ClusterCharacters cc = ClusterCharacters();

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

            // print_info(out_results[i]);

            // sort detected characters into texts
            start = clock();
            vector<vector<string>> texts = cc.find_words(out_results[i]);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;

            cout << "Character clustering takes " << elapsed << " seconds\n\n";
            cout << "After character clustering, texts are: \n";
            cout << "##########################\n";
            for (const auto& text : texts) {
                for (const auto& word : text) {
                    cout << word << " ";
                }
                cout << "\n";
            }
            cout << "##########################\n\n";

            
            display_results(images[i], out_results[i]);
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


void display_results(cv::Mat& image, const vector<DetectionResult>& results, const string& window_name) {
    cv::namedWindow(window_name, cv::WINDOW_FREERATIO);
    // TODO: you can change the size of the display window
    // cv::resizeWindow(window_name, 800, 1200);

    for (const auto& result : results) {
        if (result.mask.empty()) {
            draw_box(image, result);
        }
        else {
            draw_mask(image, result);
        }

        // print labels, label indices, and confidence scores on the ima
        // TODO: you can comment it to not print info on test images
        // draw_info(image, result);
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
        cout << "\n\n";
    }
}