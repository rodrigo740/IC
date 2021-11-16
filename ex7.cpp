#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){

    if(argc < 2){
        cerr << "Usage: ./ex7 <input_img>\nExample: ./ex7 images/lena.ppm " << endl;
        return -1;
    }

    Mat image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    int numPixels = image.total();

    vector<Mat> bgr_planes;
    split(image, bgr_planes);

    
    Mat histBlue = Mat::zeros(256, 1, CV_32F);
    Mat histRed = Mat::zeros(256, 1, CV_32F);
    Mat histGreen = Mat::zeros(256, 1, CV_32F);
    Mat hist2gray = Mat::zeros(256, 1, CV_32F);

    bgr_planes[0].convertTo(bgr_planes[0], CV_32F);
    bgr_planes[1].convertTo(bgr_planes[1], CV_32F);
    bgr_planes[2].convertTo(bgr_planes[2], CV_32F);
    gray.convertTo(gray, CV_32F);    
    
    double value, valueB, valueR, valueG;
    
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            valueB = bgr_planes[0].at<float>(i,j);
            valueG = bgr_planes[1].at<float>(i,j);
            valueR = bgr_planes[2].at<float>(i,j);

            histBlue.at<float>(valueB) += 1;
            histRed.at<float>(valueR) += 1;
            histGreen.at<float>(valueG) += 1;


            value = gray.at<float>(i,j);
            hist2gray.at<float>(value) += 1;
        }        
    }

    
    Mat hist_img_blue(400, 512, CV_8UC3, Scalar(0, 0, 0));
    Mat hist_img_red(400, 512, CV_8UC3, Scalar(0, 0, 0));
    Mat hist_img_green(400, 512, CV_8UC3, Scalar(0, 0, 0));
    Mat hist_img_gray(400, 512, CV_8UC3, Scalar(0, 0, 0));
    Mat normalized_hist_blue, normalized_hist_red, normalized_hist_green, normalized_hist_gray;

    normalize(histBlue, normalized_hist_blue, 0, 400, NORM_MINMAX, -1, Mat());
    normalize(histRed, normalized_hist_red, 0, 400, NORM_MINMAX, -1, Mat());
    normalize(histGreen, normalized_hist_green, 0, 400, NORM_MINMAX, -1, Mat());
    normalize(hist2gray, normalized_hist_gray, 0, 400, NORM_MINMAX, -1, Mat());


    for(int i = 0; i < 256; i++){

        rectangle(hist_img_blue, Point(2 * i, hist_img_blue.rows - normalized_hist_blue.at<float>(i)),
			Point(2 * (i + 1), hist_img_blue.rows), Scalar(255,0,0), -1);

        rectangle(hist_img_red, Point(2 * i, hist_img_red.rows - normalized_hist_red.at<float>(i)),
			Point(2 * (i + 1), hist_img_red.rows), Scalar(0,0,255), -1);

        rectangle(hist_img_green, Point(2 * i, hist_img_green.rows - normalized_hist_green.at<float>(i)),
			Point(2 * (i + 1), hist_img_green.rows), Scalar(0,255,0), -1);
        
        rectangle(hist_img_gray, Point(2 * i, hist_img_gray.rows - normalized_hist_gray.at<float>(i)),
			Point(2 * (i + 1), hist_img_gray.rows), Scalar(255,0,0), -1);
    }

    /*
    namedWindow("Histogram Blue", WINDOW_NORMAL);
    imshow("Histogram Blue", hist_img_blue);
    
    namedWindow("Histogram Red", WINDOW_NORMAL);
    imshow("Histogram Red", hist_img_red);

    namedWindow("Histogram Green", WINDOW_NORMAL);
    imshow("Histogram Green", hist_img_green);

    namedWindow("Histogram grayscale", WINDOW_NORMAL);
    imshow("Histogram grayscale", hist_img_gray);

    waitKey(0);
    */

    double h1 = 0;
    for(int row = 0; row < histBlue.rows; ++row) {
        for(int col = 0; col < histBlue.cols; ++col) {
            double prob = (static_cast<double>(histBlue.at<float>(row,col))/static_cast<double>(numPixels));
            if(prob != 0){
                h1 = h1-prob*log2(prob);
            }
        }
    }
    cout << "Entropy Blue: " << h1 << endl;

    double h2 = 0;
    for(int row = 0; row < histRed.rows; ++row) {
        for(int col = 0; col < histRed.cols; ++col) {
            double prob = (static_cast<double>(histRed.at<float>(row,col))/static_cast<double>(numPixels));
            if(prob != 0){
                h2 = h2-prob*log(prob);
            }
        }
    }
    cout << "Entropy Red: " << h2 << endl;

    double h3 = 0;
    for(int row = 0; row < histGreen.rows; ++row) {
        for(int col = 0; col < histGreen.cols; ++col) {
            double prob = (static_cast<double>(histGreen.at<float>(row,col))/static_cast<double>(numPixels));
            if(prob != 0){
                h3 = h3-prob*log2(prob);
            }
        }
    }
    cout << "Entropy Green: " << h3 << endl;

    double h4 = 0;
    for(int row = 0; row < hist2gray.rows; ++row) {
        for(int col = 0; col < hist2gray.cols; ++col) {
            double prob = (static_cast<double>(hist2gray.at<float>(row,col))/static_cast<double>(numPixels));
            if(prob != 0){
                h4 = h4-prob*log2(prob);
            }
        }
    }
    cout << "Entropy Grayscale: " << h4 << endl;

    imwrite("histograms/blue_histogram.jpg",hist_img_blue);
    imwrite("histograms/red_histogram.jpg",hist_img_red);
    imwrite("histograms/green_histogram.jpg",hist_img_green);
    imwrite("histograms/grayscale_histogram.jpg",hist_img_gray);


    return 0;
}