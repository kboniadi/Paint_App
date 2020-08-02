#include "ellipse.h"

Ellipse::Ellipse(Ellipse &&other) noexcept
    : Rectangle{(id_t) -1}
{
    swap(other);
    std::swap(width, other.width);
    std::swap(height, other.height);
}

Ellipse &Ellipse::operator=(Ellipse &&other) noexcept
{
    Ellipse temp{std::move(other)};
    swap(temp);
    std::swap(width, temp.width);
    std::swap(height, temp.height);
    return *this;
}

void Ellipse::draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setBrush(getBrush());

	QRect rect = getRect();
	rect.moveCenter(QPoint{});

	getPainter().drawEllipse(rect);
	getPainter().end();
}

QRect Ellipse::getRect() const
{
	QRect rect{0, 0, radius_x * 2, radius_y * 2};
	rect.moveCenter(getPosition());
	return rect;
}

double Ellipse::area() const
{
    return M_PI * std::abs(radius_x) * std::abs(radius_y);
}

double Ellipse::perimeter() const
{
	double c = pow((radius_x-radius_y), 2);
	double d = pow((radius_x+radius_y), 2);
	return M_PI * (radius_x+radius_y) *
		( 3 * ( c / (d * sqrt(-3*c/d+4) + 10) ) + 1 );
}
