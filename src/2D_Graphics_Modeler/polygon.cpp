#include "polygon.h"

Polygon::Polygon(std::vector<QPoint> points, const Shape::id_t id, const QPen &pen, const QBrush &brush)
	: Polyline{std::move(points), id, pen, brush} {}

Polygon::~Polygon() = default;

Polygon::Polygon(Polygon &&other) noexcept
	: Polyline{{QPoint{}}, (id_t) -1}
{
    swap(other);
    std::swap(points, other.points);
}

Polygon &Polygon::operator=(Polygon &&other) noexcept
{
    Polygon temp{std::move(other)};
    swap(temp);
    std::swap(points, temp.points);
    return *this;
}

void Polygon::draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setBrush(getBrush());
	getPainter().translate(getPos());
	getPainter().drawPolygon(points.data(), points.size());
	getPainter().end();
}

double Polygon::area() const
{
	double area = 0.0;
	int j = points.size() - 1;

	for (std::size_t i = 0; i < points.size(); ++i) {
		area += (points[j].x() + points[i].x()) *
		(points[j].y() - points[i].y());
		j = i;
	}

	return std::abs(area / 2.0);
}

double Polygon::perimeter() const
{
	double perimeter = 0.0;
	int j = points.size() - 1;

	for (std::size_t i = 0; i < points.size(); ++i) {
		perimeter += Dist_Formu(points[i], points[j]);
		j = i;
	}

	return perimeter;
}
