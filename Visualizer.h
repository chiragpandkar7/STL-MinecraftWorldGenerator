#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QSpinBox>
#include <QColorDialog>
#include "Triangle.h"
class OpenGLWindow;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWindow* parent = nullptr);
    ~Visualizer();
    std::vector<Triangle> trianglesData;
    std::string fileName;
private:
    void setupUi();

private:
    QPushButton* mOpenButton;
    QPushButton* mRenderButton;
    QPushButton* mVoxelizeButton;
    QPushButton* mColorDialogButton;
    QSpinBox* mSpinBox;
    OpenGLWindow* mRenderer;

private:
    void openFileDialog();
    void showColorDialog();
    void renderSTL();
    void voxelizeSTL();
};

