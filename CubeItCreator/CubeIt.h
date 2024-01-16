#include "pch.h"
#pragma once
#include <string>
#include <vector>
#include <Point3D.h>

class CUBEITCREATOR_API CubeIt
{
public:
	static CubeIt* getVoxelizer(std::string fileName, int voxelSize);

	std::vector<float> vertices() const;
	std::vector<float> colors() const;
	void setVoxelSize(int inVoxelSize);

private:
	CubeIt(std::string fileName, int inVoxelSize);
	~CubeIt();

	void makeCubeIt(std::string fileName);

	void addCubicalVetices(const Point3D& point1, const Point3D& point2, int voxelSize);

	void addCube(const Point3D& corner, int voxelSize);

	void addQuad(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4);

private:
	int mVoxelSize;
	std::vector<float> mVertices;
	std::vector<float> mColors;
};

