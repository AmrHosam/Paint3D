#ifndef Cylinder_H
#define Cylinder_H

#include"Shape.h"
#include <vtkCylinderSource.h>

class Cylinder : public Shape
{
public:
	Cylinder();
	Cylinder(double x, double y, double z, double r, double h);
	double getRadius();
	void setRadius(double);
	void update();
	vtkSmartPointer<vtkPolyDataMapper> getMapper();
	vtkSmartPointer<vtkActor> getActor();
private:
	double radius;
	double height;
	vtkSmartPointer<vtkCylinderSource> src;
};

#endif // Cylinder_H
