#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qtimer>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <imgprocqt.h>

#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void VideoUpdate();
    void resizeEvent(QResizeEvent *);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    void PreviewUpdate(cv::Mat& bgrImg) const;

    QTimer* timer;
    cv::VideoCapture* cap;
    ImgProcQt* imgprocQt;
};

#endif // MAINWINDOW_H
