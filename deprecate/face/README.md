Face���˵��
============

##Face

�����࣬���ڱ���һ���˵����������а������˵�id�����֣��Լ�һϵ����ͼƬ��

###ʹ�÷���

####��Ҫ����˵��

* setId������id
* setName����������
* addImage�����һ��ͼƬ
* clearImages���������ͼƬ
* updata,����id������
* getName����ȡ����

##FaceStorage

���ڱ���������Ϣ��һϵ��Face�������ʽ��`FaceStorage_Test`�ļ��������test.xml���ӡ�

�����������Face�ࡢTinyXML��⣬������Ŀû�б���TinyXML�����ֻҪ��ʹ��FaceStorage�ĵط���Ҫ����TinyXML��cpp�ļ���

###ʹ�÷���

####��Ҫ����˵��

* size��������������
* load������FaceStorage���ɵ�xml�ļ�
* save������������Ϣ��xml�ļ���
* getFaceById������id��ȡ������û��ʵ�֣�
* getFaceByName������������ȡ������û��ʵ�֣�
* getAllFaces����ȡ��������
* getNameById������id��ȡ����
* operator<<������һ������
* operator>>��getAllFaces

##FrAdapter

###˵��

����һ���������ӿڡ������Ҫ�Լ�ʵ��FaceRecognizer��Ҫ��������ࡣ�����㿴����CvFrAdapter�����̳���FrAdapter��ʵ���ˣ�

* void init()
* bool train()
* int predict(cv::Mat)
* string getNameById(int)������predict�õ���id��ȡ���֡�

��Щ������

##CvFrAdapter

ʹ��opencv��ʵ������ʶ��

����ʵ��FrAdapter�ķ����⣬���У�

* setFaceStorage������FaceStorage������������
* loadTrainedFile��ֱ�Ӽ���opencvѵ���õĲ�����ʶ��������ֻ�����ñ���!TODO��
* save������opencvѵ���Ĳ������Ա��´�ֱ�Ӽ���
* load������opencv��ѵ��������


##FaceRecog

����ʹ�õ�����ʶ���֧࣬���Զ���ʶ�𷽷���
�Լ���ʵ���κι��ܣ����ǵ��ü�����FrAdapter�ĺ�����ʵ�֡�

###��Ҫ����

* setFrClass����������ʶ���࣬�ڲ�ʹ������ʵ�֡�
* train��ѵ��
* predict��Ԥ��
* getNameById������id��ȡ������


##��������

tkorays <tkorays@hotmail.com>
