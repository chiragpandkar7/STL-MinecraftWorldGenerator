// OpenGLWindow.h
#pragma once
#include "Triangle.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <vector>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
signals:
    void shapeUpdate();

public:
    OpenGLWindow(const QColor& background, QMainWindow* parent);
    ~OpenGLWindow();

    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void STLRenderer(std::string fileName);
    void voxelRenderer(std::string fileName, int voxelSize);

public:
    void shaderWatcher();
    QString readShader(QString filePath);
    void selectColor();

protected:
    void paintGL() override;
    void initializeGL() override;

private:
    void reset();

    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_normalAttr = 0;
    GLint m_matrixUniform = 0;
    QVector<QVector2D> mPixelVertices;

    std::vector<float> mVertices; 
    std::vector<float> mColors;
    std::vector<float> mNormals;
    std::vector<Point3D> mV;
    std::vector<Point3D> mC;
    std::vector<Point3D> mN;
    std::vector<float> voxelData;  
    int gridSize = 12;
    float zoomFactor = 1.0f;
    bool renderSTL;
    QQuaternion rotationAngle;
    QPoint lastPos;
    float r = 0.0f, g = 0.0f, b = 0.0f;

};