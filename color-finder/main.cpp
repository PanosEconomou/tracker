#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <iostream>
using namespace std;

#include "hueMenu.hpp"

int main(){

    // Start a video capture on the camera
    VideoCapture capture(0);

    // Image objects to hold the frames
    Mat img;

    // Read the first frame into img to properly instantiate
    capture.read(img);

    // HUE AND SATURATION PARAMS
    HueMenu* menu = new HueMenu(&capture);
    TrackbarData empty_data = {nullptr, menu};

    while(true){

        // Create a window for viewing then
        namedWindow("Capture",WINDOW_AUTOSIZE);

        // Apply the Hue Corrections to the frame
        HueMenu::onTrackbar(-1,&empty_data);

        // Wait a bit to not explode
        waitKey(1);
    }

    return 0;
}