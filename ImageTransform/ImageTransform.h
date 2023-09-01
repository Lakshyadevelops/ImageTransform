#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageTransform.h"

class ImageTransform : public QMainWindow
{
    Q_OBJECT

public:
    ImageTransform(QWidget *parent = nullptr);
    ~ImageTransform();

    std::string getFilePath();
    void setFilePath();

private:
    Ui::ImageTransformClass ui;
    std::string m_FilePath_;
    bool m_single_image_;


};
