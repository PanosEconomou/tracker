/*************************************
-------------- HUE MENU --------------
╦╔╦╗╔═╗╦  ╔═╗╔╦╗╔═╗╔╗╔╔╦╗╔═╗╔╦╗╦╔═╗╔╗╔
║║║║╠═╝║  ║╣ ║║║║╣ ║║║ ║ ╠═╣ ║ ║║ ║║║║
╩╩ ╩╩  ╩═╝╚═╝╩ ╩╚═╝╝╚╝ ╩ ╩ ╩ ╩ ╩╚═╝╝╚╝
*************************************/

#include "hueMenu.hpp"

HueMenu::HueMenu(string windowName, Mat frame, int hueLow, int hueHigh, int satLow, int satHigh, int valLow, int valHigh){

    // Set Class variables
    this->windowName    = windowName;
    this->hueLow        = hueLow;
    this->hueHigh       = hueHigh;
    this->satLow        = satLow;
    this->satHigh       = satHigh;
    this->valLow        = valLow;
    this->valHigh       = valHigh;
    this->frame         = frame;

    // Start the window
    namedWindow(windowName,WINDOW_AUTOSIZE);

    // Add the sliders
    TrackbarData hueLowData  = { &(this->hueLow),  this};
    createTrackbar("Low  Hue   ", windowName, nullptr, 179, onTrackbar, &hueLowData);
    setTrackbarPos("Low  Hue   ", windowName, hueLow);

    TrackbarData hueHighData = { &(this->hueHigh), this};
    createTrackbar("High Hue   ", windowName, nullptr, 179, onTrackbar, &hueHighData);
    setTrackbarPos("High Hue   ", windowName, hueHigh);

    TrackbarData satLowData  = { &(this->satLow),  this};
    createTrackbar("Low  Sat   ", windowName, nullptr, 255, onTrackbar, &satLowData);
    setTrackbarPos("Low  Sat   ", windowName, satLow);

    TrackbarData satHighData = { &(this->satHigh), this};
    createTrackbar("High Sat   ", windowName, nullptr, 255, onTrackbar, &satHighData);
    setTrackbarPos("High Sat   ", windowName, satHigh);

    TrackbarData valLowData  = { &(this->valLow),  this};
    createTrackbar("Low  Value ", windowName, nullptr, 255, onTrackbar, &valLowData);
    setTrackbarPos("Low  Value ", windowName, valLow);

    TrackbarData valHighData = { &(this->valHigh), this};
    createTrackbar("High Value ", windowName, nullptr, 255, onTrackbar, &valHighData);
    setTrackbarPos("High Value ", windowName, valHigh);
}

HueMenu::HueMenu(){
    HueMenu("Hue Selection Menu");
}

HueMenu::HueMenu(Mat frame){
    HueMenu("Hue Selection Menu", frame);
}

HueMenu::HueMenu(string windowName){
    Mat frame;
    HueMenu(windowName, frame);
}

HueMenu::HueMenu(string windowName, Mat frame){
    HueMenu(windowName, frame, 0, 179, 0, 255, 0, 255);
}

HueMenu::~HueMenu() = default;

// Callback function for the trackbar Edits the frame
void HueMenu::onTrackbar(int value, void* params){
    // Extract the data from the stupid void* pointer
    TrackbarData* data = static_cast<TrackbarData*>(params);

    // Skip if you got no picture
    // std::cout << data->menu->getFrame() << endl;

    // Save the value to the designated variable
    if (data->variable != nullptr) *(data->variable) = value;

    // Clip the frame according to the HSV parameters set so far
    Mat imgHSV, mask, adjusted;
    if (!data->menu->getFrame().empty()){
        cvtColor(data->menu->getFrame(),imgHSV,COLOR_BGR2HSV);                           // Convert Color to HSV
        inRange(imgHSV,data->menu->getLowScalar(),data->menu->getHighScalar(),mask);        // Create a Clipping Mask
        imgHSV.setTo(Scalar(0,0,0),mask);
        cvtColor(imgHSV,adjusted,COLOR_HSV2BGR);
    
        // Display the image
        imshow("Capture",adjusted);
        waitKey(1);
    }
}