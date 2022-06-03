#include "Sphere.h"

Sphere::Sphere() : radius(1), src(vtkSmartPointer<vtkSphereSource>::New()) {}

Sphere::Sphere(double x, double y, double z, double r) : 
	Shape(x,y,z),
	radius(r),
	src(vtkSmartPointer<vtkSphereSource>::New()) {}

double Sphere::getRadius() { return radius; }

void Sphere::setRadius(double r) { radius = r; }

void Sphere::update() {
	src->SetRadius(radius);
	src->SetCenter(x, y, z);
	src->Update();
}

vtkSmartPointer<vtkPolyDataMapper> Sphere::getMapper() {
	update();
	mapper->SetInputData(src->GetOutput());
	return mapper;
}

vtkSmartPointer<vtkActor> Sphere::getActor() {
	actor->SetMapper(getMapper());
	return actor;
}