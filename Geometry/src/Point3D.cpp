#include "pch.h"
#include "Point3D.h"

Point3D::Point3D() : mX(0.0), mY(0.0), mZ(0.0)
{

}

Point3D::Point3D(double inX, double inY, double inZ) : mX(0.0), mY(0.0), mZ(0.0)
{
    mX = inX;
    mY = inY;
    mZ = inZ;
}

Point3D::Point3D(char* facet) {
	char f1[4] = { facet[0], facet[1], facet[2], facet[3] };
	char f2[4] = { facet[4], facet[5], facet[6], facet[7] };
	char f3[4] = { facet[8], facet[9], facet[10], facet[11] };
	float xx = *((float*)f1);
	float yy = *((float*)f2);
	float zz = *((float*)f3);
	mX = double(xx);
	mY = double(yy);
	mZ = double(zz);
}

Point3D::~Point3D()
{

}

std::ostream& operator<<(std::ostream& os, Point3D v) 
{
	os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
	return os;
}

double Point3D::x() const
{
    return mX;
}

double Point3D::y() const
{
    return mY;
}

double Point3D::z() const
{
    return mZ;
}

void Point3D::setX(double inX)
{
    mX = inX;
}

void Point3D::setY(double inY)
{
    mY = inY;
}

void Point3D::setZ(double inZ)
{
    mZ = inZ;
}


const Point3D Point3D::operator+(const Point3D& rv) const 
{
	return Point3D(mX + rv.x(), mY + rv.y(), mZ + rv.z());
}

const Point3D Point3D::operator-(const Point3D& rv) const 
{
	return Point3D(mX - rv.x(), mY - rv.y(), mZ - rv.z());
}

const Point3D Point3D::operator*(const double& rv) const 
{
	return Point3D(mX * rv, mY * rv, mZ * rv);
}

const Point3D Point3D::operator/(const double& rv) const 
{
	return Point3D(mX / rv, mY / rv, mZ / rv);
}

const Point3D Point3D::operator^(const Point3D& rv) const 
{
	return Point3D(
		mY * rv.z() - mZ * rv.y(),
		mZ * rv.x() - mX * rv.z(),
		mX * rv.y() - mY * rv.x());
}

const double Point3D::operator&(const Point3D& rv) const 
{
	return mX * rv.x() + mY * rv.y() + mZ * rv.z() ;
}

Point3D& Point3D::operator+=(const Point3D& rv) 
{
	mX += rv.x();
	mY += rv.y();
	mZ += rv.z();
	return *this;
}

Point3D& Point3D::operator-=(const Point3D& rv) 
{
	mX -= rv.x();
	mY -= rv.y();
	mZ -= rv.z();
	return *this;
}

Point3D& Point3D::operator*=(const double& rv) 
{
	mX *= rv;
	mY *= rv;
	mZ *= rv;
	return *this;
}

Point3D& Point3D::operator/=(const double& rv) 
{
	mX /= rv;
	mY /= rv;
	mZ /= rv;
	return *this;
}

double Point3D::normal() const 
{
	return sqrt(mX * mX + mY * mY + mZ * mZ);
}
