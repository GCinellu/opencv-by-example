#include <iostream>
#include <string>
#include <sstream>
#include <cvaux.h>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

Mat img;
bool applyGray = false;
bool applyBlur = false;
bool applySobel = false;

String windowNameFace = "Face";
String imagePath      = "/Users/vandebron/Documents/Playground/assets/face.jpg";

void applyFilters() {
    Mat result;

    img.copyTo(result);

    if (applyGray) {
        cvtColor(result, result, COLOR_BGR2GRAY);
    }

    if (applyBlur) {
        blur(result, result, Size(5, 5));
    }

    if (applySobel) {
        Sobel(result, result, CV_8U, 1, 1);
    }

    imshow(imagePath, result);
}

void grayCallback(int state, void* userData) {
    applyGray = true;
    applyFilters();
}

void rgbCallback(int state, void* userData) {
    applyGray = false;
    applyFilters();
}

void blurCallback(int state, void* userData) {
    applyBlur = (bool)state;
    applyFilters();
}

void sobelCallback(int state, void* userData) {
    applySobel = !applySobel;
    applyFilters();
}

int main() {
    img = imread(imagePath);

    namedWindow(windowNameFace);

    createButton("Blur", blurCallback, NULL, CV_CHECKBOX, 0);

    createButton("Gray", grayCallback, NULL, CV_RADIOBOX, 0);
    createButton("RGB", rgbCallback, NULL, CV_RADIOBOX, 1);

    createButton("Sobel", sobelCallback, NULL, CV_PUSH_BUTTON, 0);

    waitKey(0);
    destroyAllWindows();

    return 0;
}