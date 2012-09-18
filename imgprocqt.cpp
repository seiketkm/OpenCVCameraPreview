#include "imgprocqt.h"
#include "Labeling.h"
// Labeling.h使用
// http://oshiro.bpe.es.osaka-u.ac.jp/people/staff/imura/products/labeling

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

void ImgProcQt::detectCard(cv::Mat& bgrImg){
    // 画面の中の明るい部分(カードは明るいはず)を抽出するためにHSVへ変換
    cv::Mat hsvImg;
    cv::vector<cv::Mat> splited(3);
    cv::cvtColor(bgrImg, hsvImg, CV_BGR2HSV);
    cv::split(hsvImg, splited);

    //　2値化
    cv::Mat binImg;
    cv::threshold(splited[2], binImg, 128, 255, CV_THRESH_BINARY);

    //Labeling
    cv::Mat rImg(binImg.size(), CV_16SC1);
    LabelingBS	labeling;
    labeling.Exec(binImg.data, (short *)rImg.data, binImg.cols, binImg.rows, true, 10);
    // カードのエリアを取得
    cv::Mat cardImg;
    cv::compare(rImg, 1, cardImg, CV_CMP_EQ);
    //　1箇所だけの輪郭を取得
    cv::vector<cv::vector<cv::Point2i> > contours;
    cv::findContours(cardImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1);

    // ラベリング時点で1つしか輪郭が取れないことが保障されている。はず。
    cv::drawContours(bgrImg, contours, 0, CV_RGB(0,255,0), 1);

    // 輪郭上の4点でよければ中央から左上右上左下右下で一番遠い点を採用すればいい。
    //　輪郭線の外側に囲む線が必要ならもうひとつ考える必要ある。
