#ifndef SHAPE_H
#define SHAPE_H

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>


class Shape
{
public:
	Shape();
	Shape(double, double, double);
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	virtual void update() = 0;
	virtual vtkSmartPointer<vtkPolyDataMapper> getMapper() = 0;
	virtual vtkSmartPointer<vtkActor> getActor() = 0;
	virtual ~Shape();
protected:
	double x;
	double y;
	double z;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
};

#endif // SHAPE_H
