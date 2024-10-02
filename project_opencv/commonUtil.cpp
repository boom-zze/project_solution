
// �b���w�q�禡�\��
#include "commonUtil.h"
using namespace std;
using namespace cv;

// Ū���v��
bool commonUtil::read_image(const string filepath, Mat & buffer, int& channels)
{
	buffer = imread(filepath);
    if (buffer.empty())
    {
        cout << "�L�kŪ���Ϥ�" << endl;
        return false;
    }

    channels = buffer.channels();

    return true;
}
// �m�Ϥ��}channel
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

//�p��v���ϰ쪺�����Ƕ�

void commonUtil::intensity(const Mat& mask, const Mat& img_src, cv::Scalar& mean, cv::Scalar& deviation)
{
    // �ˬd mask �O�_���ũΥ���
    bool use_mask = !mask.empty() && cv::countNonZero(mask) > 0;

    if (use_mask) {
        // �ϥδ��Ѫ� mask �p��
        cv::meanStdDev(img_src, mean, deviation, mask);
    }
    else {
        // �p��Ҧ������������ȩM�зǮt
        cv::meanStdDev(img_src, mean, deviation);
    }
}

// �w�q�ƹ��^�ը��
void commonUtil::getGrayValue(int event, int x, int y, int flags, void* userdata)
{

    ImageInfo* img_info = reinterpret_cast<ImageInfo*> (userdata);
    // ��ƹ�������U��
    if (event == EVENT_LBUTTONDOWN)
    {
        //ImageInfo& img_info_tmp = img_info;
        Scalar text_color;
        int channels = img_info->image.channels();
        string text;
        if (channels == 1)
        {
            int grayValue = img_info->image.at<uchar>(y, x);  // ����Ƕ���
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

        // �b�Ϲ��W��ܦǶ���
        Mat img_with_text = img_info->image.clone();

        Point textOrg(x + 10, y - 10);

        // ��ܦǶ��Ȫ���r
        putText(img_with_text, text, textOrg, FONT_HERSHEY_SIMPLEX, 0.5, text_color, 1);

        // �b�I����m�e�@�Ӥp��
        circle(img_with_text, Point(x, y), 5, text_color, -1);

        // ��ܹϹ�
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
// �Q�k��������part , �����B��γ̲׭ȱo�B��
// ���ǯżƤ@�릡 fn(x) = (-1)^n / (2n+1)! * x^ (2n+1)
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

