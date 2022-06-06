#include "Shape.h"

Shape::Shape(int shapeId, double posX, double posY, double posZ, std::string shapeName) : 
	x(posX),
	y(posY),
	z(posZ),
	id(shapeId),
	name(shapeName),
	mapper(vtkSmartPointer<vtkPolyDataMapper>::New()),
	actor(vtkSmartPointer<vtkActor>::New()) {}
double Shape::getX() const { return x; }
double Shape::getY() const { return y; }
double Shape::getZ() const { return z; }
int Shape::getID() const { return id; }
std::string Shape::getName() const { return name; }
vtkSmartPointer<vtkActor> Shape::getActor() const { return actor; }
void Shape::setX(double posX) { x = posX; }
void Shape::setY(double posY) { y = posY; }
void Shape::setZ(double posZ) { z = posZ; }
void Shape::setupShape() {
	actor->SetMapper(getMapper());
}
Shape::~Shape(){}