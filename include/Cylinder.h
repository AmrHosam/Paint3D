#ifndef Cylinder_H
#define Cylinder_H

#include"Shape.h"
#include <vtkCylinderSource.h>

class Cylinder : public Shape
{
private:
	vtkSmartPointer<vtkPolyDataMapper> getMapper();
public:
	Cylinder();
	Cylinder(int shapeId, double x, double y, double z, double r, double h);
	double getRadius() const;
	void setRadius(double);
	void update();
	void setupShape();
private:
	double radius;
	double height;
	vtkSmartPointer<vtkCylinderSource> src;
};

#endif // Cylinder_H
