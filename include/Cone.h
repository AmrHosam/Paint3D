#ifndef CONE_H
#define CONE_H

#include"Shape.h"
#include <vtkConeSource.h>

class Cone : public Shape
{
public:
	Cone();
	Cone(double x, double y, double z, double r, double h);
	double getRadius();
	void setRadius(double);
	void update();
	vtkSmartPointer<vtkPolyDataMapper> getMapper();
	vtkSmartPointer<vtkActor> getActor();
private:
	double radius;
	double height;
	vtkSmartPointer<vtkConeSource> src;
};

#endif // Cone_H
