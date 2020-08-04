#include "textparse.h"
#include <QDebug>

// helper functions for encapsulation of switch cases

Qt::BrushStyle getBrushStyle(std::string key) {
	if (key == "NoBrush") return Qt::NoBrush;
	else if (key == "SolidPattern") return Qt::SolidPattern;
	else if (key == "HorPattern") return Qt::HorPattern;
	else if (key == "VerPattern") return Qt::VerPattern;
	return Qt::NoBrush;
}

Qt::PenJoinStyle getJoinStyle(std::string key) {
	if ( key == "MiterJoin") return Qt::MiterJoin;
	else if ( key == "BevelJoin" ) return Qt::BevelJoin;
	else if ( key == "RoundJoin" ) return Qt::RoundJoin;
	else if ( key == "SvgMiterJoin" ) return Qt::SvgMiterJoin;
	return Qt::BevelJoin;
}

Qt::PenCapStyle getCapStyle(std::string key) {
	if ( key == "FlatCap") return Qt::FlatCap;
	else if ( key == "SquareCap" ) return Qt::SquareCap;
	else if ( key == "RoundCap" ) return Qt::RoundCap;
	return Qt::SquareCap;
}

Qt::PenStyle getPenStyle(std::string key) {
	if ( key == "NoPen") return Qt::NoPen;
	else if ( key == "SolidLine") return Qt::SolidLine;
	else if ( key == "DashLine") return Qt::DashLine;
	else if ( key == "DotLine") return Qt::DotLine;
	else if ( key == "DashDotLine") return Qt::DashDotLine;
	else if ( key == "DashDotDotLine") return Qt::DashDotDotLine;
	else if ( key == "CustomDashLine") return Qt::CustomDashLine;
	else return Qt::NoPen;
}

Qt::GlobalColor getColor(std::string key) {
	if (key == "white") return Qt::white;
	else if (key == "black") return Qt::black;
	else if (key == "red") return Qt::red;
	else if (key == "green") return Qt::green;
	else if (key == "blue") return Qt::blue;
	else if (key == "cyan") return Qt::cyan;
	else if (key == "magenta") return Qt::magenta;
	else if (key == "yellow") return Qt::yellow;
	else if (key == "gray") return Qt::gray;
	return Qt::black;
}

QFont::Weight getFontWeight(std::string key) {
	if ( key == "Thin") return QFont::Thin;
	if ( key == "Light") return QFont::Light;
	if ( key == "Normal") return QFont::Normal;
	if ( key == "Bold") return QFont::Bold;
	return QFont::Normal;
}

Shape * parseLine(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string pencolor, penstyle, pencap, penjoin;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
	QBrush brush(getColor(pencolor));
	QPen pen(brush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));
	return new Line(shapeid, pen, brush, QPoint(dims[0], dims[1]), QPoint(dims[2], dims[3]));
}

Shape * parsePolyline(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string pencolor, penstyle, pencap, penjoin;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;

	QBrush brush(getColor(pencolor));
	QPen pen(brush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));
	cs1c::vector<QPoint> points(dims.size() / 2);
    auto it = dims.begin();
	for (std::size_t i = 0; i < dims.size() / 2; ++i) {
        points[i].setX(*it);
        ++it;
        points[i].setY(*it);
        ++it;
    }

	 return new Polyline(shapeid, pen, brush, points);
}

Shape * parsePolygon(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;

    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	QBrush brush(getColor(brushcolor));
	QBrush penbrush(getColor(pencolor));
	QPen pen(penbrush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));
	cs1c::vector<QPoint> points(dims.size() / 2);
	auto it = dims.begin();
	for (std::size_t i = 0; i < dims.size() / 2; ++i) {
		points[i].setX(*it);
		++it;
		points[i].setY(*it);
		++it;
	}
	return new Polygon(shapeid, pen, brush, points);
}

Shape * parseRectangle(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;

    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	QBrush brush(getColor(brushcolor));
	QBrush penbrush(getColor(pencolor));
	QPen pen(penbrush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));

	return new Rectangle(pen, brush, QPoint(dims[0], dims[1]), shapeid, dims[2], dims[3]);
}

Shape * parseSquare(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;

    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
	in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	QBrush brush(getColor(brushcolor));
	QBrush penbrush(getColor(pencolor));
	QPen pen(penbrush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));

	return new Rectangle(pen, brush, QPoint(dims[0], dims[1]), shapeid, dims[2], dims[2]);
}

Shape * parseEllip(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string pencolor, penstyle, pencap, penjoin, brushcolor, brushstyle;
    int penwidth;

    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	QBrush brush(getColor(brushcolor));
	QBrush penbrush(getColor(pencolor));
	QPen pen(penbrush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));

	return new Ellipse(shapeid, pen, brush, QPoint(dims[0], dims[1]), dims[2], dims[3]);
}

