#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include "Shape.h"

namespace Ui {
	class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
	Shape* createShape(int);
	void addShape(Shape* shape);
	Shape* getShapeById(int shapeId);
	void getSelectedShapes(std::vector<Shape*> &shapes);
	void removeSelectedRows();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
	vtkSmartPointer<vtkRenderer> mRenderer;
	vtkSmartPointer<QVTKInteractor> mInteractor;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> mInteractorStyle;
	int numberOfShapes;
	std::map<int, Shape*> shapesMap;

public slots:
	void onDrawClicked();
	void onColorClicked();
	void onClearClicked();
	void onRadioBtnChecked(int);
};

#endif // MAINWINDOW_H
