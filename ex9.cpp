#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;

int main(int argc, char **argv){

    auto start = high_resolution_clock::now();

    if(argc < 3){
        cerr << "Usage: ./ex9 <input_img> <number_of_levels>\nExample: ./ex9 images/lena.ppm 32" << endl;
        return -1;
    }

    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat gray;

    vector<Mat> bgr_planes;
    split(image, bgr_planes);

    cvtColor(image, gray, COLOR_BGR2GRAY);

    /*
    namedWindow("Grayscale before", WINDOW_AUTOSIZE);
    imshow("Grayscale before", gray);
    waitKey(0);
    */
    
    bgr_planes[0].convertTo(bgr_planes[0], CV_32F);
    bgr_planes[1].convertTo(bgr_planes[1], CV_32F);
    bgr_planes[2].convertTo(bgr_planes[2], CV_32F);
    gray.convertTo(gray, CV_32F);

    
    const int d = 256/stoi(argv[2]);

    double valueByLevel[stoi(argv[2])];

    for (int i = 0; i < stoi(argv[2]); i++)
    {
        valueByLevel[i] = (i+1)*d/2 + (i*d)/2;
    }

    
    double value;
    int temp;
    int level;

    for (int i = 0; i < gray.rows; i++)
    {
        for (int j = 0; j < gray.cols; j++)
        {
            // Grayscale
            value = gray.at<float>(i,j);
            temp = trunc(value/d);
            gray.at<float>(i,j) = valueByLevel[temp];

            // Blue
            value = bgr_planes[0].at<float>(i,j);
            temp = trunc(value/d);
            bgr_planes[0].at<float>(i,j) = valueByLevel[temp];

            // Green
            value = bgr_planes[1].at<float>(i,j);
            temp = trunc(value/d);
            bgr_planes[1].at<float>(i,j) = valueByLevel[temp];

            // Red
            value = bgr_planes[2].at<float>(i,j);
            temp = trunc(value/d);
            bgr_planes[2].at<float>(i,j) = valueByLevel[temp];
        }
    }

    Mat merged;
    merge(bgr_planes,merged);

    gray.convertTo(gray, CV_8UC3);
    merged.convertTo(merged, CV_8UC3);

    /*
    namedWindow("Grayscale", WINDOW_AUTOSIZE);
    imshow("Grayscale", gray);
    namedWindow("Color", WINDOW_AUTOSIZE);
    imshow("Color", merged);
    waitKey(0);
    */

    imwrite("images/grayscale.ppm", gray);
    imwrite("images/color.ppm", merged);

    Mat image1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat image2 = imread("images/color.ppm", CV_LOAD_IMAGE_COLOR);
    Mat image3 = imread("images/grayscale.ppm", CV_LOAD_IMAGE_GRAYSCALE);
    Mat image4;
    cvtColor(image1, image4, COLOR_BGR2GRAY);

    vector<Mat> bgr_planes1,bgr_planes2;
    split(image1, bgr_planes1);
    split(image2, bgr_planes2);
    
    bgr_planes1[0].convertTo(bgr_planes1[0], CV_32F);
    bgr_planes1[1].convertTo(bgr_planes1[1], CV_32F);
    bgr_planes1[2].convertTo(bgr_planes1[2], CV_32F);
    image4.convertTo(image4, CV_32F);

    bgr_planes2[0].convertTo(bgr_planes2[0], CV_32F);
    bgr_planes2[1].convertTo(bgr_planes2[1], CV_32F);
    bgr_planes2[2].convertTo(bgr_planes2[2], CV_32F);
    image3.convertTo(image3, CV_32F);


    double value1, value2;
    double mseB, mseG, mseR, mseGray;

    for (int i = 0; i < image1.rows; i++)
    {
        for (int j = 0; j < image1.cols; j++)
        {
            // Grayscale
            value1 = image4.at<float>(i,j);
            value2 = image3.at<float>(i,j);
            mseGray += pow(abs(value1 - value2), 2);

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
    mseGray = mseGray / nPixels;

    double mse = (mseB + mseG + mseR) / 3;

    float psnr = 10 * log(255*255 / (mse * mse));
    float psnrGray = 10 * log(255*255 / (mseGray * mseGray));
    
    cout << "PSNR: " << psnr << " dB\nMaximum per pixel absolute error color version: " << mse << 
        "\n\nPSNR Grayscale: " << psnrGray <<
        " dB\nMaximum per pixel absolute error grayscale version: " << psnrGray << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Processing Time: " << duration.count() << endl;
    
    return 0;
}