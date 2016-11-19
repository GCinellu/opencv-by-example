#include <iostream>
#include <string>
#include <sstream>
#include <cvaux.h>
using namespace std;

// OpenCV
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

String imagePath   = "/Users/vandebron/Documents/Playground/assets/test_objects_full_2.jpg";
String patternPath = "/Users/vandebron/Documents/Playground/assets/test_objects_empty_2.jpg";

int thresholdAmount = 30;

Mat removeLight(Mat img, Mat pattern, int method) {
    Mat aux;

    // if method is normalization
    if(method == 1) {
        // Changing our image to 32 float for division
        Mat img32, pattern32;
        img.convertTo(img32, CV_32F);
        pattern.convertTo(pattern32, CV_32F);

        // Dividing the image by the pattern
        aux = 1 - (img32 / pattern32);

        // Scaling it to convert to 8bit format
        aux = aux * 500;

        // Converting to 8 bits format
        aux.convertTo(aux, CV_8U);
    } else {
        aux = pattern - img;
    }

    return aux;
}

Mat calculateLightPattern(Mat img) {
    Mat pattern;

    // Calculating the light pattern from one image
    blur(img, pattern, Size(img.cols / 3, img.cols / 3));
    return pattern;
}

static void onChangeTreshold(int value, void* userData) {
    if (value <= 0) return;

    Mat imgThr;
    Mat *img = (Mat*)userData;

    // Applying threshold
    threshold(*img, imgThr, value, 255, THRESH_BINARY);

    // Showing results
    imshow("Result", imgThr);
}

static void onChangeBlur(int pos, void* userData) {
    if (pos<= 0)
        return;

    Mat imgBlur;
    Mat* img = (Mat*)userData;

    // Apply a blur filterw
    blur(*img, imgBlur, Size(pos, pos));

    // Show result
    imshow("Result", imgBlur);
};

static Scalar randomColor(RNG& rng) {
    int icolor = (unsigned) rng;
    return Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255 );
}

void ConnectedComponents(Mat img) {
    // Using connected components to divide possible parts of image
    Mat labels;
    int numObjects = connectedComponents(img, labels);

    // Checking the number of objects detected
    if (numObjects < 2) {
        cout << "No objects detected" << endl;
        return;
    } else {
        cout << "Number of objects detected: " << numObjects - 1 << endl;
    }

    // Creating an outputimage coloring the objects
    Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
    RNG rng(0xFFFFFF);
    for(int i = 1; i < numObjects; i++) {
        Mat mask = labels == 1;
        output.setTo(randomColor(rng), mask);
    }

    imshow("Components", output);
}


int main() {
    Mat img     = imread(imagePath);
    Mat pattern = imread(patternPath);

    int methodLight = 1;
    int methodSeg   = 1;

    if(img.data == NULL) {
        cout << "Error loading image " << imagePath << endl;
        return 0;
    }

    Mat imgNoise;
    medianBlur(img, imgNoise, 3);

    Mat imgGray, patternGray;
    cvtColor(imgNoise, imgGray, COLOR_BGR2GRAY);
    cvtColor(pattern, patternGray, COLOR_BGR2GRAY);

    Mat lightPatternBackground = calculateLightPattern(patternGray);

    Mat removedLight = removeLight(imgGray, lightPatternBackground, 1);

    Mat imgThr;
    if (methodLight != 2) {
        threshold(removedLight, imgThr, 58, 300, THRESH_BINARY);
    } else {
        threshold(removedLight, imgThr, 140, 255, THRESH_BINARY_INV);
    }

    imshow("img", imgThr);
//     Creating trackbar for threshold
    String windowNameThreshold = "Result";

    namedWindow(windowNameThreshold);

    int thresholdAmount = 30;
    createTrackbar(windowNameThreshold, windowNameThreshold, &thresholdAmount, 255, onChangeTreshold, &removedLight);

    int blurAmount = 30;
    createTrackbar("blur", windowNameThreshold, &blurAmount, 255, onChangeBlur, &removedLight);

    imshow("Normal", img);
    imshow("Blur", imgNoise);

    waitKey(0);

    while(true) {
        Mat dst;
        int iTreshold = thresholdAmount - 30;
        int iBlur     = blurAmount - 30;

        removedLight.convertTo(dst, -1, iTreshold, iBlur);
        imshow(windowNameThreshold, dst);

        ConnectedComponents(imgThr);
//
        int ikey = waitKey(0);

        if (ikey == 27) {
            destroyAllWindows();
            break;
        }
    }

    return 0;
}