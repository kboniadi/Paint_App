#include "rectangle.h"

Rectangle::Rectangle(int id, int color, int penWidth, int style, int cap, int join,
	int brushColor, int brushStyle, int aX, int aY, double aWidth,
    double aLength, QString shapeType)
    :Shape(id, color, penWidth, style, cap, join, brushColor, brushStyle, shapeType),
		x(aX), y(aY), width(aWidth), length(aLength)
{}

//drawing the rectangle on the drawing area
void Rectangle::Draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setBrush(getBrush());
	getPainter().drawRect(x,y, width , length);
	getPainter().end();
}

//move the rectangle
void Rectangle::Move(const int xcoord, const int ycoord)
{
  x = xcoord;
  y = ycoord;
}

//return the area of the rectangle
double Rectangle::area() const
{
    return width * length;
}

//return the perimeter of the rectangle
double Rectangle::perimeter() const
{
	return 2 * (width + length);
}

