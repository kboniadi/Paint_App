#include "polyline.h"

Polyline::Polyline(std::vector<QPoint> points, id_t id, const QPen& pen,
	const QBrush& brush)
	: Shape(QPoint{}, id, pen, brush), points{std::move(points)}
{
	setCenter();
}

Polyline::Polyline(Polyline &&move) noexcept
	: Shape{QPoint{}, (id_t) -1}
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
	QPoint start = (points.empty() ? QPoint{} : points[0]) + getPos();
		QRect rect{start, start};
		for (auto p: points) {
			rect.setLeft(std::min(p.x() + getPos().x(), rect.left()));
			rect.setRight(std::max(p.x() + getPos().x(), rect.right()));
			rect.setTop(std::min(p.y() + getPos().y(), rect.top()));
			rect.setBottom(std::max(p.y() + getPos().y(), rect.bottom()));
		}
		return rect;
}

void Polyline::draw(QPaintDevice *device)
{
    getPainter().begin(device);
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
	getPainter().translate(getPos());
	getPainter().drawPolyline(points.data(), points.size());
    getPainter().end();
}

void Polyline::setCenter()
{
	QPoint temp = getPos();
	setPos(getRect().center());
	QPoint offset = temp - getPos();

	for (auto& a: points)
		a += offset;
}
