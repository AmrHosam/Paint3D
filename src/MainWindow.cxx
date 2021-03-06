#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QColorDialog>
#include <QString>
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Cube.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New()),
	numberOfShapes(1)
{
	ui->setupUi(this);
	QMainWindow::showMaximized();
	ui->buttonGroup->setId(ui->sphere_radioBtn, 0);
	ui->buttonGroup->setId(ui->cone_radioBtn, 1);
	ui->buttonGroup->setId(ui->cylinder_radioBtn, 2);
	ui->buttonGroup->setId(ui->cube_radioBtn, 3);
	ui->stackedWidget->setCurrentIndex(ui->buttonGroup->checkedId());

	// Set up the rendering
	mRenderWindow->AddRenderer(mRenderer);
	mRenderWindow->SetInteractor(mInteractor);
	ui->openGLWidget->setRenderWindow(mRenderWindow);
	mInteractor->SetInteractorStyle(mInteractorStyle);
	mInteractor->Initialize();
	mRenderer->ResetCamera();
	// Set the background color 
	mRenderer->SetBackground(1, 1, 1);

	// Set the UI connections
	QObject::connect(ui->draw_button, &QPushButton::clicked,
		this, &MainWindow::onDrawClicked);
	QObject::connect(ui->color_button, &QPushButton::clicked,
		this, &MainWindow::onColorClicked);
	QObject::connect(ui->clear_button, &QPushButton::clicked,
		this, &MainWindow::onClearClicked);
	QObject::connect(ui->buttonGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &MainWindow::onRadioBtnChecked);
	
	QObject::connect(ui->xPosition_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), 
		this, &MainWindow::onXPosChange);
	QObject::connect(ui->yPosition_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onYPosChange);
	QObject::connect(ui->zPosition_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onZPosChange);

	QObject::connect(ui->sphereRadius_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			this, &MainWindow::onSphereRediusChange);

	QObject::connect(ui->coneRadius_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onConeRediusChange);
	QObject::connect(ui->coneLength_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onConeHeightChange);

	QObject::connect(ui->cylinderRadius_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onCylinderRediusChange);
	QObject::connect(ui->cylinderLength_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onCylinderHeightChange);

	QObject::connect(ui->cubeLength1_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onCubeXLengthChange);
	QObject::connect(ui->cubeLength2_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onCubeYLengthChange);
	QObject::connect(ui->cubeLength3_spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
		this, &MainWindow::onCubeZLengthChange);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::addShape(Shape* shape) {
	shapesMap[numberOfShapes++] = shape;
}

Shape* MainWindow::getShapeById(int shapeId) {
	std::map<int, Shape*>::iterator it = shapesMap.find(shapeId);
	if (it != shapesMap.end())
		return it->second;
	return nullptr;
}

void MainWindow::getSelectedShapes(std::vector<Shape*> &shapes){
	QList<QTableWidgetItem *> list = ui->shapes_table->selectedItems();
	for (int i = 0; i < list.size(); i++) {
		if (list[i]->column() == 0) {
			int id = std::atoi(list[i]->text().toStdString().c_str());
			Shape* shape = getShapeById(id);
			if (shape != nullptr)
				shapes.push_back(shape);
		}
	}
}

void MainWindow::removeSelectedRows() {
	QList<QTableWidgetItem *> list = ui->shapes_table->selectedItems();
	for (int i = 0; i < list.size(); i++) {
		ui->shapes_table->removeRow(list[i]->row());
	}
}

Shape* MainWindow::createShape(int type) {
	double x = ui->xPosition_spinBox->value();
	double y = ui->yPosition_spinBox->value();
	double z = ui->zPosition_spinBox->value();
	Shape* shape = nullptr;
	switch (type)
	{
	case 0 :
		shape = new Sphere(numberOfShapes, x, y, z, ui->sphereRadius_spinBox->value());
		break;
	case 1 :
		shape = new Cone(numberOfShapes, x, y, z, ui->coneRadius_spinBox->value(), ui->coneLength_spinBox->value());
		break;
	case 2 :
		shape = new Cylinder(numberOfShapes, x, y, z, ui->cylinderRadius_spinBox->value(), ui->cylinderLength_spinBox->value());
		break;
	case 3 :
		shape = new Cube(numberOfShapes, x, y, z, ui->cubeLength1_spinBox->value(), ui->cubeLength2_spinBox->value(), ui->cubeLength3_spinBox->value());
		break;
	default:
		return shape;
	}
	addShape(shape);
	return shape;
}

