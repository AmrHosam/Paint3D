#ifndef Cube_H
#define Cube_H

#include"Shape.h"
#include <vtkCubeSource.h>

class Cube : public Shape
{
public:
	Cube();
	Cube(double x, double y, double z, double lx, double ly, double lz);
	double getXLength();
	void setXLength(double);
	double getYLength();
	void setYLength(double);
	double getZLength();
	void setZLength(double);
	void update();
	vtkSmartPointer<vtkPolyDataMapper> getMapper();
	vtkSmartPointer<vtkActor> getActor();
private:
	double xLength;
	double yLength;
	double zLength;
	vtkSmartPointer<vtkCubeSource> src;
};

#endif // Cube_H
