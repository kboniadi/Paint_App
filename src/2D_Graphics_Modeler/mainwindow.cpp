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
#include "serialization.h"

//#include <QAction>
#include <QCloseEvent>
//#include <QComboBox>
//#include <QMessageBox>
//#include <QPushButton>
//#include <QStatusBar>
#include <QFileDialog>
//#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	resize(sizeHint());
	setWindowTitle(tr("Chameleon Painter (Untitled)"));
	ui->statusbar->addWidget(&status);
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
	};

	SetAdminRights(false);

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

void MainWindow::SetStatusBar(const QString &str, int timeout)
{
	if (timeout == 0) {
		ui->statusbar->clearMessage();
		status.setText(str);
		if (str.isEmpty()) {
			status.hide();
		}
		else {
			status.show();
		}
	}
	else {
		ui->statusbar->showMessage(str, timeout);
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (!modified)
		event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		SetStatusBar("");
		Disconnect();
	}
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
	SetStatusBar("Click to set the top-left coordinate of the Rectangle");
	using namespace std::placeholders;
	connect(this, &MainWindow::onCanvasClick, std::bind(&MainWindow::AddRect<Rectangle>, this, _1, _2));
}

void MainWindow::on_actionAdd_Ellipse_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
	SetStatusBar("Click to set the top-left coordinate of the Ellipse");
	using namespace std::placeholders;
	connect(this, &MainWindow::onCanvasClick, std::bind(&MainWindow::AddRect<Ellipse>, this, _1, _2));
}

void MainWindow::on_actionAdd_Polygon_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
	SetStatusBar("Click to set the first point for the Polygon");

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
	SetStatusBar("Click to set the first point for the Polyline");

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
	SetStatusBar("Click and drag to set the top-left and bottom-right points for the line");

	connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		auto* line = new Line{QPoint{x, y}, QPoint{x, y}};
		storage.shapes.push_back(line);
		storage.model.itemsChanged();
		onDataChanged();

		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);

		disconnect(this, &MainWindow::onCanvasClick, nullptr, nullptr);
//		SetStatusBar("Click to set the ending point for the line");
		connect(this, &MainWindow::onCanvasDrag, [this, line](int x, int y) {
//			Disconnect();

			line->setEnd(QPoint{x, y});
			onDataChanged();
		});
	});
}

void MainWindow::on_actionAdd_Text_triggered()
{
	Disconnect();
	SetDrawCursor(Qt::CrossCursor);
	SetStatusBar("Click to add a text box");

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
	Disconnect();
	SetDrawCursor(Qt::PointingHandCursor);
	SetStatusBar("Hit the ESC key to exit delete mode");
	QObject::connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		int count = storage.shapes.size() - 1;
		if (storage.shapes.size() != 0) {
			for (auto it = storage.shapes.rbegin(); it != storage.shapes.rend(); ++it) {
				if (x >= (*it)->getRect().x() &&
					x <= (*it)->getRect().x() + (*it)->getRect().width() &&
					y >= (*it)->getRect().y() &&
					y <= (*it)->getRect().y() + (*it)->getRect().height()) {
					ui->shapeList->setCurrentIndex(count);

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

					break;
				}
				--count;
			}
//			int numShapes = ui->shapeList->currentIndex();
//			auto it = storage.shapes.begin();
//			for (int i = 0; i < numShapes; i++) {
//				++it;
//			}
//			delete *it;

//			storage.shapes.erase(it);
//			storage.model.itemsChanged();
//			onDataChanged();

//			if (storage.shapes.size() == 0) {
//				on_shapeList_currentIndexChanged(0);
//			}
//			else if (numShapes >= (int) storage.shapes.size()) {
//				ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);
//			}
//			else {
//				ui->shapeList->setCurrentIndex(numShapes);
//			}
		}
	});
//	int numShapes = ui->shapeList->currentIndex();
//	auto it = storage.shapes.begin();
//	for (int i = 0; i < numShapes; i++) {
//		++it;
//	}
//	delete *it;

//	storage.shapes.erase(it);
//	storage.model.itemsChanged();
//	onDataChanged();

//	if (storage.shapes.size() == 0) {
//		on_shapeList_currentIndexChanged(0);
//	}
//	else if (numShapes >= (int) storage.shapes.size()) {
//		ui->shapeList->setCurrentIndex(storage.shapes.size() - 1);
//	}
//	else {
//		ui->shapeList->setCurrentIndex(numShapes);
//	}
}

