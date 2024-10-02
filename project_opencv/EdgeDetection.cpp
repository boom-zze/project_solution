#include "EdgeDetection.h"
using namespace std;
using namespace cv;

// sobel_amp
bool EdgeDetection::sobel_amp(const Mat& img_src, Mat& img_out, string FilterType, int kernel_size)
{
	try
	{
		int ddepth = -1;
		if (FilterType == "x")
		{
			Sobel(img_src, img_out, ddepth, 1, 0, kernel_size);

		}
		else if (FilterType == "y")
		{
			Sobel(img_src, img_out, ddepth, 0, 1, kernel_size);
		}
		else if (FilterType == "sum_sqrt")
		{
			// 保留 xy 方向梯度
			vector<Mat> vec_img_rgb;
			split(img_src, vec_img_rgb);
			vector<Mat> vec_img_rgb_sobel(3);
			for (int i = 0; i < 3; ++i) {
				cv::Mat grad_x, grad_y;
				cv::Sobel(vec_img_rgb[i], grad_x, CV_32F, 1, 0);
				cv::Sobel(vec_img_rgb[i], grad_y, CV_32F, 0, 1);
				cv::magnitude(grad_x, grad_y, vec_img_rgb_sobel[i]);
				
				vec_img_rgb_sobel[i].convertTo(vec_img_rgb_sobel[i], CV_8U);
			}
			
			merge(vec_img_rgb_sobel, img_out);
		}
		else
		{
			return false;
		}

		return true;
	}
	catch (const exception& e)
	{
		cerr << "Exception get: " << e.what() << endl;
		return false;
	}
}