#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cap = new cv::VideoCapture(CV_CAP_ANY);
    if(!cap->isOpened())
    {
        QMessageBox msgbox;
        msgbox.setWindowTitle(tr("error"));
        msgbox.setText(tr("can't open camera device"));
        msgbox.exec();
    }

    timer = new QTimer();
    timer->setInterval(30);
    timer->start();

    imgprocQt = new ImgProcQt(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(VideoUpdate()));
}
void MainWindow::resizeEvent(QResizeEvent *resizeEvent)
{
    QMainWindow::resizeEvent(resizeEvent);
}

void MainWindow::VideoUpdate()
{
    if(cap->isOpened())
    {
        cv::Mat capImg;
        cap->retrieve(capImg);
        if(ui->ModeNormal->isChecked())
            ;
        else if(ui->ModeGray->isChecked())
            imgprocQt->cvCvtRGB2GRAY(capImg);
        else if(ui->ModeCanny->isChecked())
            imgprocQt->cvCanny(capImg,100,200);//FIX
        PreviewUpdate(capImg);
    }
}

void MainWindow::PreviewUpdate(cv::Mat& bgrImg) const
{
    cv::Mat rgbImg;
    cv::cvtColor(bgrImg, rgbImg, CV_BGR2RGB);
    QImage qimg(rgbImg.data, rgbImg.cols, rgbImg.rows, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qimg);
    ui->Preview->setPixmap(pixmap);
    // preview—Ìˆæ‚ÌƒŠƒTƒCƒY
    ui->Preview->setGeometry(0,0,pixmap.width(),pixmap.height());
}

MainWindow::~MainWindow()
{
    cap->release();
    delete ui;
}
