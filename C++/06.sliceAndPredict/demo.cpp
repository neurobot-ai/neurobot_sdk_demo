#pragma comment(lib,"Msi.lib");
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
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
using namespace std;
namespace fs = experimental::filesystem;


class smallPic
{
public:
	int row_begin, col_begin;            // the position in the big picture.
	cv::Mat image;                       // the image
	int height, width;                   // the height and width of the image
	vector<DetectionResult> res;         // the result after prediction
	smallPic(int row, int col, cv::Mat img, int height, int width) :row_begin(row), col_begin(col), image(img), height(height), width(width) {};
	bool setDetectionResult(vector<DetectionResult> result)
	{
		res = result;
		return true;
	}

};


class BigPic
{
public:
	string fileName;                     // the fileName of the big picture
	cv::Mat imageMat;                    // the image Mat object
	vector<smallPic *> child;            // all of his child
	vector<DetectionResult> res;         // the result after prediction
	BigPic(string file_name, cv::Mat image_mat)
	{
		this->fileName = file_name;
		this->imageMat = image_mat;

	}
	BigPic(string file_name, cv::Mat image_mat, vector<smallPic *> child)
	{
		this->fileName = file_name;
		this->imageMat = image_mat;
		this->child = child;
	}
};


// Data Structure UnionFindSet is used for dividing pictures may be one result.


class UnionFindSet
{
private:
	vector<int> _ufs;
public:
	UnionFindSet(size_t size) :_ufs(size, -1){}
	int findRoot(int index)
	{
		while(_ufs[index] >= 0)
		{
			index = _ufs[index];
		}
		return index;
	}
	bool Union(int a, int b)
	{
		int root1 = findRoot(a);
		int root2 = findRoot(b);
		if (root1 == root2) return false;
		_ufs[root1] += _ufs[root2];
		_ufs[root1] = root1;
		return true;
	}
	size_t Count() const
	{
		size_t count = 0;
		for(auto e: _ufs)
		{
			if (e < 0) ++count;
		}
		return count;
	}
};


// use UnionFindSet to Divide pictures into different groups


// 
// Parameters
// 
//         vector<DetectionResult>& res           [IN]           the name of dictionary.
//         vFileNames    [OUT]          the result will be put into it.
//         extension     [IN]           ZERO means having extension, such as A.jpg.
//                                      ONE means having no extension, such as A.
//  
// Returns  
//         The size of all the files.


int consolidationResult(vector<DetectionResult>& res,vector<DetectionResult>& result)
{

	vector<int> visited(res.size(), -1);
	const int i_res_size = res.size();
	for(int i_res = 0; i_res < i_res_size; i_res++)
	{
		
		if (visited[i_res] == 1) continue;
		DetectionResult tempRes = res[i_res];
		float x0 = res[i_res].box.x0;
		float y0 = res[i_res].box.y0;
		float x1 = res[i_res].box.x1;
		float y1 = res[i_res].box.y1;
		for(int j_res = i_res + 1; j_res < i_res_size; j_res++)
		{
			if(visited[j_res] == 1) continue;
			if (res[i_res].label_index == res[j_res].label_index
				&& (abs(res[i_res].box.y0 - res[j_res].box.y0) <= 1 || abs(res[i_res].box.y0 - res[j_res].box.y1) <= 1
					|| abs(res[i_res].box.y1 - res[j_res].box.y0) <= 1 || abs(res[i_res].box.y1 - res[j_res].box.y1) <= 1)
				) {
				visited[i_res] = 1;
				visited[j_res] = 1;

				x0 = min(x0, res[j_res].box.x0);
				y0 = min(y0, res[j_res].box.y0);
				x1 = max(x1, res[j_res].box.x1);
				y1 = max(y1, res[j_res].box.y0);

				// 如果在这里扩大的话，可能后续不相连的框也变大了
				//res[i_res].box.x0 = min(res[i_res].box.x0, res[j_res].box.x0);
				//res[j_res].box.x0 = res[i_res].box.x0;
				//res[i_res].box.y0 = min(res[i_res].box.y0, res[j_res].box.y0);
				//res[j_res].box.y0 = res[i_res].box.y0;
				//res[i_res].box.x1 = max(res[i_res].box.x1, res[j_res].box.x1);
				//res[j_res].box.x1 = res[i_res].box.x1;
				//res[i_res].box.y1 = max(res[i_res].box.y1, res[j_res].box.y1);
				//res[j_res].box.y1 = res[i_res].box.y1;
			}
		}
		visited[i_res] = 1;
		tempRes.box.x0 = x0;
		tempRes.box.y0 = y0;
		tempRes.box.x1 = x1;
		tempRes.box.y1 = y1;
		result.push_back(tempRes);
	}
	return result.size();
}


