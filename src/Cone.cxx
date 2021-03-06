#include "Cone.h"

Cone::Cone(int shapeId, double x, double y, double z, double r, double h) :
	Shape(shapeId,x,y,z, "Cone_" + std::to_string(shapeId)),
	radius(r),
	height(h),
	src(vtkSmartPointer<vtkConeSource>::New()) {}

double Cone::getRadius() const{ return radius; }
void Cone::setRadius(double r) { radius = r; }

double Cone::getHeight() const { return height; }
void Cone::setHeight(double h) { height = h; }

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
