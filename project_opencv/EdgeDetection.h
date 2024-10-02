#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class EdgeDetection
{
public:
	//sobel_amp(Image : EdgeAmplitude : FilterType, Size : )
	static bool sobel_amp(const Mat &img_src, Mat& img_out, string FilterType, int kernel_size);
	
};