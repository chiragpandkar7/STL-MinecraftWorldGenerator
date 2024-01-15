#include "pch.h"
#include "framework.h"
#include "GeomContainer.h"

GEOMCONTAINER_API int nGeomContainer=0;

GEOMCONTAINER_API int fnGeomContainer(void)
{
    return 0;
}

GeomContainer::GeomContainer() 
{
	mVertices.clear();
	mColors.clear();
	mNormals.clear();
}

GeomContainer::GeomContainer(std::vector<Point3D> inPoints) : mPoints(inPoints)
{
	mVertices.clear();
	mColors.clear();
	mNormals.clear();
}

GeomContainer* GeomContainer::getContainer()
{
	GeomContainer* geomContainer = new GeomContainer();
	return geomContainer;
}

GeomContainer* GeomContainer::getContainer(std::vector<Point3D> inPoints)
{
	GeomContainer* geomContainer = new GeomContainer(inPoints);
	return geomContainer;
}


void GeomContainer::makeTriangleVertices()
{
	mVertices.clear();
	mColors.clear();
	mNormals.clear();

	for (int i = 0; i < mPoints.size(); i++)
	{
	
		mVertices.push_back(mPoints[i].x());
		mVertices.push_back(mPoints[i].y());
		mVertices.push_back(mPoints[i].z());

		mColors.push_back(mColor.x());
		mColors.push_back(mColor.y());
		mColors.push_back(mColor.z());

		mNormals.push_back(mPoints[i].normal());
	}


}

void GeomContainer::makeQuadVertices(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4)
{
	mVertices.push_back(p1.x());
	mVertices.push_back(p1.y());
	mVertices.push_back(p1.z());

	mVertices.push_back(p2.x());
	mVertices.push_back(p2.y());
	mVertices.push_back(p2.z());

	mVertices.push_back(p3.x());
	mVertices.push_back(p3.y());
	mVertices.push_back(p3.z());

	mVertices.push_back(p4.x());
	mVertices.push_back(p4.y());
	mVertices.push_back(p4.z());

	mColors.push_back(mColor.x());
	mColors.push_back(mColor.y());
	mColors.push_back(mColor.z());

	mColors.push_back(mColor.x());
	mColors.push_back(mColor.y());
	mColors.push_back(mColor.z());

	mColors.push_back(mColor.x());
	mColors.push_back(mColor.y());
	mColors.push_back(mColor.z());

	mColors.push_back(mColor.x());
	mColors.push_back(mColor.y());
	mColors.push_back(mColor.z());
}

std::vector<float> GeomContainer::vertices()
{
	return mVertices;
}

std::vector<float> GeomContainer::colors()
{
	return mColors;
}

std::vector<float> GeomContainer::normals()
{
	return mNormals;
}