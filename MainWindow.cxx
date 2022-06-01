#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	mRenderer(vtkSmartPointer<vtkRenderer>::New()),
	mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
	mInteractorStyle(vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New())
{
	ui->setupUi(this);
	ui->sphere_radioBtn->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);
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
	QObject::connect(ui->drawSphere_button, &QPushButton::clicked,
		this, &MainWindow::onDrawSphereClick);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onDrawSphereClick() {
	double r = ui->sphereRadius_spinBox->value();
	cout << "the radius = " << r << "\n";
	double x = ui->xPosition_spinBox->value();
	cout << "the x = " << x << "\n";
	double y = ui->yPosition_spinBox->value();
	cout << "the y = " << y << "\n";
	double z = ui->zPosition_spinBox->value();
	cout << "the z = " << z << "\n";

	if (ui->sphere_radioBtn->isChecked())
		cout << "SPHERE\n";
	else if (ui->cone_radioBtn->isChecked())
		cout << "CONE\n";
	else if (ui->cube_radioBtn->isChecked())
		cout << "CUBE\n";
	else if (ui->cylinder_radioBtn->isChecked())
		cout << "Cylinder\n";
}