#include "shape.h"
#include <QMap>

static unsigned int shapeid = 0;

const QMap<Qt::GlobalColor, QString> COLOR_NAMES {
	{Qt::white, "white"},
	{Qt::black, "black"},
	{Qt::red, "red"},
	{Qt::green, "green"},
	{Qt::blue, "blue"},
	{Qt::cyan, "cyan"},
	{Qt::magenta, "magenta"},
	{Qt::yellow, "yellow"},
	{Qt::gray, "gray"}
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

Shape::Shape(id_t id, const QPen &pen, const QBrush &brush, const QPoint &pos)
	: id{id}, pen{std::move(pen)}, brush{brush}, position{pos}
{
	if (id == 0)
		id = ++shapeid;
	else if (id != (id_t) -1 && id > shapeid)
		shapeid = id;
}

void Shape::move(int dx, int dy)
{
	position.rx() += dx;
	position.ry() += dy;
}

void Shape::swap(Shape &other) noexcept
{
	std::swap(id, other.id);
	std::swap(pen, other.pen);
	std::swap(brush, other.brush);
	std::swap(position, other.position);
}
