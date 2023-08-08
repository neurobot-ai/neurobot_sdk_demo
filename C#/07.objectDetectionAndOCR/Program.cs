﻿using NeuroDetection;
using OpenCvSharp;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Net;
using static System.Net.WebRequestMethods;
using static System.Net.Mime.MediaTypeNames;

namespace NeuroDetection
{
    class ClusterCharacters
    {
        public ClusterCharacters() { }

        // return clustered characters as words, line by line
        public List<List<string>> FindWords(ref DetectionResult[] results)
        {
            List<List<string>> texts = new List<List<string>>();
            if (results.Length == 0)
            {
                return texts;
            }

            Array.Sort(results, lessCompY); // find lines from top to bottom
            HashSet<int> groupID = new HashSet<int>(); // record characters' id which have already been clustered

            int i = 0;
            while (i < results.Length)
            {
                int lastID = -1;
                for (int j = i + 1; j < results.Length; ++j)
                {
                    if (IsOnSameLine(results[i].box, results[j].box))
                    {
                        if (!groupID.Contains(i))
                        {
                            groupID.Add(i);
                            lastID = i;
                        }
                        if (!groupID.Contains(j))
                        {
                            groupID.Add(j);
                            lastID = j;
                        }
                    }
                }

                // if no character is on the same line with ith character, then itself forms a line
                if (groupID.Count() == 0)
                {
                    groupID.Add(i);
                    lastID = i;
                }

                DetectionResult[] group = new DetectionResult[groupID.Count()];
                int k = 0;
                foreach (int id in groupID) 
                {
                    group[k++] = results[id];
                }
                Array.Sort(group, lessCompX); // find texts from left to right in this line

                List<string> words = new List<string>();
                string word = "";
                for (int j = 0; j < group.Length; ++j)
                {
                    word += group[j].label;

                    // they are two different words
                    if (j < group.Length - 1 && IsDifferentWord(group[j].box, group[j + 1].box))
                    {
                        words.Add(word);
                        word = "";
                    }
                }
                words.Add(word);
                texts.Add(words);

                i = lastID + 1;
                groupID.Clear();
            }

            return texts;
        }

        // return true if box2 is on the same line with box1
        public bool IsOnSameLine(in Boxes box1, in Boxes box2) 
        {
            float box1CenterY = GetCenterY(box1);
            float box2CenterY = GetCenterY(box2);

            float height1 = GetMaxY(box1) - GetMinY(box1);
            
            // around +/- the character's height can be regarded as one line
            if (Math.Abs(box1CenterY - box2CenterY) < 1.0 * height1) return true;
            else return false;
        }

        // return true if box1 and box2 are two different words
        public bool IsDifferentWord(in Boxes box1, in Boxes box2)
        {
            float width1 = GetMaxX(box1) - GetMinX(box1);
            float gap = GetCenterX(box2) - GetCenterX(box1);
            // if they are at least 1 character's width far, then they are different words
            if (gap > 2 * width1) return true; 
            else return false;
        }

        public float GetCenterX(in Boxes box) 
        {
            return (box.x0 + box.x1 + box.x2 + box.x3) / 4;
        }

        public float GetCenterY(in Boxes box)
        {
            return (box.y0 + box.y1 + box.y2 + box.y3) / 4;
        }

        public float GetMinX(in Boxes box)
        {
            return Math.Min(Math.Min(box.x0, box.x1), Math.Min(box.x2, box.x3));
        }

        public float GetMinY(in Boxes box)
        {
            return Math.Min(Math.Min(box.y0, box.y1), Math.Min(box.y2, box.y3));
        }

        public float GetMaxX(in Boxes box)
        {
            return Math.Max(Math.Max(box.x0, box.x1), Math.Max(box.x2, box.x3));
        }

        public float GetMaxY(in Boxes box)
        {
            return Math.Max(Math.Max(box.y0, box.y1), Math.Max(box.y2, box.y3));
        }

        private Comparison<DetectionResult> lessCompX = (result1, result2) =>
        {
            float result1CenterX = (result1.box.x0 + result1.box.x1 + result1.box.x2 + result1.box.x3) / 4;
            float result2CenterX = (result2.box.x0 + result2.box.x1 + result2.box.x2 + result2.box.x3) / 4;
            if (result1CenterX < result2CenterX)
            {
                return -1;
            }
            else if (result1CenterX > result2CenterX)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        };

