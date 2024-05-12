#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::string path_to_images = "C:\\Data\\vs coding\\HelloCV\\HelloCV\\tree images"; // 이미지 폴더 경로
    std::string output_video_path = "C:\\Data\\vs coding\\HelloCV\\HelloCV\\tree_video.avi"; // 출력 동영상 파일 경로
    std::vector<cv::Mat> images;

    // 이미지 파일 읽기
    for (const auto& entry : fs::directory_iterator(path_to_images)) {
        cv::Mat img = cv::imread(entry.path().string());
        if (img.empty()) {
            std::cout << "Could not open or find the image: " << entry.path() << std::endl;
            continue;
        }
        images.push_back(img);
    }

    // 이미지 시퀀스가 비어 있지 않은지 확인
    if (images.empty()) {
        std::cout << "No images found in the directory." << std::endl;
        return -1;
    }

    // 동영상 작성자 생성
    cv::Size frame_size = images[0].size();
    int fps = 30; // 프레임레이트
    cv::VideoWriter video(output_video_path, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame_size, true);

    // 이미지를 동영상으로 저장
    for (const auto& img : images) {
        video.write(img);
    }

    video.release(); // 비디오 작성자 해제
    std::cout << "Video written successfully." << std::endl;
    return 0;
}