#ifndef SHAPE_H
#define SHAPE_H

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>

class Shape
{
protected:
	virtual vtkSmartPointer<vtkPolyDataMapper> getMapper() = 0;
public:
	Shape(int shapeId, double posX, double posY, double posZ, std::string shapeName);
	double getX() const;
	double getY() const;
	double getZ() const;
	int getID() const;
	std::string getName() const;
	vtkSmartPointer<vtkActor> getActor() const;
	void setX(double posX);
	void setY(double posY);
	void setZ(double posZ);
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