Shape * parseCircle(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string shapeType="Circle", pencolor, penstyle, pencap, penjoin,
		brushcolor, brushstyle;
    int penwidth;
    in >> pencolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penwidth;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penstyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> pencap;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> penjoin;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushcolor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> brushstyle;

	QBrush brush(getColor(brushcolor));
	QBrush penbrush(getColor(pencolor));
	QPen pen(penbrush, penwidth, getPenStyle(penstyle), getCapStyle(pencap), getJoinStyle(penjoin));

	return new Ellipse(shapeid, pen, brush, QPoint(dims[0], dims[1]), dims[2], dims[2]);
}

Shape * parseText(std::ifstream& in, int shapeid, cs1c::vector<int> &dims) {
	std::string text, textColor, textAlig, textFont, textFontStyle, textFontWeight;
    int textpointsize;

	std::getline(in, text, '\n');
	QString str(text.c_str());
    in.ignore(100, ' ');
    in >> textColor;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> textAlig;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> textpointsize;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
	std::getline(in, textFont, '\n');
	QString fontfam(textFont.c_str());
    in.ignore(100, ' ');
    in >> textFontStyle;
    in.ignore(100, '\n');
    in.ignore(100, ' ');
    in >> textFontWeight;
	QBrush brush(getColor(textColor));
	QPen pen(getColor(textColor));
	pen.setCapStyle(getCapStyle(textFontStyle));
	QFont font(fontfam.trimmed(), textpointsize, getFontWeight(textFontWeight), false);

	return new Text(pen, brush, QPoint(dims[0], dims[1]), shapeid, font,
		str.trimmed(), ALIGNMENT_TYPES.key(QString::fromStdString(textAlig)),
		dims[2], dims[3]);
}

Shape::ShapeType getShapeType(std::string key) {
	if (key == "Line") return Shape::ShapeType::Line;
	if (key == "Polyline") return Shape::ShapeType::Polyline;
	if (key == "Polygon") return Shape::ShapeType::Polygon;
	if (key == "Rectangle") return Shape::ShapeType::Rectangle;
	if (key == "Square") return Shape::ShapeType::Square;
	if (key == "Ellipse") return Shape::ShapeType::Ellipse;
	if (key == "Circle") return Shape::ShapeType::Circle;
	if (key == "Text") return Shape::ShapeType::Text;
	return Shape::ShapeType::NoShape;
}

cs1c::vector<Shape *> textParse() {
    std::ifstream in;
    in.open("shapes.txt");
    std::string shapeType;
    cs1c::vector<int> dims;
    cs1c::vector<Shape*> shapes;
	Shape* temp;
	Shape* temp2;
    int shapeIdtemp, dimsTemp;
	while (true) {
        dims.clear();
        in.ignore(100, '\n');
        in.ignore(100, ' ');
        in >> shapeIdtemp;
        if (in.fail()) {
            in.clear();
            return shapes;
        }
        in.ignore(100, '\n');
        in.ignore(100, ' ');
        in >> shapeType;
        in.ignore(100, '\n');
        in.ignore(100, ' ');
        while (in >> dimsTemp) {
            dims.push_back(dimsTemp);
            in.ignore(100, ' ');
        }
        in.clear();

        switch(getShapeType(shapeType)) {
		case Shape::ShapeType::Line:
			shapes.push_back(parseLine(in, shapeIdtemp, dims));
			break;
		case Shape::ShapeType::Polyline:
			shapes.push_back(parsePolyline(in, shapeIdtemp, dims));
			break;
		case Shape::ShapeType::Polygon:
			shapes.push_back(parsePolygon(in, shapeIdtemp, dims));
			break;
		case Shape::ShapeType::Rectangle:
			shapes.push_back(parseRectangle(in, shapeIdtemp, dims));
			break;
		case Shape::ShapeType::Square:
			shapes.push_back(parseSquare(in, shapeIdtemp, dims));
			break;
		case Shape::ShapeType::Ellipse:
			shapes.push_back(parseEllip(in, shapeIdtemp, dims));
			temp = shapes[5];
			break;
		case Shape::ShapeType::Circle:
			shapes.push_back(parseCircle(in, shapeIdtemp, dims));
			temp2 = shapes[6];
			break;
		case Shape::ShapeType::Text:
			shapes.push_back(parseText(in, shapeIdtemp, dims));
			break;
		default:
			qDebug() << "NO Shape Found\n";
			assert(false);
			break;
        }
    }
}
