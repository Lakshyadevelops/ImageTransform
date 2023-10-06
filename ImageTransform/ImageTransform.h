#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageTransform.h"
#include<opencv2/opencv.hpp>
#include"Run.h"


class ImageTransform : public QMainWindow
{
    Q_OBJECT


public:
    ImageTransform( QWidget *parent = nullptr );
    ~ImageTransform();

    std::string GetFilePath();
    void SetFilePath();
    void Start();

private:
    Ui::ImageTransformClass ui;
    std::string m_file_path_;
    bool m_single_image_;
    std::vector< cv::Mat > m_img_list_;
    int m_model_selected;
    std::unordered_map< int, std::string > model_names;
    std::unordered_map< std::string, int > m_hyper_parameters_;
    Run r_;
    
};
