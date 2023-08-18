#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageTransform.h"

class ImageTransform : public QMainWindow
{
    Q_OBJECT

public:
    ImageTransform(QWidget *parent = nullptr);
    ~ImageTransform();

private:
    Ui::ImageTransformClass ui;
};
