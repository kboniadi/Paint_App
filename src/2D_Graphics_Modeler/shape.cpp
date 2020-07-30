#include "shape.h"


Shape::Shape(int shapeId, int color, QString shapeType) : id{shapeId}, shape{shapeType}
{
    pen.setColor(color_list[color]);
}

Shape::Shape(int shapeId, int color, int width, int style, int cap, int join,
             int brush_color, int brush_style, QString shapeType) : id{shapeId}, shape{shapeType}
{
	assert(color < 17 && color > -1);
	assert(style < 7 && style > -1);
	assert(cap < 3 && cap > -1);
	assert(join < 4 && join > -1);
	pen.setColor(color_list[color]);
	pen.setWidth(width);
	pen.setStyle(style_list[style]);
	pen.setCapStyle(cap_list[cap]);
	pen.setJoinStyle(join_list[join]);
	brush.setColor(color_list[brush_color]);
	brush.setStyle(bstyle_list[brush_style]);
}

void Shape::setPen(Qt::GlobalColor color, qreal width, Qt::PenStyle style,
	Qt::PenCapStyle cap, Qt::PenJoinStyle join)
{
	pen.setColor(color);
	pen.setWidth(width);
	pen.setStyle(style);
	pen.setCapStyle(cap);
	pen.setJoinStyle(join);
}

void Shape::setBrush(Qt::GlobalColor color, Qt::BrushStyle style)
{
	brush.setColor(color);
	brush.setStyle(style);
}

void Shape::setDefautStyle()
{
	pen = QPen();
	brush = QBrush();
	painter.setPen(pen);
	painter.setBrush(brush);
}
