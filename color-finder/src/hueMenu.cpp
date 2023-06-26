/*************************************
-------------- HUE MENU --------------
╦╔╦╗╔═╗╦  ╔═╗╔╦╗╔═╗╔╗╔╔╦╗╔═╗╔╦╗╦╔═╗╔╗╔
║║║║╠═╝║  ║╣ ║║║║╣ ║║║ ║ ╠═╣ ║ ║║ ║║║║
╩╩ ╩╩  ╩═╝╚═╝╩ ╩╚═╝╝╚╝ ╩ ╩ ╩ ╩ ╩╚═╝╝╚╝
*************************************/

#include "hueMenu.hpp"


HueMenu::HueMenu(){
    construct("Hue Menu", nullptr,0,179,0,255,0,255);
}

HueMenu::HueMenu(VideoCapture* capture, string fwindowName, int fhueLow, int fhueHigh, int fsatLow, int fsatHigh, int fvalLow, int fvalHigh){
    construct(fwindowName, capture, fhueLow, fhueHigh, fsatLow, fsatHigh, fvalLow, fvalHigh);
}

HueMenu::~HueMenu(){}

void HueMenu::construct(string fwindowName, VideoCapture* fcapture, int fhueLow, int fhueHigh, int fsatLow, int fsatHigh, int fvalLow, int fvalHigh){
    // Set Class variables
    windowName    = fwindowName;
    hueLow        = fhueLow;
    hueHigh       = fhueHigh;
    satLow        = fsatLow;
    satHigh       = fsatHigh;
    valLow        = fvalLow;
    valHigh       = fvalHigh;
    capture       = fcapture;

    //Create the menu
    createTrackbars();
}

void HueMenu::createTrackbars(){
    // Initialize the data for each trackbar
    TrackbarData* trackbarData = new TrackbarData[6];

    // Start the window
    namedWindow(windowName,WINDOW_AUTOSIZE);

    // Add the sliders
    trackbarData[0] = { &hueLow,  this};
    createTrackbar("Low  Hue   ", windowName, nullptr, 179, &HueMenu::onTrackbar, &(trackbarData[0]));
    setTrackbarPos("Low  Hue   ", windowName, hueLow);

    trackbarData[1] = { &hueHigh, this};
    createTrackbar("High Hue   ", windowName, nullptr, 179, &HueMenu::onTrackbar, &(trackbarData[1]));
    setTrackbarPos("High Hue   ", windowName, hueHigh);

    trackbarData[2] = { &(this->satLow),  this};
    createTrackbar("Low  Sat   ", windowName, nullptr, 255, &HueMenu::onTrackbar, &(trackbarData[2]));
    setTrackbarPos("Low  Sat   ", windowName, satLow);

    trackbarData[3] = { &satHigh, this};
    createTrackbar("High Sat   ", windowName, nullptr, 255, &HueMenu::onTrackbar, &(trackbarData[3]));
    setTrackbarPos("High Sat   ", windowName, satHigh);

    trackbarData[4] = { &valLow,  this};
    createTrackbar("Low  Value ", windowName, nullptr, 255, &HueMenu::onTrackbar, &(trackbarData[4]));
    setTrackbarPos("Low  Value ", windowName, valLow);

    trackbarData[5] = { &valHigh, this};
    createTrackbar("High Value ", windowName, nullptr, 255, &HueMenu::onTrackbar, &(trackbarData[5]));
    setTrackbarPos("High Value ", windowName, valHigh);
}

// Callback function for the trackbar Edits the frame
void HueMenu::onTrackbar(int value, void* params){
    // Extract the data from the stupid void* pointer
    TrackbarData* data = static_cast<TrackbarData*>(params);

    // Save the value to the designated variable
    if (data->variable != nullptr) *(data->variable) = value;

    // Get the frame
    Mat img, hsv, blur, mask, adjusted;
    vector<vector<Point>> contours;
    data->menu->getCapture()->read(img);

    // Clip the frame according to the HSV parameters set so far
    if (!img.empty()){
        cvtColor(img,hsv,COLOR_BGR2HSV);                                                 // Convert Color to HSV
        GaussianBlur(hsv, blur, Size(13,13), 7, 7);
        inRange(blur,data->menu->getLowScalar(),data->menu->getHighScalar(),mask);        // Create a Clipping Mask
        img.copyTo(adjusted,mask);                                                          // Apply the mask
        findContours(mask,contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

        for (const auto& contour : contours) {
            Rect boundingBox = boundingRect(contour);

            // Access bounding box coordinates
            int x = boundingBox.x;
            int y = boundingBox.y;
            int width = boundingBox.width;
            int height = boundingBox.height;

            // Draw the bounding box on the original image (optional)
            rectangle(adjusted, boundingBox, cv::Scalar(0, 255, 0), 2);
        }

        // Display the image
        imshow("Capture",adjusted);
    }
}