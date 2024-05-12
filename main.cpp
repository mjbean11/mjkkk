#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string path_to_images = "C:\\Data\\vs coding\\HelloCV\\HelloCV\\tree images"; // �̹��� ���� ���
    std::string output_video_path = "C:\\Data\\vs coding\\HelloCV\\HelloCV\\tree_video.avi"; // ��� ������ ���� ���
    std::vector<cv::Mat> images;

    // �̹��� ���� �б�
    for (const auto& entry : fs::directory_iterator(path_to_images)) {
        cv::Mat img = cv::imread(entry.path().string());
        if (img.empty()) {
            std::cout << "Could not open or find the image: " << entry.path() << std::endl;
            continue;
        }
        images.push_back(img);
    }

    // �̹��� �������� ��� ���� ������ Ȯ��
    if (images.empty()) {
        std::cout << "No images found in the directory." << std::endl;
        return -1;
    }

    // ������ �ۼ��� ����
    cv::Size frame_size = images[0].size();
    int fps = 30; // �����ӷ���Ʈ
    cv::VideoWriter video(output_video_path, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame_size, true);

    // �̹����� ���������� ����
    for (const auto& img : images) {
        video.write(img);
    }

    video.release(); // ���� �ۼ��� ����
    std::cout << "Video written successfully." << std::endl;
    return 0;
}