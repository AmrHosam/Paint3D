#include "Cone.h"

Cone::Cone() :
	radius(1),
	height(1),
	src(vtkSmartPointer<vtkConeSource>::New()){}

Cone::Cone(int shapeId, double x, double y, double z, double r, double h) :
	Shape(shapeId,x,y,z, "Cone_" + std::to_string(shapeId)),
	radius(r),
	height(h),
	src(vtkSmartPointer<vtkConeSource>::New()) {}

double Cone::getRadius() const{ return radius; }

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

void Cone::setupShape() {
	actor->SetMapper(getMapper());
}