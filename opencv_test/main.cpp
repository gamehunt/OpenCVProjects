#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int main(int argc, char* argv[])
{
        // получаем любую подключённую камеру
        CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY); //cvCaptureFromCAM( 0 );
        assert( capture );
        IplImage* frame=0;

        cvNamedWindow("capture", CV_WINDOW_AUTOSIZE);
        int mode = 0;
        std::cin>>mode;
        while(true){

                frame = cvQueryFrame( capture );
                if(mode == 0){
                IplImage* gray = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                IplImage* binary = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                IplImage* cpy = cvCloneImage(frame);
                CvMemStorage* s = cvCreateMemStorage();
                CvSeq* cont = 0;
                CvScalar color(255,255,255);
                CvScalar color1(0,0,0);
                cvCvtColor(frame,gray,CV_RGB2GRAY);
                cvInRangeS(gray, cvScalar(40), cvScalar(150), binary);
                cvFindContours(binary,s,&cont,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
                for(CvSeq* seq0 = cont;seq0!=0;seq0 = seq0->h_next){
                    cvDrawContours(cpy, seq0, CV_RGB(255,216,0), CV_RGB(0,0,250), 0, 1, 8);
                }

                cvShowImage("capture", cpy);
                } else if(mode == 1){
                    IplImage* edges = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                    cvCvtColor(frame, edges, CV_BGR2GRAY);
                    cvSmooth(edges,edges,CV_GAUSSIAN,7,7,1.5,1.5);
                    cvCanny(edges, edges, 0, 30, 3);
                    cvShowImage("capture", edges);
                }else if (mode == 2){
                    IplImage* gray = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                    IplImage* binary = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                    cvCvtColor(frame,gray,CV_RGB2GRAY);
                    cvInRangeS(gray, cvScalar(40), cvScalar(150), binary);
                    cvShowImage("capture", binary);
                }else if (mode == 3){
                    IplImage* gray = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                    IplImage* binary = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
                    CvMemStorage* s = cvCreateMemStorage();
                    CvSeq* cont = 0;
                    cvCvtColor(frame,gray,CV_RGB2GRAY);
                    cvInRangeS(gray, cvScalar(40), cvScalar(150), binary);
                    cvFindContours(binary,s,&cont,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE,cvPoint(0,0));
                    cvShowImage("capture", binary);
                }else if (mode == 4){
                    IplImage* neg = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,3);
                    cvNot(frame,neg);
                    cvShowImage("capture",neg);
                }

                char c = cvWaitKey(33);
                if (c == 27) { // нажата ESC
                        break;
                }
        }
        // освобождаем ресурсы
        cvReleaseCapture( &capture );
        cvDestroyWindow("capture");
        return 0;
}

