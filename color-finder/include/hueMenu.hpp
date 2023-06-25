/***************************************************************

Generates a window with a scrollbars that one can use to adjust 
the hue saturation and other parameters

┌─┐┌─┐┌┐┌┌─┐
├─┘├─┤││││ │
┴  ┴ ┴┘└┘└─┘
***************************************************************/

#ifndef HUE_MENU
#define HUE_MENU

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

#include <iostream>
using namespace std;

class HueMenu {

    public:
        HueMenu();
        HueMenu(Mat frame);
        HueMenu(string windowName);
        HueMenu(string windowName, Mat frame);
        HueMenu(string windowName, Mat frame, int hueLow, int hueHigh, int satLow, int satHigh, int valLow, int valHigh);
        ~HueMenu();

        int     getHueLow()          {return hueLow;}
        int     getHueHigh()         {return hueHigh;}
        int     getSatLow()          {return satLow;}
        int     getSatHigh()         {return satHigh;}
        int     getValLow()          {return valLow;}
        int     getValHigh()         {return valHigh;}
        Scalar  getLowScalar()       {return Scalar(hueLow,  satLow,  valLow);}
        Scalar  getHighScalar()      {return Scalar(hueHigh, satHigh, valHigh);}
        Mat     getFrame()           {return frame;}

        void    setHueLow(int low)   {hueLow  = low;}
        void    setHueHigh(int high) {hueHigh = high;}
        void    setSatLow(int low)   {satLow  = low;}
        void    setSatHigh(int high) {satHigh = high;}
        void    setValLow(int low)   {valLow  = low;}
        void    setValHigh(int high) {valHigh = high;}
        void    setFrame(Mat frame)  {this->frame = frame;}

        // Updates the frame using the corresponding HSV clipping
        static void onTrackbar(int value, void* params);

    private:
        int     hueLow;
        int     hueHigh;
        int     satLow;
        int     satHigh;
        int     valLow;
        int     valHigh;
        Mat     frame;
        string  windowName;
};

// A struct to store the data passed on each trackbar call
struct TrackbarData {
    int* variable;
    HueMenu* menu;
};

#endif