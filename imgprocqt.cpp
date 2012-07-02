#include "imgprocqt.h"

ImgProcQt::ImgProcQt(QObject *parent) :
    QObject(parent)
{

}

void ImgProcQt::cvCvtRGB2GRAY(cv::Mat& bgrImg)
{
    cv::Mat grayImg;
    cv::cvtColor(bgrImg, grayImg, CV_RGB2GRAY);
    cv::cvtColor(grayImg, bgrImg, CV_GRAY2RGB);
}

void ImgProcQt::cvCanny(cv::Mat& bgrImg, double th1, double th2)
{
    cv::Mat cannyImg;
    cv::Canny(bgrImg, cannyImg, th1, th2);
    cv::cvtColor(cannyImg, bgrImg, CV_GRAY2RGB);
}
