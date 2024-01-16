#include "stdafx.h"
#include "Visualizer.h"
#include "STLReader.h"
#include "OpenGLWindow.h"
#include<string>

Visualizer::Visualizer(QWindow* parent)
{
    setupUi();

    connect(mOpenButton, &QPushButton::clicked, this, &Visualizer::openFileDialog);

    connect(mRenderButton, &QPushButton::clicked, this, &Visualizer::renderSTL);

    connect(mVoxelizeButton, &QPushButton::clicked, this, &Visualizer::voxelizeSTL);

    connect(mColorDialogButton, &QPushButton::clicked, mRenderer, &OpenGLWindow::selectColor);
}

Visualizer::~Visualizer()
{
}

void Visualizer::setupUi()
{

    QWidget* mCentralWidget = new QWidget(this);

    //main Horizontal Layout
    QHBoxLayout* mainHorizontalLayout = new QHBoxLayout(mCentralWidget);

    //openGL renderer
    mRenderer = new OpenGLWindow(QColor(1.0, 1.0, 0.0), this);
    mainHorizontalLayout->addWidget(mRenderer);

    // Vertical Layout for Buttons
    QVBoxLayout* buttonsVerticalLayout = new QVBoxLayout();

    mOpenButton = new QPushButton(this);
    mOpenButton->setText("Open STL");
    mOpenButton->setFixedSize(150, 50);

    mRenderButton = new QPushButton(this);
    mRenderButton->setText("Render STL");
    mRenderButton->setFixedSize(150, 50);

    mVoxelizeButton = new QPushButton(this);
    mVoxelizeButton->setText("Voxelize");
    mVoxelizeButton->setFixedSize(150, 50);

    mSpinBox = new QSpinBox(this);
    mSpinBox->setGeometry(QRect(1795, 650, 90, 30));
    mSpinBox->setMinimum(1); // Set minimum value
    mSpinBox->setMaximum(100); // Set maximum value
    mSpinBox->setValue(1); // Set default value

    QLabel* mSizeLabel = new QLabel("Voxel Size", this);
    mSizeLabel->setGeometry(QRect(1810, 680, 90, 30));
    mSizeLabel->setTextFormat(Qt::RichText);
    mSizeLabel->setText("<b>" + mSizeLabel->text() + "</b>");

    mColorDialogButton = new QPushButton(this);
    mColorDialogButton->setText("Color");
    mColorDialogButton->setFixedSize(150, 50);

    buttonsVerticalLayout->addWidget(mOpenButton);
    buttonsVerticalLayout->addWidget(mRenderButton);
    buttonsVerticalLayout->addWidget(mVoxelizeButton);
    buttonsVerticalLayout->addWidget(mColorDialogButton);

    // Add Vertical Layout to Main Horizontal Layout
    mainHorizontalLayout->addLayout(buttonsVerticalLayout);

    setCentralWidget(mCentralWidget);
    showMaximized();
}



void Visualizer::openFileDialog()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files (*.stl);;All Files (*)"));

    if (!qFileName.isEmpty())
    {
        fileName = qFileName.toStdString();
    }
}

// Slot for rendering the STL file
void Visualizer::renderSTL()
{
     mRenderer->STLRenderer(fileName);
}

// Slot for voxelizing the STL file
void Visualizer::voxelizeSTL()
{
    // Get the voxel size from the SpinBox
    int voxelSize = mSpinBox->value();

    // Assuming you have a slot in OpenGLWindow to handle voxelization
    emit  mRenderer->voxelRenderer(fileName, voxelSize);
}


void Visualizer::showColorDialog()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid())
    {
        // Do something with the selected color
        qDebug() << "Selected Color: " << color;
    }
}
