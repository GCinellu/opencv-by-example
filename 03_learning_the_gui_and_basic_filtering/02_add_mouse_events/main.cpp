#include <iostream>
#include <string>
#include <sstream>
#include <cvaux.h>
#include <cv.hpp>

using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int blurAmount = 15;

String windowNameTrump = "Trump";
String imagePath       = "/Users/vandebron/Documents/Playground/assets/image.jpg";

// Create a trackbar
static void onChange(int pos, void* userData) {
    if (pos<= 0)
        return;

    Mat imgBlur;
    Mat* img = (Mat*)userData;

    // Apply a blur filter
    blur(*img, imgBlur, Size(pos, pos));

    // Show result
    imshow(windowNameTrump, imgBlur);
};

// Mouse callback
static void onMouse(int event, int x, int y, int, void* userInput) {
    if (event != EVENT_LBUTTONDOWN)
        return;

    // Get the pointer input image
    Mat* img = (Mat*)userInput;

    // Draw a circle
    circle(*img, Point(x, y), 10, Scalar(0, 255,0), 3);

    // Call on change to get blurred image
    onChange(blurAmount, img);
};

int main(int argc, const char** argv) {
    // Read image
    Mat trump = imread(imagePath);

    // Create window
    namedWindow(windowNameTrump);

    createTrackbar(windowNameTrump, windowNameTrump, &blurAmount, 30, onChange, &trump);

    setMouseCallback(windowNameTrump, onMouse, &trump);

    // Call to onChange to init
    onChange(blurAmount, &trump);

    waitKey(0);

    destroyAllWindows();
    return 0;
}
