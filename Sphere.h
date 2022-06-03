#ifndef SPHERE_H
#define SPHERE_H

#include"Shape.h"
#include <vtkSphereSource.h>

class Sphere : public Shape
{
public:
	Sphere();
	Sphere(double x, double y, double z, double r);
	double getRadius();
	void setRadius(double);
	void update() override;
	vtkSmartPointer<vtkPolyDataMapper> getMapper() override;
	vtkSmartPointer<vtkActor> getActor() override;
private:
	double radius;
	vtkSmartPointer<vtkSphereSource> src;
};

#endif // SPHERE_H
