#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>

using namespace std;
using namespace cv;


void createTracker(string *trackerType, Ptr<cv::legacy::Tracker> *tracker){
    if (*trackerType == "KCF"){
        *tracker = legacy::TrackerKCF::create();
    }
    else if (*trackerType == "TLD"){
        *tracker = legacy::TrackerTLD::create();
    }
    else if (*trackerType == "BOOSTING"){
        *tracker = legacy::TrackerBoosting::create();
    }
    else if (*trackerType == "MEDIANFLOW"){
        *tracker = legacy::TrackerMedianFlow::create();
    }
    else if (*trackerType == "MOSSE"){
        *tracker = legacy::TrackerMOSSE::create();
    }
    else if (*trackerType == "CSRT"){
        *tracker = legacy::TrackerCSRT::create();
    }
    else{
        cout << "\nDesteklenmeyen tracker, varsayilan tracker kullaniliyor.\n" << endl;
        *trackerType = "MEDIANFLOW";
        *tracker = legacy::TrackerMedianFlow::create();
    }
}

int main(int argc, char** argv){
    bool cameraOn = true;
    string trackerType = "KCF";
    char* video_input = (char*) "0";
    
    // Argumanlarin ayristirilmasi edilmesi.
    for (int idx = 2; idx < argc; idx+=2){
        if(strcmp("-v", argv[idx-1]) == 0){
            video_input = argv[idx];
            cameraOn = false;
        }
        else if(strcmp("-c", argv[idx-1]) == 0){
            video_input = argv[idx];
            cameraOn = true;
        }
        else if(strcmp("-t", argv[idx-1]) == 0){
            trackerType = argv[idx];
        }
        else{
            continue;
        }
    }

    // Goruntunun acilmasi ve ilk frame'in okunmasi.
    VideoCapture *cap;
    Mat frame;
    if(cameraOn){
        unsigned short camIdx = atoi(video_input);
        cap = new cv::VideoCapture(camIdx);
    }
    else{
        cap = new cv::VideoCapture(video_input);
    }
    cap->read(frame);
    
    // Takip algoritmasinin yuklenmesi.
    Ptr<cv::legacy::Tracker> tracker;
    createTracker(&trackerType, &tracker);

    // Takip algoritmasinin ilk frame icerisinden secilen nesne ile baslatilmasi.
    Rect2d rect = selectROI(frame);
    tracker->init(frame, rect);

    // Frame dongusu.
    while(cap->read(frame)){
        // Takip edilen nesnenin yeni konumunun guncellenmesi.
        bool status = tracker->update(frame, rect);

        // Takip edilen nesnenin yeni konumunun cizdirilmesi.
        if (status){
            rectangle(frame, rect, Scalar(255, 0, 0), 3, 1);
        }
        else{
            putText(frame, "Nesne Kaybedildi!", Point(20, frame.size[0]-20), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2);
        }

        // Takip algoritmasinin frame'e yazdirilmasi.
        putText(frame, trackerType, Point(0, 30), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 0), 2);

        // Frame'in gosterilmesi.
        imshow("Takip_Uygulamasi", frame);

        // ESC tusunun cikis olarak belirlenmesi..
        if (waitKey(1) == 27) 
            break;
    }
    
    return 0;
}