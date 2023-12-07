#include "ImageTransform.h"
#include<qfiledialog.h>
#include<qmessagebox.h>
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
    
    for (Models model : ModelsList) {
        ui.cb_model_select->addItem(QString::fromStdString(r_.getModelName(model)));
    }
    


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
        if (m_file_path_.empty()) {
            return;
        }
        cv::Mat img = cv::imread(m_file_path_,cv::IMREAD_UNCHANGED);
        QImage qImage;

        if (img.channels()==1) {
            cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
            m_img_BW_ = true;
            qImage = QImage((const unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        }
        else if(img.channels()==3) {
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            m_img_BW_ = false;
            qImage = QImage((const unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        }
        else if(img.channels()==4){
            cv::cvtColor(img, img, cv::COLOR_BGRA2RGB);
            m_img_BW_ = false;
            qImage = QImage((const unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        }
        else {
            std::cout << "ERROR : unhandled Channels. Channels are " << img.channels() << std::endl;
        }
        m_img_list_.push_back(img);

        ui.lb_input_image->setPixmap(QPixmap::fromImage(qImage));
    }
    else {
        m_file_path_ = QFileDialog::getExistingDirectory(nullptr).toStdString();
        
        // TO DO load all images
    }
}

void ImageTransform::Start() {
    if (m_file_path_.empty()) {
        ThrowEmptyPathError();
        return;
    }

    r_.run(ui.cb_model_select->currentIndex(),m_img_list_,m_hyper_parameters_,m_img_BW_);
    m_img_list_.clear();
    m_file_path_.clear();

}

void ImageTransform::ThrowEmptyPathError()
{
    QMessageBox::information(
        this,
        tr(""),
        tr("Select File"));
}
