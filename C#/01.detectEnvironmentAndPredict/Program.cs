using System;
using System.Collections.Generic;
using OpenCvSharp;
using System.IO;
using NeuroDetection;
using Newtonsoft.Json.Linq;
using System.Linq;

namespace NeuroDetection
{
    class Program
    {
        // Return all image file names in the path <dirPath>.
        // Inputs: dirPath:		the path of folder containing all test images
        //		   extension:   whether the image name has an extension or not
        // Modify: None
        // Output: A list of strings (image file names)
        static List<string> GetFilesName(string dirPath, bool extension = true)
        {
            List<string> fileNames = new List<string>();
            try
            {
                string[] files = Directory.GetFiles(dirPath);

                foreach (string file in files)
                {
                    string fileName = Path.GetFileName(file);

                    if (extension)
                    {
                        fileNames.Add(fileName);
                    }
                    else
                    {
                        string fileNameWithoutExtension = Path.GetFileNameWithoutExtension(file);
                        fileNames.Add(fileNameWithoutExtension);
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("An error occurred while reading the directory: " + ex.Message);
                return new List<string>();
            }

            return fileNames;
        }


        // Draw a mask on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       add a mask into image.
        // Output: None
        static void DrawMask(ref Mat image,   DetectionResult res)
        {
            // create a mask
            Mat mask = res.mask;
            int x0 = Math.Max(Convert.ToInt32(Math.Floor(res.box.x0)) - 1, 0);
            int y0 = Math.Max(Convert.ToInt32(Math.Floor(res.box.y0)) - 1, 0);
            Rect roi = new Rect(x0, y0, res.mat_mask_width, res.mat_mask_height);

            // draw the mask on image
            Mat[] channels = new Mat[3];
            Cv2.Split(image, out channels);
            Cv2.BitwiseOr(mask, channels[0][roi], channels[0][roi]);
            Cv2.Merge(channels, image);
        }


        // Draw a box on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       add a box into image.
        // Output: None
        static void DrawBox(ref Mat image,   DetectionResult res)
        {
            Point p1 = new Point(res.box.x0, res.box.y0);
            Point p2 = new Point(res.box.x1, res.box.y1);
            // white. TODO: change it if you want
            Scalar color = new Scalar(0, 255, 0);
            Cv2.Rectangle(image, p1, p2, color, 2);
        }


        // Print information on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       add information (labels, label indices, and confidence scores) into image.
        // Output: None
        static void PrintInfo(ref Mat image,   DetectionResult res)
        {
            string tagLabel = "Label: " + res.label;
            string tagLabelIndex = "Label index: " + res.label_index;
            string tagScore = "Score: " + res.score;

            // TODO: change following values if you need to display texts clearly on your test images.
            // size of characters. TODO: change it if you want
            double fontScale = 3;
            // thickness of characters. TODO: change it if you want
            int thickness = 4;
            // white. TODO: change it if you want
            Scalar color = new Scalar(255, 255, 255);
            // font. TODO: change it if you want
            HersheyFonts font = HersheyFonts.HersheyPlain;
            // the position where to print tagLabel. TODO: change it if you want
            Point up = new Point(res.box.x0, res.box.y0);
            // the position where to print tagLabelIndex. TODO: change it if you want
            Point center = new Point(res.box.x0, (res.box.y0 + res.box.y1) / 2);
            // the position where to print tagScore. TODO: change it if you want
            Point bottom = new Point(res.box.x0, res.box.y1);
            Cv2.PutText(image, tagLabel, up, font, fontScale, color, thickness);
            Cv2.PutText(image, tagLabelIndex, center, font, fontScale, color, thickness);
            Cv2.PutText(image, tagScore, bottom, font, fontScale, color, thickness);
        }


        // Display test images (with)
        // Inputs: image:		the test image
        //		   res:         all detection results on <image> 
        // Modify: Display <image> and all detection results (masks)
        // Output: None
        static void DisplayResults(ref Mat image,   DetectionResult[] res)
        {
            Cv2.NamedWindow("Image", WindowMode.FreeRatio);
            // TODO: you can change the size of the display window
            // Cv2.ResizeWindow("Image", 800, 1200);

            for (int i = 0; i < res.Length; ++i)
            {
                // OCR or Detection
                if (res[i].mask == null)
                {
                    DrawBox(ref image,   res[i]);
                }
                // Segmentation
                else
                {
                    DrawMask(ref image,   res[i]);
                }

                // print labels, label indices, and confidence scores on the image
                // TODO: you can comment it to not print info on test images
                PrintInfo(ref image,   res[i]);
            }

            Cv2.ImShow("Image", image);
            Cv2.WaitKey(0);
            Cv2.DestroyWindow("Image");
        }

        static void CheckEnvironment()
        {
            // 使用Process类来执行checkEnv.bat脚本
            System.Diagnostics.Process process = new System.Diagnostics.Process();
            process.StartInfo.FileName = "./checkEnv.bat";
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.RedirectStandardOutput = true;
            process.Start();
            process.WaitForExit();

            // 输出脚本执行结果
            string output = process.StandardOutput.ReadToEnd();
            Console.WriteLine(output);

            if (process.ExitCode != 0)
            {
                Environment.Exit(-1);
            }
        }

        static int ReadDataFromJson()
        {
            string jsonString = System.IO.File.ReadAllText("checked.json");
            JObject root = JObject.Parse(jsonString);

            int requiredNum = root["required"].Count();
            int recommendNum = root["recommend"].Count();

            for (int i = 0; i < requiredNum; i++)
            {
                int status = root["required"][i]["status"].Value<int>();
                if (status == 0)
                {
                    Console.Error.WriteLine(root["required"][i]["info"]);
                    return -1;
                }
            }

            for (int i = 0; i < recommendNum; i++)
            {
                int status = root["recommend"][i]["status"].Value<int>();
                if (status == 0)
                {
                    Console.WriteLine(root["recommend"][i]["info"]);
                }
            }

            return 1;
        }

        static void Main(string[] args)
        {
            CheckEnvironment();
            int result = ReadDataFromJson();
            if (result < 0)
            {
                Environment.Exit(-1);
            }
            SDK sdk = new SDK();
            // TODO: change to your test image folder path!
            string imageFolderPath = "TODO: change to your test image folder path!";
            Console.WriteLine("Image folder path: " + imageFolderPath);

            List<string> fileNames = GetFilesName(imageFolderPath, extension: true);
            int numFiles = fileNames.Count;
            if (numFiles == 0)
            {
                Console.WriteLine("Error: This image folder is empty!");
                return;
            }

            Console.WriteLine("The total number of test images: " + numFiles);
            // TODO: change to your model folder path!
            string modelPath = "TODO: change to your model folder path!";
            // TODO: change to your model name!
            string modelName = "TODO: change to your model name!";
            // TODO: change to your device name!
            string deviceName = "TODO: change to your device name!";
            Console.WriteLine("Model path: " + modelPath);
            Console.WriteLine("Model name: " + modelName);
            Console.WriteLine("Device name: " + deviceName);

            int status = sdk.LoadModel(modelName, modelPath, deviceName);
            if (status != 0)
            {
                Console.WriteLine("ERROR: Fail to load the model. Status code: " + status);
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
                    Console.WriteLine("Warning: The image is empty. File name: " + iFileName);
                    continue;
                }

                Mat[] mats = new Mat[] { image };
                Console.WriteLine("Image size (height, width)： " + image.Height + " " + image.Width);

                PredictionResult res = sdk.PredictModel(modelName, mats);

                if (res.status != 0)
                {
                    Console.WriteLine("ERROR: Fail to predict. Status code: " + res.status);
                    continue;
                }

                DetectionResult[][] outResults = res.outResults;

                for (int i = 0; i < outResults.Length; ++i)
                {
                    if (outResults[i] == null)
                    {
                        Console.WriteLine("Waring: this image has no prediction results!");
                        continue;
                    }

                    Console.WriteLine();
                    for (int j = 0; j < outResults[i].Length; ++j)
                    {
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

                    DisplayResults(ref image,   outResults[i]);
                }
                Console.WriteLine();
                Console.WriteLine();
            }
        }
    }
}
