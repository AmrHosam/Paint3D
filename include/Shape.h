#ifndef SHAPE_H
#define SHAPE_H

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>


class Shape
{
protected:
	virtual vtkSmartPointer<vtkPolyDataMapper> getMapper() = 0;
public:
	Shape();
	Shape(int, double, double, double, std::string);
	double getX() const;
	double getY() const;
	double getZ() const;
	int getID() const;
	std::string getName() const;
	vtkSmartPointer<vtkActor> getActor() const;
	void setX(double);
	void setY(double);
	void setZ(double);
	virtual void update() = 0;
	void setupShape();
	virtual ~Shape();
protected:
	double x;
	double y;
	double z;
	int id;
	std::string name;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
};

#endif // SHAPE_H
