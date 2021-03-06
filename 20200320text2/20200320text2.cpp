#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


int main() {
	cv::Mat srcMat = imread("E:\\Git\\coin.png", 0);
	//读取图片
	if (srcMat.empty()) {
		return -1;
	}//读取失败
	cv::Mat binaryMat;
	threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);
	cv::imshow("二值化", binaryMat);//显示二值化图像
	//二值化
	//创建结构元素
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	//闭运算
	morphologyEx(binaryMat, binaryMat, MORPH_CLOSE, kernel);
	cv::Mat labelMat;
	cv::Mat statsMat;
	cv::Mat centreMat;
	cv::Mat resultMat;
	int nccomps = cv::connectedComponentsWithStats(
		binaryMat,
		labelMat,
		statsMat,
		centreMat,
		8,
		CV_32S
		);

	for (int i = 1; i < nccomps; i++) {
		cout << "connected Copmonents NO. " << i << endl;
		cout << "pixels = " << statsMat.at<int>(i, 4) << endl;
		cout << "width = " << statsMat.at<int>(i, 2) << endl;
		cout << "height = " << statsMat.at<int>(i, 3) << endl;
		cout << endl;
	}
	cout << "the number of connected Components = " << nccomps - 1 << endl;
	//画bounding box
	for (int i = 1; i < nccomps; i++) {
		Rect bndbox;
		bndbox.x = statsMat.at<int>(i, 0);
		bndbox.y = statsMat.at<int>(i, 1);
		bndbox.width = statsMat.at<int>(i, 2);
		bndbox.height = statsMat.at<int>(i, 3);
		//绘制
		rectangle(binaryMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	imshow("results", binaryMat);
	waitKey(0);
}