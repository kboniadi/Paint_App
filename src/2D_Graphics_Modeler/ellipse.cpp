#include "ellipse.h"

Ellipse::Ellipse(int id, int color, int pen_width, int style, int cap, int join,
    int brush_color, int brush_style, QPoint center, int a, int b, QString shapeType)
    : Shape(id, color, pen_width, style, cap, join, brush_color, brush_style, shapeType),
      center(center), a(a), b(b)
{}

void Ellipse::Move(const int xcoord, const int ycoord)
{
    center = QPoint(xcoord, ycoord);
}

void Ellipse::Draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setBrush(getBrush());
	getPainter().drawEllipse(center, a, b);
	getPainter().end();
}

double Ellipse::area() const
{
    return M_PI * a * b;
}

double Ellipse::perimeter() const
{
    double c = pow((a-b), 2);
    double d = pow((a+b), 2);
    return M_PI * (a+b) * ( 3 * ( c / (d * sqrt(-3*c/d+4) + 10) ) + 1 );
}
