#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char** argv) {
    Mat thr, gray, con;
    Mat src = imread("digits.png", 1);
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, thr, 200, 255, THRESH_BINARY_INV);
    thr.copyTo(con);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat sample;
    Mat response_array;
    findContours(con, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    for (int i = 0; i < contours.size(); i=hierarchy[i][0]) {
        Rect r = boundingRect(contours[i]);
        rectangle(src, Point(r.x, r.y), Point(r.x+r.width, r.y+r.height), 
                Scalar(0, 0, 255), 2, 8, 0);
        Mat ROI = thr(r);
        Mat tmp1, tmp2;
        resize(ROI, tmp1, Size(10, 10), 0, 0, INTER_LINEAR);
        tmp1.convertTo(tmp2, CV_32FC1);
        sample.push_back(tmp2.reshape(1, 1));
        imshow("src", src);
        int c = waitKey(0);
        c -= 0x30;
        response_array.push_back(c);
        rectangle(src, Point(r.x, r.y), Point(r.x+r.width, r.y+r.height),
                Scalar(0, 255, 0), 2, 8, 0);
    }

    Mat response, tmp;
    tmp = response_array.reshape(1, 1);
    tmp.convertTo(response, CV_32FC1);

    FileStorage Data("TrainingData.yml", FileStorage::WRITE);
    Data << "data" << sample;
    Data.release();

    FileStorage Label("LabelData.yml", FileStorage::WRITE);
    Label << "label" << response;
    Label.release();

    cout << "Training and Label data created successfully!" << endl;
    
    imshow("src", src);
    waitKey();
}

