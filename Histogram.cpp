#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
   
    VideoCapture cap(1);
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); 
        return -1;
    }

    String windowNameOfOriginalImage = "Original Video";
    String windowNameOfHistogramEqualized = "Histogram Equalized Video";

    namedWindow(windowNameOfOriginalImage, WINDOW_NORMAL);
    namedWindow(windowNameOfHistogramEqualized, WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // Read a new frame from the video file 

        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }
        
        Mat hist_equalized_image;
        cvtColor(frame, hist_equalized_image, COLOR_BGR2YCrCb);
        
        vector<Mat> vec_channels;
        split(hist_equalized_image, vec_channels);

        equalizeHist(vec_channels[0], vec_channels[0]);


        merge(vec_channels, hist_equalized_image);

        cvtColor(hist_equalized_image, hist_equalized_image, COLOR_YCrCb2BGR);

        imshow(windowNameOfOriginalImage, frame);
        imshow(windowNameOfHistogramEqualized, hist_equalized_image);

        if (waitKey(5) == 27)
        {
            cout << "Esc key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }

    destroyAllWindows(); //Destroy all opened windows

    return 0;

}
