
# VS 下使用QT开发NeuroBot 桌面应用程序
## 1：下载QT
- https://www.qt.io/download
- 自己选择 Windows版本下载
![Alt text](image-5.png)
- 一路点击确认即可，要确保磁盘空间足够。
### 1.1：遇到的问题
![Alt text](image-4.png)
## 2:VS槽函数
- 定义槽函数
![Alt text](image-6.png)
- 实现槽函数
![Alt text](image-7.png)
- 绑定槽函数
![Alt text](image-8.png)
- 通过1，选择2，其中2需要手动输入，之前定义的槽函数
![Alt text](image-9.png)
![Alt text](image-10.png)
- line 选择 textchanged()
- button 选择 click()


## 3：QT 相关语法
### 3.1：弹出信息栏
``` cpp
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
QString status_str = QString::fromStdString("status code: " + to_string(status));
if (status != 0) {
    QMessageBox::about(NULL, "ERROR in load model ", status_str);
    return -1;
}
```
### 3.2：选择文件窗口 & 判断文件是否存在

- QT 如何在本地浏览目录，并获取目录地址
- QT 使用QFileDialog，选择目录，并获取选取目录地址
- QT 当前文件夹下是否有特定文件

``` cpp
#include <QDir>
#include <QString>
#include <QMessageBox>
QString filePath = QDir::currentPath() + "/License.txt";  // 替换为您要检查的文件名
if (!QFile::exists(filePath)) {
    QMessageBox::about(NULL, "ERROR in device_name ", "License does not exist");
}
```

### 3.3：填充文本
``` cpp
int newNeuroBot::onModelPath() {
    model_path = ui.lineEdit_9->text().toStdString();
    myPrint("modelpath", model_path);
    return 1;
}
```

### 3.4：string之间的转换

``` cpp
cout << selectedDir.toStdString() << endl;

QString mystring(string str) {
    return  QString::fromStdString(str);
}

``` 
### 3.5：中文乱码

``` cpp
 1、QString str = QStringLiteral("1你好世界 abc");		

 2、QString str = QObject::tr("2你好世界 abc");    

 3、QString str = QString::fromLocal8Bit("3你好世界 abc"); // 推荐

 4、QString str = QString::fromLatin1("4你好世界 abc");		

 5、QString str = QString::fromUtf8("5你好世界 abc");		

 6、QString str = QString::fromWCharArray(L"6你好世界 abc");

 7、QString str = QStringLiteral("7你好世界 abc");		    

 8、QString str = (u8"8你好世界 abc");		   

```



## 4：QT 设计师

### 4.1：添加资源
![Alt text](image-11.png)
![Alt text](image-12.png)
### 4.2：取消最上面一条线
![Alt text](image-13.png)
![Alt text](image-14.png)
### 4.3：添加背景图片
![Alt text](image-15.png)
![Alt text](image-16.png)
### 4.4：更改icon
- windowicon

### 4.5：修改窗口名称
- Windowtitle
## 5：完整代码
### 5.1：newNeuroBot.h
``` cpp

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_newNeuroBot.h"
class newNeuroBot : public QMainWindow
{
    Q_OBJECT

public:
    newNeuroBot(QWidget *parent = nullptr);
    ~newNeuroBot();

private slots: 
    int predict();
    int onModelName();
    int onModelPath();
    int onPicturePath();
    int onDeviceName();
    int getModelPath();
    int getPicPath();

private:
    Ui::newNeuroBotClass ui;
};

```

