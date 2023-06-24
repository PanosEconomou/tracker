#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <iostream>
using namespace std;


// View Webcam!
int main(){

    // Start a video capture object on camera 0
    VideoCapture cap(0);

    // The image object
    Mat img;
    Mat imgGrey, imgBlur, imgCanny;

    while (true){
        //Read the camera frame into the image
        cap.read(img);

        //Convert the color to grey
        cvtColor(img,imgGrey,COLOR_BGR2GRAY);

        // Get a blured image too
        GaussianBlur(img,imgBlur,Size(11,11),3,0);

        //Get the edges
        Canny(img,imgCanny,50,150);

        // Display the image
        imshow("Camera of Pano",img);
        imshow("Grey Camera of Pano",imgCanny);

        waitKey(1);
    }

    return 0;
}