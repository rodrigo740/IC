#include <iostream>
#include <opencv2/highgui.hpp>
#include <chrono>

using namespace std;
using namespace cv;
using namespace std::chrono;

int main(int argc, char **argv){

    auto start = high_resolution_clock::now();

    if(argc != 5){
        cerr << "Usage: ./ex4 <original_img> <copied_img> <original_vid> <copied_vid>\nExample: ./ex4 images/lena.ppm images/lenaCopy.ppm video/teste.avi video/testeCopy.avi" << endl;
        return -1;
    }

    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat clone = Mat::zeros(image.rows, image.cols, image.type());

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            clone.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);
        }
        
    }
    
    imwrite(argv[2], clone);

    VideoCapture cap = VideoCapture(argv[3]);

    if(!cap.isOpened()){
        cerr << "Failed to open video" << endl;
        return -1;
    }

    int fps = cap.get(5);
    int frame_count = cap.get(7);
    int frame_width = static_cast<int>(cap.get(3));
    int frame_height = static_cast<int>(cap.get(4));
    Size frame_size(frame_width, frame_height);

    VideoWriter output (argv[4], VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame_size); //Encodes to AVI format

    while(cap.isOpened()){
        Mat frame;

        if(cap.read(frame)){
            output.write(frame);
        }else{
            break;
        }

    }

    cap.release();
    output.release();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Processing Time: " << duration.count() << endl;
    return 0;
}