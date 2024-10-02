// project_opencv.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include "commonUtil.h"
#include "EdgeDetection.h"
//D:\opencv\build\include\opencv2
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

ImageInfo img_info;


int main()
{
    // 實例
    commonUtil comUtil;
    commonMath comMath;
    EdgeDetection EdgeDect;
    unsigned int index = 0;
    cout << "Index 1: RGB channel separation and mean value calculation" << endl;
    cout << "Please assign the index of test case: ";
    
    cin >> index;
    cout << " The selected index = " << index << endl;

    string img_path = "D:\\dog.jpg";
    Mat src;
    int channels;
    comUtil.read_image(img_path, src, channels);
    switch (index)
    {

    case 1:
    {
        //func1 : read image
        //func2 : decompose
        //func3 : compose
        //func4 : intensity
        try
        {
            
            cv::imshow("image", src);
            cout << "The image channels is: " << channels << endl;
            Mat img_r, img_g, img_b;
            comUtil.decompose(src, img_r, img_g, img_b);
           
            // 怎樣的區域的平均灰階
            cv::imshow("r channel image", img_r);
            cv::imshow("g channel image", img_g);
            cv::imshow("b channel image", img_b);
            cv::waitKey(0);
            cv::destroyAllWindows();
            
            vector<Mat> vec_img = {img_r,img_g,img_b};
            
            
            //--------------------------------------------------------------
            Mat mask;
            cv::Scalar mean;
            cv::Scalar deviation;
            comUtil.intensity(mask, src, mean, deviation);
            
            if (channels == 3)
                cout << "The color image's mean {B,G,R} is: " << mean << endl;
            else
                cout << "The color image's mean {B,G,R} is: " << mean[0] << endl;
            
   
            Mat img_out;
            comUtil.compose(img_r, img_g, img_b, img_out);

            cv::imshow("merge RGB image", img_out);
            cv::waitKey(0);
            cv::destroyAllWindows();
            //--------------------------------------------------------------
        }
        catch (const exception& e)
        {
            cerr << "Exception get: " << e.what() << endl;
        }

        break;
    }
    case 2:
    {
        int edgeDetect, kernel_size =3;
        cout << "please assign the method of edge detection, 0 for sobel x , 1 for sobel y, 2 for xy  ";
        cin >> edgeDetect;
        
        Mat dst;
      
     
        switch (edgeDetect)
        {
        case 0:
        {
            EdgeDect.sobel_amp(src, dst, "x", kernel_size);
            imshow("x direction of Sobel image", dst);
            break;
        }
        case 1:
        {
            EdgeDect.sobel_amp(src, dst, "y", kernel_size);
            imshow("y direction of Sobel image", dst);
            break;
        }
        case 2:
        {
            EdgeDect.sobel_amp(src, dst, "sum_sqrt", kernel_size);
            imshow("xy direction of Sobel image", dst);
            break;
        }
        default:
            cout << "Invalid index selected." << endl; // Added message for clarity
            break;
        }

        waitKey(0);
        destroyAllWindows();

        break;
    }

    //-------------------------------------------------------------------------------------------
    //practice
    //-------------------------------------------------------------------------------------------
    case -99:
    {
        // 遞迴及迭代問題 斐波那契數列
        cout << "Please assign the number of term that calculate the FibonacciRecursive " << endl;
        int num;
        cin >> num;
        cout << "The assign number is: " << num << endl;

        int result = comMath.FibonacciRecursive(num);
        cout << "The FibonacciRecursive answer is: " << result << endl;
        int result_2 = comMath.FibonacciIterative(num);
        cout << "The FibonacciIterative answer is: " << result_2 << endl;
        
        break;
    }

    case -100: 
    {
        // 正弦的泰勒級數
        int num_term, calculate_value;
        cout << "Please assign the number of term: " << endl;
        cin >> num_term;
        cout << "Please assign the calculate value: " << endl;
        cin >> calculate_value;

        double result = comMath.calculate_TalyorSeries(num_term, calculate_value);
        cout << "The terms " << num_term << " answer value is: " << result << endl;

        break;
    }
    //-------------------------------------------------------------------------------------------
    default :
        cout << "Invalid index selected." << endl; // Added message for clarity
        break;
    }
    return 0;
    //-------------------------------------------------------------------------------------------

}


