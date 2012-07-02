#ifndef IMGPROCQT_H
#define IMGPROCQT_H

#include <QObject>
#include <opencv2/imgproc/imgproc.hpp>
class ImgProcQt : public QObject
{
    Q_OBJECT
public:
    explicit ImgProcQt(QObject *parent = 0);
    void cvCvtRGB2GRAY(cv::Mat&);
    void cvCanny(cv::Mat&, double th1, double th2);
signals:
    
public slots:
    
};

#endif // IMGPROCQT_H
