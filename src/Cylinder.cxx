#include "Cylinder.h"
#include <vtkActor.h>


Cylinder::Cylinder() :
	radius(1),
	height(1),
	src(vtkSmartPointer<vtkCylinderSource>::New()){}

Cylinder::Cylinder(int shapeId, double x, double y, double z, double r, double h) :
	Shape(shapeId,x,y,z, "Cylinder_" + std::to_string(shapeId)),
	radius(r),
	height(h),
	src(vtkSmartPointer<vtkCylinderSource>::New()) {}

double Cylinder::getRadius() const{ return radius; }

void Cylinder::setRadius(double r) { radius = r; }

void Cylinder::update() {
	src->SetCenter(x, y, z);
	src->SetHeight(height);
	src->SetRadius(radius);
	src->Update();
}

vtkSmartPointer<vtkPolyDataMapper> Cylinder::getMapper() {
	update();
	mapper->SetInputData(src->GetOutput());
	return mapper;
}

vtkSmartPointer<vtkActor> Cylinder::getActor() {
	actor->SetMapper(getMapper());
	return actor;
}