void MainWindow::on_actionMove_triggered()
{
	Disconnect();
	SetStatusBar("Hit the ESC key to exit move mode");
	SetDrawCursor(Qt::OpenHandCursor);

	QObject::connect(this, &MainWindow::onCanvasClick, [this](int x, int y) {
		int count = storage.shapes.size() - 1;
		int dx = 0;
		int dy = 0;
//		qDebug() << storage.shapes[0]->getRect().x() << " " << storage.shapes[0]->getRect().y() << '\n';
//		qDebug() << storage.shapes[0]->getRect().center() << '\n';
//		qDebug() << x << ' ' << y << '\n';
//		qDebug() << storage.shapes[0]->getPos() << '\n';
		if (storage.shapes.size() != 0) {
			for (auto it = storage.shapes.rbegin(); it != storage.shapes.rend(); it++) {
				if (x >= (*it)->getRect().x() &&
					x <= (*it)->getRect().x() + (*it)->getRect().width() &&
					y >= (*it)->getRect().y() &&
					y <= (*it)->getRect().y() + (*it)->getRect().height()) {
					ui->shapeList->setCurrentIndex(count);
					dx = x - (*it)->getRect().center().x();
					dy = y - (*it)->getRect().center().y();

					QObject::connect(this, &MainWindow::onCanvasDrag, [this, dx, dy](int x, int y) {
						int index = ui->shapeList->currentIndex();
						storage.shapes[index]->setPos(x - dx, y - dy);
						storage.model.itemsChanged();
						onDataChanged();
						ui->shapeList->setCurrentIndex(index);
					});

					break;
				} else {
					DisconnectDrag();
				}
				--count;
			}
		}
	});

//	QObject::connect(this, &MainWindow::onCanvasDrag, [this, dx, dy](int x, int y) {
//		int index = ui->shapeList->currentIndex();
//		storage.shapes[index]->setPos(x - dx, y - dy);
//		storage.model.itemsChanged();
//		onDataChanged();
//		ui->shapeList->setCurrentIndex(index);
//	});


//	QObject::connect(this, &MainWindow::onCanvasDrag, [this](int x, int y) {
//		int index = 0;
//		if (storage.shapes.size() != 0) {
//			index = ui->shapeList->currentIndex();
//			if (x >= storage.shapes[index]->getRect().x() &&
//				x <= storage.shapes[index]->getRect().x() + storage.shapes[index]->getRect().width() &&
//				y >= storage.shapes[index]->getRect().y() &&
//				y <= storage.shapes[index]->getRect().y() + storage.shapes[index]->getRect().height()) {
//				storage.shapes[index]->setPos(x, y);
//				storage.model.itemsChanged();
//				onDataChanged();
//				ui->shapeList->setCurrentIndex(index);
//			}
//		}
//	});

//	for (auto it = storage.shapes.begin(); it != storage.shapes.end(); ++it) {
//		if (x >= (*it)->getRect().x() &&
//			x <= (*it)->getRect().x() + (*it)->getRect().width() &&
//			y >= (*it)->getRect().y() &&
//			y <= (*it)->getRect().y() + (*it)->getRect().height()) {
//			storage.shapes[numShapes]->setPos(x, y);
//			storage.model.itemsChanged();
//			ui->shapeList->setCurrentIndex(numShapes);
//			onDataChanged();
//			break;
//		}
//	}
//	QObject::connect(this, &MainWindow::onCanvasDoubleClick, [this](int x, int y) {
//		int count = 0;
//		for (auto it = storage.shapes.begin(); it != storage.shapes.end(); ++it) {
//			if (x >= (*it)->getRect().x() &&
//				x <= (*it)->getRect().x() + (*it)->getRect().width() &&
//				y >= (*it)->getRect().y() &&
//				y <= (*it)->getRect().y() + (*it)->getRect().height()) {
//				ui->shapeList->setCurrentIndex(count);
//				break;
//			}
//			count++;
//		}
//	});

}

void MainWindow::on_actionLogout_triggered()
{
	SetAdminRights(false);
}

void MainWindow::on_actionNew_triggered()
{
	for (auto itr = storage.shapes.begin(); itr != storage.shapes.end(); ++itr)
		delete *itr;

	Shape::shapeid = 0;
	setWindowTitle(tr("Chameleon Painter (Untitled)"));
	storage.shapes.clear();
	storage.model.itemsChanged();
	on_shapeList_currentIndexChanged(0);
	onDataChanged();
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
	QObject::disconnect(this, &MainWindow::onCanvasDrag, nullptr, nullptr);
	SetDrawCursor(Qt::ArrowCursor);
	SetStatusBar("");
}

void MainWindow::DisconnectDrag()
{
	QObject::disconnect(this, &MainWindow::onCanvasDrag, nullptr, nullptr);
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

void MainWindow::on_actionSave_triggered()
{
	QString filter = "TEXT file (*.txt)";
	QString filename = QFileDialog::getSaveFileName(this,
													tr("Save File"),
													QDir::homePath(),
													filter);

	if (!filename.contains(tr(".txt"))) {
		filename.append(".txt");
	}

	QFileInfo info{filename};
	{
		std::ofstream file{filename.toStdString()};
		file << storage.shapes;
	}

	SetStatusBar("File has been saved", 1000);
	setWindowTitle(tr("Chameleon Painter (%1)").arg(info.fileName()));
}

void MainWindow::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this,
													tr("Open File"),
													QDir::homePath(),
													tr("TEXT file (*.txt)"));

	if (!filename.isEmpty()) {
		QFileInfo info{filename};
		on_actionNew_triggered();
		storage.shapes = textParse(filename);
		onDataChanged();
		setWindowTitle(tr("Chameleon Painter (%1)").arg(info.fileName()));
	}
}
