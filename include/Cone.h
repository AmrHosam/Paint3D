#ifndef CONE_H
#define CONE_H

#include"Shape.h"
#include <vtkConeSource.h>

class Cone : public Shape
{
private:
	vtkSmartPointer<vtkPolyDataMapper> getMapper() override;
public:
	Cone(int shapeId, double x, double y, double z, double r, double h);
	double getRadius() const;
	void setRadius(double r);
	double getHeight() const;
	void setHeight(double h);
	void update() override;
private:
	double radius;
	double height;
	vtkSmartPointer<vtkConeSource> src;
};

#endif // Cone_H
