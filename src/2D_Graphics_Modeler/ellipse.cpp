#include "ellipse.h"

Ellipse::~Ellipse() = default;

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
	getPainter().translate(getPos());

	QRect rect = getRect();
	rect.moveCenter(QPoint{});

	getPainter().drawEllipse(rect);
	getPainter().end();
}

double Ellipse::area() const
{
	return M_PI * std::abs(width) * std::abs(height);
}

double Ellipse::perimeter() const
{
	double c = pow((width-height), 2);
	double d = pow((width+height), 2);
	return M_PI * (width+height) *
			( 3 * ( c / (d * sqrt(-3*c/d+4) + 10) ) + 1 );
}
