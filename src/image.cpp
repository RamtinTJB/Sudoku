#include "image.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace {
    cv::Mat gray_scale_and_blur(cv::Mat& src) {
        cv::Mat output;
        cv::cvtColor(src, output, cv::COLOR_BGR2GRAY);
        cv::blur(output, output, cv::Size(3, 3));
        return output;
    }

    std::vector<std::vector<cv::Point>> find_contours(cv::Mat& src) {
        cv::Mat canny_output;
        cv::Canny(src, canny_output, 255/3, 255);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        return contours;
    }

    int get_max_area_contour_id(std::vector<std::vector<cv::Point>> contours) {
        double maxArea = 0;
        int contour_id = -1;
        for (int j = 0; j < contours.size(); ++j) {
            double newArea = cv::contourArea(contours[j]);
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
                cv::Rect cell_rect(col*cell_width, row*cell_height, cell_width, cell_height);
                cells.push_back(src(cell_rect));
            }
        } 
        return cells;
    }

    int ocr_sudoku_cell(cv::Mat& cell) {

    }
}

void get_board_from_image(const std::string& image_path) {
    cv::Mat src = cv::imread(image_path);
    if (src.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return;
    }
    cv::Mat gray_scale = gray_scale_and_blur(src);
    auto contours = find_contours(gray_scale);
    auto largest_index = get_max_area_contour_id(contours);
    auto board = warp_sudoku_board_to_fill_screen(src, contours[largest_index]);
    auto cells = make_9_by_9_grid(board);

    const char* source_window = "Source";
    imshow(source_window, board);
    for (int i = 0; i < 9; i++) {
        std::string window_title = "Cell " + std::to_string(i);
        imshow(window_title.c_str(), cells[i]);
    }
}
