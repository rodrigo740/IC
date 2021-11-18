#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){

    if(argc < 3){
        cerr << "Usage: ./ex10 <original_img> <noise_img>\nExample: ./ex10 images/lena.ppm images/color.ppm" << endl;
        return -1;
    }

    Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat image2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

    vector<Mat> bgr_planes1,bgr_planes2;
    split(image1, bgr_planes1);
    split(image2, bgr_planes2);
    
    bgr_planes1[0].convertTo(bgr_planes1[0], CV_32F);
    bgr_planes1[1].convertTo(bgr_planes1[1], CV_32F);
    bgr_planes1[2].convertTo(bgr_planes1[2], CV_32F);
    
    bgr_planes2[0].convertTo(bgr_planes2[0], CV_32F);
    bgr_planes2[1].convertTo(bgr_planes2[1], CV_32F);
    bgr_planes2[2].convertTo(bgr_planes2[2], CV_32F);

    double value1, value2;
    double mseB, mseG, mseR;

    for (int i = 0; i < image1.rows; i++)
    {
        for (int j = 0; j < image1.cols; j++)
        {
            // Blue
            value1 = bgr_planes1[0].at<float>(i,j);
            value2 = bgr_planes2[0].at<float>(i,j);
            mseB += pow(abs(value1 - value2), 2);

            // Green
            value1 = bgr_planes1[1].at<float>(i,j);
            value2 = bgr_planes2[1].at<float>(i,j);
            mseG += pow(abs(value1 - value2), 2);

            // Red
            value1 = bgr_planes1[2].at<float>(i,j);
            value2 = bgr_planes2[2].at<float>(i,j);
            mseR += pow(abs(value1 - value2), 2);
        }
    }

    int nPixels = image1.rows * image1.cols;

    mseB = mseB / nPixels;
    mseG = mseG / nPixels;
    mseR = mseR / nPixels;

    double mse = (mseB + mseG + mseR) / 3;

    float psnr = 10 * log(255*255 / (mse * mse));
    
    cout << "PSNR: " << psnr << " dB" << "\nMaximum per pixel absolute error: " << mse << endl;

    return 0;
}