void MainWindow::onDrawClicked() {

	Shape* shape = createShape(ui->buttonGroup->checkedId());
	if (shape == nullptr)
		return;
	shape->setupShape();
	vtkSmartPointer<vtkActor> actor = shape->getActor();

	int r = 255, g = 0, b = 0;
	QColor color = ui->color_button->palette().background().color();
	if (color.isValid()) {
		color.getRgb(&r, &g, &b);
	}
	actor->GetProperty()->SetColor(r/255.0, g/255.0, b/255.0);

	mRenderer->AddActor(actor);
	mRenderer->ResetCamera();
	mRenderWindow->Render();

	ui->shapes_table->insertRow(ui->shapes_table->rowCount());
	ui->shapes_table->setItem(ui->shapes_table->rowCount() - 1, 0, new QTableWidgetItem(std::to_string(shape->getID()).c_str()));
	ui->shapes_table->setItem(ui->shapes_table->rowCount() - 1, 1, new QTableWidgetItem(shape->getName().c_str()));
}

void MainWindow::onRadioBtnChecked(int id) {
	ui->stackedWidget->setCurrentIndex(id);
}

void MainWindow::onColorClicked() {
	int r = 0, g = 0, b = 0;
	QColor color = QColorDialog::getColor();
	if (color.isValid()) {
		color.getRgb(&r, &g, &b);
		std::string styleSheet = "background-color: rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ");";
		ui->color_button->setStyleSheet(QString::fromUtf8(styleSheet.c_str()));

		//change the color of the selected shapes if any
		std::vector<Shape*> selectedShapes(0);
		getSelectedShapes(selectedShapes);
		for (int i = 0; i < selectedShapes.size(); i++) {
			selectedShapes[i]->getActor()->GetProperty()->SetColor(r / 255.0, g / 255.0, b / 255.0);
			mRenderWindow->Render();
		}
	}

}

void MainWindow::onClearClicked() {
	std::vector<Shape*> shapes(0);
	getSelectedShapes(shapes);
	for (int i = 0; i < shapes.size(); i++) {
		mRenderer->RemoveActor(shapes[i]->getActor());
		shapesMap.erase(shapes[i]->getID());
	}
	removeSelectedRows();
	mRenderWindow->Render();
}

void MainWindow::onXPosChange(double x) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		selectedShapes[i]->setX(x);
		selectedShapes[i]->update();
	}
	mRenderWindow->Render();
}
void MainWindow::onYPosChange(double y) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		selectedShapes[i]->setY(y);
		selectedShapes[i]->update();
	}
	mRenderWindow->Render();
}
void MainWindow::onZPosChange(double z) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		selectedShapes[i]->setZ(z);
		selectedShapes[i]->update();
	}
	mRenderWindow->Render();
}

void MainWindow::onSphereRediusChange(double r) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Sphere* sphere = dynamic_cast<Sphere*>(selectedShapes[i]);
		if (sphere) {
			sphere->setRadius(r);
			sphere->update();
		}
	}
	mRenderWindow->Render();
}

void MainWindow::onConeRediusChange(double r) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cone* shape = dynamic_cast<Cone*>(selectedShapes[i]);
		if (shape) {
			shape->setRadius(r);
			shape->update();
		}
	}
	mRenderWindow->Render();
}
void MainWindow::onConeHeightChange(double h) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cone* shape = dynamic_cast<Cone*>(selectedShapes[i]);
		if (shape) {
			shape->setHeight(h);
			shape->update();
		}
	}
	mRenderWindow->Render();
}

void MainWindow::onCylinderRediusChange(double r) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cylinder* shape = dynamic_cast<Cylinder*>(selectedShapes[i]);
		if (shape) {
			shape->setRadius(r);
			shape->update();
		}
	}
	mRenderWindow->Render();
}
void MainWindow::onCylinderHeightChange(double h) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cylinder* shape = dynamic_cast<Cylinder*>(selectedShapes[i]);
		if (shape) {
			shape->setHeight(h);
			shape->update();
		}
	}
	mRenderWindow->Render();
}

void MainWindow::onCubeXLengthChange(double l) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cube* shape = dynamic_cast<Cube*>(selectedShapes[i]);
		if (shape) {
			shape->setXLength(l);
			shape->update();
		}
	}
	mRenderWindow->Render();
}
void MainWindow::onCubeYLengthChange(double l) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cube* shape = dynamic_cast<Cube*>(selectedShapes[i]);
		if (shape) {
			shape->setYLength(l);
			shape->update();
		}
	}
	mRenderWindow->Render();
}
void MainWindow::onCubeZLengthChange(double l) {
	std::vector<Shape*> selectedShapes(0);
	getSelectedShapes(selectedShapes);
	for (int i = 0; i < selectedShapes.size(); i++) {
		Cube* shape = dynamic_cast<Cube*>(selectedShapes[i]);
		if (shape) {
			shape->setZLength(l);
			shape->update();
		}
	}
	mRenderWindow->Render();
}