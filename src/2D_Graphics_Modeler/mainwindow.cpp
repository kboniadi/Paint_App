#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "about.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"
#include "polyline.h"
#include "line.h"
#include "text.h"
#include "shapepropdelegate.h"
#include "proptree.h"
#include "itembutton.h"

//need this for QGridLayout
#include <QtWidgets>
#include <QComboBox>
#include <QObject>

#include <QAction>
#include <QCloseEvent>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QStatusBar>

#include <fstream>
#include <sstream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
		ui->actionMove,
		ui->prop_tree,
		ui->shapeList
	};

	SetAdminRights(false);

	storage.shapes = textParse();
	ui->renderarea->setStorage(&storage.shapes);

	ui->shapeList->setModel(&storage.model);
	ui->shapeList->setEnabled(storage.shapes.size());

	ui->prop_tree->setHeaderLabels({"Property", "Value"});
	ui->prop_tree->setItemDelegate(new ShapePropDelegate());
	ui->prop_tree->setEditTriggers(QAbstractItemView::AllEditTriggers);
	modified = false;
	this->setCentralWidget(ui->renderarea);
}

MainWindow::~MainWindow()
{
	delete ui->prop_tree->itemDelegate();
	delete ui;
}

void MainWindow::SetDrawCursor(const QCursor &cursor)
{
	ui->renderarea->setCursor(cursor);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (!modified)
		event->accept();
}

void MainWindow::on_shapeList_currentIndexChanged(int index)
{
	disconnect(ui->prop_tree, &QTreeWidget::itemChanged, nullptr, nullptr);
	QTreeWidgetItem* old = ui->prop_tree->topLevelItem(0);
	if (old) {
		ui->prop_tree->removeItemWidget(old, 0);
		delete old;
	}

	if (index < (int) storage.shapes.size()) {
		Shape* s = storage.shapes[index];
		new PropertyItem<Shape>(ui->prop_tree->invisibleRootItem(), *s);
		ui->prop_tree->expandAll();
	}

	ui->renderarea->setSelected(index);
	ui->prop_tree->update();

	connect(ui->prop_tree, &QTreeWidget::itemChanged, this, &MainWindow::onDataChanged);
}

void MainWindow::onDataChanged()
{
	ui->renderarea->update();
	modified = true;
	ui->shapeList->setEnabled(storage.shapes.size());
//	this->setWindowTitle(QString("%1*").arg("Chameleon Painter"));
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
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
	using namespace std::placeholders;
	connect(this, &MainWindow::onCanvasClick, std::bind(&MainWindow::AddRect<Rectangle>, this, _1, _2));
}

void MainWindow::on_actionAdd_Ellipse_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);

	using namespace std::placeholders;
	connect(this, &MainWindow::onCanvasClick, std::bind(&MainWindow::AddRect<Ellipse>, this, _1, _2));
}

void MainWindow::on_actionAdd_Polygon_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
//	SetStatusText("Click the first point for the polygon");

	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		auto* poly = new Polygon{{QPoint{x, y}}};
		storage.shapes.push_back(poly);
		storage.model.itemsChanged();
		onDataChanged();

		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);

//		Use existing point adding logic
		auto* item = ui->prop_tree->topLevelItem(0)->child(3)->child(0);
		auto* propitem = dynamic_cast<PropertyItem<QList<QPoint>>*>(item);
		propitem->add();
	});
}

void MainWindow::on_actionAdd_Polyline_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
//	SetStatusText("Click the first point for the polygon");

	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		auto* poly = new Polyline{{QPoint{x, y}}};
		storage.shapes.push_back(poly);
		storage.model.itemsChanged();
		onDataChanged();

		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);

		// Use existing point adding logic
		auto* item = ui->prop_tree->topLevelItem(0)->child(2)->child(0);
		auto* propitem = dynamic_cast<PropertyItem<QList<QPoint>>*>(item);
		propitem->add();
	});
}

void MainWindow::on_actionAdd_Line_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
//	SetStatusText("Click the starting point for the line");

	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		auto* line = new Line{QPoint{x, y}, QPoint{x, y}};
		storage.shapes.push_back(line);
		storage.model.itemsChanged();
		onDataChanged();

		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);

		disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
//		SetStatusText("Click the ending point for the line");
		connect(this, &MainWindow::onCanvasClick, [this, line](int x, int y) {
			Disconnect();

			line->setEnd(QPoint{x, y});
			onDataChanged();
		});
	});
}

void MainWindow::on_actionAdd_Text_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
//	SetStatusText("Click to add a text box");

	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		Disconnect();
		storage.shapes.push_back(new Text{QPen{}, QBrush{}, QPoint{x, y}, 0, QFont{}, "", Qt::AlignCenter, -1, -1});
		storage.model.itemsChanged();
		onDataChanged();

		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);

		auto* item = ui->prop_tree->topLevelItem(0)->child(1)->child(0);
		ui->prop_tree->setCurrentItem(item);
		ui->prop_tree->editItem(item, 1);
	});
}

void MainWindow::on_actionDelete_triggered()
{
	int numShapes = ui->shapeList->currentIndex();
	auto it = storage.shapes.begin();
	for (int i = 0; i < numShapes; i++) {
		++it;
	}
	delete *it;

	storage.shapes.erase(it);
	storage.model.itemsChanged();
	onDataChanged();

	if (storage.shapes.size() == 0) {
		on_shapeList_currentIndexChanged(0);
	}
	else if (numShapes >= (int) storage.shapes.size()) {
		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);
	}
	else {
		ui->shapeList->setCurrentIndex(numShapes);
	}
}

void MainWindow::on_actionMove_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
	int numShapes = ui->shapeList->currentIndex();
	using namespace std::placeholders;
	QObject::connect(this, &MainWindow::onCanvasClick, [this, numShapes](int x, int y){
		Disconnect();
		storage.shapes[numShapes]->setPos(x, y);
		storage.model.itemsChanged();
		ui->shapeList->setCurrentIndex(numShapes);
		onDataChanged();
	});
}

void MainWindow::on_actionLogout_triggered()
{
	SetAdminRights(false);
}

template<class T>
void MainWindow::AddRect(int x, int y)
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
	auto *rect = new T{QRect{x, y, 0, 0}};
	storage.shapes.push_back(rect);
	storage.model.itemsChanged();
	onDataChanged();

	ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);
	auto* item = ui->prop_tree->topLevelItem(0)->child(3);
	auto* widget = dynamic_cast<ItemButton*>(ui->prop_tree->itemWidget(item, 1));
	widget->clicked(1);
}

void MainWindow::Disconnect()
{
	QObject::disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
	SetDrawCursor(Qt::ArrowCursor);
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
