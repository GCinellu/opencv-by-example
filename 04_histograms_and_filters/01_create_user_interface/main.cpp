#include <iostream>
#include <string>
#include <sstream>
#include <cvaux.h>
using namespace std;

// OpenCV
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

Mat img;

//String imagePath = "/Users/vandebron/Documents/Playground/assets/image.jpg";
String imagePath = "/Users/vandebron/Desktop/wallpapers/1477168345054.jpg";

const String keys = {
        "{help h usage ? | | print this message}"
        "{@image | | Image to process}"
};

void showHistoCallback(int state, void* userData) {
    // Separate image in BGR
    vector<Mat> bgr;
    split(img, bgr);

    // Create histogram for 256bins
    // The number of possible values (0..255)
    int numBins = 256;

    // Setting range for B,G,R
    float range[] = {0, 256};
    const float* histRange = { range };

    Mat b_hist, g_hist, r_hist;

    calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &numBins, &histRange);
    calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &numBins, &histRange);
    calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &numBins, &histRange);

    // Draw the histogram
    // Drawing a line for each channel
    int width  = 512;
    int height = 300;

    // Creating an image with gray base
    Mat histImage(height, width, CV_8UC3, Scalar(20,20,20));

    normalize(b_hist, b_hist, 0, height, NORM_MINMAX);
    normalize(g_hist, g_hist, 0, height, NORM_MINMAX);
    normalize(r_hist, r_hist, 0, height, NORM_MINMAX);

    int binStep = cvRound((float)width/(float)numBins);
    for(int i = 0; i < numBins; i++) {
        line(histImage,
             Point(binStep*(i-1), height - cvRound(b_hist.at<float>(i-1))),
             Point(binStep*(i), height - cvRound(b_hist.at<float>(i))),
             Scalar(255,0,0));

        line(histImage,
             Point(binStep*(i-1), height - cvRound(g_hist.at<float>(i-1))),
             Point(binStep*(i), height - cvRound(g_hist.at<float>(i))),
             Scalar(0,255,0));

        line(histImage,
             Point(binStep*(i-1), height - cvRound(r_hist.at<float>(i-1))),
             Point(binStep*(i), height - cvRound(r_hist.at<float>(i))),
             Scalar(0,0,255));
    }

    imshow("Histogram", histImage);
}

void equalizeCallback(int state, void* userData) {
    Mat result;
    // Converting BGR image to YCBCR
    Mat ycrcb;
    cvtColor(img, ycrcb, COLOR_BGR2YCrCb);

    // Splitting image into channels
    vector<Mat> channels;
    split(ycrcb, channels);

    // Equalizing the Y channel only
    equalizeHist(channels[0], channels[0]);

    // Merging the result channels
    merge(channels, ycrcb);

    // Converting back YCRCB to BGR
    cvtColor(ycrcb, result, COLOR_YCrCb2BGR);

    // Show image
    imshow("Equalized", result);
}

void lomoCallback(int state, void* userData) {
    Mat result;

    const double exponential_e = exp(1.0);
    // Creating lookup table for color curve effect
    Mat lut(1, 256, CV_8UC1);
    for (int i = 0; i < 256; i++) {
        float x = (float)i/256.0;
        lut.at<uchar>(i) = cvRound(256 * (1 / (1 + pow(exponential_e,-((x - 0.5)/0.1)))));
    }

    // Splitting the image channels and applying curve transform
    // only to red channel
    vector<Mat> bgr;
    split(img, bgr);
    LUT(bgr[2], lut, bgr[2]);

    // Merging results
    merge(bgr, result);

    // Creating image for halo dark
    Mat halo(img.rows, img.cols, CV_32FC3, Scalar(0.3, 0.3, 0.3));
    // Creating a circle
    circle(halo, Point(img.cols/2, img.rows/2), img.cols/3, Scalar(1, 1, 1), -1);
    blur(halo, halo, Size(img.cols/3, img.cols/3));

    // Converting the result to float to allow multiply by 1 factor
    Mat resultf;
    result.convertTo(resultf, CV_32FC3);

    // Multiplying the results with the halo
    multiply(resultf, halo, resultf);

    // Converting to 8 bits
    resultf.convertTo(result, CV_8UC3);

    // Showing Result
    imshow("Lomography", result);
}

void cartoonCallback(int state, void* userData) {
    /** EDGES **/
    // Applying median filter to remove possible noise
    Mat imgMedian;
    medianBlur(img, imgMedian, 7);

    // Detecting edges with canny
    Mat imgCanny;
    Canny(imgMedian, imgCanny, 50, 150);

    // Dilating the edges
    Mat kernel = getStructuringElement(MORPH_RECT, Size(2,2));
    dilate(imgCanny, imgCanny, kernel);

    // Scaling edge values to 1 and inverting values
    imgCanny = imgCanny / 255;
    imgCanny = 1 - imgCanny;

    // Using float values to allow multiply between 0 and 1
    Mat imgCannyf;
    imgCanny.convertTo(imgCannyf, CV_32FC3);

    // Blurring the edges to do smooth effect
    blur(imgCannyf, imgCannyf, Size(5,5));

    /** COLOR **/
    // Applying bilateral filter to homogenizes color
    Mat imgBF;
    bilateralFilter(img, imgBF, 9, 150.0, 150.0);

    // truncating colors
    Mat result = imgBF / 25;
    result = result * 25;

    /** MERGES COLOR + EDGES **/
    // Creating 3 channels for the edges
    Mat imgCanny3c;
    Mat cannyChannels[] = {imgCannyf, imgCannyf, imgCannyf};
    merge(cannyChannels, 3, imgCanny3c);

    // Converting color results to float
    Mat resultf;
    result.convertTo(resultf, CV_32FC3);

    // Multiply color and edges matrices
    multiply(resultf, imgCanny3c, resultf);

    // Converting to 8 bits color
    resultf.convertTo(result, CV_8UC3);

    // Show image
    imshow("Result", result);
}

int main(int argc, const char** argv) {
    img = imread(imagePath);
    namedWindow("Input");

    // UI Buttons
    createButton("Show histogram", showHistoCallback, NULL, CV_PUSH_BUTTON, 0);
    createButton("Equalize histogram", equalizeCallback, NULL, CV_PUSH_BUTTON, 0);
    createButton("Lomography Effect", lomoCallback, NULL, CV_PUSH_BUTTON, 0);
    createButton("Cartoonize Effect", cartoonCallback, NULL, CV_PUSH_BUTTON, 0);

    imshow("Input", img);

    waitKey(0);
    destroyAllWindows();
    return 0;
}