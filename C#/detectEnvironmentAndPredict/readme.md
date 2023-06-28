 # 1：How to Use it ?

 - Put two files **detectEnvironmetnAndPreedict.exe and checkEnv.bat** in the folder of bin in SDK.
 - Run this exe in your command line, and there is an example
``` bash
detectEnvironmetnAndPreedict.exe -m C:\\NeuroBot\\ModelPath -f C:\\NeuroBot\\FilePath -n ModelName
```
- After -m, it's the model path in your computer.
- After -f, it's the pictures's dictionary.
- after -n. it's a name for the model, and you can name it by yourself.


# 2：What does it do?
- It can detect whether your computer is capable to use our model, including the following information. And the first three are necessary, and others are recommended.
  - Configuration file And model file exist.
  - The system is a Windows 64 bit version.
  - NVIDIA graphics card and driver are installed.
  - Turn off firewall And antivirus software.
  - CPU is with Intel main frequency 2.5GHZ 6-core and above versions.
  - System memory is greater than 8GB.
- You can easily use our executable file to predict. Use the command line parameters to accept the input of model file and test picture directory. The parameters support default values. In the absence of parameters, use the default model file name and test picture directory name. 
- It can load a model that predicts pictures of a directory, a pop-up window that displays the tested picture and an overlay that shows the result box, while logging the specific value on the console.