        private Comparison<DetectionResult> lessCompY = (result1, result2) =>
        {
            float result1CenterY = (result1.box.y0 + result1.box.y1 + result1.box.y2 + result1.box.y3) / 4;
            float result2CenterY = (result2.box.y0 + result2.box.y1 + result2.box.y2 + result2.box.y3) / 4;
            if (result1CenterY < result2CenterY)
            {
                return -1;
            }
            else if (result1CenterY > result2CenterY)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        };
    }
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
                Console.WriteLine("Error: Fail to read the directory: " + dirPath);
                Console.WriteLine("Error message: " + ex.Message);
                return new List<string>();
            }

            return fileNames;
        }


        // print detection information in the terminal
        // Inputs: results:      detection results of a single test image
        // Modify: None
        // Output: None
        static void PrintInfo(in DetectionResult[] results)
        {
            Console.WriteLine();
            for (int i = 0; i < results.Length; ++i)
            {
                Console.WriteLine("label:                                               " + results[i].label);
                Console.WriteLine("confidential score of the bounding box:              " + results[i].box_score);
                Console.WriteLine("confidential score of the content inside the box:    " + results[i].score);
                Console.WriteLine("Positions of the bounding box's 4 vertices:");
                Console.WriteLine("(x0, y0):                                            " + "(" + results[i].box.x0 + ", " + results[i].box.y0 + ")");
                Console.WriteLine("(x1, y1):                                            " + "(" + results[i].box.x1 + ", " + results[i].box.y1 + ")");
                Console.WriteLine("(x2, y2):                                            " + "(" + results[i].box.x2 + ", " + results[i].box.y2 + ")");
                Console.WriteLine("(x3, y3):                                            " + "(" + results[i].box.x3 + ", " + results[i].box.y3 + ")");
                Console.WriteLine();
                Console.WriteLine();
            }
        }


        // Draw a box on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       draw a box on the image
        // Output: None
        static void DrawBox(ref Mat image, in DetectionResult result)
        {
            Point p1 = new Point(result.box.x0, result.box.y0);
            Point p2 = new Point(result.box.x1, result.box.y1);
            Point p3 = new Point(result.box.x2, result.box.y2);
            Point p4 = new Point(result.box.x3, result.box.y3);
            Point[] vertices = new Point[] { p1, p2, p3, p4 };
            // green. TODO: change it if you want
            Scalar color = new Scalar(0, 255, 0);
            // thickness of your box line. TODO: change it if you want
            int thickness = 2;
            Cv2.Polylines(image, new[] { vertices }, true, color, thickness);
        }


        // Draw detection information on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       draw detection information (labels) on the image.
        // Output: None
        static void DrawInfo(ref Mat image, in DetectionResult result)
        {
            string tagLabel = result.label;

            // TODO: change following values if you need to display texts clearly on your test images.
            // size of characters. TODO: change it if you want
            double fontScale = 2;
            // thickness of characters. TODO: change it if you want
            int thickness = 2;
            // white. TODO: change it if you want
            Scalar color = new Scalar(255, 255, 255);
            // font. TODO: change it if you want
            HersheyFonts font = HersheyFonts.HersheyPlain;
            // the position where to print tagLabel. TODO: change it if you want
            Point center = new Point((result.box.x0 + result.box.x1 + result.box.x2 + result.box.x3) / 4,
                                     (result.box.y0 + result.box.y1 + result.box.y2 + result.box.y3) / 4);

            Cv2.PutText(image, tagLabel, center, font, fontScale, color, thickness);
        }


        // Display test images in a pop-up window
        // Inputs: image:		the test image
        //		   res:         all detection results on <image> 
        // Modify: Display <image> and all detection results (masks)
        // Output: None
        static void DisplayResults(ref Mat image, in DetectionResult[] results, in string windowName = "Prediction result")
        {
            Cv2.NamedWindow(windowName, WindowMode.FreeRatio);
            // TODO: you can change the size of the display window
            // Cv2.ResizeWindow("Image", 800, 1200);

            for (int i = 0; i < results.Length; ++i)
            {
                DrawBox(ref image, in results[i]);
                // print labels, label indices, and confidence scores on the image
                // TODO: you can uncomment it to print info on test images
                // DrawInfo(ref image, in results[i]);
            }

            Cv2.ImShow(windowName, image);
            Cv2.WaitKey(0);
            Cv2.DestroyAllWindows();
        }


        static void Main(string[] args)
        {
            // TODO: change to your test image folder path
            string imageFolderPath = "D:\\new_sdk\\sdk\\image";
            // TODO: change to your detection model folder path
            string detModelPath = "D:\\new_sdk\\sdk\\model\\dbnet";
            // TODO: change to your recognition model folder path
            string recModelPath = "D:\\new_sdk\\sdk\\model\\satrn_mydata3_fp16_b1";
            // TODO: change to your model name
            string modelName = "test";
            // TODO: change to your device name
            string deviceName = "cuda";
            // TODO: change to your device index (Nonnegative int)
            int deviceIndex = 0;
            // TODO: change to your detection threshold. Range: [0, 1] or -1 (default, which is 0.7)
            float detectThres = -1;

            Console.WriteLine("\n");
            Console.WriteLine("Test image folder path: " + imageFolderPath);
            Console.WriteLine("Detection model path: " + detModelPath);
            Console.WriteLine("Recognition model path: " + recModelPath);
            Console.WriteLine("Model name: " + modelName);
            Console.WriteLine("Device name: " + deviceName);
            Console.WriteLine("Device index: " + deviceIndex);
            Console.WriteLine("Detection threshold: " + detectThres);
            Console.WriteLine("\n");

            SDK sdk = new SDK();

            // check imageFolderPath
            List<string> fileNames = GetFilesName(imageFolderPath, extension: true);
            int numFiles = fileNames.Count;
            if (numFiles == 0)
            {
                Console.WriteLine("Error: This image folder is empty!");
                Console.ReadKey();
                return;
            }
            Console.WriteLine("The total number of test images: " + numFiles);

            // check deviceName
            if (!(deviceName == "cpu" || deviceName == "cuda"))
            {
                Console.WriteLine("Error: deviceName is incorrect. It's either cpu or cuda!");
                Console.ReadKey();
                return;
            }

            // check deviceIndex
            if (deviceIndex < 0)
            {
                Console.WriteLine("Error: deviceIndex should be a nonnegative integer");
                Console.ReadKey();
                return;
            }

            // check detectThres
            if (!(0 <= detectThres && detectThres <= 1) && detectThres != -1)
            {
                Console.WriteLine("Error: the range of detectThres is [0, 1] or -1");
                Console.ReadKey();
                return;
            }

            // load model
            int status = sdk.LoadModel(modelName, detModelPath, recModelPath, deviceName, deviceIndex);
            if (status != 0)
            {
                Console.WriteLine("ERROR: Fail to load the model. Status code: " + status);
                Console.ReadKey();
                return;
            }

            int batchSize = 1; // it's fixed in the current version
            Console.WriteLine("Batch size: " + batchSize);

            ClusterCharacters cc = new ClusterCharacters();
            for (int iFile = 0; iFile < numFiles;)
            {
                Mat[] images = new Mat[batchSize];
                List<string> batchNames = new List<string>();

                // read [bacth_size] images
                for (int iBatch = 0; iBatch < batchSize; ++iBatch, ++iFile)
                {
                    if (iFile >= numFiles)
                    {
                        break;
                    }

                    string fileName = imageFolderPath + "\\" + fileNames[iFile];
                    Console.WriteLine("Reading the image: " + fileName);
                    Mat image = new Mat(fileName);
                    if (image.Empty())
                    {
                        Console.WriteLine("Warning: Fail to read the image: " + fileName);
                        --iBatch;
                        continue;
                    }

                    images[iBatch] = image;
                    batchNames.Add(fileName);
                    Console.WriteLine("Image size (height, width): " + image.Height + " " + image.Width);

                    // drop images if the number of images are less than [batch_size]
                    if (batchNames.Count != batchSize)
                    {
                        Console.WriteLine("Warning: Last " + batchNames.Count + " images will be dropped because the model's batch size is " + batchSize);
                        foreach (string batchName in batchNames)
                        {
                            Console.WriteLine("Warning: image: " + batchName + " will be dropped!");
                        }
                        continue;
                    }
                }

                // the number of inputs should match the number of input names
                Debug.Assert(images.Length == batchNames.Count);

                // predict
                Stopwatch timer = new Stopwatch();
                timer.Start();
                PredictionResult res = sdk.PredictModel(modelName, images, detectThres);
                timer.Stop();
                double elapsedTime = timer.ElapsedMilliseconds;
                Console.WriteLine("Model prediction takes " + elapsedTime / 1000 + " seconds");
                if (res.status != 0)
                {
                    Console.WriteLine("ERROR: Fail to perform model prediction. Status code: " + res.status);
                    Console.ReadKey();
                    return;
                }

                // the number of results should match the number of inputs
                DetectionResult[][] outResults = res.outResults;
                Debug.Assert(images.Length == outResults.Length);

                // show prediction results
                for (int i = 0; i < outResults.Length; ++i)
                {
                    if (outResults[i] == null)
                    {
                        Console.WriteLine("Waring: This image has no prediction results!");
                        Console.WriteLine("Waring: Image name: " + batchNames[i]);
                        continue;
                    }

                    // PrintInfo(outResults[i]);

                    // sort detected characters into texts
                    timer = new Stopwatch();
                    timer.Start();
                    List<List<string>> texts = cc.FindWords(ref outResults[i]);
                    timer.Stop();
                    elapsedTime = timer.ElapsedMilliseconds;

                    Console.WriteLine("Character clustering takes " + elapsedTime / 1000 + " seconds");
                    Console.WriteLine("After character clustering, texts are:");
                    Console.WriteLine("##########################");
                    foreach (List<string> words in texts)
                    {
                        foreach (string word in words)
                        {
                            Console.Write(word + " ");
                        }
                        Console.WriteLine();
                    }
                    Console.WriteLine("##########################");

                    DisplayResults(ref images[i], in outResults[i]);
                }
            }

            // destroy model
            sdk.DestroyModel(modelName);
            Console.WriteLine("Destroyed the model. Press any key to quit the program...");
            Console.ReadKey();
            return;
        }
    }
}