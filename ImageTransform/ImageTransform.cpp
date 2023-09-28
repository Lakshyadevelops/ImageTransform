#include "ImageTransform.h"
#include<qfiledialog.h>
#include<qmessagebox.h>
#include<qmetaobject.h>
#include<opencv2/opencv.hpp>
#include "Run.h"

ImageTransform::ImageTransform(QWidget *parent)
    : QMainWindow(parent), m_model_selected(0)
{
    ui.setupUi(this);
    
    connect(ui.pb_single_image, &QPushButton::clicked, this, [this]() {m_single_image_=true; });
    connect(ui.pb_batch_processing, &QPushButton::clicked, this, [this]() {m_single_image_ = false;; });

    connect(ui.pb_single_image, &QPushButton::clicked, this, &ImageTransform::SetFilePath);
    connect(ui.pb_batch_processing, &QPushButton::clicked, this, &ImageTransform::SetFilePath);

    connect(ui.pb_start, &QPushButton::clicked, this, &ImageTransform::Start);
    
    /* TO DO - e=create enunm and display elements in QComboBox
    QMetaEnum metaEnum = QMetaEnum::fromType<models>(models);
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        ui.cb_model_select->addItem(metaEnum.key(i));
    }*/


}

ImageTransform::~ImageTransform()
{

}

std::string ImageTransform::GetFilePath()
{
    return m_file_path_;
}

void ImageTransform::SetFilePath()
{
    if (m_single_image_) {
        m_file_path_ = QFileDialog::getOpenFileName(nullptr, "Select a File").toStdString();
        cv::Mat img = cv::imread(m_file_path_);

        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);

        QImage qImage((const unsigned char*)img.data, img.cols, img.rows, QImage::Format_RGB888);

        ui.lb_input_image->setPixmap(QPixmap::fromImage(qImage));
    }
    else {
        m_file_path_ = QFileDialog::getExistingDirectory(nullptr).toStdString();
    }
}

void ImageTransform::Start() {
    if (m_file_path_.empty()) {
        QMessageBox::information(
            this,
            tr(""),
            tr("Select File"));
    }


}
