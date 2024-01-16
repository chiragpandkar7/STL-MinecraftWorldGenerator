# STL - Minecraft world generator

This project provides a user-friendly interface for working with STL files, allowing users to open, render, and voxelize 3D models. The primary features include:

## Key Features
Open STL File: Users can input STL files using the "Open STL" button, facilitating easy access to 3D models.

Render STL: The "Render STL" button enables users to visualize the 3D model directly within the application, providing a convenient preview.

Voxelize Model: The "Voxelize" button allows users to voxelize the loaded STL file, converting the 3D model into a grid of cubes.

Voxel Size Control: A spin box is provided to set the voxel size, giving users flexibility in defining the granularity of the voxelization process.

Color Customization: Users can customize the rendering color of the 3D model using the "Color" button, enhancing the visualization experience.

## Overview

This project consists of several components, including a Geometry DLL, a CubeItCreator DLL, a GeomContainer DLL and a Reader DLL.

## Geometry DLL

### Point3D Class

#### Methods
- 'Point3D p1() const': Get the first point.
- 'Point3D p2() const': Get the second point.
- 'Point3D p3() const': Get the third point.
- 'Point3D normal() const': Get the normal.
- 'void setNormal(Point3D inNormal)': Set the normal.
- 'bool containsPoint(const Point3D& point) const': Check if the given point is inside the triangle.
- Friend Function :
- 'std::ostream& operator<<(std::ostream& os, Triangle& tri)': Output stream operator to print the triangle.
- 
### Triangle Class

#### Methods
- `Triangle()`: Default constructor.
- `Triangle(Point3D inP1, Point3D inP2, Point3D inP3)`: Constructor with initial points.
- `Triangle(Point3D inNormal, Point3D inP1, Point3D inP2, Point3D inP3)`: Constructor with normal and initial points.
- `~Triangle()`: Destructor.
- `Point3D p1() const`: Get the first point.
- `Point3D p2() const`: Get the second point.
- `Point3D p3() const`: Get the third point.
- `Point3D normal() const`: Get the normal.
- `void setNormal(Point3D inNormal)`: Set the normal.
- `std::ostream& operator<<(std::ostream& os, Triangle& tri)`: Output stream operator to print the triangle.
- `bool containsPoint(const Point3D& point) const`: Check if the given point is inside the triangle.

## Reader DLL

### STLReader Class

The `STLReader` class is responsible for reading STL files and extracting vertices, colors, and normals.

#### Methods

- `STLReader()`: Default constructor.
- `STLReader(std::string filePath, std::vector<Point3D>& vertices, std::vector<Point3D>& colors, std::vector<Point3D>& normals)`: Constructor taking a file path and vectors to store vertices, colors, and normals.
- `~STLReader()`: Destructor.
- `void readSTL(std::string filePath, std::vector<Point3D>& vertices, std::vector<Point3D>& colors, std::vector<Point3D>& normals)`: Read an STL file and populate vectors with vertices, colors, and normals.


## GeomContainer DLL

### GeomContainer Class

The `GeomContainer` class serves as a container for geometric data. It can be used to store points, colors, and normals.

#### Methods

- `GeomContainer()`: Default constructor.
- `GeomContainer(std::vector<Point3D> inPoints)`: Constructor with initial points.
- `GeomContainer* getContainer()`: Static method to get an instance of `GeomContainer`.
- `GeomContainer* getContainer(std::vector<Point3D> inPoints)`: Static method to get an instance of `GeomContainer` with initial points.
- `void makeTriangleVertices()`: Generate vertices for a triangle based on stored points.
- `void makeQuadVertices(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4)`: Generate vertices for a quad.
- `std::vector<float> vertices()`: Get the vertices.
- `std::vector<float> colors()`: Get the colors.
- `std::vector<float> normals()`: Get the normals.


## CubeItCreator DLL

### CubeIt Class

The `CubeIt` class is responsible for voxelizing 3D models from STL files. It takes a file name and voxel size as input and generates a voxelized representation of the 3D model.

#### Methods

- `CubeIt(std::string fileName, int inVoxelSize)`: Constructor taking a file name and voxel size.
- `~CubeIt()`: Destructor.
- `CubeIt* getVoxelizer(std::string fileName, int voxelSize)`: Static method to get an instance of `CubeIt`.
- `std::vector<float> vertices() const`: Get the vertices of the voxelized model.
- `std::vector<float> colors() const`: Get the colors of the voxelized model.
- `void setVoxelSize(int inVoxelSize)`: Set the voxel size.
- `void makeCubeIt(std::string fileName)`: Voxelizes the STL model.
- `void addCubicalVetices(const Point3D& point1, const Point3D& point2, int voxelSize)`: Helper method to add vertices for cubical voxelization.
- `void addCube(const Point3D& corner, int voxelSize)`: Helper method to add a cube to the voxelized representation.
- `void addQuad(const Point3D& p1, const Point3D& p2, const Point3D& p3, const Point3D& p4)`: Helper method to add a quad to the voxelized representation.




