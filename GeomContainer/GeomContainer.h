#pragma once
#include <vector>
#include "pch.h"
#include "Point3D.h"
// This class is exported from the dll
class GEOMCONTAINER_API GeomContainer {
public:
	static GeomContainer* getContainer();
	static GeomContainer* getContainer(std::vector<Point3D> inPoints);
	void makeTriangleVertices();
	void makeQuadVertices(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4);

	std::vector<float> vertices();
	std::vector<float> colors();
	std::vector<float> normals();
	 
private:
	GeomContainer();
	GeomContainer(std::vector<Point3D> inPoints);
	void addQuad(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4);

private:
	std::vector<Point3D> mPoints;
	std::vector<float> mVertices;
	std::vector<float> mColors;
	std::vector<float> mNormals;
	
	Point3D mColor;
};

extern GEOMCONTAINER_API int nGeomContainer;

GEOMCONTAINER_API int fnGeomContainer(void);
