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
    HueMenu* menu           = new HueMenu(img); // We pass the frame as a parameter
    TrackbarData empty_data = {nullptr, menu};
    

    while(true){

        // Read the next frame into img
        capture.read(img);
        menu->setFrame(img);

        //Apply the Hue Corrections to the frame
        menu->onTrackbar(-1,&empty_data);

        // Display the image
        // imshow("Capture",img);

        // Wait a bit to not explode
        waitKey(1);
    }

    return 0;
}


