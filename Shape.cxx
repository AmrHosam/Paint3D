#include "Shape.h"

Shape::Shape() :
	x(0),
	y(0),
	z(0),
	mapper(vtkSmartPointer<vtkPolyDataMapper>::New()),
	actor(vtkSmartPointer<vtkActor>::New()){}
Shape::Shape(double posX, double posY, double posZ) : 
	x(posX),
	y(posY),
	z(posZ), 
	mapper(vtkSmartPointer<vtkPolyDataMapper>::New()),
	actor(vtkSmartPointer<vtkActor>::New()) {}
double Shape::getX() { return x; }
double Shape::getY() { return y; }
double Shape::getZ() { return z; }
void Shape::setX(double posX) { x = posX; }
void Shape::setY(double posY) { y = posY; }
void Shape::setZ(double posZ) { z = posZ; }
Shape::~Shape(){}