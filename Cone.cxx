#include "Cone.h"

Cone::Cone() :
	radius(1),
	height(1),
	src(vtkSmartPointer<vtkConeSource>::New()){}

Cone::Cone(double x, double y, double z, double r, double h) :
	Shape(x,y,z),
	radius(r),
	height(h),
	src(vtkSmartPointer<vtkConeSource>::New()) {}

double Cone::getRadius() { return radius; }

void Cone::setRadius(double r) { radius = r; }

void Cone::update() {
	src->SetCenter(x, y, z);
	src->SetHeight(height);
	src->SetRadius(radius);
	src->Update();
}

vtkSmartPointer<vtkPolyDataMapper> Cone::getMapper() {
	update();
	mapper->SetInputData(src->GetOutput());
	return mapper;
}

vtkSmartPointer<vtkActor> Cone::getActor() {
	actor->SetMapper(getMapper());
	return actor;
}