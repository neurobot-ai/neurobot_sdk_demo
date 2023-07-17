using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NeuroDetection;
using OpenCvSharp;


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Globalization;
using OpenCvSharp;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using NeuroDetection;
namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public string modelName = "";
        public string deviceName = "";
        public string modelPath = "";
        public string imageFolderPath = "";


        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {



        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged_1(object sender, EventArgs e)
        {
            int index = setDeviceName.SelectedIndex;
            string str = (string)setDeviceName.SelectedItem;
            deviceName = str;
            Console.WriteLine(deviceName);

        }

        private void label7_Click(object sender, EventArgs e)
        {
            

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void onModeName(object sender, KeyPressEventArgs e)
        {
            modelName = setModelName.Text;
            if (modelName.Length < 1)
            {
                MessageBox.Show("请输入模型名称，按回车结束");
            }

        }

        private void onModelPath(object sender, KeyPressEventArgs e)
        {

                string str = setModelName.Text;
                string outStr = str.Replace("\\", "\\\\");
                modelPath = outStr;
           


        }

        private void onPicPath(object sender, KeyPressEventArgs e)
        {
 
                string str = setModelName.Text;
                string outStr = str.Replace("\\", "\\\\");
                imageFolderPath = outStr;
             

        }

        public void sdkMain()
        {
            SDK sdk = new SDK();
            mysdk demo = new mysdk();
            Console.WriteLine("Image folder path: " + imageFolderPath);
            List<string> fileNames = demo.GetFilesName(imageFolderPath, extension: true);
            int numFiles = fileNames.Count;
            if (numFiles == 0)
            {
                Console.WriteLine("Error: This image folder is empty!");
                return;
            }

            Console.WriteLine("The total number of test images: " + numFiles);
            Console.WriteLine("Model path: " + modelPath);
            Console.WriteLine("Model name: " + modelName);
            Console.WriteLine("Device name: " + deviceName);

            int status = sdk.LoadModel(modelName, modelPath, deviceName);
            if (status != 0)
            {
                MessageBox.Show("ERROR: Fail to load the model. Status code: " + status);
                return;
            }
            Console.WriteLine("Batch size: " + sdk.GetBatch(modelName) + "\n");

            for (int iFile = 0; iFile < numFiles; ++iFile)
            {
                string iFileName = imageFolderPath + "\\" + fileNames[iFile];
                Console.WriteLine("Reading the image: " + iFileName);

                Mat image = new Mat(iFileName);
                if (image.Empty())
                {
                    MessageBox.Show("Warning: The image is empty.File name: " + iFileName);

                    continue;
                }

                Mat[] mats = new Mat[] { image };
                Console.WriteLine("Image size (height, width)： " + image.Height + " " + image.Width);

                PredictionResult res = sdk.PredictModel(modelName, mats);

                if (res.status != 0)
                {
                    MessageBox.Show("ERROR: Fail to predict. Status code: " + res.status);
                    continue;
                }

                DetectionResult[][] outResults  = res.outResults;

                for (int i = 0; i < outResults.Length; ++i)
                {
                    if (outResults[i] == null)
                    {
                        MessageBox.Show("Waring: this image has no prediction results!");
                        continue;
                    }

                    Console.WriteLine();
                    for (int j = 0; j < outResults[i].Length; ++j)
                    {
                        labelindex.Text = outResults[i][j].label_index.ToString();
                        label.Text = outResults[i][j].label_index.ToString();
                        socre.Text = outResults[i][j].score.ToString();
                        x0.Text = outResults[i][j].box.x0.ToString();
                        y0.Text = outResults[i][j].box.y0.ToString();
                        x1.Text = outResults[i][j].box.x1.ToString();
                        y1.Text = outResults[i][j].box.y1.ToString();

                        Console.WriteLine("label:                              " + outResults[i][j].label);
                        Console.WriteLine("label_index:                        " + outResults[i][j].label_index);
                        Console.WriteLine("confidential score:                 " + outResults[i][j].score);
                        Console.WriteLine("position of result(x0,y0,x1,y1):    " + "(" + outResults[i][j].box.x0 + ", " + outResults[i][j].box.y0 + ", " + outResults[i][j].box.x1 + ", " + outResults[i][j].box.y1 + ")");
                        Console.WriteLine("row_index:                          " + outResults[i][j].row_index);
                        Console.WriteLine("col_index:                          " + outResults[i][j].col_index);
                        Console.WriteLine("mask_width:                         " + outResults[i][j].mask_width);
                        Console.WriteLine("mask_height:                        " + outResults[i][j].mask_height);
                        Console.WriteLine("mat_mask_width:                     " + outResults[i][j].mat_mask_width);
                        Console.WriteLine("mat_mask_height:                    " + outResults[i][j].mat_mask_height);
                        Console.WriteLine();
                        Console.WriteLine();
                        
                    }

                    demo.DisplayResults(ref image, outResults[i]);
                }
                Console.WriteLine();
                Console.WriteLine();
            }

            sdk.DestroyModel(modelName);
        }

        private void makePrediction(object sender, EventArgs e)
        {

            Console.WriteLine(deviceName);
            Console.WriteLine(imageFolderPath);
            Console.WriteLine(modelPath);
            Console.WriteLine(modelName);

            if (!Directory.Exists(modelPath))
            {
                MessageBox.Show("输入的模型路径有误，请检查后重新输入");
                return;
            }
            else
            {
                if (!Directory.Exists(imageFolderPath))
                {
                    MessageBox.Show("输入的图片路径有误，请检查后重新输入");
                    return;

                }
                else
                {
                    if ("cpu" == deviceName || deviceName == "cuda")
                    {
                    }
                    else
                    {
                        MessageBox.Show("设备类型只能是cup 或 cuda，请检查后重新输入");
                        return;
                    }
                }
            }

            sdkMain();

        }

        private void onDeviceName(object sender, EventArgs e)
        {
            int index = setDeviceName.SelectedIndex;
           
            string str = (string)setDeviceName.SelectedItem;
            deviceName = str;
            //Console.WriteLine(deviceName);
        }

        private void browseModelPath(object sender, EventArgs e)
        {
            FolderBrowserDialog dilog = new FolderBrowserDialog();
            dilog.Description = "请选择文件夹";
            if (dilog.ShowDialog() == DialogResult.OK || dilog.ShowDialog() == DialogResult.Yes)
            {
                setModePath.Text = dilog.SelectedPath;
                string outStr = setModePath.Text.Replace("\\", "\\\\");
                modelPath = outStr;
            }
        }

        private void browsePicPath(object sender, EventArgs e)
        {
            FolderBrowserDialog dilog = new FolderBrowserDialog();
            dilog.Description = "请选择文件夹";
            if (dilog.ShowDialog() == DialogResult.OK || dilog.ShowDialog() == DialogResult.Yes)
            {
                setPicPath.Text = dilog.SelectedPath;
                string outStr = setPicPath.Text.Replace("\\", "\\\\");
                imageFolderPath = outStr;
            }
        }

        private void closing(object sender, FormClosingEventArgs e)
        {
            System.Environment.Exit(0);
        }
    }
}
