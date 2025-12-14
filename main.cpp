#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <cctype>


int brightness = 100;
int contrastValue = 100;
int saturationValue = 100;

void onBrightnessChange(int, void*){}
void onContrastChange(int, void*){}
void onSatuationChange(int, void*){}

cv::Mat applyAdjustments(const cv::Mat& frame, int brightness, int contrast, int saturation){
    int actualBrightness = brightness - 100;
    double actualConstrast = contrast/100.0;
    double actualSaturation = saturation / 100.0;

    cv::Mat result;
    
    frame.convertTo(result, -1, actualConstrast, actualBrightness);

    if(actualSaturation != 1.0){
        cv::Mat hsvImage;
        cv::cvtColor(result, hsvImage, cv::COLOR_BGR2HSV);

        std::vector<cv::Mat> hsvChannels;
        cv::split(hsvImage, hsvChannels);

        hsvChannels[1].convertTo(hsvChannels[1], -1, actualSaturation,0);

        cv::merge(hsvChannels, hsvImage);
        cv::cvtColor(hsvImage, result, cv::COLOR_HSV2BGR);
    }

    return result;
}

int main() {

    std::cout << "Enter file path and name" << std::endl;
    std::string filename;
    std::getline(std::cin, filename);
    if(filename.length() < 4){
        std::cout << "Invalid filename" << std::endl;
        return -1;
    }

    std::string extension = filename.substr(filename.length()-4);
    for (char& c : extension) {
        c = std::tolower(c);
    }
    if (extension != ".mp4") {
        std::cout << "Only accept mp4 file" << std::endl;
        return -1;
    }

    cv::VideoCapture cap(filename);
    if (!cap.isOpened()) {
        std::cout << "Error: Could not open video file" << std::endl;
        return -1;
    }

    double fps = cap.get(cv::CAP_PROP_FPS);
    int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    

    std::cout << "Video: " << width << "x" << height 
            << " @ " << fps << " fps" << std::endl;
    
    cv::Mat frame;
    cv::Mat lastframe;
    cv::Mat currentFrame;
    bool video_end_naturally = false;
    bool hasValidFrame = false;
    bool isPause = false;

    cv::namedWindow("Video Player", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("Brightness", "Video Player", &brightness, 200, onBrightnessChange);
    cv::createTrackbar("Constrast", "Video Player", &contrastValue, 200, onContrastChange);
    cv::createTrackbar("Saturation", "Video Player", &saturationValue, 200, onSatuationChange);

    std::cout << "Controls:" << std::endl;
    std::cout << "  SPACE - Pause/Resume" << std::endl;
    std::cout << "  Q/ESC - Exit" << std::endl;
    std::cout << "  Trackbar - Adjust brightness, constrast, saturation\n" << std::endl;
    
    while(true){

        if(!isPause){
            bool success = cap.read(frame);

            if(!success || frame.empty()){
                std::cout << "End of video" << std::endl;
                video_end_naturally = true;
                break;
            }

            frame.copyTo(currentFrame);
            hasValidFrame = true;
        }
        

        cv::Mat adjustedFrame = applyAdjustments(currentFrame, brightness, contrastValue, saturationValue);

        //lastframe = frame.clone();//save a copy of this frame

        //display the frame
        cv::imshow("Video Player", adjustedFrame);

        if(isPause){
            cv::Mat displayFrame = adjustedFrame.clone();
            cv::putText(displayFrame, "PAUSED", 
                        cv::Point(10,50), 
                        cv::FONT_HERSHEY_SIMPLEX,
                        1.5, 
                        cv::Scalar(0,255,255),
                        3);
            cv::imshow("Video Player", displayFrame);
        }else{
            cv::imshow("Video Player", adjustedFrame);
        }

        //wait for 30ms
        //If user presses 'q', exit
        char key = cv::waitKey(30);

        if(key == 32){
            isPause = !isPause;
            if(isPause){
                std::cout << "Paused - Edit, press SPACE to resume" << std::endl;
            }
            else{
                std::cout << "Resumed" << std::endl;
            }
        }
        else if(key == 'q' || key == 27){ //27 is the esc key
            break;
        }

        if(!isPause){
            adjustedFrame.copyTo(lastframe);
        }
    }
    if(video_end_naturally && !lastframe.empty()){
        std::cout << "Frozen on last frame. Adjust settings with trackbars. Press Q/ESC to exit." << std::endl;

        cv::Mat originalLastFrame = lastframe.clone();

        while(true){
            cv::Mat adjustedFrame = applyAdjustments(originalLastFrame, brightness, contrastValue, saturationValue);

            cv::imshow("Video Player", adjustedFrame);

            int key = cv::waitKey(100);
            if(key == 'q' || key == 'Q' || key == 27){
                std::cout << "Exiting ..." << std::endl;
                break;
            }
            if(cv::getWindowProperty("Video Player", cv::WND_PROP_VISIBLE)<1){
                break;
            }
        }
    }

    cap.release(); //close the video file
    cv::destroyAllWindows(); //close all opencv windows
    //cv::waitKey(1);

    return 0;
}