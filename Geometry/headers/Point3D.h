#pragma once

#include "pch.h"
#include<iostream>

class GEOMETRY_API Point3D
{
public:
	Point3D();
	Point3D(double inX, double inY, double inZ);
	Point3D(char* facet);
	~Point3D();

	friend std::ostream& operator<<(std::ostream& os, Point3D v);

	double x() const;
	double y() const;
	double z() const;

	void setX(double inX);
	void setY(double inY);
	void setZ(double inZ);


	const Point3D operator+(const Point3D& rv) const;
	const Point3D operator-(const Point3D& rv) const;
	const Point3D operator*(const double& rv) const;
	const Point3D operator/(const double& rv) const;
	// extern product
	const Point3D operator^(const Point3D& rv) const;
	// inner product
	const double operator&(const Point3D& rv) const;
	// add
	Point3D& operator+=(const Point3D& rv);
	// substract
	Point3D& operator-=(const Point3D& rv);
	// multiply
	Point3D& operator*=(const double& rv);
	// divide
	Point3D& operator/=(const double& rv);


	// normal vector
	double normal() const;

private:
	double mX;
	double mY;
	double mZ;
};
