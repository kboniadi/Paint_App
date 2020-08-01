#include "polyline.h"

Polyline::Polyline(const id_t id, const QPen& pen,
				   const QBrush& brush, cs1c::vector<QPoint> points)
	: Shape(id, pen, brush, QPoint{}), points{std::move(points)}
{
	setCenter();
}

Polyline::Polyline(Polyline &&move) noexcept
    : Shape{(id_t) -1}
{
    swap(move);
    std::swap(points, move.points);
}

Polyline& Polyline::operator=(Polyline &&other) noexcept
{
    Polyline temp{std::move(other)};
    swap(temp);
    std::swap(points, temp.points);
    return *this;
}

QRect Polyline::getRect() const
{
	QPoint start = (points.empty() ? QPoint{} : points[0]) + getPosition();
		QRect rect{start, start};
		for (auto p: points) {
			rect.setLeft(std::min(p.x() + getPosition().x(), rect.left()));
			rect.setRight(std::max(p.x() + getPosition().x(), rect.right()));
			rect.setTop(std::min(p.y() + getPosition().y(), rect.top()));
			rect.setBottom(std::max(p.y() + getPosition().y(), rect.bottom()));
		}
		return rect;
}

void Polyline::draw(QPaintDevice *device)
{
    getPainter().begin(device);
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
	getPainter().drawPolyline(&(*points.begin()), points.size());
    getPainter().end();
}

void Polyline::setCenter()
{
	QPoint temp = getPosition();
	setPosition(getRect().center());
	QPoint offset = temp - getPosition();

	for (auto a: points)
		a += offset;
}
