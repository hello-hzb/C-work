//#include<iostream>
//using namespace std;
//#include <vector>
//
//float input_image[28][28][3];
//
////https://blog.csdn.net/tostq/article/details/51786315
//void test(int h, int w, int c)
//{
//	vector<vector<vector<float>>>inputs;
//	float*** input_image;
//
//
//}
//
//
//void conv(float*** inputs, float*** conv_core, float* bias, int step);
//float activate(float input);
//void max_pool(float*** inputs, int step);
//void ave_pool(float*** inputs, int step);
//void fc(float***, float** weight, float* bias);
//
///*******************************************************************************
//float a = (float*)malloc(sizeof(float));
//*a = 0.1;
////a代表存储0.1的地址
////*a代表0.1；
////&a代表指针变量
//总结：&a位置存储的是指针变量的float* a的地址， a存储的是0.1的地址， *a是将a存储的地址所指向的value返回（也就是0.1）
//
//
//********************************************************************************/
////int main()
////{
////	//float* a = (float*)malloc(sizeof(float));
////	float* a = nullptr;
////	a = (float*)malloc(sizeof(float)*3);
////	a[0] = 0.1;
////	a[2] = 0.8;
////	a[1] = 0.3;
////	std::cout <<a << std::endl;
////	std::cout << *a << std::endl;
////	std::cout << &a << std::endl;
////	std::cin >> *a;
////
////}

#include <stdlib.h>
#include<stdio.h>


// 卷积层
typedef struct convolutional_layer{
	int inputWidth;   //输入图像的宽
	int inputHeight;  //输入图像的长
	int mapSize;      //特征模板的大小，模板一般都是正方形

	int inChannels;   //输入图像的数目
	int outChannels;  //输出图像的数目

	// 关于特征模板的权重分布，这里是一个四维数组
	// 其大小为inChannels*outChannels*mapSize*mapSize大小
	// 这里用四维数组，主要是为了表现全连接的形式，实际上卷积层并没有用到全连接的形式
	// 这里的例子是DeapLearningToolboox里的CNN例子，其用到就是全连接
	float**** mapData;     //存放特征模块的数据
	float**** dmapData;    //存放特征模块的数据的局部梯度

	float* basicData;   //偏置，偏置的大小，为outChannels
	bool isFullConnect; //是否为全连接
	bool* connectModel; //连接模式（默认为全连接）

	// 下面三者的大小同输出的维度相同
	float*** v; // 进入激活函数的输入值
	float*** y; // 激活函数后神经元的输出

	// 输出像素的局部梯度
	float*** d; // 网络的局部梯度,δ值  
}CovLayer;


// 采样层 pooling
typedef struct pooling_layer{
	int inputWidth;   //输入图像的宽
	int inputHeight;  //输入图像的长
	int mapSize;      //特征模板的大小

	int inChannels;   //输入图像的数目
	int outChannels;  //输出图像的数目

	int poolType;     //Pooling的方法
	float* basicData;   //偏置

	float*** y; // 采样函数后神经元的输出,无激活函数
	float*** d; // 网络的局部梯度,δ值
}PoolLayer;

// 输出层 全连接的神经网络
typedef struct nn_layer{
	int inputNum;   //输入数据的数目
	int outputNum;  //输出数据的数目

	float** wData; // 权重数据，为一个inputNum*outputNum大小
	float* basicData;   //偏置，大小为outputNum大小

	// 下面三者的大小同输出的维度相同
	float* v; // 进入激活函数的输入值
	float* y; // 激活函数后神经元的输出
	float* d; // 网络的局部梯度,δ值

	bool isFullConnect; //是否为全连接
}OutLayer;



typedef struct cnn_network{
	int layerNum;
	CovLayer* C1;
	PoolLayer* S2;
	CovLayer* C3;
	PoolLayer* S4;
	OutLayer* O5;

	float* e; // 训练误差
	float* L; // 瞬时误差能量
}CNN;


typedef struct train_opts{
	int numepochs; // 训练的迭代次数
	float alpha; // 学习速率
}CNNOpts;