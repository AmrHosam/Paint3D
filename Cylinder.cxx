#include "Cylinder.h"
#include <vtkActor.h>


Cylinder::Cylinder() :
	radius(1),
	height(1),
	src(vtkSmartPointer<vtkCylinderSource>::New()){}

Cylinder::Cylinder(double x, double y, double z, double r, double h) :
	Shape(x,y,z),
	radius(r),
	height(h),
	src(vtkSmartPointer<vtkCylinderSource>::New()) {}

double Cylinder::getRadius() { return radius; }

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