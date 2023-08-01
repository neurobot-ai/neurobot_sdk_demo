# loadMultiModelsInMultiThread



- This example shows how to load multiple models to predict in multi-thread. This means that instead of waiting for each model to finish loading before moving onto the next one, the program can load several models at once, significantly speeding up the process.
- Each thread loads its own model used by this thread. Inter-threads are model-isolated, and predictions are made within a single thread using the model bound to this thread.
- Note that there are two different types of models, and you should use different model_name for different models.



###  Appendix

#### 1：Load Error Code Definitions:

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


#### 2：Predict Error Code Definitions:
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