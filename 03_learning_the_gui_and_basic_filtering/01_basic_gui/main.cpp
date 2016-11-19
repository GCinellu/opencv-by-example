#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

//const int CV_GUI_NORMAL = 0x10;

int main() {
    String windowNameTrump = "Trump";
    String windowNameDojo  = "Dojo";

    // Read images
    Mat trump = imread("/Users/vandebron/Documents/Playground/assets/image.jpg");
    Mat dojo  = imread("/Users/vandebron/Documents/Playground/assets/image2.jpg");

    // Create Windows
    namedWindow(windowNameTrump, CV_GUI_NORMAL);
    namedWindow(windowNameDojo, WINDOW_AUTOSIZE);

    // Move windows
    moveWindow(windowNameTrump, 10, 10);
    moveWindow(windowNameDojo, 520, 10);

    // Show images
    imshow(windowNameTrump, trump);
    imshow(windowNameDojo, dojo);

    // Resize window, it also cut the image
    resizeWindow(windowNameTrump, 512, 512);

    // Wait for any key to press
    waitKey(0);

    // Destroy the windows
    destroyAllWindows();

    return 0;
}