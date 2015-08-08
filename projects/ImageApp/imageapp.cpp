#include "imageapp.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtWidgets>

extern "C"{
#include <vl/generic.h>
#include <vl/slic.h>
}

/*https://github.com/bsdnoobz/opencv-code*/

ImageApp::ImageApp(QWidget *parent)
    : QWidget(parent)
{
    originalImage = cv::imread("/Users/willard/Pictures/Lenna.png");
    if (originalImage.data)
        cv::cvtColor(originalImage, originalImage, cv::COLOR_BGR2RGB);
    setupUi();
    showImage(originalImage);
}

ImageApp::~ImageApp(){
}

void ImageApp::setupUi(){
   imageLabel = new QLabel();
   originalButton = new QPushButton("打开图像");
   connect(originalButton, SIGNAL(clicked()), this, SLOT(doOpenImage()));
   //connect(originalButton, SIGNAL(clicked()), this, SLOT(showOriginalImage()));

   blurButton = new QPushButton("高斯模糊");
   connect(blurButton, SIGNAL(clicked()), this, SLOT(doGaussianBlur()));

   cannyButton = new QPushButton("边缘检测");
   connect(cannyButton, SIGNAL(clicked()), this, SLOT(doCanny()));

   slicButton = new QPushButton("超像素分割");
   connect(slicButton, SIGNAL(clicked()), this, SLOT(doSLIC()));

   quitButton = new QPushButton("退出");
   connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

   buttonsLayout = new QVBoxLayout();  // 实例化一个QVBoxLayout对象，用于放置各个按钮
   buttonsLayout->addWidget(originalButton);
   buttonsLayout->addWidget(blurButton);
   buttonsLayout->addWidget(cannyButton);
   buttonsLayout->addWidget(slicButton);
   buttonsLayout->addStretch();  //创建一个可伸缩的box
   buttonsLayout->addWidget(quitButton);

   mainLayout = new QHBoxLayout();
   mainLayout->addWidget(imageLabel);

   if (originalImage.data) {
       mainLayout->addLayout(buttonsLayout);
   }
   setLayout(mainLayout);
   setWindowTitle("图像处理小玩意");
}

/**
* open original image
*/
void ImageApp::doOpenImage(){
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Images"), QDir::currentPath(), tr("Image Files [ *.jpg , *.jpeg , *.bmp , *.png , *.gif]"));
    originalImage = cv::imread(imagePath.toStdString());
    if (imagePath.length() == 0)
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    if (originalImage.data)
        cv::cvtColor(originalImage, originalImage, cv::COLOR_BGR2RGB);
    showImage(originalImage);
}

/**
* Redraw original image
*/
void ImageApp::showOriginalImage()
{
   showImage(originalImage);
}

/**
* Perform Canny edge detection on original image and display the result
*/
void ImageApp::doCanny()
{
   cv::Mat gray;
   cv::cvtColor(originalImage, gray, cv::COLOR_RGB2GRAY);
   cv::Canny(gray, processedImage, 150, 150);
   cv::cvtColor(processedImage, processedImage, cv::COLOR_GRAY2RGB);
   showImage(processedImage);
}

/**
* Perform Gaussian blurring on original image and display the result
*/
void ImageApp::doGaussianBlur()
{
   cv::GaussianBlur(originalImage, processedImage, cv::Size(15, 15), 0, 0);
   showImage(processedImage);
}

/**
* Draw OpenCV matrix using QLabel
*/
void ImageApp::doSLIC()
{
    processedImage = originalImage; //浅拷贝
    //processedImage = originalImage.clone(); //深拷贝
    float* image = new float[processedImage.rows*processedImage.cols*processedImage.channels()];
    for (int i = 0; i < processedImage.rows; ++i) {
        for (int j = 0; j < processedImage.cols; ++j) {
            // Assuming three channels ...
            image[j + processedImage.cols*i + processedImage.cols*processedImage.rows*0] = processedImage.at<cv::Vec3b>(i, j)[0];
            image[j + processedImage.cols*i + processedImage.cols*processedImage.rows*1] = processedImage.at<cv::Vec3b>(i, j)[1];
            image[j + processedImage.cols*i + processedImage.cols*processedImage.rows*2] = processedImage.at<cv::Vec3b>(i, j)[2];
        }
    }

    // The algorithm will store the final segmentation in a one-dimensional array.
    vl_uint32* segmentation = new vl_uint32[processedImage.rows*processedImage.cols];
    vl_size height = processedImage.rows;
    vl_size width = processedImage.cols;
    vl_size channels = processedImage.channels();

    // The region size defines the number of superpixels obtained.
    // Regularization describes a trade-off between the color term and the
    // spatial term.
    vl_size region = 30;
    float regularization = 10000.;
    vl_size minRegion = 10;

    vl_slic_segment(segmentation, image, width, height, channels, region, regularization, minRegion);

    // Convert segmentation.
    int** labels = new int*[processedImage.rows];
    for (int i = 0; i < processedImage.rows; ++i) {
        labels[i] = new int[processedImage.cols];

        for (int j = 0; j < processedImage.cols; ++j) {
            labels[i][j] = (int) segmentation[j + processedImage.cols*i];
        }
    }

    int label = 0;
    int labelTop = -1;
    int labelBottom = -1;
    int labelLeft = -1;
    int labelRight = -1;

    for (int i = 0; i < processedImage.rows; i++) {
        for (int j = 0; j < processedImage.cols; j++) {

            label = labels[i][j];

            labelTop = label;
            if (i > 0) {
                labelTop = labels[i - 1][j];
            }

            labelBottom = label;
            if (i < processedImage.rows - 1) {
                labelBottom = labels[i + 1][j];
            }

            labelLeft = label;
            if (j > 0) {
                labelLeft = labels[i][j - 1];
            }

            labelRight = label;
            if (j < processedImage.cols - 1) {
                labelRight = labels[i][j + 1];
            }

            if (label != labelTop || label != labelBottom || label!= labelLeft || label != labelRight) {
                processedImage.at<cv::Vec3b>(i, j)[0] = 0;
                processedImage.at<cv::Vec3b>(i, j)[1] = 0;
                processedImage.at<cv::Vec3b>(i, j)[2] = 255;
            }
        }
    }
    showImage(processedImage);
}

/**
* Draw OpenCV matrix using QLabel
*/
void ImageApp::showImage(cv::Mat img)
{
   if (img.data) {
       QImage _img(img.data, img.cols, img.rows, QImage::Format_RGB888);
       imageLabel->setPixmap(QPixmap::fromImage(_img));
   } else {
       imageLabel->setText("Cannot load the input image!");
   }
}
