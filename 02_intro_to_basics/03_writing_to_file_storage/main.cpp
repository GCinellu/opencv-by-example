#include "opencv2/opencv.hpp"
using namespace cv;

int main(int, char** argv) {
  FileStorage fs("/Users/vandebron/Documents/Playground/c++/opencv/opencv-by-example/02_intro_to_basics/03_writing_to_file_storage/test.yml", FileStorage::WRITE);

    // Save an int
    int fps = 5;
    fs << "fps" << fps;

    // Creating sample matrixes
    Mat m1 = Mat::eye(2, 3, CV_32F);
    Mat m2 = Mat::ones(2, 3, CV_32F);

    Mat result = (m1 + 1).mul(m1 + 3);

    fs << "Result" << result;
    fs.release();

    FileStorage fs2("test.yml", FileStorage::READ);

    Mat r;
    fs2["Result"] >> r;
    std::cout << r << std::endl;

    fs2.release();

    return 0;
}