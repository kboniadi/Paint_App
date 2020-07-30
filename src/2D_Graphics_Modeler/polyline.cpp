#include "polyline.h"

Polyline::Polyline(int id, int color, int width, int style, int cap, int join,
                   int brush_color, int brush_style, int verts, QPoint *points, QString shapeType)
         : Shape(id, color, width, style, cap, join, brush_color, brush_style, shapeType)
{
    vert_count = verts;
    assert(verts < 9 && verts > -1);
    for (int i = 0; i < verts; ++i)
        vert_list[i] = points[i];
}

void Polyline::Move(const int xcoord, const int ycoord)
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

void Polyline::Draw(QPaintDevice *device)
{
    getPainter().begin(device);
    getPainter().setPen(getPen());
    getPainter().setBrush(getBrush());
    getPainter().drawPolyline(vert_list, vert_count);
    getPainter().end();
}

//double Polyline::perimeter() const
//{
//    double length = 0.0;

//    for (int i = 0; i < vert_count-1; ++i)
//        length += DistanceFormu(vert_list[i], vert_list[i+1]);

//    return length;
//}
