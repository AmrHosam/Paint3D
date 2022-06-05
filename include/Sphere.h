#ifndef SPHERE_H
#define SPHERE_H

#include"Shape.h"
#include <vtkSphereSource.h>

class Sphere : public Shape
{
private:
	vtkSmartPointer<vtkPolyDataMapper> getMapper() override;
public:
	Sphere();
	Sphere(int shapeId, double x, double y, double z, double r);
	double getRadius() const;
	void setRadius(double);
	void update() override;
	vtkSmartPointer<vtkActor> getActor() override;
private:
	double radius;
	vtkSmartPointer<vtkSphereSource> src;
};

#endif // SPHERE_H
