#include "image.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml/ml.hpp>

#define SUDOKU_OPENCV_DEBUG_ON

namespace {
    cv::Mat gray_scale_and_blur(cv::Mat& src) {
        cv::Mat output;
        cv::cvtColor(src, output, cv::COLOR_BGR2GRAY);
        cv::blur(output, output, cv::Size(3, 3));
        return output;
    }

    std::vector<std::vector<cv::Point>> find_contours(cv::Mat& src) {
        cv::Mat canny_output, tmp;
        auto high_thresh = cv::threshold(src, tmp, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        auto low_thresh = 0.5*high_thresh;
        cv::Canny(src, canny_output, low_thresh, high_thresh);

#ifdef SUDOKU_OPENCV_DEBUG_ON
        cv::imshow("Debug", canny_output);
        cv::waitKey(0);
#endif

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        return contours;
    }

    int get_max_area_contour_id(std::vector<std::vector<cv::Point>> contours) {
        double maxArea = 0;
        int contour_id = -1;
        std::vector<cv::Point2f> bounding_rect;
        for (int j = 0; j < contours.size(); ++j) {
            auto perimeter = cv::arcLength(contours[j], true);
            cv::approxPolyDP(contours[j], bounding_rect, 0.015*perimeter, true);
            /* double newArea = cv::contourArea(contours[j]); */
            double newArea = cv::contourArea(bounding_rect);
            if (newArea > maxArea) {
                maxArea = newArea;
                contour_id = j;
            }
        }
        return contour_id;
    }

    cv::Mat warp_sudoku_board_to_fill_screen(cv::Mat& src, std::vector<cv::Point>& cnt) {
        auto perimeter = cv::arcLength(cnt, true);
        std::vector<cv::Point2f> bounding_rect;
        cv::approxPolyDP(cnt, bounding_rect, perimeter*0.015, true);

        std::vector<cv::Point2f> dst = {{0,0}, {0, 450}, {450, 450}, {450, 0}};
        auto M = cv::getPerspectiveTransform(bounding_rect, dst);

        cv::Mat output;
        cv::warpPerspective(src, output, M, cv::Size(450, 450));
        return output;
    }

    std::vector<cv::Mat> make_9_by_9_grid(cv::Mat& src) {
        auto cell_width = src.cols / 9;
        auto cell_height = src.rows / 9;
        std::vector<cv::Mat> cells;

        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                cv::Rect cell_rect(col*cell_width+5, row*cell_height+5, cell_width-10, cell_height-10);
                cells.push_back(src(cell_rect));
            }
        } 
        return cells;
    }

    std::vector<int> ocr_sudoku_cells(std::vector<cv::Mat>& cells) {
        std::vector<int> numbers;

        cv::Mat sample;
        cv::Mat response, tmp;
        cv::FileStorage Data("TrainingData.yml", cv::FileStorage::READ);
        Data["data"] >> sample;
        Data.release();

        cv::FileStorage Label("LabelData.yml", cv::FileStorage::READ);
        Label["label"] >> response;
        Label.release();

        auto knn = cv::ml::KNearest::create();
        knn->train(sample, cv::ml::ROW_SAMPLE, response);

        for (auto& cell: cells) {
            std::vector<std::vector<cv::Point>> contours;
            std::vector<cv::Vec4i> hierarchy;
            cv::Mat thr, gray, empty;
            cv::cvtColor(cell, gray, cv::COLOR_BGR2GRAY);
            cv::threshold(gray, thr, 200, 255, cv::THRESH_BINARY_INV);

            if (cv::countNonZero(thr) < 1) {
                std::cout << "0 ";
                numbers.push_back(0);
                continue;
            }

            cv::findContours(thr, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
            auto index = get_max_area_contour_id(contours);
            cv::Rect r = cv::boundingRect(contours[index]);
            cv::Mat ROI = thr(r); 
            cv::Mat tmp1, tmp2;
            cv::resize(ROI, tmp1, cv::Size(10, 10), 0, 0, cv::INTER_LINEAR);
            tmp1.convertTo(tmp2, CV_32FC1);
            float p = knn->findNearest(tmp2.reshape(1, 1), 1, empty);
            std::cout << (int)p << " ";  
            numbers.push_back((int)p);
        }

        return numbers;
    }
}

void get_board_from_image(const std::string& image_path, board& b) {
    cv::Mat src = cv::imread(image_path);

#ifdef SUDOKU_OPENCV_DEBUG_ON
    cv::imshow("Debug", src);
    cv::waitKey(0);
#endif

    if (src.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return;
    }
    cv::Mat gray_scale = gray_scale_and_blur(src);
#ifdef SUDOKU_OPENCV_DEBUG_ON
    cv::imshow("Debug", gray_scale);
    cv::waitKey(0);
#endif
    auto contours = find_contours(gray_scale);
    auto largest_index = get_max_area_contour_id(contours);
    auto brd = warp_sudoku_board_to_fill_screen(src, contours[largest_index]);

#ifdef SUDOKU_OPENCV_DEBUG_ON
    cv::Mat contour_src;
    src.copyTo(contour_src);
    cv::drawContours(contour_src, contours, -1, cv::Scalar(0,0,255), 8, 8);
    cv::imshow("Debug", contour_src);
    cv::waitKey(0);

    src.copyTo(contour_src);
    cv::drawContours(contour_src, contours, largest_index, cv::Scalar(0,0,255), 8, 8);
    cv::imshow("Debug", contour_src);
    cv::waitKey(0);

    cv::imshow("Debug", brd);
    cv::waitKey(0);
#endif

#ifndef SUDOKU_OPENCV_DEBUG_ON
    auto cells = make_9_by_9_grid(brd);
    auto numbers = ocr_sudoku_cells(cells);
    b.fill(numbers);
#endif
}
