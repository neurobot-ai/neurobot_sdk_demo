# Neurobot SDK

&nbsp;&nbsp;&nbsp;&nbsp;Here are some examples that may be of interest to you for using our SDK with ease and at a low cost. To ensure these examples run smoothly, please follow the guidelines to set up your computer environment. Click [here][SDK] to configure your computer environment.<br>

&nbsp;&nbsp;&nbsp;&nbsp;Here is a list of common examples.

[SDK]: https://neurobot.readthedocs.io/en/latest/Deployment/HowToUseSDK/


### 1： Directly use an executable file to predict
- This example is in dictionary **C++ / detectEnvironmentAndPredict**（C++ version）, or in dictionary **C# / detectEnvironmentAndPredict**（C# version）
- This example supports environment detection and outputs an executable file. With environment detection, It can detect whether your computer is capable to use our model, including the following information. And the first three are necessary, and others are recommended.
  - Configuration file And model file exist.
  - The system is a Windows 64 bit version.
  - NVIDIA graphics card and driver are installed.
  - Turn off firewall And antivirus software.
  - CPU is with Intel main frequency 2.5GHZ 6-core and above versions.
  - System memory is greater than 8GB.
- You can easily use our executable file to predict. Use the command line parameters to accept the input of model file and test picture directory. The parameters support default values. In the absence of parameters, use the default model file name and test picture directory name. 
- It can load a model that predicts pictures of a directory, a pop-up window that displays the tested picture and an overlay that shows the result box, while logging the specific value on the console.


### 2：Check OK or NG
- This example is in dictionary **C++ / checkOKORNG**（C++ version）, or in dictionary **C# / checkOKORNG**（C# version）
- This example involves two different colors red and green to display the label and output the label specific coordinate values on the console.
- Execute a test that involves only two labels. It works well if the result label is OK, Otherwise there is something wrong, it is NG.


### 3：Load multiple models in single-thread
- This example is in dictionary **C++ / loadMultiModelsInSingleThread**（C++ version）, or in dictionary **C# / loadMultiModelsInSingleThread**（C# version）
- This example shows how to load multiple models to predict in single-thread. Exactly, it will load these models one by one, and call the predict interface of each model in turn, which means it will output the result serially.
loadMultiModelsInMultiThread.cpp	


### 4：Load multiple models in multi-thread
- This example is in dictionary **C++ / loadMultiModelInMultiThread**（C++ version）, or in dictionary **C# / loadMultiModelInMultiThread**（C# version）
- This example shows how to load multiple models to predict in multi-thread. This means that instead of waiting for each model to finish loading before moving onto the next one, the program can load several models at once, significantly speeding up the process.
- Each thread loads its own model used by this thread. Inter-threads are model-isolated, and predictions are made within a single thread using the model bound to this thread.


### 5：Load one model to predict in multi-thread
- This example is in dictionary **C++ / LoadOneModelInSingleThread**（C++ version）, or in dictionary **C# / LoadOneModelInSingleThread**（C# version）
- This example shows how to predict in multi-thread, and we use mutex to ensure mutual exclusion.


### 6：Crop large images into small images and then make predictions

- In some scenarios with large images and small targets, it is recommended to perform image slicing first and then training.
- This example shows how to slice and dice an image, and finally output the result.


### 7：Object detection and OCR in one
- In some scenarios, the object localization model will be used first to identify and crop the ROI area, and then do further identification for the ROI area by using OCR.
- This example uses a different SDK (specially dedicated to solving this type of problem) to do object detection first, and use OCR to do further identification.
  

### 8：Cluster characters in OCR
- The raw result of OCR character recognition are single characters. 
- This example shows how to cluster characters, and output them as complete lines of words.


### 9：Object localization with rotation
- If the angle of an image needs to be recognized, the image must be rotated before doing object localization.
- This example demonstrates how to perform object localization while taking rotation into account.


### 10：Filter output based on the result of Pixel Segmentation
- Pixel segmentation is a model commonly used for detecting defects, and it requires calculations and screening of the identified problem areas. 
- The example shows how to process the raw detection data, preform area calculation, filter the output.


### 11：Use our SDK with GUI
- This example shows how to do package our SDK to implement a software with GUI in WIN10/11.