// Print all the information from the DetectionResult
// 
// Parameters
// 
//         r           [IN]          DetectionResult
//  
//


void printInfo(DetectionResult r)
{
	cout << "label:                              " << r.label << endl;
	cout << "Label_index:                        " << r.label_index << endl;
	cout << "Confidential score:                 " << r.score << endl;
	cout << "Position of result(x0,y0,x1,y1):    " << r.box.x0 << "  " << r.box.y0 << "  " << r.box.x1 << "  " << r.box.y1 << endl;
	cout << "Row_index:                          " << r.row_index << endl;
	cout << "Col_index:                          " << r.col_index << endl;
	cout << "Mask_width:                         " << r.mask_width << endl;
	cout << "Mask_height:                        " << r.mask_height << endl << endl << endl;
}


// test Function consolidationResult


void testconsolidationResult(vector<DetectionResult>& res)
{
	vector<DetectionResult> result;
	int len = consolidationResult(res,result);
	for(int i_res = 0; i_res < result.size(); i_res++)
	{
		printInfo(result[i_res]);
	}

}


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


int getAllImageName(const std::string dir, std::vector<std::string>& vFileNames, bool extension = 1)
{
	for (const auto& entry : fs::directory_iterator(dir))
	{
		if (1 == extension)
		{
			// with extension
			string path = dir + "\\" + entry.path().filename().string();
			vFileNames.push_back(path);
		}
		else if (0 == extension)
		{
			// without extension
			std::string fileName;
			fileName = entry.path().filename().string();
			int pos = fileName.rfind(".");
			string path = dir + "\\" + std::string(fileName, 0, pos);
			vFileNames.push_back(path);
			fileName.clear();
		}
	}
	if (vFileNames.empty()) {
		std::cout << "This dictionary is Empty, please check your dictinoary path." << endl;
	}
	return vFileNames.size();

}


// crop the big picture and row * col smaller pictures.
// You can also crop the picture with different methods, such as according to the Total pixel size， or 1/3 part.
// 
// Parameters
// 
//         iMat          [OUT]          add the smallPic Object to the array 
//         image         [IN]           the big picture Mat
//         row           [IN]           the number of the row
//         col           [IN]           the number of the col
//  
// Returns  
//         The size of iMat.    


int dividePicture(vector<smallPic *> &iMat, cv::Mat& image, int row, int col)
{
	int rowSize = image.cols;            
	int colSize = image.rows;
	int eachRowSize = rowSize / row;            // the height of each small picture
	int eachColSize = colSize / col;            // the width  of each small picture
	for (int i_row = 0; i_row < row; ++i_row)
	{
		for (int j_col = 0; j_col < col; ++j_col)
		{
			int row_begin = i_row * eachRowSize;
			int col_begin = j_col * eachColSize;

			// Crop picture from the big picture.
			// Rect(x_begin, y_begin, width, height)
			cv::Mat newMat(image, Rect(row_begin, col_begin, eachRowSize, eachColSize));

			// Construct a smallPic Object, adding it to the iMat.
			// all the smallPic object are the children of the image.
			smallPic *mySmallPic = new smallPic(row_begin, col_begin, newMat.clone(), eachRowSize,eachColSize );

			//for debug.
			//string window_name = to_string(i_row) + "  " + to_string(j_col);
			//cv::namedWindow(window_name, WINDOW_AUTOSIZE);
			//cv::imshow(window_name, newMat);
			//cv::waitKey(0);
			//cv::destroyAllWindows();
			iMat.push_back(mySmallPic);
		}
	}
	return iMat.size();
}


