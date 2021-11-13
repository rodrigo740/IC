#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){

    if(argc < 3){
        cerr << "Usage: ./d9 <input_img> <quantization>\nExample: ./d8 lena.ppm 8" << endl;
        return -1;
    }

    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat gray;

    vector<Mat> bgr_planes;
    split(image, bgr_planes);

    cvtColor(image, gray, COLOR_BGR2GRAY);

    namedWindow("Grayscale before", WINDOW_AUTOSIZE);
    imshow("Grayscale before", gray);
    waitKey(0);

    
    bgr_planes[0].convertTo(bgr_planes[0], CV_32F);
    bgr_planes[1].convertTo(bgr_planes[1], CV_32F);
    bgr_planes[2].convertTo(bgr_planes[2], CV_32F);
    gray.convertTo(gray, CV_32F);

    
    const int quantization = stoi(argv[2]);
    const int d = 256/quantization;

    double value;
    int temp;

    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols; j++)
        {
            // Grayscale
            value = gray.at<float>(i,j);
            temp = trunc(value/d);
            gray.at<float>(i,j) = temp * d;

            // Blue
            value = bgr_planes[0].at<float>(i,j);
            temp = trunc(value/d);
            bgr_planes[0].at<float>(i,j) = temp * d;

            // Green
            value = bgr_planes[1].at<float>(i,j);
            temp = trunc(value/d);
            bgr_planes[1].at<float>(i,j) = temp * d;

            // Red
            value = bgr_planes[2].at<float>(i,j);
            temp = trunc(value/d);
            bgr_planes[2].at<float>(i,j) = temp * d;
        }
    }

    Mat merged;
    merge(bgr_planes,merged);
    
    namedWindow("Grayscale", WINDOW_AUTOSIZE);
    imshow("Grayscale", gray);
    namedWindow("Color", WINDOW_AUTOSIZE);
    imshow("Color", merged);
    waitKey(0);


    return 0;
}