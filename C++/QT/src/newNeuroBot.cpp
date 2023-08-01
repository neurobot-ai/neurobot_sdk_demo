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

// C++ 23 新增加了头文件 print 

string image_folder_path = "D:\\Intern\\test_image\\seg_test_image";
// TODO: change to your model folder path
string model_path = "D:\\Intern\\model\\det_gpu";
// TODO: change to your model name
string model_name = "test";
// TODO: change to your device name
string device_name = "cpu";
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
    device_name = ui.devicename->currentText().toStdString();
    qDebug() << ui.devicename->currentText();
    myPrint("devicename", device_name);
    return 1;
}
int newNeuroBot::getModelPath() {
    QString selectedDir = QFileDialog::getExistingDirectory(nullptr, "Select Directory", QDir::currentPath());
    if (selectedDir.isEmpty()) {
        
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


void newNeuroBot::closeEvent(QCloseEvent* event)
{
    switch (QMessageBox::information(this, tr("Quit"),
        tr("Do you really want to quit?"),
        tr("Yes"), tr("No"),
        0, 1))
    {
    case 0:
        event->accept();
        exit(0);
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
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
            return -1;
        }  
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
    qDebug() << img_paths.size();
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
                qDebug() << out_results.size();
                for (auto res : out_results) {
                    if (res.empty()) {
                        QMessageBox::about(NULL, "Warning in predict ", "No result");
                        continue;
                    }
                    for (auto r : res) {
                        ui.time_2->setText(mystring(to_string(timeCost) + "  ms"));
                        ui.score->setText(mystring(to_string(r.score)));
                        ui.label->setText(QString::fromLocal8Bit(r.label));
                        ui.labelindex->setText(mystring(to_string(r.label_index)));
                        ui.x0->setText(mystring(to_string(r.box.x0)));
                        ui.y0->setText(mystring(to_string(r.box.y0)));
                        ui.lineEdit_19->setText(mystring(to_string(r.box.x1)));
                        ui.y1->setText(mystring(to_string(r.box.y1)));
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