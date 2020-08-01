#include "line.h"
#include "shape.h"

Line::Line(Line &&other) noexcept: Shape{(id_t) -1}
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

void Line::draw(QPaintDevice *device)
{
    getPainter().begin(device);
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawLine(startPoint, endPoint);
    getPainter().end();
}

QRect Line::getRect() const
{
	QRect rect{QPoint{std::min(startPoint.x(), endPoint.x()),
					std::min(startPoint.y(), endPoint.y())},
			   QPoint{std::max(startPoint.x(), endPoint.x()),
					std::max(startPoint.y(), endPoint.y())}};
	rect.moveCenter(getPosition());
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
