#pragma once
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/imgcodecs.hpp"

// this header file is for the new SDK, which is specially dedicated to solving the problem: 
// detect objects with characters first using a detection model, 
// and then detect characters in objects using an OCR model

// the bounding box containing a detected object (a character), which is represented by four vertices:
// (x0, y0), (x1, y1), (x2, y2), (x3, y3). They are arranged in a clockwise order but
// (x0, y0) is not always the top left vertex of the bounding box
struct Boxes {
	float x0;
	float y0;
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
};


// detection result
struct DetectionResult
{
	Boxes box;          // the bounding box containing a single object (a single character)
	float score;        // the confidence score of the character
	float box_score;    // the confidence score of the bounding box
	std::string label;  // the label of the detected object (a single character)
};



// Load the model
// Inputs: model_name:		Name of the model
//		   dete_model_path: File path which stores the detection model
//         rec_model_path:  File path which stores the OCR model
// 		   device_name:  	Name of the device. "cuda" for GPU and "cpu" for CPU. Default: "cuda"
//		   device_index: 	Index of the device. Default: 0
// Modify: None
// Output: A status code indicating whether loading the model is successful or not.
//		   0 means success and non-zero values mean failure
extern "C" __declspec(dllexport) int load_model(const char* model_name, const char* dete_model_path, const char* rec_model_path, 
												const char* device_name = "cuda", const int device_index = 0);



// Use the model to predict and get results
// Inputs: model_name:		Name of the model
//         mats:		    An array of test images. Each image is read by OpenCV in the format of cv::Mat	
//         out_results:		An empty 2D vector which is used for storing detection results
//         dete_thres:	    Threshold for detection model. The default is -1.0, meaning using the default configuration.
// 							Here the default is 0.7. 
//         rec_thres:	    Threshold for OCR model. The default is -1.0, meaning using the default configuration.
// 							Here the default is 0.7. 
// Modify: out_results:		Store detection results in out_results if the model predicts successfully
// Output: A status code indicating whether the model predicts successfully or not.
//		   0 means success and non-zero values mean failure
extern "C" __declspec(dllexport) int predict_model(const char* model_name, const std::vector<cv::Mat>& mats, 
												   std::vector<std::vector<DetectionResult>>& out_results, 
												   float dete_thres = -1.0, float rec_thres = -1.0);



// Release memory spaces (primarily for GPU) used by the model
// Inputs: model_name:		Name of the model
// Modify: None
// Output: None
extern "C" __declspec(dllexport) void destroy_model(const char* model_name);
