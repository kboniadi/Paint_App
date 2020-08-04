#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderarea.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "polyline.h"
#include "line.h"
#include "text.h"
//need this for QGridLayout
#include <QtWidgets>
#include <QComboBox>
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //add "renderArea" as a member field in "mainwindow.h"
	renderArea = new RenderArea;
	setWindowTitle(tr("Chameleon Painter"));
	adminFeats = {
		ui->actionAdd_Ellipse,
		ui->actionAdd_Line,
		ui->actionAdd_Polygon,
		ui->actionAdd_Polyline,
		ui->actionAdd_Rectangle,
        ui->actionAdd_Text,
		ui->actionDelete,
		ui->actionOpen,
		ui->actionSave,
		ui->actionNew,
		ui->actionCopy,
        ui->actionPaste,
        ui->actionMove
	};
	SetAdminRights(false);
	this->setCentralWidget(ui->renderarea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetDrawCursor(const QCursor &cursor)
{
	ui->renderarea->setCursor(cursor);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
}

void MainWindow::on_actionLogin_triggered()
{
	Login *login = new Login(this);
	connect(login, &QDialog::accepted, std::bind(&MainWindow::SetAdminRights, this, true));
	login->show();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAbout_triggered()
{
    About *about = new About(this);
	about->setWindowTitle(tr("Meet the Team"));
    about->show();
}

void MainWindow::on_actionAdd_Rectangle_triggered()
{
	using namespace std::placeholders;
	connect(this, &MainWindow::onAreaClick, std::bind(&MainWindow::AddRect<Rectangle>, this, _1, _2));
//    Rectangle *rect = new Rectangle(renderArea->getVectLength() + 1, 6, 0, 2, 2, 2, 2, 10, 20, 200, 200, 100, QString{"Rectangle"});
//	renderArea->addShape(rect);
}

void MainWindow::on_actionAdd_Ellipse_triggered()
{
//    Ellipse *ellipse = new Ellipse(renderArea->getVectLength() + 1, 2, 12, 1, 0, 0, 0, 0, QPoint(520, 300), 170,
//								   100, QString("Ellipse"));
//	renderArea->addShape(ellipse);
}

void MainWindow::on_actionAdd_Polygon_triggered()
{
//    QPoint points[] = {QPoint(900, 190), QPoint(910, 120), QPoint(970, 140),
//                       QPoint(980, 180)};
//	Polygon *polygon = new Polygon(renderArea->getVectLength() + 1, 8, 6, 4, 0, 0, 11, 1, 4, points, QString("Polygon"));
//	renderArea->addShape(polygon);
}

void MainWindow::on_actionAdd_Polyline_triggered()
{
//    QPoint points[] = {QPoint(430, 90), QPoint(440, 20), QPoint(500, 40),
//                       QPoint(510, 80)};
//	Polyline *pLine = new Polyline(renderArea->getVectLength() + 1, 4, 6, 1, 0, 0, 0, 0, 4, points, QString("Polyline"));
//	renderArea->addShape(pLine);
}

void MainWindow::on_actionAdd_Line_triggered()
{
//	Line *line = new Line(renderArea->getVectLength() + 1, 6, 2, 4, 0, 0, 0, 0, QPoint(100, 100), QPoint(150, 200), QString("Line"));
//	renderArea->addShape(line);
}

void MainWindow::on_actionAdd_Text_triggered()
{
//	Text *text = new Text(renderArea->getVectLength() + 1, QString("Class Project"), 6,  4, 10,
//						  QString("Comic Sans MS"), 0, 2, 100, 100, 500, 100, QString("Text"));
//	renderArea->addShape(text);
}

void MainWindow::on_actionDelete_triggered()
{
	int numShapes = renderArea->getShapes().size();
    Delete *del = new Delete(numShapes, this);
    QObject::connect(del, &Delete::ID_Delete_Signal, this,
                     &MainWindow::ID_Delete_Signal_Handler);
    del->show();
}

void MainWindow::ID_Delete_Signal_Handler(int ID)
{
	renderArea->deleteShape(ID);
}

void MainWindow::on_actionMove_triggered()
{
	int numShapes = renderArea->getShapes().size();
    Move *move = new Move(numShapes, this);
    QObject::connect(move, &Move::Move_Signal, this,
                     &MainWindow::Move_Signal_Handler);
    move->show();
}

void MainWindow::Move_Signal_Handler(int ID, int x_coord, int y_coord)
{
	renderArea->moveShape(ID, x_coord, y_coord);
}

void MainWindow::on_actionLogout_triggered()
{
	SetAdminRights(false);
}

template<class T>
void MainWindow::AddRect(int x, int y)
{
	auto *rect = new T{QRect{x, y, 0, 0}};
	renderArea->getShapes().push_back(rect);
	ui->renderarea->update();
}

void MainWindow::SetAdminRights(bool val)
{
	for (auto* a: adminFeats) {
		if (auto* widget = dynamic_cast<QWidget*>(a)) {
			widget->setEnabled(val);
		}
		else if (auto* action = dynamic_cast<QAction*>(a)) {
			action->setEnabled(val);
		}
	}
	ui->actionLogin->setEnabled(!val);
	ui->actionLogout->setEnabled(val);
}
