#include "serialization.h"

// needed for conversion between QString and std::string
std::ostream& operator<<(std::ostream &out, const QString &str)
{
	return out << str.toStdString();
}

std::ostream& operator<<(std::ostream &out, const cs1c::vector<Shape *> &shapes)
{
	out << '\n';
	for (Shape *shape: shapes) {
		out << "ShapeID: " << shape->getID() << '\n';
		out << "ShapeType: " << SHAPE_NAMES[shape->getShape()] << '\n';
		out << "ShapeDimensions: ";

#define TYPE_CAST(type) auto* cast = dynamic_cast<type*>(shape)
		if (TYPE_CAST(Line)) {
			QPoint start = cast->getStart();
			QPoint end = cast->getEnd();
			out << start.x() << ", " << start.y() << ", " << end.x() << ", "
			<< end.y() << '\n';
		} else if (TYPE_CAST(Polyline)) {
			for (std::size_t i = 0; i < cast->getSize(); i++) {
				QPoint point = cast->getPoint(i);
				out << point.x() << ", " << point.y();
				if (i != cast->getSize() - 1)
					out << ", ";
			}
			out << '\n';
		} else if (TYPE_CAST(Rectangle)) {
			QRect rect = cast->getRect();

			out << rect.x() << ", " << rect.y() << ", " << rect.width() << ", "
			<< rect.height() << '\n';
		} else if (TYPE_CAST(Ellipse)) {
			QRect rect = cast->getRect();

			out << rect.x() << ", " << rect.y() << ", " << rect.width()
			<< ", " << rect.height() << '\n';
		} else if (TYPE_CAST(Text)) {
			QRect rect = cast->getRect();

			out << rect.x() << ", " << rect.y() << ", " << rect.width() << ", "
			<< rect.height() << '\n';
		}

		if (shape->getShape() != Shape::Text) {
			const QPen &pen = shape->getPen();

			out << "PenColor: " << COLOR_NAMES.key(pen.color()) << '\n';
			out << "PenWidth: " << pen.width() << '\n';
			out << "PenStyle: " << STYLE_NAMES[pen.style()] << '\n';
			out << "PenCapStyle: " << CAP_NAMES[pen.capStyle()] << '\n';
			out << "PenJoinStyle: " << JOIN_NAMES[pen.joinStyle()] << '\n';
		}

		if (TYPE_CAST(Text)) {
			const QFont &font = cast->getFont();

			out << "TextString: " << cast->getText() << '\n';
			out << "TextColor: " << COLOR_NAMES.key(cast->getPen().color())
			<< '\n';
			out << "TextAlignment: " << ALIGNMENT_TYPES[cast->getAlignment()]
			<< '\n';
			out << "TextPointSize: " << font.pointSize() << '\n';
			out << "TextFontFamily: " << font.family() << '\n';
			out << "TextFotnStype: " << FONT_STYLES[font.style()] << '\n';
			out << "TextFontWeight: "
			<< FONT_WEIGHTS[static_cast<QFont::Weight>(font.weight())] << '\n';
		}

		if (Shape::hasfill(shape->getShape())) {
			const QBrush &brush = shape->getBrush();
			out << "BrushColor: " << COLOR_NAMES.key(brush.color()) << '\n';
			out << "BrushStyle: " << BSTYLE_NAMES[brush.style()] << '\n';
		}
#undef TYPE_CAST
		out << '\n';
	}

	return  out;
}
