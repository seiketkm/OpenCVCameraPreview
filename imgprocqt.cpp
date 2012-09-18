#include "imgprocqt.h"
#include "Labeling.h"
// Labeling.h�g�p
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
    // ��ʂ̒��̖��邢����(�J�[�h�͖��邢�͂�)�𒊏o���邽�߂�HSV�֕ϊ�
    cv::Mat hsvImg;
    cv::vector<cv::Mat> splited(3);
    cv::cvtColor(bgrImg, hsvImg, CV_BGR2HSV);
    cv::split(hsvImg, splited);

    //�@2�l��
    cv::Mat binImg;
    cv::threshold(splited[2], binImg, 128, 255, CV_THRESH_BINARY);

    //Labeling
    cv::Mat rImg(binImg.size(), CV_16SC1);
    LabelingBS	labeling;
    labeling.Exec(binImg.data, (short *)rImg.data, binImg.cols, binImg.rows, true, 10);
    // �J�[�h�̃G���A���擾
    cv::Mat cardImg;
    cv::compare(rImg, 1, cardImg, CV_CMP_EQ);
    //�@1�ӏ������̗֊s���擾
    cv::vector<cv::vector<cv::Point2i> > contours;
    cv::findContours(cardImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_L1);

    // ���x�����O���_��1�����֊s�����Ȃ����Ƃ��ۏႳ��Ă���B�͂��B
    cv::drawContours(bgrImg, contours, 0, CV_RGB(0,255,0), 1);

    // �֊s���4�_�ł悯��Β������獶��E�㍶���E���ň�ԉ����_���̗p����΂����B
    //�@�֊s���̊O���Ɉ͂ސ����K�v�Ȃ�����ЂƂl����K�v����B
