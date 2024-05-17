#include <opencv2/opencv.hpp> 
#include <iostream>           
using namespace cv;          
using namespace std;         

// �� �̹����� SSIM ���� ����ϴ� �Լ�
double computeSSIM(const Mat& img1, const Mat& img2) {
    const double C1 = 6.5025, C2 = 58.5225;  
    int d = CV_32F;                          

    Mat I1, I2;
    img1.convertTo(I1, d);                   
    img2.convertTo(I2, d);                   

    Mat I2_2 = I2.mul(I2);                 
    Mat I1_2 = I1.mul(I1);                 
    Mat I1_I2 = I1.mul(I2);                 

    Mat mu1, mu2;
    GaussianBlur(I1, mu1, Size(11, 11), 1.5); 
    GaussianBlur(I2, mu2, Size(11, 11), 1.5); 

    Mat mu1_2 = mu1.mul(mu1);              
    Mat mu2_2 = mu2.mul(mu2);             
    Mat mu1_mu2 = mu1.mul(mu2);              

    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5); 
    sigma1_2 -= mu1_2;                                

    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);  
    sigma2_2 -= mu2_2;                                

    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);  
    sigma12 -= mu1_mu2;                              

    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);

    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);

    Mat ssim_map;
    divide(t3, t1, ssim_map);                
    Scalar mssim = mean(ssim_map);           
    return mssim[0];                         
}

int main() {
    Mat img1 = imread("frame_0.jpg", IMREAD_GRAYSCALE); 
    Mat img2 = imread("frame_5842.jpg", IMREAD_GRAYSCALE); 

    if (img1.empty() || img2.empty()) {                 
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    double ssim_value = computeSSIM(img1, img2);        
    cout << "SSIM: " << ssim_value << endl;            

    return 0;
}