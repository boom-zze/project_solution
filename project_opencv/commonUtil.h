#pragma once
// «Å§i¨ç¦¡
#include<opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

struct ImageInfo 
{
	Mat image;
	string windowName;
};

class commonUtil 
{
public:
	static bool read_image (const string filePath, Mat& buffer, int & channels);
	static void getGrayValue(int event, int x, int y, int flags, void* userdata);
	static void decompose(const Mat& src, Mat& img_r, Mat& img_g, Mat& img_b);
	static void compose(const Mat& img_r, const Mat& img_g, const Mat& img_b, Mat& img_out);
	static void intensity(const Mat& mask, const Mat& img_src, cv::Scalar& mean, cv::Scalar& deviation);
};

class commonMath
{
public:
	static int FibonacciRecursive(int number);
	static int FibonacciIterative(int number);
	static double calculate_factorial(int n);
	static double calculate_TalyorSeries(int n, double x);
};


