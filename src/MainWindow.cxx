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
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New())
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
}

MainWindow::~MainWindow()
{
	delete ui;
}

Shape* MainWindow::createShape(int type) {
	double x = ui->xPosition_spinBox->value();
	double y = ui->yPosition_spinBox->value();
	double z = ui->zPosition_spinBox->value();
	switch (type)
	{
	case 0 :
		return new Sphere(x, y, z, ui->sphereRadius_spinBox->value());
	case 1 :
		return new Cone(x, y, z, ui->coneRadius_spinBox->value(), ui->coneLength_spinBox->value());
	case 2 :
		return new Cylinder(x, y, z, ui->cylinderRadius_spinBox->value(), ui->cylinderLength_spinBox->value());
	case 3 :
		return new Cube(x, y, z, ui->cubeLength1_spinBox->value(), ui->cubeLength2_spinBox->value(), ui->cubeLength3_spinBox->value());
	default:
		return new Sphere();
	}
}

void MainWindow::onDrawClicked() {
	double x = ui->xPosition_spinBox->value();
	cout << "the x = " << x << "\n";
	double y = ui->yPosition_spinBox->value();
	cout << "the y = " << y << "\n";
	double z = ui->zPosition_spinBox->value();
	cout << "the z = " << z << "\n";
	Shape* shape = createShape(ui->buttonGroup->checkedId());
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
}

void MainWindow::onRadioBtnChecked(int id) {
	cout << id << "\n";
	ui->stackedWidget->setCurrentIndex(id);
}

void MainWindow::onColorClicked() {
	int r = 0;
	int g = 0;
	int b = 0;
	QColor color = QColorDialog::getColor();
	if (color.isValid()) {
		color.getRgb(&r, &g, &b);
		cout << r << "  " << g << "  " << b << "\n";
		std::string styleSheet = "background-color: rgb(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ");";
		ui->color_button->setStyleSheet(QString::fromUtf8(styleSheet.c_str()));
	}

}

void MainWindow::onClearClicked() {
	mRenderer->RemoveAllViewProps();
	mRenderWindow->Render();
}