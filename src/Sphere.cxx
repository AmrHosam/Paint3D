#include "Sphere.h"

Sphere::Sphere(int shapeId, double x, double y, double z, double r) :
	Shape(shapeId,x,y,z, "Sphere_" + std::to_string(shapeId)),
	radius(r),
	src(vtkSmartPointer<vtkSphereSource>::New()) {}

double Sphere::getRadius() const { return radius; }

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