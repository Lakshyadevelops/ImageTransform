#include "ImageTransform.h"
#include<qfiledialog.h>
#include<opencv2/opencv.hpp>

ImageTransform::ImageTransform(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.pb_single_image, &QPushButton::clicked, this, [this]() {m_single_image_=true; });
    connect(ui.pb_batch_processing, &QPushButton::clicked, this, [this]() {m_single_image_ = false;; });

    connect(ui.pb_single_image, &QPushButton::clicked, this, &ImageTransform::setFilePath);
    connect(ui.pb_batch_processing, &QPushButton::clicked, this, &ImageTransform::setFilePath);


}

ImageTransform::~ImageTransform()
{}

std::string ImageTransform::getFilePath()
{
    return m_FilePath_;
}

void ImageTransform::setFilePath()
{
    m_FilePath_ = QFileDialog::getOpenFileName(nullptr, "Select a File").toStdString();
    if (m_single_image_) {
        cv::Mat img = cv::imread(m_FilePath_);

    }
}