// Read image from dir, and construct BigPic arrary according to the row and col.
// 
// Parameters
// 
//         dir           [IN]          the strings of all the pictures.
//         res           [OUT]           the Bigpic
//         row           [IN]           the number of the row
//         col           [IN]           the number of the col
//  
// Returns  
//         The size of iMat.


int getBigPic(const vector<string>& dir, vector<BigPic *>& res, int row, int col)
{
	
	for (int i = 0; i < dir.size(); ++i)
	{
		string fileName = dir[i];                         //  get fileName
		cv::Mat imageMat = cv::imread(fileName);          //  get image Mat object
		vector<smallPic *> imat;                          //  all the children 
		int mystatus = dividePicture(imat,imageMat, row, col);
		BigPic*myBigPic = new BigPic(fileName, imageMat, imat);
		res.push_back(myBigPic);
	}
	return res.size();

}


// Add all of the children's result to the Parent
// 
// Parameters
// 
//         res           [IN & OUT]          BigPic
//  
// Returns  
//         The size of children's result.


int convertPicToOriginalRes(BigPic * res)
{
	uint32_t size = 0;
	vector<smallPic*> iMat = res->child;
	for(int i = 0; i < iMat.size(); ++i)
	{
		for(int j = 0; j < iMat[i]->res.size(); ++j)
		{
			int row_begin = iMat[i]->row_begin;
			int col_begin = iMat[i]->col_begin;
			iMat[i]->res[j].box.x0 += row_begin;   // Position in the big picture is the x_bgin add row_begin
			iMat[i]->res[j].box.y0 += col_begin;   // Position in the big picture is the y_bgin add col_begin
			iMat[i]->res[j].box.x1 += row_begin;  
			iMat[i]->res[j].box.y1 += col_begin;  
			res->res.push_back(iMat[i]->res[j]);
			size++;
		}
	}
	return size;
}


// Add all of the children's result to the Parent, particularly in index i.
// 
// Parameters
// 
//         res           [IN & OUT]          BigPic array
//         i             [IN]                   
//  
// Returns  
//         The size of children's result.


