#ifndef Cube_H
#define Cube_H

#include"Shape.h"
#include <vtkCubeSource.h>

class Cube : public Shape
{
private:
	vtkSmartPointer<vtkPolyDataMapper> getMapper() override;
public:
	Cube();
	Cube(int shapeId, double x, double y, double z, double lx, double ly, double lz);
	double getXLength() const;
	double getYLength() const;
	double getZLength() const;
	void setXLength(double);
	void setYLength(double);
	void setZLength(double);
	void update() override;
private:
	double xLength;
	double yLength;
	double zLength;
	vtkSmartPointer<vtkCubeSource> src;
};

#endif // Cube_H