### 5.1：newNeuroBot.h
``` cpp
#include "newNeuroBot.h"
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <Windows.h>
#include <experimental/filesystem>
#include <direct.h>
#include <vector>
#include <neuro_core.h>
#include <opencv2/opencv.hpp>
#include <QDir>
#include <QString>
#pragma execution_character_set("utf-8")
namespace fs = std::experimental::filesystem;
using namespace std;

#undef max
#undef min


string image_folder_path = "D:\\Intern\\test_image\\seg_test_image";
// TODO: change to your model folder path
string model_path = "D:\\Intern\\model\\det_gpu";
// TODO: change to your model name
string model_name = "test";
// TODO: change to your device name
string device_name = "cuda";
// TODO: change to your device index (Nonnegative int)
int device_index = 0;
// TODO: change to your detection threshold. Range: [0, 1] or -1 (default, which is 0.7)
float detect_thres = -1;


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


void myPrint(string name, string str) {
    cout << name << " :  " << str << endl;
}
newNeuroBot::newNeuroBot(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

}
newNeuroBot::~newNeuroBot()
{}

int newNeuroBot::onModelName() {
    model_name = ui.modelname->text().toStdString();
    myPrint("modelname", model_name);
    return 1;
}
int newNeuroBot::onModelPath() {
    model_path = ui.lineEdit_9->text().toStdString();
    myPrint("modelpath", model_path);
    return 1;
}
int newNeuroBot::onPicturePath() {
    image_folder_path = ui.picturepath->text().toStdString();
    myPrint("picturepath", image_folder_path);
    return 1;
}
int newNeuroBot::onDeviceName() {
    device_name = ui.devicename->text().toStdString();
    myPrint("devicename", device_name);
    return 1;
}
int newNeuroBot::getModelPath() {
    QString selectedDir = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::currentPath());
    if (!selectedDir.isEmpty()) {
        
        qDebug() << "Selected directory: " << selectedDir;
        QMessageBox::about(NULL, "ERROR", "Empty Dictionary");
    }
    ui.lineEdit_9->setText(selectedDir);
    cout << selectedDir.toStdString() << endl;
    return 1;
}
int newNeuroBot::getPicPath() {
    QString selectedDir = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::currentPath());
    if (!selectedDir.isEmpty()) {
        // Do something with the selected directory
        qDebug() << "Selected directory: " << selectedDir;
    }
    ui.picturepath->setText(selectedDir);
    cout << selectedDir.toStdString() << endl;
    return 1;
}

QString mystring(string str) {
    return  QString::fromStdString(str);
}


int newNeuroBot::predict() {
    device_name = device_name;  
    if (device_name == "cpu") {
        cout << device_name << endl;
    }
    else if (device_name == "cuda") {
        QString filePath = QDir::currentPath() + "/License.txt"; 
        if (!QFile::exists(filePath)) {
            QMessageBox::about(NULL, "ERROR in device_name ", "License does not exist");
        }
        return -1;
    }
    else {
        QMessageBox::about(NULL, "ERROR in device_name ", "Device_name must be cpu or cuda");
        return -1;
    }
    int status = load_model(model_name.c_str(), model_path.c_str(), device_name.c_str());
    QString status_str = QString::fromStdString("status code: " + to_string(status));
    if (status != 0) {
        QMessageBox::about(NULL, "ERROR in load model ", status_str);
        return -1;
    }

    std::vector<std::string> img_paths;
    getFilesName(image_folder_path, img_paths);

    std::vector<cv::Mat> images;
    std::vector<int> image_ids;
    std::vector<cv::Mat> mats;

    for (int j = 0; j < 1; j++) {
        for (int i = 0; i < (int)img_paths.size(); ++i) {
            auto img = cv::imread(image_folder_path + "\\" + img_paths[i]);
            if (!img.data) {
                fprintf(stderr, "failed to load image: %s\n", img_paths[i].c_str());
                continue;
            }
            images.push_back(img);
            image_ids.push_back(i);
            mats.push_back(img);

            // process batch inference
            if ((int)mats.size() == get_batch(model_name.c_str())) {
                std::vector<std::vector<DetectionResult>> out_results{};
                DWORD start = GetTickCount64();
                int status = predict_model(model_name.c_str(), mats, out_results, -1);
                if (status != 0) {
                    string predictStatus = "status: " + to_string(status);
                    QMessageBox::about(NULL, "ERROR in predict ", mystring(predictStatus));
                    continue;
                }
                DWORD end = GetTickCount64();
                long timeCost = end - start;
                int k = 0;
                for (auto res : out_results) {
                    if (res.empty()) {
                        QMessageBox::about(NULL, "Warning in predict ", "No result");
                        continue;
                    }
                    for (auto r : res) {
                        ui.time_2->setText(mystring(to_string(timeCost)));
                        ui.score->setText(mystring(to_string(r.score)));
                        ui.label->setText(QString::fromLocal8Bit(r.label));
                        ui.labelindex->setText(mystring(to_string(r.label_index)));
                        ui.x0->setText(mystring(to_string(r.box.x0)));
                        ui.y0->setText(mystring(to_string(r.box.y0)));
                        ui.lineEdit_19->setText(mystring(to_string(r.box.x1)));
                        ui.y1->setText(mystring(to_string(r.box.y1)));
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
        (void)predict_model(model_name.c_str(), mats, out_results);
    }

    destroy_model(model_name.c_str());
    system("pause");
    return 0;

}

```



##  6：Appendix

### 6.1：Load Error Code Definitions:

|status|  Definitions  |
|  ----  | ----  |
|0|Success|
|1|	Configuration file not found|
|2|Batch parameter not found|
|3|dete_thres parameter not found|
|4|class parameter not found|
|5|	Missing required DLL for execution|
|6|ARG - NVIDIA graphics card error|
|7|Not supported|
|8|Out of bounds|
|9|	Insufficient memory|
|10|Missing model-related files for loading|
|11|	Load failed|
|12|Status count|
|50|Model type error or unable to read model.conf file|


### 6.2：Predict Error Code Definitions:
|status|  Definitions  |
|  ----  | ----  |
|0|Success|
|1|	Configuration file not found|
|2|Batch parameter not found|
|3|dete_thres parameter not found|
|4|class parameter not found|
|5|	Missing required DLL for execution|
|6|ARG - NVIDIA graphics card error|
|7|Not supported|
|50|Authorization file does not exist or permission to read is denied|
|51|	Insufficient memory|
|52|Missing model-related files for loading|
|53|	Load failed|
|54|Status count|
|55|Model type error or unable to read model.conf file|
|56|No write permission for the authorization file|
|57|Unknown error related to authorization|
|58|Authorization file version is different from SDK version|
|59|Exceeded the limit of the number of labels|

