#include "line.h"
#include "shape.h"
#include <QDebug>

static QPoint center(QPoint &A, QPoint &B, const QPoint &offset)
{
	QPoint center = (A + offset + B + offset) / 2;
	A += offset - center;
	B += offset - center;
	return center;
}


Line::Line(const QPoint &pos_A, const QPoint &pos_B, Shape::id_t id, const QPen &pen, const QBrush &brush)
	: Shape{QPoint{}, id, pen, brush}, startPoint{pos_A}, endPoint{pos_B}
{
	setPos(center(startPoint, endPoint, getPos()));
}

Line::Line(Line &&other) noexcept: Shape{QPoint{}, (id_t) -1}
{
    swap(other);
    std::swap(startPoint, other.startPoint);
    std::swap(endPoint, other.endPoint);
}

Line &Line::operator=(Line &&other) noexcept
{
    Line temp{std::move(other)};
    swap(temp);
    std::swap(startPoint, other.startPoint);
    std::swap(endPoint, other.endPoint);
	return *this;
}

void Line::setStart(const QPoint &otherstart)
{
	startPoint = otherstart - getPos();
	setPos(center(startPoint, endPoint, getPos()));
}

void Line::setEnd(const QPoint &otherend)
{
	endPoint = otherend - getPos();
	setPos(center(startPoint, endPoint, getPos()));
}

void Line::draw(QPaintDevice *device)
{
    getPainter().begin(device);
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
	getPainter().translate(getPos());
    getPainter().drawLine(startPoint, endPoint);
    getPainter().end();
}

QRect Line::getRect() const
{
	QRect rect{QPoint{std::min(startPoint.x(), endPoint.x()),
					std::min(startPoint.y(), endPoint.y())},
			   QPoint{std::max(startPoint.x(), endPoint.x()),
					std::max(startPoint.y(), endPoint.y())}};
	rect.moveCenter(getPos());
	return  rect;
}

double Line::area() const
{
	return -1;
}

double Line::perimeter() const
{
	return -1;
}
