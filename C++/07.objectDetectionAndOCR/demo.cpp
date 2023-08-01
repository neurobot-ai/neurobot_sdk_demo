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
using std::min;
using std::floor;
using std::cout;
using std::exception;
using std::to_string;
using std::unordered_set;

class ClusterCharacters {
public:
    ClusterCharacters() {}
    vector<vector<string>> find_words(vector<DetectionResult>& results);
    bool is_on_same_line(const Boxes& box1, const Boxes& box2);
    bool is_different_word(const Boxes& box1, const Boxes& box2);
    float get_center_x(const Boxes& box) { return (box.x0 + box.x1 + box.x2 + box.x3) / 4; }
    float get_center_y(const Boxes& box) { return (box.y0 + box.y1 + box.y2 + box.y3) / 4; }
    float get_min_x(const Boxes& box) { return min(min(box.x0, box.x1), min(box.x2, box.x3)); }
    float get_min_y(const Boxes& box) { return min(min(box.y0, box.y1), min(box.y2, box.y3)); }
    float get_max_x(const Boxes& box) { return max(max(box.x0, box.x1), max(box.x2, box.x3)); }
    float get_max_y(const Boxes& box) { return max(max(box.y0, box.y1), max(box.y2, box.y3)); }
private:
    // comparator for sorting characters
    struct lessCompX {
        bool operator() (const DetectionResult& result1, const DetectionResult& result2) {
            float result1_center_x = (result1.box.x0 + result1.box.x1 + result1.box.x2 + result1.box.x3) / 4;
            float result2_center_x = (result2.box.x0 + result2.box.x1 + result2.box.x2 + result2.box.x3) / 4;
            return result1_center_x < result2_center_x;
        }
    };

    // comparator for sorting characters
    struct lessCompY {
        bool operator() (const DetectionResult& result1, const DetectionResult& result2) {
            float result1_center_y = (result1.box.y0 + result1.box.y1 + result1.box.y2 + result1.box.y3) / 4;
            float result2_center_y = (result2.box.y0 + result2.box.y1 + result2.box.y2 + result2.box.y3) / 4;
            return result1_center_y < result2_center_y;
        }
    };
};


// Return all image file names in the path <dir_path>.
// Inputs: dirPath:		the path of folder containing all test images
//		   extension:   whether the image name has an extension or not
// Modify: None
// Output: A vector of strings (image file names)
vector<string> get_file_names(const string& dir_path, bool extension = true);


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


int main(int argc, char** argv) {
    // TODO: change to your test image folder path
    string image_folder_path = "D:\\new_sdk\\sdk\\image";
    // TODO: change to your detection model folder path
    string det_model_path = "D:\\new_sdk\\sdk\\model\\dbnet";
    // TODO: change to your recognition model folder path
    string rec_model_path = "D:\\new_sdk\\sdk\\model\\satrn_mydata3_fp16_b2";
    // TODO: change to your model name
    string model_name = "test";
    // TODO: change to your device name
    string device_name = "cuda";
    // TODO: change to your device index (Nonnegative int)
    int device_index = 0;
    // TODO: change to your detection threshold. Range: [0, 1] or -1 (default, which is 0.7)
    float detect_thres = -1;
    
    cout << "\n\n";
    cout << "Test image folder path: " << image_folder_path << "\n";
    cout << "Detection model path: " << det_model_path << "\n";
    cout << "Recognition model path: " << rec_model_path << "\n";
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
    int load_status = load_model(model_name.c_str(), det_model_path.c_str(), rec_model_path.c_str(), device_name.c_str(), device_index);
    if (load_status != 0) {
        cout << "Error: Fail to load the model. Status code: " << load_status << "\n";
        system("pause");
        return load_status;
    }

    int batch_size = 1; // it is fixed in the current version
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


// return clustered characters as words, line by line
vector<vector<string>> ClusterCharacters::find_words(vector<DetectionResult>& results) {
    vector<vector<string>> texts;
    if (results.empty()) return texts;

    sort(results.begin(), results.end(), lessCompY()); // find lines from top to bottom
    unordered_set<int> group_id; // record characters' id which have already been clustered

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

        // if no character is on the same line with ith character, then itself forms a line
        if (group_id.empty()) {
            group_id.insert(i);
            last_id = i;
        }

        vector<DetectionResult> group;
        for (int id : group_id) group.push_back(results[id]);
        sort(group.begin(), group.end(), lessCompX()); // find texts from left to right in this line

        vector<string> words;
        string word = "";
        for (int j = 0; j < group.size(); ++j) {
            word += group[j].label;
            // they are two different words
            if (j < group.size() - 1 && is_different_word(group[j].box, group[j + 1].box)) {
                words.push_back(word);
                word.clear();
            }
        }
        words.push_back(word);
        texts.push_back(words);

        i = last_id + 1;
        group_id.clear();
    }

    return texts;
}

