#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

int main() {
    // Read Image
    Mat color = imread("/Users/vandebron/Documents/Playground/c++/opencv/opencv-by-example/02_intro_to_basics/image.jpg", CV_LOAD_IMAGE_COLOR);
    Mat gray  = imread("/Users/vandebron/Documents/Playground/c++/opencv/opencv-by-example/02_intro_to_basics/image.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    imwrite("/Users/vandebron/Documents/Playground/c++/opencv/opencv-by-example/02_intro_to_basics/imageGray.jpg", gray);

//     Get same pixel with opencv function
    int myRow = color.cols - 1;
    int myCol = color.rows - 1;

    // Show Images
    imshow("Image BGR", color);
    imshow("Image Gray", gray);

    waitKey(0);
    return 0;
}