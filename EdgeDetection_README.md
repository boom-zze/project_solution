# EdgeDetection.cpp 說明文件

此文件主要實現了基於 Sobel 算子的邊緣檢測演算法

## 主要功能
'sobel_amp' 函数
  ==> 支持 X 方向、Y 方向及 XY 方向(sum_sqrt) 邊緣檢測功能
  
```cpp
sobel_amp(const Mat& img_src, Mat& img_out, string FilterType, int kernel_size)
img_src : 輸入影像
img_out : 輸出影像
FilterType : 邊緣檢測型態, 參數必須為 "x"、"y" 或 "sum_sqrt"
kernel_size : sobel mask size, 建議使用奇數（如 3、5、7） 

Sobel 算子 mask
對於 kernel_size = 3 的情況：
X direction      Y direction
[-1  0  1]       [-1 -2 -1]
[-2  0  2]       [ 0  0  0]
[-1  0  1]       [ 1  2  1]


