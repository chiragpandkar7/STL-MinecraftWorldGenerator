#include "stdafx.h"
#include "OpenGLWindow.h"
#include "STLReader.h"
#include "CubeIt.h"
#include "GeomContainer.h"

#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QFileInfo>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ostream>
#include <string>
#include <cmath>


OpenGLWindow::OpenGLWindow(const QColor& background, QMainWindow* parent) 
	: mBackground(background), renderSTL(false)
{
	setParent(parent);
	setMinimumSize(1300, 784);
}

OpenGLWindow::~OpenGLWindow()
{
	reset();
}

void OpenGLWindow::reset()
{
	makeCurrent();
	delete mProgram;
	mProgram = nullptr;
	delete mVshader;
	mVshader = nullptr;
	delete mFshader;
	mFshader = nullptr;
	mVbo.destroy();
	doneCurrent();

	QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(255.0, 255.0, 255.0, 1.0);
	mProgram->bind();

	QMatrix4x4 matrix;
	matrix.ortho(-30.0f * zoomFactor, 30.0f * zoomFactor, -30.0f * zoomFactor, 30.0f * zoomFactor, -100.0f, 100.0f * zoomFactor);
	matrix.translate(0, 0, -2);
	matrix.rotate(rotationAngle);

	mProgram->setUniformValue(m_matrixUniform, matrix);
	mProgram->setUniformValue("r", r);
	mProgram->setUniformValue("g", g);
	mProgram->setUniformValue("b", b);


	glEnableVertexAttribArray(m_posAttr);
	glEnableVertexAttribArray(m_colAttr);
	


	if (renderSTL)
	{
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mVertices.data());
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mColors.data());

		glEnableVertexAttribArray(m_posAttr);
		glEnableVertexAttribArray(m_colAttr);
		glDrawArrays(GL_LINE_LOOP, 0, mVertices.size() / 3);
	}

	else 
	{
		glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, mVertices.data());
		glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, mColors.data());

		glEnableVertexAttribArray(m_posAttr);
		glEnableVertexAttribArray(m_colAttr);

		glDrawArrays(GL_QUADS, 0, mVertices.size() / 3);
	}

	glDisableVertexAttribArray(m_colAttr);
	glDisableVertexAttribArray(m_posAttr);
}

void OpenGLWindow::initializeGL()
{
	
	QString vertexShaderSource = readShader("vertexShader.glsl");
	QString fragmentShaderSource = readShader("fragmentShader.glsl");

	initializeOpenGLFunctions();

	mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	mProgram->link();
	m_posAttr = mProgram->attributeLocation("posAttr");
	Q_ASSERT(m_posAttr != -1);
	m_colAttr = mProgram->attributeLocation("colAttr");
	Q_ASSERT(m_colAttr != -1);
	m_matrixUniform = mProgram->uniformLocation("matrix");
	Q_ASSERT(m_matrixUniform != -1);
}

QString OpenGLWindow::readShader(QString filePath) 
{
	QFile file(filePath);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return "Invalid file";

	QTextStream stream(&file);
	QString line = stream.readLine();

	while (!stream.atEnd()) {
		line.append(stream.readLine());
	}
	file.close();
	return line;
}

void OpenGLWindow::shaderWatcher()
{
	QString vertexShaderSource = readShader("vertexShader.glsl");
	QString fragmentShaderSource = readShader("fragmentShader.glsl");

	mProgram->release();
	mProgram->removeAllShaders();
	mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	mProgram->link();
}

void OpenGLWindow::selectColor()
{
	QColorDialog colorDialog(this);
	QColor selectedColor = colorDialog.getColor();

	if (selectedColor.isValid()) {
		// Set the selected color
		r = selectedColor.redF();
		g = selectedColor.greenF();
		b = selectedColor.blueF();
		update();
	}
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event) 
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5f * dx);
		QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.5f * dy);

		rotationAngle = rotX * rotY * rotationAngle;
		update();
	}
	lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
	int delta = event->angleDelta().y();

	// Adjust the zoom factor based on the mouse wheel movement
	if (delta > 0) {
		// Zoom in
		zoomFactor *= 1.1f;
	}
	else {
		// Zoom out
		zoomFactor /= 1.1f;
	}

	update();
}

void OpenGLWindow::voxelRenderer(std::string fileName, int voxelSize)
{
	renderSTL = false;
	CubeIt* cubeIt = CubeIt::getVoxelizer(fileName, voxelSize);
	mVertices = cubeIt->vertices();
	mColors = cubeIt->colors();
	
	update();
}

void OpenGLWindow::STLRenderer(std::string fileName)
{
	mVertices.clear();
	mColors.clear();
	mNormals.clear();
	renderSTL = true;
	IOOperation::STLReader reader(fileName, mV, mC, mN);
	GeomContainer* geomContainer = GeomContainer::getContainer(mV);
	geomContainer->makeTriangleVertices();
	mVertices = geomContainer->vertices();
	mColors = geomContainer->colors();
	mNormals = geomContainer->normals();
	update();
}