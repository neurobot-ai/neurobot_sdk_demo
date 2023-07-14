using NeuroDetection;
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


        // Draw a mask on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       draw a mask on the image
        // Output: None
        static void DrawMask(ref Mat image, in DetectionResult result)
        {
            Mat mask = result.mask;
            int x0 = Math.Max(Convert.ToInt32(Math.Floor(result.box.x0)) - 1, 0);
            int y0 = Math.Max(Convert.ToInt32(Math.Floor(result.box.y0)) - 1, 0);
            Rect roi = new Rect(x0, y0, result.mat_mask_width, result.mat_mask_height);

            // draw the mask on image
            Mat[] channels = new Mat[3];
            Cv2.Split(image, out channels);
            Cv2.BitwiseOr(mask, channels[0][roi], channels[0][roi]);
            Cv2.Merge(channels, image);
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
            // white. TODO: change it if you want
            Scalar color = new Scalar(0, 255, 0);
            // thickness of your box line. TODO: change it if you want
            int thickness = 2;
            Cv2.Rectangle(image, p1, p2, color, thickness);
        }


        // Draw detection information on the <image>.
        // Inputs: image:		the test image
        //		   res:         a single detection result
        // Modify: image:       draw detection information (labels, label indices, and confidence scores) on the image.
        // Output: None
        static void DrawInfo(ref Mat image, in DetectionResult result)
        {
            string tagLabel = "Label: " + result.label;
            string tagLabelIndex = "Label index: " + result.label_index;
            string tagScore = "Score: " + result.score;

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
            Point up = new Point(result.box.x0, result.box.y0);
            // the position where to print tagLabelIndex. TODO: change it if you want
            Point center = new Point(result.box.x0, (result.box.y0 + result.box.y1) / 2);
            // the position where to print tagScore. TODO: change it if you want
            Point bottom = new Point(result.box.x0, result.box.y1);
            Cv2.PutText(image, tagLabel, up, font, fontScale, color, thickness);
            Cv2.PutText(image, tagLabelIndex, center, font, fontScale, color, thickness);
            Cv2.PutText(image, tagScore, bottom, font, fontScale, color, thickness);
        }


        // Display test images in a pop-up window
        // Inputs: image:		the test image
        //		   res:         all detection results on <image> 
        // Modify: Display <image> and all detection results (masks)
        // Output: None
        static void DisplayResults(ref Mat image, in DetectionResult[] results, in string window_name = "Prediction result")
        {
            Cv2.NamedWindow(window_name, WindowMode.FreeRatio);
            // TODO: you can change the size of the display window
            // Cv2.ResizeWindow("Image", 800, 1200);

            for (int i = 0; i < results.Length; ++i) {
                DrawMask(ref image, in results[i]);
                // print labels, label indices, and confidence scores on the image
                // TODO: you can comment it to not print info on test images
                DrawInfo(ref image, in results[i]);
            }

            Cv2.ImShow(window_name, image);
            Cv2.WaitKey(0);
            Cv2.DestroyWindow(window_name);
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
                Console.WriteLine("label:                              " + results[i].label);
                Console.WriteLine("label_index:                        " + results[i].label_index);
                Console.WriteLine("confidential score:                 " + results[i].score);
                Console.WriteLine("position of result(x0,y0,x1,y1):    " + "(" + results[i].box.x0 + ", " + results[i].box.y0
                                                                         + ", " + results[i].box.x1 + ", " + results[i].box.y1 + ")");
                Console.WriteLine("row_index:                          " + results[i].row_index);
                Console.WriteLine("col_index:                          " + results[i].col_index);
                Console.WriteLine("mask_width:                         " + results[i].mask_width);
                Console.WriteLine("mask_height:                        " + results[i].mask_height);
                Console.WriteLine("mat_mask_width:                     " + results[i].mat_mask_width);
                Console.WriteLine("mat_mask_height:                    " + results[i].mat_mask_height);
                Console.WriteLine("mask area (#pixels):                " + Cv2.CountNonZero(results[i].mask));
                Console.WriteLine();
                Console.WriteLine();
            }
        }


        // filter out masks which doesn't meet certain requirements
        // Inputs: results:              detection results of a single test image
        //         topK:                 specify how many largest masks need to be kept
        //         maskAreaLowerbound    ignore masks whose area < maskAreaLowerbound
        //         maskAreaUpperbound    ignore masks whose area > maskAreaUpperbound
        // Modify: None
        // Output: an array of (filtered) detection results
        static DetectionResult[] filterMask(in DetectionResult[] results, int topK, int maskAreaLowerbound, int maskAreaUpperbound) {
            SortedDictionary<int, int> decreasingDict = new SortedDictionary<int, int>();
            for (int i = 0; i < results.Length; ++i)
            {
                // it should be a segmentation task
                Debug.Assert(!results[i].mask.Empty());

                // calculate mask area and filter out ones which don't meet requirements
                int whitePixelCount = Cv2.CountNonZero(results[i].mask);
                if (maskAreaLowerbound <= whitePixelCount && whitePixelCount <= maskAreaUpperbound)
                {
                    decreasingDict.Add(-whitePixelCount, i); // default is increasing, therefore add into negative number
                }
            }

            // maintain largest k masks
            int size = decreasingDict.Count;
            if (topK > 0)
            {
                size = Math.Min(size, topK);
            }

            // output
            List<KeyValuePair<int, int>> decreasingList = decreasingDict.ToList();
            DetectionResult[] filteredResults = new DetectionResult[size];
            for (int i = 0; i < size; ++i) {
                filteredResults[i] = results[decreasingList[i].Value];
            }

            return filteredResults;
        }


        // This demo shows, in a segementation task, how to filter out masks which doesn't meet certain requirements.
        // For example, we only want to keep k largest masks in an image or keep masks whose area (#pixels) is larger than a threshold
        static void Main(string[] args)
        {
            // TODO: change to your test image folder path
            string imageFolderPath = "D:\\Intern\\test_image\\seg_test_image";
            // TODO: change to your model folder path
            string modelPath = "D:\\Intern\\model\\seg_gpu";
            // TODO: change to your model name
            string modelName = "test";
            // TODO: change to your device name
            string deviceName = "cuda";
            // TODO: change to your device index (Nonnegative int)
            int deviceIndex = 0;
            // TODO: change to your detection threshold. Range: [0, 1] or -1 (default, which is 0.7)
            float detectThres = -1;

            // Filter out masks which don't meet requirements
            // TODO: change to your top_k (if k<=0, ignore; if k>0, keep k largest masks)
            int topK = 2;
            // TODO: change to your mask_area_lowerbound (-1 means unbounded)
            int maskAreaLowerbound = 100000;
            // TODO: change to your mask_area_upperbound 
            int maskAreaUpperbound = 500000;

            Console.WriteLine("\n");
            Console.WriteLine("Test image folder path: " + imageFolderPath);
            Console.WriteLine("Model path: " + modelPath);
            Console.WriteLine("Model name: " + modelName);
            Console.WriteLine("Device name: " + deviceName);
            Console.WriteLine("Device index: " + deviceIndex);
            Console.WriteLine("Detection threshold: " + detectThres);
            Console.WriteLine("Top k choice: k = " + topK);
            Console.WriteLine("Mask area lowerbound: " + maskAreaLowerbound);
            Console.WriteLine("Mask area upperbound: " + maskAreaUpperbound);
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

            // check maskAreaLowerbound and maskAreaUpperbound
            if (!((0 <= maskAreaLowerbound) && (maskAreaLowerbound <= maskAreaUpperbound)))
            {
                Console.WriteLine("Error: It should be 0 <= mask_area_lowerbound <= mask_area_upperbound");
                Console.ReadKey();
                return;
            }

            // load model
            int status = sdk.LoadModel(modelName, modelPath, deviceName, deviceIndex);
            if (status != 0)
            {
                Console.WriteLine("ERROR: Fail to load the model. Status code: " + status);
                Console.ReadKey();
                return;
            }

            int batchSize = sdk.GetBatch(modelName);
            Console.WriteLine("Batch size: " + batchSize);

            for (int iFile = 0; iFile < numFiles;)
            {
                Mat[] images = new Mat[batchSize];
                List<string>  batchNames = new List<string>();

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
                    Console.WriteLine("Image size (height, width)： " + image.Height + " " + image.Width);

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

                    DetectionResult[] filteredResults = filterMask(in outResults[i], topK, maskAreaLowerbound, maskAreaUpperbound);
                    PrintInfo(filteredResults);
                    DisplayResults(ref images[i], in filteredResults);
                }
            }

            // destroy model
            sdk.DestroyModel(modelName);
            Console.ReadKey();
            return;
        }
    }
}
