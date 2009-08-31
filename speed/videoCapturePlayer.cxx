/*
Should be able to compile with:
g++ -Wall `pkg-config --cflags opencv` `pkg-config --libs opencv` -o VCP videoCapturePlayer.cxx
*/

#include <string>
#include <iostream>

#include "cv.h"
#include "highgui.h"

#include "videoCapturePlayer.h"

#define WINDOW_TITLE "Video Aquisition" 

using namespace std;


VideoCapturePlayer::VideoCapturePlayer( CvMat *( *processFunction)(CvMat *), int device, bool show ) 
:show(show), device(device)
{
    processFunc = processFunction;
}
    
VideoCapturePlayer::~VideoCapturePlayer()
{
    /* free memory */
    cvReleaseCapture( &capture );
    cvDestroyWindow( WINDOW_TITLE );
}

void VideoCapturePlayer::init()
{
    /* Try load a webcam */
    capture = cvCreateCameraCapture(device);
    
    /* always check that this worked! */
    if( !capture ){ 
        cout << "Couldn't create camera capture" << endl; 
    }
    
    /* get fps, needed to set the delay */
    fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );
    //fps /= 2;
    
    
    if(show){
        /* open the display window */
        cvNamedWindow( WINDOW_TITLE, CV_WINDOW_AUTOSIZE );
    }

    
}

void VideoCapturePlayer::main()
{
    while( key != 'q' ) {
        
        /* get a frame - image should not be released or modified*/
        frame = cvQueryFrame( capture );
        
        /* Convert to a CvMat*/
        {
            CvMat temp_mat;
            mat_frame = cvGetMat( frame, &temp_mat);
        }
        /* always check */
        if( !frame ) break;
        
        if (processFunc)
        {
            mat_frame = processFunc(mat_frame);
        }
        
        /* display frame */
        if(show)
        {
            cvShowImage( WINDOW_TITLE, mat_frame );
        }
        
        /* quit if user press 'q' */
        key = cvWaitKey( 1 /*1000 / fps*/ );
    }

}



/**
 This is a template for a function that can be fed into VideoCapturePlayer
 It must take a CvMat, and return a CvMat
 */
CvMat * doNothing(CvMat *x)
{
    ///*
    CvPoint pt1, pt2;
    pt1.x = pt1.y = 200;
    pt2.x = pt2.y = 250;
    
    cvRectangle( x, pt1, pt2, CV_RGB(30,0,200) );
    //*/
    return x;
} 

int main( int argc, char** argv )
{
        
    VideoCapturePlayer vcp = VideoCapturePlayer(&doNothing);
    //VideoCapturePlayer vcp = VideoCapturePlayer();
    vcp.init();
    vcp.main();
    
    return 0;
}
