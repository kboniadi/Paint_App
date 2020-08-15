#include "shape.h"
#include <QMap>

id_t Shape::shapeid = 0;

const QMap<Shape::ShapeType, QString> SHAPE_NAMES {
	{Shape::Line, "Line"},
	{Shape::Polyline, "Polyline"},
	{Shape::Polygon, "Polygon"},
	{Shape::Rectangle, "Rectangle"},
	{Shape::Ellipse, "Ellipse"},
	{Shape::Text, "Text"}
};

const QMap<QString, QColor> COLOR_NAMES {
	{"white", QColor{Qt::white}},
	{"black", QColor{Qt::black}},
	{"red", QColor{Qt::red}},
	{"green", QColor{Qt::green}},
	{"blue", QColor{Qt::blue}},
	{"cyan", QColor{Qt::cyan}},
	{"magenta", QColor{Qt::magenta}},
	{"yellow", QColor{Qt::yellow}},
	{"gray", QColor{Qt::gray}}
};

const QMap<Qt::PenStyle, QString> STYLE_NAMES {
	{Qt::NoPen, "NoPen"},
	{Qt::SolidLine, "SolidLine"},
	{Qt::DashLine, "DashLine"},
	{Qt::DotLine, "DotLine"},
	{Qt::DashDotLine, "DashDotLine"},
	{Qt::DashDotDotLine, "DashDotDotLine"},
	{Qt::CustomDashLine, "CustomDashLine"}
};

const QMap<Qt::PenCapStyle, QString> CAP_NAMES {
	{Qt::FlatCap, "FlatCap"},
	{Qt::SquareCap, "SquareCap"},
	{Qt::RoundCap, "RoundCap"}
};

const QMap<Qt::PenJoinStyle, QString> JOIN_NAMES {
	{Qt::MiterJoin, "MiterJoin"},
	{Qt::BevelJoin, "BevelJoin"},
	{Qt::RoundJoin, "RoundJoin"},
	{Qt::SvgMiterJoin, "SvgMiterJoin"}
};

const QMap<Qt::BrushStyle, QString> BSTYLE_NAMES {
	{Qt::NoBrush, "NoBrush"},
	{Qt::SolidPattern, "SolidPattern"},
	{Qt::HorPattern, "HorPattern"},
	{Qt::VerPattern, "VerPattern"}
};

Shape::Shape(const QPoint& pos, id_t id, const QPen& pen, const QBrush& brush)
	: position{pos}, id{id}, pen{std::move(pen)}, brush{brush}
{
	if (id == 0)
		this->id = ++shapeid;
	else if (id != (id_t) -1 && id > shapeid)
		shapeid = id;
}

void Shape::move(int dx, int dy)
{
	position.rx() += dx;
	position.ry() += dy;
}

bool Shape::hasfill(Shape::ShapeType type)
{
	return type != Line && type != Polyline && type != Text;
}

void Shape::swap(Shape &other) noexcept
{
	std::swap(id, other.id);
	std::swap(pen, other.pen);
	std::swap(brush, other.brush);
	std::swap(position, other.position);
}
