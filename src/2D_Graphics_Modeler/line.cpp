#include "line.h"
#include "shape.h"

Line::Line(int id, int color, int width, int style, int cap, int join,
            int brush_color, int brush_style, QPoint point1, QPoint point2, QString shapeType)
            : Shape(id, color, width, style, cap, join, brush_color, brush_style, shapeType)
{
    startPoint = point1;
    endPoint = point2;
}

void Line::Move(const int xcoord, const int ycoord)
{

	int xOffset = endPoint.x() - startPoint.x();
	int yOffset = endPoint.y() - startPoint.y();

	 startPoint.setX(xcoord);
	 startPoint.setY(ycoord);

	 endPoint.setX(xcoord + xOffset);
	 endPoint.setY(ycoord + yOffset);
}

void Line::Draw(QPaintDevice *device)
{
    getPainter().begin(device);
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawLine(startPoint, endPoint);
    getPainter().end();
}

double Line::area() const
{
	return -1;
}

double Line::perimeter() const
{
	return -1;
}
