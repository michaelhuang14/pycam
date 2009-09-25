/*
 *      blur_opencv.cxx
 *      
 *      Copyright 2009 Brian Thorne <brian.thorne@canterbury.ac.nz>
 * 
 *      Compile with:
 * 
 * 
 * 
 *  
 */


#include <iostream>
#include "videoCapturePlayer.h"

CvMat * gaussianBlur(CvMat *x)
{
    // Filter with gaussian smoothing
    int filterSize = 43;
    cvSmooth(x, x,CV_GAUSSIAN, filterSize, 0, 6.949999999999999);
    return x;
}

bool test_guassian_blur()
{
    std::cout << "Testing Median Blur C++ function" << std::endl;
    CvMat temp;
    CvMat *i = cvGetMat( cvLoadImage("/usr/share/doc/opencv-doc/examples/c/lena.jpg"), &temp );
    CvMat *blurred_image = gaussianBlur(i);
    cvSaveImage("blurred_imag_cpp_opencv_gaussian.jpg", blurred_image);
    return true;
}

int main( int argc, char** argv )
{
    if(argc > 1){
        test_guassian_blur();
    } else {
        std::cout << "Starting Gassian Blur C++ demo" << std::endl;
        std::cout << "Press 'q' to exit the program" << std::endl;
        VideoCapturePlayer vcp = VideoCapturePlayer(&gaussianBlur);
        vcp.init(); vcp.main();
    }
    return 0;
}