int convertPicToOriginalRes(vector<BigPic *>& res, int i )
{
	uint32_t size = 0;

	vector<smallPic *> iMat = res[i]->child;
	for (int j = 0; j < iMat.size(); ++j)
	{
		for (int z = 0; z < iMat[j]->res.size(); ++z)
		{
			int row_begin = iMat[j]->row_begin;
			int col_begin = iMat[j]->col_begin;
			iMat[j]->res[z].box.x0 += row_begin;
			iMat[j]->res[z].box.y0 += col_begin;
			iMat[j]->res[z].box.x1 += row_begin;
			iMat[j]->res[z].box.y1 += col_begin;
			res[i]->res.push_back(iMat[j]->res[z]);
			size++;
		}
	}
	return size;

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
		cerr << "input is empty, please check the path!" << std::endl;
		return;
	}

	int fontface = cv::FONT_HERSHEY_PLAIN;
	// thickness 是结果的边框宽度
	// fontsize 是字体的大小
	int fontsize = 10;
	double thickness = 1;

	for (int i = 0; i < info.size(); i++)
	{
		//  Generate two points and show the label on the graph.
		cv::Point p1(info[i].box.x0, info[i].box.y0), p2(info[i].box.x1, info[i].box.y1);
		cout << (info[i].label).c_str() << endl;
		putTextZH(image, (info[i].label).c_str(), p1, cv::Scalar(0, 0, 255), fontsize, "Arial", false, false);
		if (info[i].mask.empty()) {
			cv::rectangle(image, p1, p2, cv::Scalar(0, 255, 0), thickness);
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


// testgetFilesFullName
// 
// Parameters
// 
//         dir           [IN]          DetectionResult
//  
//


void testgetFilesFullName(string dir)
{
	vector<string> fullNames;
	getAllImageName(dir, fullNames);
	for (int i = 0; i < fullNames.size(); ++i)
	{
		cout << fullNames[i] << endl;
	}
}


int main(int argc, char** argv)
{
	
	string device_name = "cuda";
	string model_path = "C:\\Users\\NeuroBot\\Desktop\\disney\\gpu_model_divide_and_predict";
	string file_path = "E:\\Blood Cells Image Dataset\\bloodcells_dataset\\basophil";
	string model_name = "A";

	//	image can be divided into n equal parts according to the set x*y parameters.
	//	And the resolution of each part will remain the same.
	//  row is the number to be cropped in height.
	//  col is the number to be cropped in width.
	int row = 2;   
	int col = 2;
	int status = load_model(model_name.c_str(), model_path.c_str(), device_name.c_str());
	if (status != 0) {
		cerr << "failed to create detector, code: " << status << endl;
		return -1;
	}
	vector<string> img_paths;
	vector<cv::Mat> images;
	int imageNameSize = getAllImageName(file_path, img_paths);
	if (imageNameSize <= 0)
	{
		cerr << "[Error] read image error!" << endl;
		return -1;
	}
	vector<BigPic *> allBigPic;
	int bigPicSize = getBigPic(img_paths, allBigPic, row, col);
	for (int i = 0; i < allBigPic.size(); ++i) {
		for (int j = 0; j < allBigPic[i]->child.size(); j++)
		{
			images.push_back(allBigPic[i]->child[j]->image);
			cout << allBigPic[i]->fileName << endl;
			if ((int)images.size() == get_batch(model_name.c_str())) {
				vector<vector<DetectionResult>> out_results;
				DWORD start = GetTickCount64();
				int predictStatus = predict_model(model_name.c_str(), images, out_results);
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
				int index = 0;
				for (auto res : out_results) {
					for(auto info : res)
					{
						printInfo(info);
					}
					allBigPic[i]->child[j]->res = res;
				}
			}
			images.pop_back();
		}
		int convertSize = convertPicToOriginalRes(allBigPic, i);
		cout << convertSize << endl;
		vector<DetectionResult> finalResult;
		int status = consolidationResult(allBigPic[i]->res, finalResult);
		cout << status << endl;
		string fileName = allBigPic[i]->fileName;
		for (int j = 0; j < finalResult.size(); ++j)
		{
			cout << "label:                              " << finalResult[j].label << endl;
			cout << "Label_index:                        " << finalResult[j].label_index << endl;
			cout << "Confidential score:                 " << finalResult[j].score << endl;
			cout << "Position of result(x0,y0,x1,y1):    " << finalResult[j].box.x0 << "  " << finalResult[j].box.y0 << "  " << finalResult[j].box.x1 << "  " << finalResult[j].box.y1 << endl;
			cout << "Row_index:                          " << finalResult[j].row_index << endl;
			cout << "Col_index:                          " << finalResult[j].col_index << endl;
			cout << "Mask_width:                         " << finalResult[j].mask_width << endl;
			cout << "Mask_height:                        " << finalResult[j].mask_height << endl << endl << endl;
		}
		cout << endl << endl << endl;
		visualResult(allBigPic[i]->imageMat, finalResult, fileName);
	}
	destroy_model(model_name.c_str());
	system("pause");
}








