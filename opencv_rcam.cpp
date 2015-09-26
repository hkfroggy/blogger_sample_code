/**
 * @file   main.cpp
 * 
 * @author Richard
 * @date   27/9/2015
 * 
 * $Revision: 0.1 $
 * 
 */


#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
    time_t timer_begin, timer_end;
    raspicam::RaspiCam_Cv Camera;

    Mat image;
    int nCount = 100;
    string wname = "uBot";

    // create a simple window to display the video
    namedWindow(wname, WINDOW_AUTOSIZE); // Create a window for display.

    //set camera params
    Camera.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    //Open camera
    cout << "Opening Camera..." << endl;
    if (!Camera.open()) {
        cerr << "Error opening the camera" << endl;
        return -1;
    }

    //Start capture
    cout << "Capturing " << nCount << " frames ...." << endl;
    time(&timer_begin);

    for (int i = 0; i < nCount; i++) {
        Camera.grab();
        Camera.retrieve(image);
        imshow(wname, image);

        cout << "\r captured " << i << " images" << std::flush;
        waitKey(1);
    }
    cout << "Stop camera..." << endl;
    Camera.release();
    //show time statistics
    time(&timer_end); /* get current time; same as: timer = time(NULL)  */

    double secondsElapsed = difftime(timer_end, timer_begin);
    cout << secondsElapsed << " seconds for " << nCount << "  frames : FPS = " << (float) ((float) (nCount) / secondsElapsed) << endl;

    // save image 
    cv::imwrite("raspicam_cv_image.jpg", image);
    cout << "Image saved at raspicam_cv_image.jpg" << endl;

    waitKey(0);

}
