
// 在此定義函式功能
#include "commonUtil.h"
using namespace std;
using namespace cv;

// 讀取影像
bool commonUtil::read_image(const string filepath, Mat & buffer, int& channels)
{
	buffer = imread(filepath);
    if (buffer.empty())
    {
        cout << "無法讀取圖片" << endl;
        return false;
    }

    channels = buffer.channels();

    return true;
}
// 彩圖分開channel
void commonUtil::decompose(const Mat &src, Mat &img_r, Mat &img_g, Mat &img_b)
{
    vector <Mat> vec_split_rgb;
    int channels = src.channels();
    if (channels == 3)
    {
        split(src, vec_split_rgb); //bgr
        img_b = vec_split_rgb[0];
        img_g = vec_split_rgb[1];
        img_r = vec_split_rgb[2];
    }
    else
    {
        cout << "The image is gray" << endl;
    }
}
void commonUtil::compose(const Mat &img_r, const Mat &img_g, const Mat &img_b, Mat &img_out) 
{

    cv::merge(vector<cv::Mat>{img_b, img_g, img_r}, img_out);
}

//計算影像區域的平均灰階

void commonUtil::intensity(const Mat& mask, const Mat& img_src, cv::Scalar& mean, cv::Scalar& deviation)
{
    // 檢查 mask 是否為空或全黑
    bool use_mask = !mask.empty() && cv::countNonZero(mask) > 0;

    if (use_mask) {
        // 使用提供的 mask 計算
        cv::meanStdDev(img_src, mean, deviation, mask);
    }
    else {
        // 計算所有像素的平均值和標準差
        cv::meanStdDev(img_src, mean, deviation);
    }
}

// 定義滑鼠回調函數
void commonUtil::getGrayValue(int event, int x, int y, int flags, void* userdata)
{

    ImageInfo* img_info = reinterpret_cast<ImageInfo*> (userdata);
    // 當滑鼠左鍵按下時
    if (event == EVENT_LBUTTONDOWN)
    {
        //ImageInfo& img_info_tmp = img_info;
        Scalar text_color;
        int channels = img_info->image.channels();
        string text;
        if (channels == 1)
        {
            int grayValue = img_info->image.at<uchar>(y, x);  // 獲取灰階值
            text = "Gray: " + to_string(grayValue);
            text_color = Scalar(255);
        }
        else
        {
            Vec3b pixelValue = img_info->image.at<Vec3b>(y, x);
            text = "R: " + to_string(pixelValue[2]) +
                " G: " + to_string(pixelValue[1]) +
                " B: " + to_string(pixelValue[0]);
            text_color = Scalar(0, 0, 255);
        }

        // 在圖像上顯示灰階值
        Mat img_with_text = img_info->image.clone();

        Point textOrg(x + 10, y - 10);

        // 顯示灰階值的文字
        putText(img_with_text, text, textOrg, FONT_HERSHEY_SIMPLEX, 0.5, text_color, 1);

        // 在點擊位置畫一個小圓
        circle(img_with_text, Point(x, y), 5, text_color, -1);

        // 顯示圖像
        imshow(img_info->windowName, img_with_text);
    }
}

int commonMath::FibonacciRecursive(int number)
{
    if (number <= 2)
    {
        return 1;
    }
    else
    {
        return FibonacciRecursive(number - 1) + FibonacciRecursive(number - 2);
    }
    
}
int commonMath::FibonacciIterative(int number)
{
    if (number <=2)
    {
        return 1;
    }
    
    int prev = 1, cur = 1;
    for (int i = 3; i <= number; i++)
    {
        int next = prev + cur;

        prev = cur;
        cur = next;
    }
    return cur;
}
// 想法拆分成兩個part , 項的運算及最終值得運算
// 泰勒級數一般式 fn(x) = (-1)^n / (2n+1)! * x^ (2n+1)
double commonMath::calculate_factorial(int n)
{
    double factorial =1;
    double num = 2 * n + 1;
    for (int i = num; i > 1; i--)
    {
        factorial = factorial * i;
    }
    //cout << "The factorial value is: " << factorial << endl;
    return factorial;
}

double commonMath::calculate_TalyorSeries(int n, double x)
{
    double coefficient = pow(-1, n) / calculate_factorial(n);

    return coefficient * pow(x, (2 * n + 1));
}

