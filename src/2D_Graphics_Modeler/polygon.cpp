#include "polygon.h"

Polygon::Polygon(int id, int color, int width, int style, int cap, int join,
    int brush_color, int brush_style, int verts, QPoint *points, QString shapeType)
    : Shape(id, color, width, style, cap, join, brush_color, brush_style, shapeType)
{
	vert_count = verts;
    assert(verts < 9 && verts > -1);
	for (int i = 0; i < verts; ++i) {
		vert_list[i] = points[i];
	}
}

void Polygon::Move(const int xcoord, const int ycoord)
{
    if (vert_count > 0) {
        int xOffset = xcoord - vert_list[0].x();
        int yOffset = ycoord - vert_list[0].y();

        for (int i = 0; i < vert_count; ++i) {
            vert_list[i].setX( vert_list[i].x() + xOffset );
            vert_list[i].setY( vert_list[i].y() + yOffset );
        }
    }
}

void Polygon::Draw(QPaintDevice *device)
{
	getPainter().begin(device);
	getPainter().setPen(getPen());
	getPainter().setBrush(getBrush());
	getPainter().drawConvexPolygon(vert_list, vert_count);
	getPainter().end();
}

double Polygon::area() const
{
	double area = 0.0;
	int j = vert_count - 1;

	for (int i = 0; i < vert_count; ++i) {
		area += (vert_list[j].x() + vert_list[i].x()) *
		(vert_list[j].y() - vert_list[i].y());
		j = i;
	}

	return abs(area / 2.0);
}

double Polygon::perimeter() const
{
	double perimeter = 0.0;
	int j = vert_count - 1;

	for (int i = 0; i < vert_count; ++i) {
		perimeter += Dist_Formu(vert_list[i], vert_list[j]);
		j = i;
	}

	return perimeter;
}
