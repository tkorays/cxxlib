Face类库说明
============

##Face

人脸类，用于保存一个人的人脸。其中包含该人的id，名字，以及一系列脸图片。

###使用方法

####主要函数说明

* setId，设置id
* setName，设置名字
* addImage，添加一张图片
* clearImages，清除所有图片
* updata,更新id和名字
* getName，获取名字

##FaceStorage

用于保存人脸信息，一系列Face，具体格式见`FaceStorage_Test`文件夹里面的test.xml例子。

依赖于上面的Face类、TinyXML类库，由于项目没有编译TinyXML，因此只要在使用FaceStorage的地方都要加入TinyXML的cpp文件。

###使用方法

####主要函数说明

* size，里面人脸个数
* load，加载FaceStorage生成的xml文件
* save，保存人脸信息到xml文件中
* getFaceById，根据id获取人脸（没有实现）
* getFaceByName，根据人名获取人脸（没有实现）
* getAllFaces，获取所有人脸
* getNameById，根据id获取人名
* operator<<，加入一个人脸
* operator>>，getAllFaces

##FrAdapter

###说明

这是一个适配器接口。如果你要自己实现FaceRecognizer就要集成这个类。正如你看到的CvFrAdapter，它继承自FrAdapter，实现了：

* void init()
* bool train()
* int predict(cv::Mat)
* string getNameById(int)，根据predict得到的id获取名字。

这些方法。

##CvFrAdapter

使用opencv来实现人脸识别

除了实现FrAdapter的方法外，还有：

* setFaceStorage，设置FaceStorage来加载人脸。
* loadTrainedFile，直接加载opencv训练好的参数来识别人脸，只是设置变量!TODO。
* save，保存opencv训练的参数，以便下次直接加载
* load，加载opencv的训练参数。


##FaceRecog

最终使用的人脸识别类，支持自定义识别方法。
自己不实现任何功能，都是调用集成自FrAdapter的函数来实现。

###主要函数

* setFrClass，设置人脸识别类，内部使用它来实现。
* train，训练
* predict，预测
* getNameById，根据id获取人名。


##关于作者

tkorays <tkorays@hotmail.com>
