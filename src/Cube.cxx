#include "Cube.h"

Cube::Cube(int shapeId, double x, double y, double z, double lx, double ly, double lz) :
	Shape(shapeId,x,y,z, "Cube_" + std::to_string(shapeId)),
	xLength(lx),
	yLength(ly),
	zLength(lz),
	src(vtkSmartPointer<vtkCubeSource>::New()) {}

double Cube::getXLength() const { return xLength; }
double Cube::getYLength() const { return yLength; }
double Cube::getZLength() const { return zLength; }

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
