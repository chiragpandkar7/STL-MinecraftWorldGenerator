#include "pch.h"
#include "framework.h"
#include "Triangle.h"

Triangle::Triangle() : mP1(Point3D(0, 0, 0)), mP2(Point3D(0, 0, 0)), mP3(Point3D(0, 0, 0)), mNormal(Point3D(0, 0, 0))
{
}

Triangle::Triangle(Point3D inP1, Point3D inP2, Point3D inP3) : mP1(Point3D(0, 0, 0)), mP2(Point3D(0, 0, 0)), mP3(Point3D(0, 0, 0)), mNormal(Point3D(0, 0, 0))
{
    mP1 = inP1;
    mP2 = inP2;
    mP3 = inP3;
}

Triangle::Triangle(Point3D inNormal, Point3D inP1, Point3D inP2, Point3D inP3) :
    mNormal(inNormal), mP1(inP1), mP2(inP2), mP3(inP3)
{
}

Triangle::~Triangle()
{

}

Point3D Triangle::p1() const
{
    return mP1;
}

Point3D Triangle::p2() const
{
    return mP2;
}

Point3D Triangle::p3() const
{
    return mP3;
}

Point3D Triangle::normal() const
{
    return mNormal;
}

void Triangle::setNormal(Point3D inNormal)
{
    mNormal = inNormal;
}

std::ostream& operator<<(std::ostream& os, Triangle& tri)
{
    os << "(\n  " << tri.p1() << "\n  " << tri.p2() << "\n  " << tri.p3() << "\n)";
    return os;
}

bool Triangle::containsPoint(const Point3D& point) const
{
    // Calculate barycentric coordinates
    float detT = (mP2.y() - mP3.y()) * (mP1.x() - mP3.x()) + (mP3.x() - mP2.x()) * (mP1.y() - mP3.y());
    float alpha = ((mP2.y() - mP3.y()) * (point.x() - mP3.x()) + (mP3.x() - mP2.x()) * (point.y() - mP3.y())) / detT;
    float beta = ((mP3.y() - mP1.y()) * (point.x() - mP3.x()) + (mP1.x() - mP3.x()) * (point.y() - mP3.y())) / detT;
    float gamma = 1.0f - alpha - beta;

    // Check if the point is inside the triangle
    return alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f;
}