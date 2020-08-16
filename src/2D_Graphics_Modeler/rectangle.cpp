#include "rectangle.h"

Rectangle::Rectangle(Rectangle &&move) noexcept
	: Shape{QPoint{}, (id_t) -1}, width{0}, height{0}
{
	swap(move);
	std::swap(width, move.width);
	std::swap(height, move.height);

	move.width = 0;
	move.height = 0;
	move.setID((id_t) -1);
	move.setPen(QPen{});
	move.setBrush(QBrush{});
}
Rectangle& Rectangle::operator=(Rectangle rhs) noexcept
{
	swap(rhs);
	std::swap(width, rhs.width);
	std::swap(height, rhs.height);
	return *this;
}

Rectangle& Rectangle::operator=(Rectangle &&rhs) noexcept
{
	Rectangle move{std::move(rhs)};
	swap(move);
	std::swap(width, move.width);
	std::swap(height, move.height);
	return *this;
}

QRect Rectangle::getRect() const
{
	QRect rect{0, 0, width, height};
	rect.moveCenter(getPos());
	return rect;
}

void Rectangle::setRect(const QRect &rect)
{
	setPos(rect.center());
	width = rect.width();
	height = rect.height();
}

//drawing the rectangle on the drawing area
void Rectangle::draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setBrush(getBrush());
	getPainter().translate(getPos());

	QRect rect = getRect();
	rect.moveCenter(QPoint{});

	getPainter().drawRect(rect);
	getPainter().end();
}

//return the area of the rectangle
double Rectangle::area() const
{
	return std::abs(width * height);
}

//return the perimeter of the rectangle
double Rectangle::perimeter() const
{
	return std::abs(2 * (width + height));
}
