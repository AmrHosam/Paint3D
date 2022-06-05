#include "Cube.h"

Cube::Cube() :
	xLength(1),
	yLength(1),
	zLength(1),
	src(vtkSmartPointer<vtkCubeSource>::New()){}

Cube::Cube(double x, double y, double z, double lx, double ly, double lz) :
	Shape(x,y,z),
	xLength(lx),
	yLength(ly),
	zLength(lz),
	src(vtkSmartPointer<vtkCubeSource>::New()) {}

double Cube::getXLength() { return xLength; }
double Cube::getYLength() { return yLength; }
double Cube::getZLength() { return zLength; }

void Cube::setXLength(double lx) { xLength = lx; }
void Cube::setYLength(double ly) { yLength = ly; }
void Cube::setZLength(double lz) { zLength = lz; }


void Cube::update() {
	src->SetCenter(x, y, z);
	src->SetXLength(xLength);
	src->SetYLength(yLength);
	src->SetZLength(zLength);
	src->Update();
}

vtkSmartPointer<vtkPolyDataMapper> Cube::getMapper() {
	update();
	mapper->SetInputData(src->GetOutput());
	return mapper;
}

vtkSmartPointer<vtkActor> Cube::getActor() {
	actor->SetMapper(getMapper());
	return actor;
}