// return true if box2 is on the same line with box1
bool ClusterCharacters::is_on_same_line(const Boxes& box1, const Boxes& box2) {
    float box1_center_y = get_center_y(box1);
    float box2_center_y = get_center_y(box2);

    float height1 = get_max_y(box1) - get_min_y(box1);
    // around +/- the character's height can be regarded as one line
    if (fabs(box1_center_y - box2_center_y) <=  1.0 * height1) return true;
    else return false;
}

// return true if box1 and box2 are two different words
bool ClusterCharacters::is_different_word(const Boxes& box1, const Boxes& box2) {
    float width1 = get_max_x(box1) - get_min_x(box1);
    float gap = get_center_x(box2) - get_center_x(box1);
    if (gap > 2 * width1) return true; // if they are at least 1 character's width far, then they are different words
    else return false;
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


void draw_box(cv::Mat& image, const DetectionResult& result) {
    cv::Point p1 = cv::Point(result.box.x0, result.box.y0);
    cv::Point p2 = cv::Point(result.box.x1, result.box.y1);
    cv::Point p3 = cv::Point(result.box.x2, result.box.y2);
    cv::Point p4 = cv::Point(result.box.x3, result.box.y3);
    // green. TODO: change it if you want
    cv::Scalar color = cv::Scalar(0, 255, 0);
    // thickness of your box line. TODO: change it if you want
    int thickness = 2;
    bool is_closed = true;
    vector<cv::Point>points = { p1, p2, p3, p4 };

    cv::polylines(image, points, is_closed, color, thickness);
}


void draw_info(cv::Mat& image, const DetectionResult& result) {
    string tag_label = result.label;

    // TODO: change following values if you need to display texts clearly on your test images.
    // size of characters. TODO: change it if you want
    double fontScale = 2;
    // thickness of characters. TODO: change it if you want
    int thickness = 2;
    // green. TODO: change it if you want
    cv::Scalar color = cv::Scalar(255, 255, 255);
    // font. TODO: change it if you want
    auto font = cv::FONT_HERSHEY_PLAIN;
    // the position where to print tag_label. TODO: change it if you want
    cv::Point center = cv::Point((result.box.x0 + result.box.x1 + result.box.x2 + result.box.x3) / 4,
        (result.box.y0 + result.box.y1 + result.box.y2 + result.box.y3) / 4);

    cv::putText(image, tag_label, center, font, fontScale, color, thickness);
}


void display_results(cv::Mat& image, const vector<DetectionResult>& results, const string& window_name) {
    cv::namedWindow(window_name, cv::WINDOW_FREERATIO);
    // TODO: you can change the size of the display window
    // cv::resizeWindow(window_name, 800, 1200);

    for (const auto& result : results) {
        draw_box(image, result);
        // draw_info(image, result);
    }

    cv::imshow(window_name, image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}


void print_info(const vector<DetectionResult>& results) {
    cout << "\n";
    for (auto& result : results) {
        cout << "label:                                                " << result.label << "\n";
        cout << "confidential score of the bounding box:               " << result.box_score << "\n";
        cout << "confidential score of the content inside the box:     " << result.score << "\n";
        cout << "Positions of the bounding box's 4 vertices:\n";
        cout << "(x0, y0):                                             " << "(" << result.box.x0 << ", " << result.box.y0 << ")\n";
        cout << "(x1, y1):                                             " << "(" << result.box.x1 << ", " << result.box.y1 << ")\n";
        cout << "(x2, y2):                                             " << "(" << result.box.x2 << ", " << result.box.y2 << ")\n";
        cout << "(x3, y3):                                             " << "(" << result.box.x3 << ", " << result.box.y3 << ")\n";
        cout << "\n\n";
    }
}