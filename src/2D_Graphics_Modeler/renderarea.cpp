#include <QMouseEvent>
#include "renderarea.h"
#include "mainwindow.h"

#include <QMouseEvent>

RenderArea::RenderArea(QWidget *parent)
	: QWidget(parent), shapes{nullptr}, target{":/res/img/target_small.png"}, selected{-1}
{
    //sets the background to white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
	setMouseTracking(true);
//	shapes_list = textParse();
//    update();
}

//QSize RenderArea::sizeHint() const
//{
//    return QSize(400, 200);
//}

//QSize RenderArea::minimumSizeHint() const
//{
//	return QSize(1200, 700);
//}

void RenderArea::setStorage(cs1c::vector<Shape *> *v)
{
	shapes = v;
}

void RenderArea::setSelected(int x)
{
	selected = x;
	update();
}

void RenderArea::paintEvent(QPaintEvent */*event*/)
{
	static QPoint offset{target.size().width() / 2, target.size().height() / 2};
	if (shapes) {
		//initialize variables for specific shapes
		//e.g. QPoints for a polygon
		for (auto it = shapes->begin(); it != shapes->end(); ++it) {
			(*it)->draw(this);
		}

		if (selected >= 0 && selected < (int) shapes->size()) {
			Shape* s = (*shapes)[selected];
			QPainter paint{this};
			QPen outline;
			outline.setStyle(Qt::NoPen);
			paint.setPen(outline);
			paint.drawRect(s->getRect().marginsAdded(QMargins{2, 2, 2, 2}));
			paint.drawImage(s->getPos() - offset, target);
		}

	}
}

void RenderArea::addShape(Shape *shape)
{
	shapes->push_back(shape);
    update();
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
	if (event->button() & Qt::LeftButton) {
		dynamic_cast<MainWindow*>(window())->onCanvasClick(event->x(), event->y());
	}
}
